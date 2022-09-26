/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <common/all-versions/VersionUtils.h>
#include "include/HidlUtils.h"

namespace android {
namespace hardware {
namespace audio {
namespace common {
namespace CPP_VERSION {
namespace implementation {

status_t HidlUtils::audioConfigFromHal(const audio_config_t& halConfig, AudioConfig* config) {
    return audioConfigFromHal(halConfig, true /*isInput*/, config);
}

std::unique_ptr<audio_port_config[]> HidlUtils::audioPortConfigsToHal(const hidl_vec<AudioPortConfig>& configs) {
    std::unique_ptr<audio_port_config[]> halConfigs(new audio_port_config[configs.size()]);
    status_t ret = audioPortConfigsToHal(configs, &halConfigs);
    if (ret == NO_ERROR)
        return halConfigs;
    else
        return nullptr;
}

}  // namespace implementation
}  // namespace CPP_VERSION
}  // namespace common
}  // namespace audio
}  // namespace hardware
}  // namespace android
