#ifndef NSAPPLINKRPC_SLIDER_REQUEST_INCLUDE
#define NSAPPLINKRPC_SLIDER_REQUEST_INCLUDE

#include <vector>
#include <string>

#include "JSONHandler/ALRPCRequest.h"


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

///  Creates a full screen or pop-up overlay (depending on platform) with a single user controlled slider.

  class Slider_request : public ALRPCRequest
  {
  public:
  
    Slider_request(const Slider_request& c);
    Slider_request(void);
    
    virtual ~Slider_request(void);
  
    Slider_request& operator =(const Slider_request&);
  
    bool checkIntegrity(void);

    const unsigned int* get_numTicks(void) const;
    unsigned int get_position(void) const;
    const std::string* get_sliderHeader(void) const;
    const std::vector<std::string>* get_sliderFooter(void) const;
    unsigned int get_timeout(void) const;

    void reset_numTicks(void);
    bool set_numTicks(unsigned int numTicks_);
    bool set_position(unsigned int position_);
    void reset_sliderHeader(void);
    bool set_sliderHeader(const std::string& sliderHeader_);
    void reset_sliderFooter(void);
    bool set_sliderFooter(const std::vector<std::string>& sliderFooter_);
    bool set_timeout(unsigned int timeout_);

  private:
  
    friend class Slider_requestMarshaller;


///  Number of selectable items on a horizontal axis
      unsigned int* numTicks;	//!<  (2,26)

///  Initial position of slider control (cannot exceed numTicks)
      unsigned int position;	//!<  (1,26)

///  Text header to display
      std::string* sliderHeader;	//!< (500)

/**
     Text footer to display (meant to display min/max threshold descriptors).
     For a static text footer, only one footer string shall be provided in the array.
     For a dynamic text footer, the number of footer text string in the array must match the numTicks value.
     For a dynamic text footer, text array string should correlate with potential slider position index.
     If omitted on supported displays, no footer text shall be displayed.
*/
      std::vector<std::string>* sliderFooter;	//!<   [%s..%s] (500)

///  App defined timeout.
      unsigned int timeout;	//!<  (0,65535)
  };

}

#endif
