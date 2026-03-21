/*
 * ServoButtonAdapter.h
 *
 *  Created on: 17.02.2020
 *      Author: dev
 */

#ifndef LIB_ADAPTER_ServoButtonAdapter_H_
#define LIB_ADAPTER_ServoButtonAdapter_H_

#include <stdint.h>
#include <Button.h>

class Indicator;
class CmdSequence;

class ServoButtonAdapter : public ButtonAdapter
{
public:
  ServoButtonAdapter(Indicator* indicator);
  virtual ~ServoButtonAdapter();

  void assignCmdSequence(CmdSequence* cmdSequence);

  void notifyStatusChanged(bool isActive);

private:
  DbgTrace_Port* m_trPort;
  Indicator* m_indicator;
  CmdSequence* m_cmdSequence;

private:  // forbidden functions
  ServoButtonAdapter();                                           // default constructor
  ServoButtonAdapter(const ServoButtonAdapter& src);              // copy constructor
  ServoButtonAdapter& operator = (const ServoButtonAdapter& src); // assignment operator
};


#endif /* LIB_ADAPTER_ServoButtonAdapter_H_ */
