/* Diagnostic Client library
* Copyright (C) 2022  Avijit Dey
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef DIAGNOSTIC_CLIENT_LIB_APPL_SRC_DCM_SERVICE_VD_MESSAGE_H
#define DIAGNOSTIC_CLIENT_LIB_APPL_SRC_DCM_SERVICE_VD_MESSAGE_H
/* includes */
#include "ara/diag/uds_transport/uds_message.h"
#include "include/diagnostic_client_message_type.h"

namespace diag {
namespace client {
namespace vd_message {

class VdMessage final : public ara::diag::uds_transport::UdsMessage {
public:
  // ctor
  VdMessage(vehicle_info::VehicleInfoListRequestType vehicle_info_request, IpAddress host_ip_address);

  // default ctor
  VdMessage() noexcept;

  // dtor
  ~VdMessage() noexcept = default;

private:
  // SA
  Address source_address_;

  // TA
  Address target_address_;

  // TA type
  TargetAddressType target_address_type;

  // Host Ip Address
  IpAddress host_ip_address_;

  // store the vehicle info payload
  ara::diag::uds_transport::ByteVector vehicle_info_payload_;

  // add new metaInfo to this message.
  void AddMetaInfo(std::shared_ptr<const MetaInfoMap> meta_info) override {
    // Todo [Add meta info information]
  }

  // Get the UDS message data starting with the SID (A_Data as per ISO)
  const ara::diag::uds_transport::ByteVector& GetPayload() const override { return vehicle_info_payload_; }

  // return the underlying buffer for write access
  ara::diag::uds_transport::ByteVector& GetPayload() override { return vehicle_info_payload_; }

  // Get the source address of the uds message.
  Address GetSa() const noexcept override { return source_address_; }

  // Get the target address of the uds message.
  Address GetTa() const noexcept override { return target_address_; }

  // Get the target address type (phys/func) of the uds message.
  TargetAddressType GetTaType() const noexcept override { return target_address_type; }

  // Get Host Ip address
  IpAddress GetHostIpAddress() const noexcept override { return host_ip_address_; }

  // Get Host port number
  PortNumber GetHostPortNumber() const noexcept override { return 13400U; }

  // Serialize Data from VehicleInfoListRequest
  ara::diag::uds_transport::ByteVector SerializeVehicleInfoList(
      vehicle_info::VehicleInfoListRequestType vehicle_info_request);
};

}  // namespace vd_message
}  // namespace client
}  // namespace diag

#endif  // DIAGNOSTIC_CLIENT_LIB_APPL_SRC_DCM_SERVICE_VD_MESSAGE_H