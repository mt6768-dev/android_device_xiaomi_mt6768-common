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

#ifndef HARDWARE_USB_USBGADGETCOMMON_H
#define HARDWARE_USB_USBGADGETCOMMON_H

#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/unique_fd.h>

#include <android/hardware/usb/gadget/1.1/IUsbGadget.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/inotify.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/Log.h>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

namespace android {
namespace hardware {
namespace usb {
namespace gadget {

constexpr int kBufferSize = 512;
constexpr int kMaxFilePathLength = 256;
constexpr int kEpollEvents = 10;
constexpr bool kDebug = false;
constexpr int kDisconnectWaitUs = 100000;
constexpr int kPullUpDelay = 500000;
constexpr int kShutdownMonitor = 100;

constexpr char kBuildType[] = "ro.build.type";
constexpr char kPersistentVendorConfig[] = "persist.vendor.usb.usbradio.config";
constexpr char kVendorConfig[] = "vendor.usb.config";

#define GADGET_PATH "/config/usb_gadget/g1/"
#define PULLUP_PATH GADGET_PATH "UDC"
#define PERSISTENT_BOOT_MODE "ro.bootmode"
#define VENDOR_ID_PATH GADGET_PATH "idVendor"
#define PRODUCT_ID_PATH GADGET_PATH "idProduct"
#define DEVICE_CLASS_PATH GADGET_PATH "bDeviceClass"
#define DEVICE_SUB_CLASS_PATH GADGET_PATH "bDeviceSubClass"
#define DEVICE_PROTOCOL_PATH GADGET_PATH "bDeviceProtocol"
#define DESC_USE_PATH GADGET_PATH "os_desc/use"
#define OS_DESC_PATH GADGET_PATH "os_desc/b.1"
#define CONFIG_PATH GADGET_PATH "configs/b.1/"
#define CONFIG_STR_PATH CONFIG_PATH "strings/0x409/configuration"
#define FUNCTIONS_PATH GADGET_PATH "functions/"
#define FUNCTION_NAME "f"
#define FUNCTION_PATH CONFIG_PATH FUNCTION_NAME
#define RNDIS_PATH FUNCTIONS_PATH "rndis.gs4"

using ::android::base::GetProperty;
using ::android::base::SetProperty;
using ::android::base::unique_fd;
using ::android::base::WriteStringToFile;
using ::android::hardware::usb::gadget::V1_0::GadgetFunction;
using ::android::hardware::usb::gadget::V1_0::Status;

using ::std::lock_guard;
using ::std::move;
using ::std::mutex;
using ::std::string;
using ::std::thread;
using ::std::unique_ptr;
using ::std::vector;
using ::std::chrono::microseconds;
using ::std::chrono::steady_clock;
using ::std::literals::chrono_literals::operator""ms;

//**************** Helper functions ************************//

// Removes all the usb functions link in the specified path.
int unlinkFunctions(const char* path);
// Craetes a configfs link for the function.
int linkFunction(const char* function, int index);
// Sets the USB VID and PID.
Status setVidPid(const char* vid, const char* pid);
// Extracts vendor functions from the vendor init properties.
std::string getVendorFunctions();
// Adds all applicable generic android usb functions other than ADB.
Status addGenericAndroidFunctions(uint64_t functions, int* functionCount);
// Pulls down USB gadget.
Status resetGadget();

}  // namespace gadget
}  // namespace usb
}  // namespace hardware
}  // namespace android
#endif
