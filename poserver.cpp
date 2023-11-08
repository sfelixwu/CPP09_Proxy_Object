
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "poserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// Core classes
// Objects
#include "Labeled_GPS.h"
Labeled_GPS *object_1001 = NULL;

// popular ones
#include <strings.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception> 
#include <time.h>

using namespace jsonrpc;
using namespace std;

class mypoServer : public poServer
{
public:
  mypoServer(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value setGPSLabel(const std::string& action, const std::string& class_name,
				  const std::string& label, const std::string& object_id);
  virtual Json::Value dump2JSON(const std::string& action, const std::string& class_name,
				const std::string& object_id);
};

mypoServer::mypoServer(AbstractServerConnector &connector, serverVersion_t type)
  : poServer(connector, type)
{
  std::cout << "mypoServer Object created" << std::endl;
}

// member functions

Json::Value
mypoServer::setGPSLabel
(const std::string& action, const std::string& class_name,
 const std::string& label, const std::string& object_id)
{
  Json::Value result;
  std::cout << action << " " << class_name << " " << object_id << " " << label << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  if ((object_1001 == NULL) ||
      (class_name != "Labeled_GPS") ||
      (object_id != "1001"))
    {
      result["status"] = "Object or Class not found";
      result["result"] = false;
    }
  else
    {
      // object_1001->label = label;
      // result["result"] = true;
      
      result["status"] = "successful";
      result["result"] = object_1001->setGPSLabel(label);
    }
  std::cout << result.toStyledString() << std::endl;
  return result;
}

Json::Value
mypoServer::dump2JSON
(const std::string& action, const std::string& class_name,
 const std::string& object_id)
{
  Json::Value result;
  std::cout << action << " " << class_name << " " << object_id << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  if ((object_1001 == NULL) ||
      (class_name != "Labeled_GPS") ||
      (object_id != "1001"))
    {
      result["status"] = "Object or Class not found";
    }
  else
    {
      result = object_1001->dump2JSON();
      result["status"] = "successful";
    }
  std::cout << result.toStyledString() << std::endl;
  return result;
}

int
main
(void)
{
  object_1001 = new Labeled_GPS { 38.672215864622636, -121.72280111121437, "Costco, Woodland" };

  HttpServer httpserver(8300);
  mypoServer s(httpserver,
	       JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
