#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\NimBLE-Arduino\\src\\nimble\\porting\\nimble\\include\\sysinit\\sysinit.h"
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

#ifndef __SYSINIT_H__
#define __SYSINIT_H__

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSINIT_ASSERT_ACTIVE()

#define SYSINIT_PANIC_ASSERT(rc)        assert(rc);

#ifdef __cplusplus
}
#endif

#endif /* __SYSINIT_H__ */
