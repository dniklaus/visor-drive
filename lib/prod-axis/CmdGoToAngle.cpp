#include "CmdGoToAngle.h"
#include <Indicator.h>
#include <Axis.h>
#include <CmdSequence.h>

CmdGoToAngle::CmdGoToAngle(CmdSequence* cmdSequence, long int timeMillis,
                           Axis* axis, Indicator* targetToggleIndicator, int targetAngle0, int targetAngle1, int velocity)
    : Cmd(cmdSequence, timeMillis, (0 != axis) ? axis->name() : ""),
      m_axis(axis),
      m_indicator(targetToggleIndicator),
      m_targetAngle0(targetAngle0),
      m_targetAngle1(targetAngle1),
      m_velocity(velocity) {}

CmdGoToAngle::~CmdGoToAngle() {}

void CmdGoToAngle::execute()
{
    if (0 != m_axis)
    {
        m_axis->goToTargetAngle((m_indicator->getState() == Indicator::EIndState::off) ? m_targetAngle0 : m_targetAngle1, m_velocity);
    }
}

void CmdGoToAngle::leave()
{
    if (0 != m_axis)
    {
        m_axis->stop();
    }
}
