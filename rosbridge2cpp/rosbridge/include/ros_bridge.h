#pragma once 

#include <iostream>
#include <functional>
#include <unordered_map>

#include "types.h"
#include "helper.h"

//#include "itransport_layer.h"
#include "client/socket_tcp_connection.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "messages/rosbridge_advertise_msg.h"
#include "messages/rosbridge_advertise_service_msg.h"
#include "messages/rosbridge_call_service_msg.h"
#include "messages/rosbridge_msg.h"
#include "messages/rosbridge_publish_msg.h"
#include "messages/rosbridge_service_response_msg.h"
#include "messages/rosbridge_subscribe_msg.h"
#include "messages/rosbridge_unadvertise_msg.h"
#include "messages/rosbridge_unadvertise_service_msg.h"
#include "messages/rosbridge_unsubscribe_msg.h"

using json = rapidjson::Document;

namespace rosbridge2cpp{

/*
   * The main rosbridge2cpp class that connects to the rosbridge server.
   * The library is inspired by [roslibjs](http://wiki.ros.org/roslibjs),
   * which is a feature-rich client-side implementation of the rosbridge protocol in java script.
   */
class ROSBridge {

public:
    ROSBridge(SocketTCPConnection &transport): status_(false), transport_layer_(transport){}

    // Init the underlying transport layer and everything thats required
    // to initialized in this class.
    bool Init(QUrl ip_addr);

    // Send arbitrary string-data over the given TransportLayer
    bool SendMessage(std::string data);

    // Send json data over the transport layer,
    // by serializing it and using
    // ROSBridge::send_message(std::string data)
    bool SendMessage(json &data);

    bool SendMessage(ROSBridgeMsg &msg);

    // Registration function for topic callbacks.
    // This method should ONLY be called by ROSTopic instances.
    // It will pass the received data to the registered std::function.
    //
    // Please note:
    // _If you register more than one callback for the
    // same topic, the old one get's overwritten_
    void RegisterTopicCallback(std::string topic_name, FunVrROSPublishMsg fun);

    // This method should ONLY be called by ROSTopic instances.
    // If you call this on your own, the housekeeping in ROSTopic
    // might fail which leads to missing unsubscribe messages etc.
    //
    // @return true, if the passed callback has been found and removed. false otherwise.
    bool UnregisterTopicCallback(std::string topic_name, FunVrROSPublishMsg fun);

    // Register the callback for a service call.
    // This callback will be executed when we receive the response for a particular Service Request
    void RegisterServiceCallback(std::string service_call_id, FunVrROSServiceResponseMsg fun);

    // Register the callback that shall be executed,
    // whenever we receive a request for a service that
    // this ROSBridge has advertised via a ROSService.
    void RegisterServiceRequestCallback(std::string service_name, FunVrROSCallServiceMsgrROSServiceResponseMsgrAllocator fun);
    void RegisterServiceRequestCallback(std::string service_name, FunVrROSCallServiceMsgrROSServiceResponseMsg fun);

    // An ID Counter that will be used to generate increasing
    // IDs for service/topic etc. messages
    long id_counter = 0;

private:
    // Callback function for the used ITransportLayer.
    // It receives the received json that was contained
    // in the incoming ROSBridge packet
    //
    // @pre This method assumes a valid json variable
    void IncomingMessageCallback(json &data);

    // Handler Method for reply packet
    void HandleIncomingPublishMessage(ROSBridgePublishMsg &data);

    // Handler Method for reply packet
    void HandleIncomingServiceResponseMessage(ROSBridgeServiceResponseMsg &data);

    // Handler Method for reply packet
    void HandleIncomingServiceRequestMessage(std::string id, ROSBridgeCallServiceMsg &data);

    bool status_ = false;
    SocketTCPConnection &transport_layer_;
    std::unordered_map<std::string, std::list<FunVrROSPublishMsg>> registered_topic_callbacks_;
    std::unordered_map<std::string, FunVrROSServiceResponseMsg> registered_service_callbacks_;
    std::unordered_map<std::string, FunVrROSCallServiceMsgrROSServiceResponseMsgrAllocator> registered_service_request_callbacks_;
    std::unordered_map<std::string, FunVrROSCallServiceMsgrROSServiceResponseMsg> registered_service_request_callbacks_bson_;
};
}
