#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/UI/GetDeviceList.h"
#include "../src/../include/JSONHandler/RPC2Objects/Marshaller.h"

/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Nov 29 14:32:09 2012
  source stamp	Thu Nov 29 14:32:05 2012
  author	robok0der
*/

using namespace NsRPC2Communication::UI;


GetDeviceList& GetDeviceList::operator =(const GetDeviceList& c)
{
  return *this;
}


GetDeviceList::~GetDeviceList(void)
{
}


GetDeviceList::GetDeviceList(void) : 
  RPC2Request(Marshaller::METHOD_NSRPC2COMMUNICATION_UI__GETDEVICELIST)
{
}


GetDeviceList::GetDeviceList(const GetDeviceList& c) : RPC2Request(Marshaller::METHOD_NSRPC2COMMUNICATION_UI__GETDEVICELIST,c.getId())
{
  *this=c;
}


bool GetDeviceList::checkIntegrity(void)
{
  return GetDeviceListMarshaller::checkIntegrity(*this);
}
