#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\lv_arduino\\src\\src\\lv_misc\\lv_types.h"
/**
 * @file lv_types.h
 *
 */

#ifndef LV_TYPES_H
#define LV_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

#if __STDC_VERSION__ >= 199901L  // If c99 or newer, use stdint.h to determine arch size
#include <stdint.h>
#endif


// If __UINTPTR_MAX__ or UINTPTR_MAX are available, use them to determine arch size
#if defined(__UINTPTR_MAX__) && __UINTPTR_MAX__ > 0xFFFFFFFF
#define LV_ARCH_64

#elif defined(UINTPTR_MAX) && UINTPTR_MAX > 0xFFFFFFFF
#define LV_ARCH_64

// Otherwise use compiler-dependent means to determine arch size
#elif defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined (__aarch64__)
#define LV_ARCH_64

#endif


/**********************
 *      TYPEDEFS
 **********************/

/**
 * LVGL error codes.
 */
enum {
    LV_RES_INV = 0, /*Typically indicates that the object is deleted (become invalid) in the action
                       function or an operation was failed*/
    LV_RES_OK,      /*The object is valid (no deleted) after the action*/
};
typedef uint8_t lv_res_t;



#if __STDC_VERSION__ >= 199901L
// If c99 or newer,  use the definition of uintptr_t directly from <stdint.h>
typedef uintptr_t lv_uintptr_t;

#else

// Otherwise, use the arch size determination
#ifdef LV_ARCH_64
typedef uint64_t lv_uintptr_t;
#else
typedef uint32_t lv_uintptr_t;
#endif

#endif


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#define LV_UNUSED(x) ((void) x)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TYPES_H*/

