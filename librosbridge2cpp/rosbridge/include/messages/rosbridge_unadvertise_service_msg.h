#pragma once

#include <iostream>
#include "messages/rosbridge_msg.h"

class ROSBridgeUnadvertiseServiceMsg : public ROSBridgeMsg{
public:
  ROSBridgeUnadvertiseServiceMsg () : ROSBridgeMsg(){}

  ROSBridgeUnadvertiseServiceMsg (bool init_opcode) : ROSBridgeMsg(){
    if(init_opcode)
      op_ = ROSBridgeMsg::UNADVERTISE_SERVICE;
  }

  virtual ~ROSBridgeUnadvertiseServiceMsg () = default;

  // Unadvertise messages will never be received from the client
  // So we don't need to fill this instance from JSON or other wire-level representations
  bool FromJSON(const rapidjson::Document &data) = delete;

  rapidjson::Document ToJSON(rapidjson::Document::AllocatorType& alloc){
    rapidjson::Document d(rapidjson::kObjectType);
    d.AddMember("op",getOpCodeString(),alloc);
    add_if_value_changed(d, alloc, "id", id_);
    add_if_value_changed(d, alloc, "service", service_);
    return d;
  }

  std::string service_;

private:
  /* data */
};


