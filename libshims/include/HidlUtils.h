/*
 * Copyright (C) 2018 The Android Open Source Project
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

#ifndef android_hardware_audio_Hidl_Utils_H_
#define android_hardware_audio_Hidl_Utils_H_

#include PATH(android/hardware/audio/common/FILE_VERSION/types.h)

#include <memory>
#include <string>
#include <vector>

#include <system/audio.h>

namespace android {
namespace hardware {
namespace audio {
namespace common {
namespace CPP_VERSION {
namespace implementation {

using ::android::hardware::hidl_vec;
using namespace ::android::hardware::audio::common::CPP_VERSION;

struct HidlUtils {
    static status_t audioConfigFromHal(const audio_config_t& halConfig, bool isInput,
                                       AudioConfig* config);
    static status_t audioConfigFromHal(const audio_config_t& halConfig,
                                       AudioConfig* config); // VNDK30
    static status_t audioConfigToHal(const AudioConfig& config, audio_config_t* halConfig);
#if MAJOR_VERSION >= 4
    static status_t audioContentTypeFromHal(const audio_content_type_t halContentType,
                                            AudioContentType* contentType);
    static status_t audioContentTypeToHal(const AudioContentType& contentType,
                                          audio_content_type_t* halContentType);
#endif
    static status_t audioGainConfigFromHal(const struct audio_gain_config& halConfig, bool isInput,
                                           AudioGainConfig* config);
    static status_t audioGainConfigToHal(const AudioGainConfig& config,
                                         struct audio_gain_config* halConfig);
    static status_t audioGainFromHal(const struct audio_gain& halGain, bool isInput,
                                     AudioGain* gain);
    static status_t audioGainToHal(const AudioGain& gain, struct audio_gain* halGain);
    static status_t audioUsageFromHal(audio_usage_t halUsage, AudioUsage* usage);
    static status_t audioUsageToHal(const AudioUsage& usage, audio_usage_t* halUsage);
    static status_t audioOffloadInfoFromHal(const audio_offload_info_t& halOffload,
                                            AudioOffloadInfo* offload);
    static status_t audioOffloadInfoToHal(const AudioOffloadInfo& offload,
                                          audio_offload_info_t* halOffload);
    static status_t audioPortConfigFromHal(const struct audio_port_config& halConfig,
                                           AudioPortConfig* config);
    static status_t audioPortConfigToHal(const AudioPortConfig& config,
                                         struct audio_port_config* halConfig);
    static status_t audioPortConfigsFromHal(unsigned int numHalConfigs,
                                            const struct audio_port_config* halConfigs,
                                            hidl_vec<AudioPortConfig>* configs);
    static status_t audioPortConfigsToHal(const hidl_vec<AudioPortConfig>& configs,
                                          std::unique_ptr<audio_port_config[]>* halConfigs);
    static std::unique_ptr<audio_port_config[]> audioPortConfigsToHal(
                                          const hidl_vec<AudioPortConfig>& configs); // VNDK30
    static status_t audioPortFromHal(const struct audio_port& halPort, AudioPort* port);
    static status_t audioPortToHal(const AudioPort& port, struct audio_port* halPort);
    static status_t audioSourceFromHal(audio_source_t halSource, AudioSource* source);
    static status_t audioSourceToHal(const AudioSource& source, audio_source_t* halSource);
#if MAJOR_VERSION >= 5
    static status_t deviceAddressToHal(const DeviceAddress& device, audio_devices_t* halDeviceType,
                                       char* halDeviceAddress);
    static status_t deviceAddressFromHal(audio_devices_t halDeviceType,
                                         const char* halDeviceAddress, DeviceAddress* device);
#endif

#if MAJOR_VERSION >= 7
    static constexpr char sAudioTagSeparator = ';';

    static status_t audioChannelMaskFromHal(audio_channel_mask_t halChannelMask, bool isInput,
                                            AudioChannelMask* channelMask);
    static status_t audioChannelMasksFromHal(const std::vector<std::string>& halChannelMasks,
                                             hidl_vec<AudioChannelMask>* channelMasks);
    static status_t audioChannelMaskToHal(const AudioChannelMask& channelMask,
                                          audio_channel_mask_t* halChannelMask);
    static status_t audioConfigBaseFromHal(const audio_config_base_t& halConfigBase, bool isInput,
                                           AudioConfigBase* configBase);
    static status_t audioConfigBaseToHal(const AudioConfigBase& configBase,
                                         audio_config_base_t* halConfigBase);
    static status_t audioConfigBaseOptionalFromHal(const audio_config_base_t& halConfigBase,
                                                   bool isInput, bool formatSpecified,
                                                   bool sampleRateSpecified,
                                                   bool channelMaskSpecified,
                                                   AudioConfigBaseOptional* configBase);
    static status_t audioConfigBaseOptionalToHal(const AudioConfigBaseOptional& configBase,
                                                 audio_config_base_t* halConfigBase,
                                                 bool* formatSpecified, bool* sampleRateSpecified,
                                                 bool* channelMaskSpecified);
    static status_t audioDeviceTypeFromHal(audio_devices_t halDevice, AudioDevice* device);
    static status_t audioDeviceTypeToHal(const AudioDevice& device, audio_devices_t* halDevice);
    static status_t audioFormatFromHal(audio_format_t halFormat, AudioFormat* format);
    static status_t audioFormatsFromHal(const std::vector<std::string>& halFormats,
                                        hidl_vec<AudioFormat>* formats);
    static status_t audioFormatToHal(const AudioFormat& format, audio_format_t* halFormat);
    static status_t audioGainModeMaskFromHal(audio_gain_mode_t halGainModeMask,
                                             hidl_vec<AudioGainMode>* gainModeMask);
    static status_t audioGainModeMaskToHal(const hidl_vec<AudioGainMode>& gainModeMask,
                                           audio_gain_mode_t* halGainModeMask);
    static status_t audioPortFromHal(const struct audio_port_v7& halPort, AudioPort* port);
    static status_t audioPortToHal(const AudioPort& port, struct audio_port_v7* halPort);
    static status_t audioProfileFromHal(const struct audio_profile& halProfile, bool isInput,
                                        AudioProfile* profile);
    static status_t audioProfileToHal(const AudioProfile& profile,
                                      struct audio_profile* halProfile);
    static status_t audioStreamTypeFromHal(audio_stream_type_t halStreamType,
                                           AudioStreamType* streamType);
    static status_t audioStreamTypeToHal(const AudioStreamType& streamType,
                                         audio_stream_type_t* halStreamType);
    static status_t audioTagsFromHal(const std::vector<std::string>& strTags,
                                     hidl_vec<AudioTag>* tags);
    static status_t audioTagsToHal(const hidl_vec<AudioTag>& tags, char* halTags);
    static hidl_vec<AudioTag> filterOutNonVendorTags(const hidl_vec<AudioTag>& tags);
    static std::vector<std::string> filterOutNonVendorTags(const std::vector<std::string>& tags);
    static std::vector<std::string> splitAudioTags(const char* halTags);
    static status_t audioTransportsFromHal(const struct audio_port_v7& halPort, bool isInput,
                                           hidl_vec<AudioTransport>* transports);
    static status_t audioTransportsToHal(const hidl_vec<AudioTransport>& transports,
                                         struct audio_port_v7* halTransport);

  private:
    static status_t audioIndexChannelMaskFromHal(audio_channel_mask_t halChannelMask,
                                                 AudioChannelMask* channelMask);
    static status_t audioInputChannelMaskFromHal(audio_channel_mask_t halChannelMask,
                                                 AudioChannelMask* channelMask);
    static status_t audioOutputChannelMaskFromHal(audio_channel_mask_t halChannelMask,
                                                  AudioChannelMask* channelMask);
    static status_t audioPortExtendedInfoFromHal(
            audio_port_role_t role, audio_port_type_t type,
            const struct audio_port_config_device_ext& device,
            const struct audio_port_config_mix_ext& mix,
            const struct audio_port_config_session_ext& session, AudioPortExtendedInfo* ext,
            bool* isInput);
    static status_t audioPortExtendedInfoToHal(const AudioPortExtendedInfo& ext,
                                               audio_port_role_t* role, audio_port_type_t* type,
                                               struct audio_port_config_device_ext* device,
                                               struct audio_port_config_mix_ext* mix,
                                               struct audio_port_config_session_ext* session);
    static status_t encapsulationTypeFromHal(audio_encapsulation_type_t halEncapsulationType,
                                             AudioEncapsulationType* encapsulationType);
    static status_t encapsulationTypeToHal(const AudioEncapsulationType& encapsulationType,
                                           audio_encapsulation_type_t* halEncapsulationType);

#endif  // MAJOR_VERSION >= 7

    // V4 and below have DeviceAddress defined in the 'core' interface.
    // To avoid duplicating code, the implementations of deviceAddressTo/FromHal
    // are defined as templates. These templates can be only used directly by V4
    // and below.
#if MAJOR_VERSION >= 5
  private:
#endif
    template <typename DA>
    static status_t deviceAddressToHalImpl(const DA& device, audio_devices_t* halDeviceType,
                                           char* halDeviceAddress);
    template <typename DA>
    static status_t deviceAddressFromHalImpl(audio_devices_t halDeviceType,
                                             const char* halDeviceAddress, DA* device);
};

#if MAJOR_VERSION <= 6
#if MAJOR_VERSION >= 4
inline status_t HidlUtils::audioContentTypeFromHal(const audio_content_type_t halContentType,
                                                   AudioContentType* contentType) {
    *contentType = AudioContentType(halContentType);
    return NO_ERROR;
}

inline status_t HidlUtils::audioContentTypeToHal(const AudioContentType& contentType,
                                                 audio_content_type_t* halContentType) {
    *halContentType = static_cast<audio_content_type_t>(contentType);
    return NO_ERROR;
}
#endif

inline status_t HidlUtils::audioSourceFromHal(audio_source_t halSource, AudioSource* source) {
    *source = AudioSource(halSource);
    return NO_ERROR;
}

inline status_t HidlUtils::audioSourceToHal(const AudioSource& source, audio_source_t* halSource) {
    *halSource = static_cast<audio_source_t>(source);
    return NO_ERROR;
}

template <typename DA>
status_t HidlUtils::deviceAddressToHalImpl(const DA& device, audio_devices_t* halDeviceType,
                                           char* halDeviceAddress) {
    *halDeviceType = static_cast<audio_devices_t>(device.device);
    memset(halDeviceAddress, 0, AUDIO_DEVICE_MAX_ADDRESS_LEN);
    if (audio_is_a2dp_out_device(*halDeviceType) || audio_is_a2dp_in_device(*halDeviceType)) {
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "%02X:%02X:%02X:%02X:%02X:%02X",
                 device.address.mac[0], device.address.mac[1], device.address.mac[2],
                 device.address.mac[3], device.address.mac[4], device.address.mac[5]);
    } else if (*halDeviceType == AUDIO_DEVICE_OUT_IP || *halDeviceType == AUDIO_DEVICE_IN_IP) {
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "%d.%d.%d.%d",
                 device.address.ipv4[0], device.address.ipv4[1], device.address.ipv4[2],
                 device.address.ipv4[3]);
    } else if (audio_is_usb_out_device(*halDeviceType) || audio_is_usb_in_device(*halDeviceType)) {
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "card=%d;device=%d",
                 device.address.alsa.card, device.address.alsa.device);
    } else if (*halDeviceType == AUDIO_DEVICE_OUT_BUS || *halDeviceType == AUDIO_DEVICE_IN_BUS) {
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "%s", device.busAddress.c_str());
    } else if (*halDeviceType == AUDIO_DEVICE_OUT_REMOTE_SUBMIX ||
               *halDeviceType == AUDIO_DEVICE_IN_REMOTE_SUBMIX) {
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "%s",
                 device.rSubmixAddress.c_str());
    } else {
        // Fall back to bus address for other device types, e.g. for microphones.
        snprintf(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN, "%s", device.busAddress.c_str());
    }
    return NO_ERROR;
}

template <typename DA>
status_t HidlUtils::deviceAddressFromHalImpl(audio_devices_t halDeviceType,
                                             const char* halDeviceAddress, DA* device) {
    if (device == nullptr) {
        return BAD_VALUE;
    }
    device->device = AudioDevice(halDeviceType);
    if (halDeviceAddress == nullptr ||
        strnlen(halDeviceAddress, AUDIO_DEVICE_MAX_ADDRESS_LEN) == 0) {
        return NO_ERROR;
    }

    if (audio_is_a2dp_out_device(halDeviceType) || audio_is_a2dp_in_device(halDeviceType)) {
        int status =
                sscanf(halDeviceAddress, "%hhX:%hhX:%hhX:%hhX:%hhX:%hhX", &device->address.mac[0],
                       &device->address.mac[1], &device->address.mac[2], &device->address.mac[3],
                       &device->address.mac[4], &device->address.mac[5]);
        return status == 6 ? OK : BAD_VALUE;
    } else if (halDeviceType == AUDIO_DEVICE_OUT_IP || halDeviceType == AUDIO_DEVICE_IN_IP) {
        int status = sscanf(halDeviceAddress, "%hhu.%hhu.%hhu.%hhu", &device->address.ipv4[0],
                            &device->address.ipv4[1], &device->address.ipv4[2],
                            &device->address.ipv4[3]);
        return status == 4 ? OK : BAD_VALUE;
    } else if (audio_is_usb_out_device(halDeviceType) || audio_is_usb_in_device(halDeviceType)) {
        int status = sscanf(halDeviceAddress, "card=%d;device=%d", &device->address.alsa.card,
                            &device->address.alsa.device);
        return status == 2 ? OK : BAD_VALUE;
    } else if (halDeviceType == AUDIO_DEVICE_OUT_BUS || halDeviceType == AUDIO_DEVICE_IN_BUS) {
        device->busAddress = halDeviceAddress;
        return OK;
    } else if (halDeviceType == AUDIO_DEVICE_OUT_REMOTE_SUBMIX ||
               halDeviceType == AUDIO_DEVICE_IN_REMOTE_SUBMIX) {
        device->rSubmixAddress = halDeviceAddress;
        return OK;
    }
    // Fall back to bus address for other device types, e.g. for microphones.
    device->busAddress = halDeviceAddress;
    return NO_ERROR;
}
#endif  // MAJOR_VERSION <= 6

}  // namespace implementation
}  // namespace CPP_VERSION
}  // namespace common
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // android_hardware_audio_Hidl_Utils_H_
