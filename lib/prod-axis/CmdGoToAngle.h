#ifndef CMDGOTOANGLE_H
#define CMDGOTOANGLE_H

#pragma once

#include <Cmd.h>

class Axis;
class Indicator;

class CmdGoToAngle : public Cmd
{
public:
    CmdGoToAngle(CmdSequence* cmdSequence, long int timeMillis, Axis* axis, Indicator* targetToggleIndicator, 
        int targetAngle0, int targetAngle1, int velocity);
    virtual ~CmdGoToAngle();

    void execute();
    void leave();

private:
    Axis* m_axis;
    Indicator* m_indicator;
    int m_targetAngle0;
    int m_targetAngle1;
    int m_velocity;
};

#endif