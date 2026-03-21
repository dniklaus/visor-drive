/*
 * ServoButtonAdapter.cpp
 *
 *  Created on: 17.02.2020
 *      Author: dev
 */
#include <Arduino.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include <Indicator.h>
#include <CmdSequence.h>
#include "ServoButtonAdapter.h"

ServoButtonAdapter::ServoButtonAdapter(Indicator* indicator)
: m_trPort(new DbgTrace_Port("SrvBtn", DbgTrace_Level::info))
, m_indicator(indicator)
{ }

ServoButtonAdapter::~ServoButtonAdapter()
{
  delete m_trPort;
  m_trPort = 0;
}

void ServoButtonAdapter::assignCmdSequence(CmdSequence* cmdSequence)
{
  m_cmdSequence = cmdSequence;
}

void ServoButtonAdapter::notifyStatusChanged(bool isActive)
{
  if ((0 != m_indicator) && (0 != m_cmdSequence))
  {
    TR_PRINTF(m_trPort, DbgTrace_Level::info, "%s (cmdSeq %s - tgl %s)", isActive ? "pressed" : "released", m_cmdSequence->isRunning() ? "running" : "stopped", Indicator::getStateText(m_indicator->getState()));
    if (isActive && !m_cmdSequence->isRunning())
    {
        m_indicator->toggle();
        m_cmdSequence->start();
    }
  }
}