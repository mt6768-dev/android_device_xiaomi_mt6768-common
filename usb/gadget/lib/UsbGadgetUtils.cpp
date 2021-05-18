/*
 * Copyright (C) 2020 The Android Open Source Project
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

#define LOG_TAG "libusbconfigfs"

#include "include/UsbGadgetCommon.h"

namespace android {
namespace hardware {
namespace usb {
namespace gadget {

int unlinkFunctions(const char* path) {
    DIR* config = opendir(path);
    struct dirent* function;
    char filepath[kMaxFilePathLength];
    int ret = 0;

    if (config == NULL) return -1;

    // d_type does not seems to be supported in /config
    // so filtering by name.
    while (((function = readdir(config)) != NULL)) {
        if ((strstr(function->d_name, FUNCTION_NAME) == NULL)) continue;
        // build the path for each file in the folder.
        sprintf(filepath, "%s/%s", path, function->d_name);
        ret = remove(filepath);
        if (ret) {
            ALOGE("Unable  remove file %s errno:%d", filepath, errno);
            break;
        }
    }

    closedir(config);
    return ret;
}


int linkFunction(const char* function, int index) {
    char functionPath[kMaxFilePathLength];
    char link[kMaxFilePathLength];

    sprintf(functionPath, "%s%s", FUNCTIONS_PATH, function);
    sprintf(link, "%s%d", FUNCTION_PATH, index);
    if (strcmp(function, "rndis.gs4") == 0) {
        mkdir(functionPath, 0755);
    }
    if (symlink(functionPath, link)) {
        ALOGE("Cannot create symlink %s -> %s errno:%d", link, functionPath, errno);
        return -1;
    }
    return 0;
}

Status setVidPid(const char* vid, const char* pid) {
    ALOGI("setVidPid %s %s", vid, pid);
    if (!WriteStringToFile(vid, VENDOR_ID_PATH)) return Status::ERROR;

    if (!WriteStringToFile(pid, PRODUCT_ID_PATH)) return Status::ERROR;
    ALOGI("setVidPid %s %s: success", vid, pid);
    return Status::SUCCESS;
}

std::string getVendorFunctions() {
    if (GetProperty(kBuildType, "") == "user") return "user";

    std::string bootMode = GetProperty(PERSISTENT_BOOT_MODE, "");
    std::string persistVendorFunctions = GetProperty(kPersistentVendorConfig, "");
    std::string vendorFunctions = GetProperty(kVendorConfig, "");
    std::string ret = "";

    if (vendorFunctions != "") {
        ret = vendorFunctions;
    } else if (bootMode == "usbradio" || bootMode == "factory" || bootMode == "ffbm-00" ||
               bootMode == "ffbm-01") {
        if (persistVendorFunctions != "")
            ret = persistVendorFunctions;
        else
            ret = "diag";
        // vendor.usb.config will reflect the current configured functions
        SetProperty(kVendorConfig, ret);
    }

    return ret;
}

Status resetGadget() {
    ALOGI("setCurrentUsbFunctions None");

    if (!WriteStringToFile("none", PULLUP_PATH)) ALOGI("Gadget cannot be pulled down");
    ALOGI("RESETGADGET: gadget pulled down");
    if (!WriteStringToFile("0", DEVICE_CLASS_PATH)) return Status::ERROR;
    ALOGI("RESETGADGET: class reset");
    if (!WriteStringToFile("0", DEVICE_SUB_CLASS_PATH)) return Status::ERROR;
    ALOGI("RESETGADGET: subclass reset");
    if (!WriteStringToFile("0", DEVICE_PROTOCOL_PATH)) return Status::ERROR;
    ALOGI("RESETGADGET: protocol reset");
    if (!WriteStringToFile("0", DESC_USE_PATH)) return Status::ERROR;
    ALOGI("RESETGADGET: use set to 0");
    if (unlinkFunctions(CONFIG_PATH)) return Status::ERROR;

    return Status::SUCCESS;
}

Status addGenericAndroidFunctions(uint64_t functions, int* functionCount) {
    if ((functions & GadgetFunction::MTP) != 0) {
        ALOGI("setCurrentUsbFunctions MTP");
        if (linkFunction("mtp.gs0", (*functionCount)++)) return Status::ERROR;
    } else if ((functions & GadgetFunction::PTP) != 0) {
        ALOGI("setCurrentUsbFunctions PTP");
        if (linkFunction("ptp.gs1", (*functionCount)++)) return Status::ERROR;
    }
    if ((functions & GadgetFunction::MIDI) != 0) {
        ALOGI("setCurrentUsbFunctions MIDI");
        if (linkFunction("midi.gs5", (*functionCount)++)) return Status::ERROR;
    }

    if ((functions & GadgetFunction::ACCESSORY) != 0) {
        ALOGI("setCurrentUsbFunctions Accessory");
        if (linkFunction("accessory.gs2", (*functionCount)++)) return Status::ERROR;
    }

    if ((functions & GadgetFunction::AUDIO_SOURCE) != 0) {
        ALOGI("setCurrentUsbFunctions Audio Source");
        if (linkFunction("audio_source.gs3", (*functionCount)++)) return Status::ERROR;
    }

    if ((functions & GadgetFunction::RNDIS) != 0) {
        ALOGI("setCurrentUsbFunctions rndis");
        if (linkFunction("rndis.gs4", (*functionCount)++)) return Status::ERROR;
    }

    if ((functions & GadgetFunction::ADB) != 0) {
        ALOGI("setCurrentUsbFunctions ADB");
        if (linkFunction("ffs.adb", (*functionCount)++)) return Status::ERROR;
    }
    return Status::SUCCESS;
}

}  // namespace gadget
}  // namespace usb
}  // namespace hardware
}  // namespace android
