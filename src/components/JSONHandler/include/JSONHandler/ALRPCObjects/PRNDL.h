#ifndef NSAPPLINKRPC_PRNDL_INCLUDE
#define NSAPPLINKRPC_PRNDL_INCLUDE


/*
  interface	Ford Sync RAPI
  version	1.2 / 2.0O
  date		2011-05-17 / 2012-11-02
  generated at	Thu Nov 29 14:49:08 2012
  source stamp	Thu Nov 29 06:50:10 2012
  author	robok0der
*/

namespace NsAppLinkRPC
{

///  The selected gear.

  class PRNDL
  {
  public:
    enum PRNDLInternal
    {
      INVALID_ENUM=-1,

///  Parking
      PARK=0,

///  Reverse gear
      REVERSE=1,

///  No gear
      NEUTRAL=2,

///  1st gear hold
      LOWGEAR=3,
      FORWARD_DRIVE_2=4,
      FORWARD_DRIVE_3=5,

///  Or Overdrive
      FORWARD_DRIVE_4=6,

///  Or Overdrive
      FORWARD_DRIVE_5=7,

///  Or Overdrive
      FORWARD_DRIVE_6=8,
      SECOND_GEAR_HOLD=9,
      THIRD_GEAR_HOLD=10,
      FOURTH_GEAR_HOLD=11,
      FIFTH_GEAR_HOLD=12,
      SIXTH_GEAR_HOLD=13
    };
  
    PRNDL() : mInternal(INVALID_ENUM)				{}
    PRNDL(PRNDLInternal e) : mInternal(e)		{}
  
    PRNDLInternal get(void) const	{ return mInternal; }
    void set(PRNDLInternal e)		{ mInternal=e; }
  
  private:
    PRNDLInternal mInternal;
    friend class PRNDLMarshaller;
  };
  
}

#endif
