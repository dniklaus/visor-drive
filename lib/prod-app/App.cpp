/*
 * App.cpp
 *
 *  Created on: 18.05.2023
 *      Author: didi
 */
#include <Arduino.h>
#include <SerialCommand.h>
#include <SpinTimer.h>
#include <Battery.h>
#include "MyBatteryAdapter.h"
#include <Indicator.h>
#include <IndicatorFactory.h>
#include "MyServoPwrEnIndicatorAdapter.h"
#include "MyBuiltinLedIndicatorAdapter.h"
#include <Button.h>
#include <ButtonEdgeDetector.h>
#include "MyButtonAdapter.h"
#include "ServoButtonAdapter.h"
#include <ArduinoDigitalInPinSupervisor.h>
#include <ProductDebug.h>
#include <ECMqttClient.h>   // ERNI Community MQTT client wrapper library (depends on MQTT library)
#include "MqttTopic.h"
#include <DbgCliNode.h>
#include <DbgCliTopic.h>
#include <DbgCliCommand.h>
#include "ProductWiFiCmds.h"
#include "LedTestBlinkPublisher.h"
#include "TestLedMqttSubscriber.h"
#include <Axis.h>
#include <MyServoHal.h>
#include <DbgCmd_SetAngle.h>
#include <CmdSequence.h>
#include "CmdGoToAngle.h"
#include "TargetReachedNotifier.h"
#include "App.h"

#define MQTT_SERVER "test.mosquitto.org"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
// see https://github.com/espressif/arduino-esp32/issues/1960#issuecomment-429546528
#endif

//-----------------------------------------------------------------------------
// ESP8266 / ESP32 WiFi Client
//-----------------------------------------------------------------------------
#if defined(ESP8266) || defined(ESP32)
WiFiClient wifiClient;
#endif

const char App::s_termChar = '\n';
Axis* axis = 0;

App::App()
: m_sCmd(new SerialCommand(s_termChar))
, m_battery(0)
, m_led(0)
, m_servoPwrEn(0)
{ }

App::~App()
{ 
  if (0 != m_led)
  {
    delete m_led->adapter();
    m_led->assignAdapter(0);
  }

  delete m_servoPwrEn;
  m_servoPwrEn = 0;

  delete m_led;
  m_led = 0;

  delete m_battery;
  m_battery = 0;

  delete m_sCmd;
  m_sCmd = 0;
}

void App::setup()
{
  // setup basic debug environment (heap usage printer, trace ports & dbg cli)
  ProductDebug::setupProdDebugEnv(m_sCmd);

  // indicator LED
  m_led = IndicatorFactory::createIndicator("led", "Built in LED.");
  m_led->assignAdapter(new MyBuiltinLedIndicatorAdapter());

  // Servo Power Enable signal
  m_servoPwrEn = IndicatorFactory::createIndicator("srvpwr", "Servo Power Enable.");
  m_servoPwrEn->assignAdapter(new MyServoPwrEnIndicatorAdapter());


  // Servo end position indicator and button to toggle it
  Indicator* srvTglInd = IndicatorFactory::createIndicator("srvtgl", "Servo end position toggle.");
  srvTglInd->clear();
  ServoButtonAdapter* srvBtnAdapter = new ServoButtonAdapter(srvTglInd);
  new Button(new ArduinoDigitalInPinSupervisor(26), new ButtonEdgeDetector(), srvBtnAdapter);
  
  //-----------------------------------------------------------------------------
  // Battery Voltage Surveillance
  //-----------------------------------------------------------------------------
  BatteryThresholdConfig battCfg = 
  { 
    3.4, // BATT_WARN_THRSHD [V]
    3.2, // BATT_STOP_THRSHD [V]
    3.1, // BATT_SHUT_THRSHD [V]
    0.1  // BATT_HYST        [V]
  };
  m_battery = new Battery(new MyBatteryAdapter(m_led, m_servoPwrEn), battCfg);

  #ifdef USER_BTN
    new Button(new ArduinoDigitalInPinSupervisor(USER_BTN), new ButtonEdgeDetector(), new MyButtonAdapter(m_led));
  #endif

  #if defined(ESP8266)
    enableWiFiAtBootTime();
  #endif

  #if defined(ESP8266) || defined(ESP32)
    WiFi.persistent(true);
    WiFi.mode(WIFI_STA);

    //-----------------------------------------------------------------------------
    // WiFi Commands
    //-----------------------------------------------------------------------------
    DbgCli_Topic* wifiTopic = new DbgCli_Topic(DbgCli_Node::RootNode(), "wifi", "WiFi debug commands");
    new DbgCli_Cmd_WifiMac(wifiTopic);
    new DbgCli_Cmd_WifiNets(wifiTopic);
    new DbgCli_Cmd_WifiStat(wifiTopic);
    new DbgCli_Cmd_WifiDis(wifiTopic);
    new DbgCli_Cmd_WifiCon(wifiTopic);

    //-----------------------------------------------------------------------------
    // MQTT Client
    //-----------------------------------------------------------------------------
    ECMqttClient.begin(MQTT_SERVER, ECMqttClientClass::defaultMqttPort, wifiClient, WiFi.macAddress().c_str());
    new TestLedMqttSubscriber(m_led);
    new DefaultMqttSubscriber("test/startup/#");
    new MqttTopicPublisher("test/startup", WiFi.macAddress().c_str(), MqttTopicPublisher::DO_AUTO_PUBLISH);
    // new LedTestBlinkPublisher();  // TODO: fix BUG, when this object gets created
  #endif

  CmdSequence* cmdSequence = new CmdSequence();
  srvBtnAdapter->assignCmdSequence(cmdSequence);
  
  //------------------------------------------------------------------------------
  // Servo objects creation
  //------------------------------------------------------------------------------
  const int servoPins[] = {13};
  const int numServos = 1;
  for (unsigned int i = 0; i < numServos; i++)
  {
      char axisName[10];
      memset(axisName, 0, sizeof(axisName));
      sprintf(axisName, "ax%d", i);
      axis = new Axis(axisName);
      if (0 != axis)
      {
          axis->attachServoHal(new MyServoHal(servoPins[i]));
          axis->attachTargetReachedNotifier(new TargetReachedNotifier(axis, cmdSequence));
          new DbgCmd_SetAngle(axis);
      }
  }  

  new CmdGoToAngle(cmdSequence, -1, axis, srvTglInd, -90, 90, 250);
}

void App::loop()
{
  if (0 != m_sCmd)
  {
    m_sCmd->readSerial();     // process serial commands
  }
  ECMqttClient.loop();        // process MQTT Client
  scheduleTimers();           // process Timers
}
