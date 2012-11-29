#ifndef NSAPPLINKRPC_DISPLAYCAPABILITIES_V2_INCLUDE
#define NSAPPLINKRPC_DISPLAYCAPABILITIES_V2_INCLUDE

#include <vector>

#include "DisplayType.h"
#include "MediaClockFormat.h"
#include "TextField_v2.h"


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

///  Contains information about the display capabilities.

  class DisplayCapabilities_v2
  {
  public:
  
    DisplayCapabilities_v2(const DisplayCapabilities_v2& c);
    DisplayCapabilities_v2(void);
  
    bool checkIntegrity(void);
  // getters

    const DisplayType& get_displayType(void) const;
    const std::vector<MediaClockFormat>& get_mediaClockFormats(void) const;
    const std::vector<TextField_v2>& get_textFields(void) const;

// setters

    bool set_displayType(const DisplayType& displayType_);
    bool set_mediaClockFormats(const std::vector<MediaClockFormat>& mediaClockFormats_);
    bool set_textFields(const std::vector<TextField_v2>& textFields_);

  private:

    friend class DisplayCapabilities_v2Marshaller;


///  The type of the display. See DisplayType
      DisplayType displayType;

///  A set of all supported formats of the media clock. See MediaClockFormat
      std::vector<MediaClockFormat> mediaClockFormats;	//!<   [%s..%s] 

///  A set of all fields that support text data. See TextField
      std::vector<TextField_v2> textFields;	//!<   [%s..%s] 
  };

}

#endif
