#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\NimBLE-Arduino\\src\\nimble\\nimble\\host\\src\\ble_hs_atomic_priv.h"
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

#ifndef H_BLE_HS_ATOMIC_
#define H_BLE_HS_ATOMIC_

#include "ble_hs_conn_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

int ble_hs_atomic_conn_delete(uint16_t conn_handle);
void ble_hs_atomic_conn_insert(struct ble_hs_conn *conn);
int ble_hs_atomic_conn_flags(uint16_t conn_handle,
                             ble_hs_conn_flags_t *out_flags);
int ble_hs_atomic_conn_set_flags(uint16_t conn_handle,
                                 ble_hs_conn_flags_t flags, int on);
uint16_t ble_hs_atomic_first_conn_handle(void);

#ifdef __cplusplus
}
#endif

#endif
