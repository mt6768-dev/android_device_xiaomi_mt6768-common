/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ANDROID_HARDWARE_USB_GADGET_V1_1_USBGADGET_H
#define ANDROID_HARDWARE_USB_GADGET_V1_1_USBGADGET_H

#include <UsbGadgetCommon.h>
#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/unique_fd.h>
#include <android/hardware/usb/gadget/1.1/IUsbGadget.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
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
namespace V1_1 {
namespace implementation {

using ::android::sp;
using ::android::base::GetProperty;
using ::android::base::SetProperty;
using ::android::base::unique_fd;
using ::android::base::WriteStringToFile;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::usb::gadget::getVendorFunctions;
using ::android::hardware::usb::gadget::kDebug;
using ::android::hardware::usb::gadget::kDisconnectWaitUs;
using ::android::hardware::usb::gadget::linkFunction;
using ::android::hardware::usb::gadget::resetGadget;
using ::android::hardware::usb::gadget::setVidPid;
using ::android::hardware::usb::gadget::unlinkFunctions;
using ::std::string;

constexpr char kGadgetName[] = "musb-hdrc";

struct UsbGadget : public IUsbGadget {
    UsbGadget();

    // Makes sure that only one request is processed at a time.
    std::mutex mLockSetCurrentFunction;
    uint64_t mCurrentUsbFunctions;
    bool mCurrentUsbFunctionsApplied;

    Return<void> setCurrentUsbFunctions(uint64_t functions,
                                        const sp<V1_0::IUsbGadgetCallback>& callback,
                                        uint64_t timeout) override;

    Return<void> getCurrentUsbFunctions(const sp<V1_0::IUsbGadgetCallback>& callback) override;

    Return<Status> reset() override;

  private:
    V1_0::Status tearDownGadget();
    V1_0::Status setupFunctions(uint64_t functions, const sp<V1_0::IUsbGadgetCallback>& callback,
                                uint64_t timeout);
};

}  // namespace implementation
}  // namespace V1_1
}  // namespace gadget
}  // namespace usb
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_USB_V1_1_USBGADGET_H
