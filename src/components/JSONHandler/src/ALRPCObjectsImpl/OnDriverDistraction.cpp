#include "../include/JSONHandler/ALRPCObjects/OnDriverDistraction.h"
#include "OnDriverDistractionMarshaller.h"
#include "../include/JSONHandler/ALRPCObjects/Marshaller.h"
#include "DriverDistractionStateMarshaller.h"

#define PROTOCOL_VERSION	42


/*
  interface	Ford Sync RAPI
  version	1.2 / 2.0O
  date		2011-05-17 / 2012-11-02
  generated at	Thu Nov 29 14:49:08 2012
  source stamp	Thu Nov 29 06:50:10 2012
  author	robok0der
*/

using namespace NsAppLinkRPC;

OnDriverDistraction::~OnDriverDistraction(void)
{
}


OnDriverDistraction::OnDriverDistraction(const OnDriverDistraction& c)
{
  *this=c;
}


bool OnDriverDistraction::checkIntegrity(void)
{
  return OnDriverDistractionMarshaller::checkIntegrity(*this);
}


OnDriverDistraction::OnDriverDistraction(void) : ALRPCNotification(PROTOCOL_VERSION,Marshaller::METHOD_ONDRIVERDISTRACTION)
{
}



bool OnDriverDistraction::set_state(const DriverDistractionState& state_)
{
  if(!DriverDistractionStateMarshaller::checkIntegrityConst(state_))   return false;
  state=state_;
  return true;
}




const DriverDistractionState& OnDriverDistraction::get_state(void) const 
{
  return state;
}

