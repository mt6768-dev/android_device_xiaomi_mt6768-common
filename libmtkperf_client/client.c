/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "libmtkperf_client"

#include <log/log.h>

int perf_lock_acq(int hdl, int dur, long num, unsigned int tid) {
    ALOGI("[%s] hdl: %d, dur: %d, num: %ld, tid: %u",
            __func__, hdl, dur, num, tid);
    if (hdl > 0)
        return hdl;

    return 233;
}

int perf_lock_rel(int hdl) {
    ALOGI("[%s] hdl: %d", __func__, hdl);
    return 0;
}

int perf_cus_lock_hint(int hint, int dur) {
    ALOGI("[%s], hint: %d, dur: %d", __func__, hint, dur);
    return 233;
}
