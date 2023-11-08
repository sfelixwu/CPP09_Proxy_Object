
#include "Shadow_GPS.h"
#include "ecs36b_Exception.h"

// JSON RPC part
#include "poclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

Shadow_GPS::Shadow_GPS
(std::string arg_host_url, std::string arg_class_id, std::string arg_object_id)
{
  this->host_url = arg_host_url;
  this->class_id = arg_class_id;
  this->object_id = arg_object_id;
  std::cout << "Shadow_GPS Object created" << std::endl;
}

Json::Value
Shadow_GPS::dump2JSON()
{
  HttpClient httpclient((this->host_url).c_str());
  poClient myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.dump2JSON("dump2JSON", (this->class_id).c_str(),
				(this->object_id).c_str());
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  
  return result;
}

bool
Shadow_GPS::setGPSLabel
(std::string arg_label)
{
  HttpClient httpclient((this->host_url).c_str());
  poClient myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.setGPSLabel("setGPSLabel", (this->class_id).c_str(),
				  arg_label, (this->object_id).c_str());
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  bool res;
  if ((result["result"].isNull() == true) ||
      (result["result"].isBool() != true))
    {
      res = false;
    }
  else
    {
      res = result["result"].asBool();
    }
  
  return res;
}

