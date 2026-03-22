classDiagram
  class ArduinoDigitalInPinSupervisor
  class ButtonEdgeDetector
  class MyBatteryAdapter
  class MyBuiltinLedIndicatorAdapter
  class MyButtonAdapter
  class MyServoPwrEnIndicatorAdapter
  class ServoButtonAdapter
  class App
  class LedTestBlinkPublisher
  class ProductWiFiCmds
  class TestLedMqttSubscriber
  class CmdGoToAngle
  class DbgCmd_InitAxes
  class DbgCmd_SetAngle
  class MyServoHal
  class TargetReachedNotifier
  class ProductDebug

  %% Beziehungen (ohne Details)
  App --> LedTestBlinkPublisher
  App --> ProductWiFiCmds
  App --> TestLedMqttSubscriber
  App --> CmdGoToAngle
  App --> DbgCmd_SetAngle
  App --> TargetReachedNotifier
  App --> ProductDebug
  App --> MyBatteryAdapter
  App --> MyBuiltinLedIndicatorAdapter
  App --> MyButtonAdapter
  App --> MyServoPwrEnIndicatorAdapter
  App --> ServoButtonAdapter
  App --> MyServoHal
  App --> ArduinoDigitalInPinSupervisor
  App --> ButtonEdgeDetector
  App --> DbgCmd_InitAxes

  %% Gruppierung nach Ordnern
  class ArduinoDigitalInPinSupervisor,ButtonEdgeDetector,MyBatteryAdapter,MyBuiltinLedIndicatorAdapter,MyButtonAdapter,MyServoPwrEnIndicatorAdapter,ServoButtonAdapter adapter
  class App,LedTestBlinkPublisher,ProductWiFiCmds,TestLedMqttSubscriber prod-app
  class CmdGoToAngle,DbgCmd_InitAxes,DbgCmd_SetAngle,MyServoHal,TargetReachedNotifier prod-axis
  class ProductDebug prod-dbg

  %% Farben für Ordner
  class adapter fill:#e3f2fd
  class prod-app fill:#fff9c4
  class prod-axis fill:#c8e6c9
  class prod-dbg fill:#ffcdd2