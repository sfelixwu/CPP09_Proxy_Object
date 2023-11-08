
#ifndef _SHADOW_GPS_H_
#define _SHADOW_GPS_H_

#include "Labeled_GPS.h"

class Shadow_GPS: public Labeled_GPS
{
 private:
 public:
  
  std::string host_url;
  std::string class_id;
  std::string object_id;

  Shadow_GPS(std::string, std::string, std::string);
  virtual bool setGPSLabel(std::string); // print the content of the object
  virtual Json::Value dump2JSON(void); // print the content of the object
};

#endif // _SHADOW_GPS_H_
