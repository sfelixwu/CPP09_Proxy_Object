
// ecs36b WR client

#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "poclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

// for sleep()
#include <unistd.h>

#include "Shadow_GPS.h"

using namespace jsonrpc;
using namespace std;

int
main(void)
{
  Json::Value result;
  Shadow_GPS shadow_object_1001 { "http://localhost:8300", "Labeled_GPS", "1001" };
  GPS_DD * gps_ptr = &shadow_object_1001;
  Labeled_GPS * labeled_gps_ptr = &shadow_object_1001;
  
  try {
    // if (shadow_object_1001.setGPSLabel("Teaching and Learning Complex"))
    if (labeled_gps_ptr->setGPSLabel("Teaching and Learning Complex"))
      {
	std::cout << "the result is true\n";
      }
    else
      {
	std::cout << "the result is false\n";
      }
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  try {
    // result = shadow_object_1001.dump2JSON();
    result = gps_ptr->dump2JSON();
    cout << result.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
