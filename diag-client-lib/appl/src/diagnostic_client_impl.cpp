/* Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "include/diagnostic_client.h"
#include "diagnostic_client_impl.h"
#include <pthread.h>

namespace diag {
namespace client {

// ctor
DiagClientImpl::DiagClientImpl(std::string dm_client_config)
                : diag::client::DiagClient()
                , ptree{}
                , dcm_instance_ptr{nullptr} {
    // dlt register app & context
    DLT_REGISTER_APP("DCLT", "Diag Client Library");
    DLT_REGISTER_CONTEXT(diagclient_main,"main","Diag Client Main Context");

    // start parsing the config json file
    libOsAbstraction::libBoost::jsonparser::createJsonParser json_parser;
    json_parser.getJsonPtree(dm_client_config, ptree);
    
    // create single dcm instance and pass the config tree
    dcm_instance_ptr = std::make_unique<diag::client::dcm::DCMClient>(ptree);

    DLT_LOG(diagclient_main, DLT_LOG_INFO, 
        DLT_CSTRING("DiagClient instance created"));
}

// dtor
DiagClientImpl::~DiagClientImpl() {
    // de-register from dlt
    DLT_UNREGISTER_CONTEXT(diagclient_main);
    DLT_UNREGISTER_APP();
}

// Initialize all the resources and load the configs
void DiagClientImpl::Initialize() {
    // start DCM thread here
    dcm_thread_ = std::thread(&diag::client::dcm::DCMClient::Main, std::ref(*dcm_instance_ptr.get()));
    pthread_setname_np(dcm_thread_.native_handle(), "DCMClient_Main");
    
    DLT_LOG(diagclient_main, DLT_LOG_INFO, 
        DLT_CSTRING("DiagClient Initialize success"));
}

// De-initialize all the resource and free memory
void DiagClientImpl::DeInitialize() {
    // shutdown DCM module here
    dcm_instance_ptr->SignalShutdown();
    dcm_thread_.join();

    DLT_LOG(diagclient_main, DLT_LOG_INFO,
        DLT_CSTRING("DiagClient DeInitialized"));
}

// Get Required Conversation based on Conversation Name
diag::client::conversation::DiagClientConversation&
            DiagClientImpl::GetDiagnosticClientConversation(std::string conversation_name) {
    return(dcm_instance_ptr->GetDiagnosticClientConversation(conversation_name));
}

} // client
} // diag