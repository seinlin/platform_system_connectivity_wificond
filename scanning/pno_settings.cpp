/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "wificond/scanning/pno_settings.h"

#include <android-base/logging.h>

#include "wificond/parcelable_utils.h"

using android::status_t;

namespace com {
namespace android {
namespace server {
namespace wifi {
namespace wificond {

status_t PnoSettings::writeToParcel(::android::Parcel* parcel) const {
  RETURN_IF_FAILED(parcel->writeInt32(interval_ms_));
  RETURN_IF_FAILED(parcel->writeInt32(min_2g_rssi_));
  RETURN_IF_FAILED(parcel->writeInt32(min_5g_rssi_));
  RETURN_IF_FAILED(parcel->writeInt32(pno_networks_.size()));
  for (const auto& network : pno_networks_) {
    RETURN_IF_FAILED(network.writeToParcel(parcel));
  }
  return ::android::OK;
}

status_t PnoSettings::readFromParcel(const ::android::Parcel* parcel) {
  RETURN_IF_FAILED(parcel->readInt32(&interval_ms_));
  RETURN_IF_FAILED(parcel->readInt32(&min_2g_rssi_));
  RETURN_IF_FAILED(parcel->readInt32(&min_5g_rssi_));
  int32_t num_pno_networks = 0;
  RETURN_IF_FAILED(parcel->readInt32(&num_pno_networks));
  for (int i = 0; i < num_pno_networks; i++) {
    PnoNetwork network;
    RETURN_IF_FAILED(network.readFromParcel(parcel));
    pno_networks_.push_back(network);
  }
  return ::android::OK;
}

}  // namespace wificond
}  // namespace wifi
}  // namespace server
}  // namespace android
}  // namespace com
