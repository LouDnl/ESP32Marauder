#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\NimBLE-Arduino\\src\\nimble\\nimble\\host\\include\\host\\ble_ibeacon.h"
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef H_BLE_IBEACON_
#define H_BLE_IBEACON_

#ifdef __cplusplus
extern "C" {
#endif

int ble_ibeacon_set_adv_data(void *uuid128, uint16_t major,
                             uint16_t minor, int8_t measured_power);

#ifdef __cplusplus
}
#endif

#endif
