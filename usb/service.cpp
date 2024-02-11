/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.usb@1.1-service.mt6768"

#include <hidl/HidlTransportSupport.h>
#include "Usb.h"
#include "UsbGadget.h"

using android::sp;

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::usb::gadget::V1_1::IUsbGadget;
using android::hardware::usb::gadget::V1_1::implementation::UsbGadget;
using android::hardware::usb::V1_1::IUsb;
using android::hardware::usb::V1_1::implementation::Usb;

using android::OK;
using android::status_t;

int main() {
  android::sp<IUsb> service = new Usb();
  android::sp<IUsbGadget> service2 = new UsbGadget();

  configureRpcThreadpool(2, true /*callerWillJoin*/);
  status_t status = service->registerAsService();

  if (status != OK) {
    ALOGE("Cannot register USB HAL service");
    return 1;
  }

  status = service2->registerAsService();

  if (status != OK) {
    ALOGE("Cannot register USB Gadget HAL service");
    return 1;
  }

  ALOGI("USB HAL Ready.");
  joinRpcThreadpool();
  // Under noraml cases, execution will not reach this line.
  ALOGI("USB HAL failed to join thread pool.");
  return 1;
}
