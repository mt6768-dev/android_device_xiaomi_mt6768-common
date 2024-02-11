#!/usr/bin/env python
#
# Copyright (C) 2016 The CyanogenMod Project
# Copyright (C) 2017-2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

import os
import sys
from hashlib import sha1

device = 'mt6768-common'
vendor = 'xiaomi'

with open('proprietary-files.txt', 'r') as f:
    lines = f.read().splitlines()
vendorPath = '../../../vendor/' + vendor + '/' + device + '/proprietary'
needSHA1 = False


def cleanup():
    for index, line in enumerate(lines):
        # Skip empty or commented lines
        if len(line) == 0 or line[0] == '#' or '|' not in line:
            continue

        # Drop SHA1 hash, if existing
        lines[index] = line.split('|')[0]


def update():
    for index, line in enumerate(lines):
        # Skip empty lines
        if len(line) == 0:
            continue

        # Check if we need to set SHA1 hash for the next files
        if line[0] == '#':
            needSHA1 = (' - from' in line)
            continue

        if needSHA1:
            # Remove existing SHA1 hash
            line = line.split('|')[0]

            filePath = line.split(';')[0].split(':')[-1]
            if filePath[0] == '-':
                filePath = filePath[1:]

            with open(os.path.join(vendorPath, filePath), 'rb') as f:
                hash = sha1(f.read()).hexdigest()

            lines[index] = '%s|%s' % (line, hash)


if len(sys.argv) == 2 and sys.argv[1] == '-c':
    cleanup()
else:
    update()

with open('proprietary-files.txt', 'w') as file:
    file.write('\n'.join(lines) + '\n')
