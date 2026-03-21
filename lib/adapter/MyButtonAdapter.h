/*
 * MyButtonAdapter.h
 *
 *  Created on: 17.02.2020
 *      Author: dev
 */

#ifndef LIB_ADAPTER_MYBUTTONADAPTER_H_
#define LIB_ADAPTER_MYBUTTONADAPTER_H_

#include <stdint.h>
#include <Button.h>

class Indicator;
class MyButtonAdapter : public ButtonAdapter
{
public:
  MyButtonAdapter(Indicator* indicator);
  virtual ~MyButtonAdapter();

  void notifyStatusChanged(bool isActive);

private:
  Indicator* m_indicator;

private:  // forbidden functions
  MyButtonAdapter();                                        // default constructor
  MyButtonAdapter(const MyButtonAdapter& src);              // copy constructor
  MyButtonAdapter& operator = (const MyButtonAdapter& src); // assignment operator
};


#endif /* LIB_ADAPTER_MYBUTTONADAPTER_H_ */
