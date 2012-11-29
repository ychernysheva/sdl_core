#include "../include/JSONHandler/ALRPCObjects/UnsubscribeVehicleData_request.h"
#include "UnsubscribeVehicleData_requestMarshaller.h"
#include "../include/JSONHandler/ALRPCObjects/Marshaller.h"
#include "VehicleDataTypeMarshaller.h"

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
UnsubscribeVehicleData_request& UnsubscribeVehicleData_request::operator =(const UnsubscribeVehicleData_request& c)
{
  dataType= c.dataType ? new std::vector<VehicleDataType>(c.dataType[0]) : 0;

  return *this;}


UnsubscribeVehicleData_request::~UnsubscribeVehicleData_request(void)
{
  if(dataType)
    delete dataType;
}


UnsubscribeVehicleData_request::UnsubscribeVehicleData_request(const UnsubscribeVehicleData_request& c)
{
  *this=c;
}


bool UnsubscribeVehicleData_request::checkIntegrity(void)
{
  return UnsubscribeVehicleData_requestMarshaller::checkIntegrity(*this);
}


UnsubscribeVehicleData_request::UnsubscribeVehicleData_request(void) : ALRPCRequest(PROTOCOL_VERSION,Marshaller::METHOD_UNSUBSCRIBEVEHICLEDATA_REQUEST),
      dataType(0)
{
}



bool UnsubscribeVehicleData_request::set_dataType(const std::vector<VehicleDataType>& dataType_)
{
  unsigned int i=dataType_.size();
  if(i>100 || i<1)  return false;
  while(i--)
  {
    if(!VehicleDataTypeMarshaller::checkIntegrityConst(dataType_[i]))   return false;
  }
  delete dataType;
  dataType=0;

  dataType=new std::vector<VehicleDataType>(dataType_);
  return true;
}

void UnsubscribeVehicleData_request::reset_dataType(void)
{
  if(dataType)
    delete dataType;
  dataType=0;
}




const std::vector<VehicleDataType>* UnsubscribeVehicleData_request::get_dataType(void) const 
{
  return dataType;
}

