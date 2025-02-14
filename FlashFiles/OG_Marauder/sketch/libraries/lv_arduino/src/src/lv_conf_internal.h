#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\lv_arduino\\src\\src\\lv_conf_internal.h"
/**
 * GENERATED FILE, DO NOT EDIT IT!
 * @file lv_conf_internal.h
 * Make sure all the defines of lv_conf.h have a default value
**/

#ifndef LV_CONF_INTERNAL_H
#define LV_CONF_INTERNAL_H
/* clang-format off */

#include <stdint.h>

#if defined(LV_CONF_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_CONF_INCLUDE_SIMPLE)
#include "lv_conf.h"
#else
#include "../../lv_conf.h"
#endif

/* clang-format off */

#include <stdint.h>

/*====================
   Graphical settings
 *====================*/

/* Maximal horizontal and vertical resolution to support by the library.*/
#ifndef LV_HOR_RES_MAX
#define LV_HOR_RES_MAX          (480)
#endif
#ifndef LV_VER_RES_MAX
#define LV_VER_RES_MAX          (320)
#endif

/* Color depth:
 * - 1:  1 byte per pixel
 * - 8:  RGB332
 * - 16: RGB565
 * - 32: ARGB8888
 */
#ifndef LV_COLOR_DEPTH
#define LV_COLOR_DEPTH     16
#endif

/* Swap the 2 bytes of RGB565 color.
 * Useful if the display has a 8 bit interface (e.g. SPI)*/
#ifndef LV_COLOR_16_SWAP
#define LV_COLOR_16_SWAP   0
#endif

/* 1: Enable screen transparency.
 * Useful for OSD or other overlapping GUIs.
 * Requires `LV_COLOR_DEPTH = 32` colors and the screen's style should be modified: `style.body.opa = ...`*/
#ifndef LV_COLOR_SCREEN_TRANSP
#define LV_COLOR_SCREEN_TRANSP    0
#endif

/*Images pixels with this color will not be drawn (with chroma keying)*/
#ifndef LV_COLOR_TRANSP
#define LV_COLOR_TRANSP    LV_COLOR_LIME         /*LV_COLOR_LIME: pure green*/
#endif

/* Enable anti-aliasing (lines, and radiuses will be smoothed) */
#ifndef LV_ANTIALIAS
#define LV_ANTIALIAS        1
#endif

/* Default display refresh period.
 * Can be changed in the display driver (`lv_disp_drv_t`).*/
#ifndef LV_DISP_DEF_REFR_PERIOD
#define LV_DISP_DEF_REFR_PERIOD      30      /*[ms]*/
#endif

/* Dot Per Inch: used to initialize default sizes.
 * E.g. a button with width = LV_DPI / 2 -> half inch wide
 * (Not so important, you can adjust it to modify default sizes and spaces)*/
#ifndef LV_DPI
#define LV_DPI              130     /*[px]*/
#endif

/* The the real width of the display changes some default values:
 * default object sizes, layout of examples, etc.
 * According to the width of the display (hor. res. / dpi)
 * the displays fall in 4 categories.
 * The 4th is extra large which has no upper limit so not listed here
 * The upper limit of the categories are set below in 0.1 inch unit.
 */
#ifndef LV_DISP_SMALL_LIMIT
#define LV_DISP_SMALL_LIMIT  30
#endif
#ifndef LV_DISP_MEDIUM_LIMIT
#define LV_DISP_MEDIUM_LIMIT 50
#endif
#ifndef LV_DISP_LARGE_LIMIT
#define LV_DISP_LARGE_LIMIT  70
#endif

/* Type of coordinates. Should be `int16_t` (or `int32_t` for extreme cases) */

/*=========================
   Memory manager settings
 *=========================*/

/* LittelvGL's internal memory manager's settings.
 * The graphical objects and other related data are stored here. */

/* 1: use custom malloc/free, 0: use the built-in `lv_mem_alloc` and `lv_mem_free` */
#ifndef LV_MEM_CUSTOM
#define LV_MEM_CUSTOM      0
#endif
#if LV_MEM_CUSTOM == 0
/* Size of the memory used by `lv_mem_alloc` in bytes (>= 2kB)*/
#ifndef LV_MEM_SIZE
#  define LV_MEM_SIZE    (32U * 1024U)
#endif

/* Complier prefix for a big array declaration */
#ifndef LV_MEM_ATTR
#  define LV_MEM_ATTR
#endif

/* Set an address for the memory pool instead of allocating it as an array.
 * Can be in external SRAM too. */
#ifndef LV_MEM_ADR
#  define LV_MEM_ADR          0
#endif

/* Automatically defrag. on free. Defrag. means joining the adjacent free cells. */
#ifndef LV_MEM_AUTO_DEFRAG
#  define LV_MEM_AUTO_DEFRAG  1
#endif
#else       /*LV_MEM_CUSTOM*/
#ifndef LV_MEM_CUSTOM_INCLUDE
#  define LV_MEM_CUSTOM_INCLUDE <stdlib.h>   /*Header for the dynamic memory function*/
#endif
#ifndef LV_MEM_CUSTOM_ALLOC
#  define LV_MEM_CUSTOM_ALLOC   malloc       /*Wrapper to malloc*/
#endif
#ifndef LV_MEM_CUSTOM_FREE
#  define LV_MEM_CUSTOM_FREE    free         /*Wrapper to free*/
#endif
#endif     /*LV_MEM_CUSTOM*/

/* Garbage Collector settings
 * Used if lvgl is binded to higher level language and the memory is managed by that language */
#ifndef LV_ENABLE_GC
#define LV_ENABLE_GC 0
#endif
#if LV_ENABLE_GC != 0
#ifndef LV_GC_INCLUDE
#  define LV_GC_INCLUDE "gc.h"                           /*Include Garbage Collector related things*/
#endif
#ifndef LV_MEM_CUSTOM_REALLOC
#  define LV_MEM_CUSTOM_REALLOC   your_realloc           /*Wrapper to realloc*/
#endif
#ifndef LV_MEM_CUSTOM_GET_SIZE
#  define LV_MEM_CUSTOM_GET_SIZE  your_mem_get_size      /*Wrapper to lv_mem_get_size*/
#endif
#endif /* LV_ENABLE_GC */

/*=======================
   Input device settings
 *=======================*/

/* Input device default settings.
 * Can be changed in the Input device driver (`lv_indev_drv_t`)*/

/* Input device read period in milliseconds */
#ifndef LV_INDEV_DEF_READ_PERIOD
#define LV_INDEV_DEF_READ_PERIOD          30
#endif

/* Drag threshold in pixels */
#ifndef LV_INDEV_DEF_DRAG_LIMIT
#define LV_INDEV_DEF_DRAG_LIMIT           10
#endif

/* Drag throw slow-down in [%]. Greater value -> faster slow-down */
#ifndef LV_INDEV_DEF_DRAG_THROW
#define LV_INDEV_DEF_DRAG_THROW           10
#endif

/* Long press time in milliseconds.
 * Time to send `LV_EVENT_LONG_PRESSSED`) */
#ifndef LV_INDEV_DEF_LONG_PRESS_TIME
#define LV_INDEV_DEF_LONG_PRESS_TIME      400
#endif

/* Repeated trigger period in long press [ms]
 * Time between `LV_EVENT_LONG_PRESSED_REPEAT */
#ifndef LV_INDEV_DEF_LONG_PRESS_REP_TIME
#define LV_INDEV_DEF_LONG_PRESS_REP_TIME  100
#endif


/* Gesture threshold in pixels */
#ifndef LV_INDEV_DEF_GESTURE_LIMIT
#define LV_INDEV_DEF_GESTURE_LIMIT        50
#endif

/* Gesture min velocity at release before swipe (pixels)*/
#ifndef LV_INDEV_DEF_GESTURE_MIN_VELOCITY
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3
#endif

/*==================
 * Feature usage
 *==================*/

/*1: Enable the Animations */
#ifndef LV_USE_ANIMATION
#define LV_USE_ANIMATION        1
#endif
#if LV_USE_ANIMATION

/*Declare the type of the user data of animations (can be e.g. `void *`, `int`, `struct`)*/

#endif

/* 1: Enable shadow drawing*/
#ifndef LV_USE_SHADOW
#define LV_USE_SHADOW           1
#endif
#if LV_USE_SHADOW
/* Allow buffering some shadow calculation
 * LV_SHADOW_CACHE_SIZE is the max. shadow size to buffer,
 * where shadow size is `shadow_width + radius`
 * Caching has LV_SHADOW_CACHE_SIZE^2 RAM cost*/
#ifndef LV_SHADOW_CACHE_SIZE
#define LV_SHADOW_CACHE_SIZE    0
#endif
#endif

/* 1: Use other blend modes than normal (`LV_BLEND_MODE_...`)*/
#ifndef LV_USE_BLEND_MODES
#define LV_USE_BLEND_MODES      1
#endif

/* 1: Use the `opa_scale` style property to set the opacity of an object and its children at once*/
#ifndef LV_USE_OPA_SCALE
#define LV_USE_OPA_SCALE        1
#endif

/* 1: Use image zoom and rotation*/
#ifndef LV_USE_IMG_TRANSFORM
#define LV_USE_IMG_TRANSFORM    1
#endif

/* 1: Enable object groups (for keyboard/encoder navigation) */
#ifndef LV_USE_GROUP
#define LV_USE_GROUP            1
#endif
#if LV_USE_GROUP
#endif  /*LV_USE_GROUP*/

/* 1: Enable GPU interface*/
#ifndef LV_USE_GPU
#define LV_USE_GPU              1   /*Only enables `gpu_fill_cb` and `gpu_blend_cb` in the disp. drv- */
#endif
#ifndef LV_USE_GPU_STM32_DMA2D
#define LV_USE_GPU_STM32_DMA2D  0
#endif

/* 1: Enable file system (might be required for images */
#ifndef LV_USE_FILESYSTEM
#define LV_USE_FILESYSTEM       1
#endif
#if LV_USE_FILESYSTEM
/*Declare the type of the user data of file system drivers (can be e.g. `void *`, `int`, `struct`)*/
#endif

/*1: Add a `user_data` to drivers and objects*/
#ifndef LV_USE_USER_DATA
#define LV_USE_USER_DATA        0
#endif

/*1: Show CPU usage and FPS count in the right bottom corner*/
#ifndef LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR     0
#endif

/*1: Use the functions and types from the older API if possible */
#ifndef LV_USE_API_EXTENSION_V6
#define LV_USE_API_EXTENSION_V6  1
#endif

/*========================
 * Image decoder and cache
 *========================*/

/* 1: Enable indexed (palette) images */
#ifndef LV_IMG_CF_INDEXED
#define LV_IMG_CF_INDEXED       1
#endif

/* 1: Enable alpha indexed images */
#ifndef LV_IMG_CF_ALPHA
#define LV_IMG_CF_ALPHA         1
#endif

/* Default image cache size. Image caching keeps the images opened.
 * If only the built-in image formats are used there is no real advantage of caching.
 * (I.e. no new image decoder is added)
 * With complex image decoders (e.g. PNG or JPG) caching can save the continuous open/decode of images.
 * However the opened images might consume additional RAM.
 * LV_IMG_CACHE_DEF_SIZE must be >= 1 */
#ifndef LV_IMG_CACHE_DEF_SIZE
#define LV_IMG_CACHE_DEF_SIZE       1
#endif

/*Declare the type of the user data of image decoder (can be e.g. `void *`, `int`, `struct`)*/

/*=====================
 *  Compiler settings
 *====================*/
/* Define a custom attribute to `lv_tick_inc` function */
#ifndef LV_ATTRIBUTE_TICK_INC
#define LV_ATTRIBUTE_TICK_INC
#endif

/* Define a custom attribute to `lv_task_handler` function */
#ifndef LV_ATTRIBUTE_TASK_HANDLER
#define LV_ATTRIBUTE_TASK_HANDLER
#endif

/* Define a custom attribute to `lv_disp_flush_ready` function */
#ifndef LV_ATTRIBUTE_FLUSH_READY
#define LV_ATTRIBUTE_FLUSH_READY
#endif

/* With size optimization (-Os) the compiler might not align data to
 * 4 or 8 byte boundary. This alignment will be explicitly applied where needed.
 * E.g. __attribute__((aligned(4))) */
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

/* Attribute to mark large constant arrays for example
 * font's bitmaps */
#ifndef LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_CONST
#endif

/* Prefix performance critical functions to place them into a faster memory (e.g RAM)
 * Uses 15-20 kB extra memory */
#ifndef LV_ATTRIBUTE_FAST_MEM
#define LV_ATTRIBUTE_FAST_MEM
#endif

/* Export integer constant to binding.
 * This macro is used with constants in the form of LV_<CONST> that
 * should also appear on lvgl binding API such as Micropython
 *
 * The default value just prevents a GCC warning.
 */
#ifndef LV_EXPORT_CONST_INT
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning
#endif

/*===================
 *  HAL settings
 *==================*/

/* 1: use a custom tick source.
 * It removes the need to manually update the tick with `lv_tick_inc`) */
#ifndef LV_TICK_CUSTOM
#define LV_TICK_CUSTOM     0
#endif
#if LV_TICK_CUSTOM == 1
#ifndef LV_TICK_CUSTOM_INCLUDE
#define LV_TICK_CUSTOM_INCLUDE  "something.h"       /*Header for the sys time function*/
#endif
#ifndef LV_TICK_CUSTOM_SYS_TIME_EXPR
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())     /*Expression evaluating to current systime in ms*/
#endif
#endif   /*LV_TICK_CUSTOM*/


/*================
 * Log settings
 *===============*/

/*1: Enable the log module*/
#ifndef LV_USE_LOG
#define LV_USE_LOG      0
#endif
#if LV_USE_LOG
/* How important log should be added:
 * LV_LOG_LEVEL_TRACE       A lot of logs to give detailed information
 * LV_LOG_LEVEL_INFO        Log important events
 * LV_LOG_LEVEL_WARN        Log if something unwanted happened but didn't cause a problem
 * LV_LOG_LEVEL_ERROR       Only critical issue, when the system may fail
 * LV_LOG_LEVEL_NONE        Do not log anything
 */
#ifndef LV_LOG_LEVEL
#  define LV_LOG_LEVEL    LV_LOG_LEVEL_WARN
#endif

/* 1: Print the log with 'printf';
 * 0: user need to register a callback with `lv_log_register_print_cb`*/
#ifndef LV_LOG_PRINTF
#  define LV_LOG_PRINTF   0
#endif
#endif  /*LV_USE_LOG*/

/*=================
 * Debug settings
 *================*/

/* If Debug is enabled LittelvGL validates the parameters of the functions.
 * If an invalid parameter is found an error log message is printed and
 * the MCU halts at the error. (`LV_USE_LOG` should be enabled)
 * If you are debugging the MCU you can pause
 * the debugger to see exactly where  the issue is.
 *
 * The behavior of asserts can be overwritten by redefining them here.
 * E.g. #define LV_ASSERT_MEM(p)  <my_assert_code>
 */
#ifndef LV_USE_DEBUG
#define LV_USE_DEBUG        1
#endif
#if LV_USE_DEBUG

/*Check if the parameter is NULL. (Quite fast) */
#ifndef LV_USE_ASSERT_NULL
#define LV_USE_ASSERT_NULL      1
#endif

/*Checks is the memory is successfully allocated or no. (Quite fast)*/
#ifndef LV_USE_ASSERT_MEM
#define LV_USE_ASSERT_MEM       1
#endif

/*Check the integrity of `lv_mem` after critical operations. (Slow)*/
#ifndef LV_USE_ASSERT_MEM_INTEGRITY
#define LV_USE_ASSERT_MEM_INTEGRITY       0
#endif

/* Check the strings.
 * Search for NULL, very long strings, invalid characters, and unnatural repetitions. (Slow)
 * If disabled `LV_USE_ASSERT_NULL` will be performed instead (if it's enabled) */
#ifndef LV_USE_ASSERT_STR
#define LV_USE_ASSERT_STR       0
#endif

/* Check NULL, the object's type and existence (e.g. not deleted). (Quite slow)
 * If disabled `LV_USE_ASSERT_NULL` will be performed instead (if it's enabled) */
#ifndef LV_USE_ASSERT_OBJ
#define LV_USE_ASSERT_OBJ       0
#endif

/*Check if the styles are properly initialized. (Fast)*/
#ifndef LV_USE_ASSERT_STYLE
#define LV_USE_ASSERT_STYLE     0
#endif

#endif /*LV_USE_DEBUG*/

/*==================
 *    FONT USAGE
 *===================*/

/* The built-in fonts contains the ASCII range and some Symbols with  4 bit-per-pixel.
 * The symbols are available via `LV_SYMBOL_...` defines
 * More info about fonts: https://docs.lvgl.com/#Fonts
 * To create a new font go to: https://lvgl.com/ttf-font-to-c-array
 */

/* Montserrat fonts with bpp = 4
 * https://fonts.google.com/specimen/Montserrat  */
#ifndef LV_FONT_MONTSERRAT_12
#define LV_FONT_MONTSERRAT_12    0
#endif
#ifndef LV_FONT_MONTSERRAT_14
#define LV_FONT_MONTSERRAT_14    0
#endif
#ifndef LV_FONT_MONTSERRAT_16
#define LV_FONT_MONTSERRAT_16    1
#endif
#ifndef LV_FONT_MONTSERRAT_18
#define LV_FONT_MONTSERRAT_18    0
#endif
#ifndef LV_FONT_MONTSERRAT_20
#define LV_FONT_MONTSERRAT_20    0
#endif
#ifndef LV_FONT_MONTSERRAT_22
#define LV_FONT_MONTSERRAT_22    0
#endif
#ifndef LV_FONT_MONTSERRAT_24
#define LV_FONT_MONTSERRAT_24    0
#endif
#ifndef LV_FONT_MONTSERRAT_26
#define LV_FONT_MONTSERRAT_26    0
#endif
#ifndef LV_FONT_MONTSERRAT_28
#define LV_FONT_MONTSERRAT_28    0
#endif
#ifndef LV_FONT_MONTSERRAT_30
#define LV_FONT_MONTSERRAT_30    0
#endif
#ifndef LV_FONT_MONTSERRAT_32
#define LV_FONT_MONTSERRAT_32    0
#endif
#ifndef LV_FONT_MONTSERRAT_34
#define LV_FONT_MONTSERRAT_34    0
#endif
#ifndef LV_FONT_MONTSERRAT_36
#define LV_FONT_MONTSERRAT_36    0
#endif
#ifndef LV_FONT_MONTSERRAT_38
#define LV_FONT_MONTSERRAT_38    0
#endif
#ifndef LV_FONT_MONTSERRAT_40
#define LV_FONT_MONTSERRAT_40    0
#endif
#ifndef LV_FONT_MONTSERRAT_42
#define LV_FONT_MONTSERRAT_42    0
#endif
#ifndef LV_FONT_MONTSERRAT_44
#define LV_FONT_MONTSERRAT_44    0
#endif
#ifndef LV_FONT_MONTSERRAT_46
#define LV_FONT_MONTSERRAT_46    0
#endif
#ifndef LV_FONT_MONTSERRAT_48
#define LV_FONT_MONTSERRAT_48    0
#endif

/* Demonstrate special features */
#ifndef LV_FONT_MONTSERRAT_12_SUBPX
#define LV_FONT_MONTSERRAT_12_SUBPX      0
#endif
#ifndef LV_FONT_MONTSERRAT_28_COMPRESSED
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0  /*bpp = 3*/
#endif
#ifndef LV_FONT_DEJAVU_16_PERSIAN_HEBREW
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0  /*Hebrew, Arabic, PErisan letters and all their forms*/
#endif
#ifndef LV_FONT_SIMSUN_16_CJK
#define LV_FONT_SIMSUN_16_CJK            0  /*1000 most common CJK radicals*/
#endif

/*Pixel perfect monospace font
 * http://pelulamu.net/unscii/ */
#ifndef LV_FONT_UNSCII_8
#define LV_FONT_UNSCII_8     0
#endif

/* Optionally declare your custom fonts here.
 * You can use these fonts as default font too
 * and they will be available globally. E.g.
 * #define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE(my_font_1) \
 *                                LV_FONT_DECLARE(my_font_2)
 */
#ifndef LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE
#endif

/* Enable it if you have fonts with a lot of characters.
 * The limit depends on the font size, font face and bpp
 * but with > 10,000 characters if you see issues probably you need to enable it.*/
#ifndef LV_FONT_FMT_TXT_LARGE
#define LV_FONT_FMT_TXT_LARGE   0
#endif

/* Set the pixel order of the display.
 * Important only if "subpx fonts" are used.
 * With "normal" font it doesn't matter.
 */
#ifndef LV_FONT_SUBPX_BGR
#define LV_FONT_SUBPX_BGR    0
#endif

/*Declare the type of the user data of fonts (can be e.g. `void *`, `int`, `struct`)*/

/*================
 *  THEME USAGE
 *================*/

/*Always enable at least on theme*/

/* No theme, you can apply your styles as you need
 * No flags. Set LV_THEME_DEFAULT_FLAG 0 */
#ifndef LV_USE_THEME_EMPTY
 #define LV_USE_THEME_EMPTY       1
#endif

/*Simple to the create your theme based on it
 * No flags. Set LV_THEME_DEFAULT_FLAG 0 */
#ifndef LV_USE_THEME_TEMPLATE
 #define LV_USE_THEME_TEMPLATE    1
#endif

/* A fast and impressive theme.
 * Flags:
 * LV_THEME_MATERIAL_FLAG_LIGHT: light theme
 * LV_THEME_MATERIAL_FLAG_DARK: dark theme*/
#ifndef LV_USE_THEME_MATERIAL
 #define LV_USE_THEME_MATERIAL    1
#endif

/* Mono-color theme for monochrome displays.
 * If LV_THEME_DEFAULT_COLOR_PRIMARY is LV_COLOR_BLACK the
 * texts and borders will be black and the background will be
 * white. Else the colors are inverted.
 * No flags. Set LV_THEME_DEFAULT_FLAG 0 */
#ifndef LV_USE_THEME_MONO
 #define LV_USE_THEME_MONO        1
#endif

#ifndef LV_THEME_DEFAULT_INCLUDE
#define LV_THEME_DEFAULT_INCLUDE            <stdint.h>      /*Include a header for the init. function*/
#endif
#ifndef LV_THEME_DEFAULT_INIT
#define LV_THEME_DEFAULT_INIT               lv_theme_material_init
#endif
#ifndef LV_THEME_DEFAULT_COLOR_PRIMARY
#define LV_THEME_DEFAULT_COLOR_PRIMARY      LV_COLOR_RED
#endif
#ifndef LV_THEME_DEFAULT_COLOR_SECONDARY
#define LV_THEME_DEFAULT_COLOR_SECONDARY    LV_COLOR_BLUE
#endif
#ifndef LV_THEME_DEFAULT_FLAG
#define LV_THEME_DEFAULT_FLAG               LV_THEME_MATERIAL_FLAG_LIGHT
#endif
#ifndef LV_THEME_DEFAULT_FONT_SMALL
#define LV_THEME_DEFAULT_FONT_SMALL         &lv_font_montserrat_16
#endif
#ifndef LV_THEME_DEFAULT_FONT_NORMAL
#define LV_THEME_DEFAULT_FONT_NORMAL        &lv_font_montserrat_16
#endif
#ifndef LV_THEME_DEFAULT_FONT_SUBTITLE
#define LV_THEME_DEFAULT_FONT_SUBTITLE      &lv_font_montserrat_16
#endif
#ifndef LV_THEME_DEFAULT_FONT_TITLE
#define LV_THEME_DEFAULT_FONT_TITLE         &lv_font_montserrat_16
#endif

/*=================
 *  Text settings
 *=================*/

/* Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 * */
#ifndef LV_TXT_ENC
#define LV_TXT_ENC LV_TXT_ENC_UTF8
#endif

 /*Can break (wrap) texts on these chars*/
#ifndef LV_TXT_BREAK_CHARS
#define LV_TXT_BREAK_CHARS                  " ,.;:-_"
#endif

/* If a word is at least this long, will break wherever "prettiest"
 * To disable, set to a value <= 0 */
#ifndef LV_TXT_LINE_BREAK_LONG_LEN
#define LV_TXT_LINE_BREAK_LONG_LEN          0
#endif

/* Minimum number of characters in a long word to put on a line before a break.
 * Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
#ifndef LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN  3
#endif

/* Minimum number of characters in a long word to put on a line after a break.
 * Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
#ifndef LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3
#endif

/* The control character to use for signaling text recoloring. */
#ifndef LV_TXT_COLOR_CMD
#define LV_TXT_COLOR_CMD "#"
#endif

/* Support bidirectional texts.
 * Allows mixing Left-to-Right and Right-to-Left texts.
 * The direction will be processed according to the Unicode Bidirectional Algorithm:
 * https://www.w3.org/International/articles/inline-bidi-markup/uba-basics*/
#ifndef LV_USE_BIDI
#define LV_USE_BIDI     0
#endif
#if LV_USE_BIDI
/* Set the default direction. Supported values:
 * `LV_BIDI_DIR_LTR` Left-to-Right
 * `LV_BIDI_DIR_RTL` Right-to-Left
 * `LV_BIDI_DIR_AUTO` detect texts base direction */
#ifndef LV_BIDI_BASE_DIR_DEF
#define LV_BIDI_BASE_DIR_DEF  LV_BIDI_DIR_AUTO
#endif
#endif

/* Enable Arabic/Persian processing
 * In these languages characters should be replaced with
 * an other form based on their position in the text */
#ifndef LV_USE_ARABIC_PERSIAN_CHARS
#define LV_USE_ARABIC_PERSIAN_CHARS 0
#endif

/*Change the built in (v)snprintf functions*/
#ifndef LV_SPRINTF_CUSTOM
#define LV_SPRINTF_CUSTOM   0
#endif
#if LV_SPRINTF_CUSTOM
#ifndef LV_SPRINTF_INCLUDE
#  define LV_SPRINTF_INCLUDE <stdio.h>
#endif
#ifndef lv_snprintf
#  define lv_snprintf     snprintf
#endif
#ifndef lv_vsnprintf
#  define lv_vsnprintf    vsnprintf
#endif
#else   /*!LV_SPRINTF_CUSTOM*/
#ifndef LV_SPRINTF_DISABLE_FLOAT
#  define LV_SPRINTF_DISABLE_FLOAT 1
#endif
#endif  /*LV_SPRINTF_CUSTOM*/

/*===================
 *  LV_OBJ SETTINGS
 *==================*/

#if LV_USE_USER_DATA
/*Declare the type of the user data of object (can be e.g. `void *`, `int`, `struct`)*/
/*Provide a function to free user data*/
#ifndef LV_USE_USER_DATA_FREE
#define LV_USE_USER_DATA_FREE 0
#endif
#if LV_USE_USER_DATA_FREE
#ifndef LV_USER_DATA_FREE_INCLUDE
#  define LV_USER_DATA_FREE_INCLUDE  "something.h"  /*Header for user data free function*/
#endif
/* Function prototype : void user_data_free(lv_obj_t * obj); */
#ifndef LV_USER_DATA_FREE
#  define LV_USER_DATA_FREE  (user_data_free)       /*Invoking for user data free function*/
#endif
#endif
#endif

/*1: enable `lv_obj_realign()` based on `lv_obj_align()` parameters*/
#ifndef LV_USE_OBJ_REALIGN
#define LV_USE_OBJ_REALIGN          1
#endif

/* Enable to make the object clickable on a larger area.
 * LV_EXT_CLICK_AREA_OFF or 0: Disable this feature
 * LV_EXT_CLICK_AREA_TINY: The extra area can be adjusted horizontally and vertically (0..255 px)
 * LV_EXT_CLICK_AREA_FULL: The extra area can be adjusted in all 4 directions (-32k..+32k px)
 */
#ifndef LV_USE_EXT_CLICK_AREA
#define LV_USE_EXT_CLICK_AREA  LV_EXT_CLICK_AREA_TINY
#endif

/*==================
 *  LV OBJ X USAGE
 *================*/
/*
 * Documentation of the object types: https://docs.lvgl.com/#Object-types
 */

/*Arc (dependencies: -)*/
#ifndef LV_USE_ARC
#define LV_USE_ARC      1
#endif

/*Bar (dependencies: -)*/
#ifndef LV_USE_BAR
#define LV_USE_BAR      1
#endif

/*Button (dependencies: lv_cont*/
#ifndef LV_USE_BTN
#define LV_USE_BTN      1
#endif

/*Button matrix (dependencies: -)*/
#ifndef LV_USE_BTNMATRIX
#define LV_USE_BTNMATRIX     1
#endif

/*Calendar (dependencies: -)*/
#ifndef LV_USE_CALENDAR
#define LV_USE_CALENDAR 1
#endif

/*Canvas (dependencies: lv_img)*/
#ifndef LV_USE_CANVAS
#define LV_USE_CANVAS   1
#endif

/*Check box (dependencies: lv_btn, lv_label)*/
#ifndef LV_USE_CHECKBOX
#define LV_USE_CHECKBOX       1
#endif

/*Chart (dependencies: -)*/
#ifndef LV_USE_CHART
#define LV_USE_CHART    1
#endif
#if LV_USE_CHART
#ifndef LV_CHART_AXIS_TICK_LABEL_MAX_LEN
#  define LV_CHART_AXIS_TICK_LABEL_MAX_LEN    256
#endif
#endif

/*Container (dependencies: -*/
#ifndef LV_USE_CONT
#define LV_USE_CONT     1
#endif

/*Color picker (dependencies: -*/
#ifndef LV_USE_CPICKER
#define LV_USE_CPICKER   1
#endif

/*Drop down list (dependencies: lv_page, lv_label, lv_symbol_def.h)*/
#ifndef LV_USE_DROPDOWN
#define LV_USE_DROPDOWN    1
#endif
#if LV_USE_DROPDOWN != 0
/*Open and close default animation time [ms] (0: no animation)*/
#ifndef LV_DROPDOWN_DEF_ANIM_TIME
#  define LV_DROPDOWN_DEF_ANIM_TIME     200
#endif
#endif

/*Gauge (dependencies:lv_bar, lv_linemeter)*/
#ifndef LV_USE_GAUGE
#define LV_USE_GAUGE    1
#endif

/*Image (dependencies: lv_label*/
#ifndef LV_USE_IMG
#define LV_USE_IMG      1
#endif

/*Image Button (dependencies: lv_btn*/
#ifndef LV_USE_IMGBTN
#define LV_USE_IMGBTN   1
#endif
#if LV_USE_IMGBTN
/*1: The imgbtn requires left, mid and right parts and the width can be set freely*/
#ifndef LV_IMGBTN_TILED
#  define LV_IMGBTN_TILED 0
#endif
#endif

/*Keyboard (dependencies: lv_btnm)*/
#ifndef LV_USE_KEYBOARD
#define LV_USE_KEYBOARD       1
#endif

/*Label (dependencies: -*/
#ifndef LV_USE_LABEL
#define LV_USE_LABEL    1
#endif
#if LV_USE_LABEL != 0
/*Hor, or ver. scroll speed [px/sec] in 'LV_LABEL_LONG_ROLL/ROLL_CIRC' mode*/
#ifndef LV_LABEL_DEF_SCROLL_SPEED
#  define LV_LABEL_DEF_SCROLL_SPEED       25
#endif

/* Waiting period at beginning/end of animation cycle */
#ifndef LV_LABEL_WAIT_CHAR_COUNT
#  define LV_LABEL_WAIT_CHAR_COUNT        3
#endif

/*Enable selecting text of the label */
#ifndef LV_LABEL_TEXT_SEL
#  define LV_LABEL_TEXT_SEL               0
#endif

/*Store extra some info in labels (12 bytes) to speed up drawing of very long texts*/
#ifndef LV_LABEL_LONG_TXT_HINT
#  define LV_LABEL_LONG_TXT_HINT          0
#endif
#endif

/*LED (dependencies: -)*/
#ifndef LV_USE_LED
#define LV_USE_LED      1
#endif
#if LV_USE_LED
#ifndef LV_LED_BRIGHT_MIN
#  define LV_LED_BRIGHT_MIN  120      /*Minimal brightness*/
#endif
#ifndef LV_LED_BRIGHT_MAX
#  define LV_LED_BRIGHT_MAX  255     /*Maximal brightness*/
#endif
#endif

/*Line (dependencies: -*/
#ifndef LV_USE_LINE
#define LV_USE_LINE     1
#endif

/*List (dependencies: lv_page, lv_btn, lv_label, (lv_img optionally for icons ))*/
#ifndef LV_USE_LIST
#define LV_USE_LIST     1
#endif
#if LV_USE_LIST != 0
/*Default animation time of focusing to a list element [ms] (0: no animation)  */
#ifndef LV_LIST_DEF_ANIM_TIME
#  define LV_LIST_DEF_ANIM_TIME  100
#endif
#endif

/*Line meter (dependencies: *;)*/
#ifndef LV_USE_LINEMETER
#define LV_USE_LINEMETER   1
#endif
#if LV_USE_LINEMETER
/* Draw line more precisely at cost of performance.
 * Useful if there are lot of lines any minor are visible
 * 0: No extra precision
 * 1: Some extra precision
 * 2: Best precision
 */
#ifndef LV_LINEMETER_PRECISE
#  define LV_LINEMETER_PRECISE    0
#endif
#endif

/*Mask (dependencies: -)*/
#ifndef LV_USE_OBJMASK
#define LV_USE_OBJMASK  1
#endif

/*Message box (dependencies: lv_rect, lv_btnm, lv_label)*/
#ifndef LV_USE_MSGBOX
#define LV_USE_MSGBOX     1
#endif

/*Page (dependencies: lv_cont)*/
#ifndef LV_USE_PAGE
#define LV_USE_PAGE     1
#endif
#if LV_USE_PAGE != 0
/*Focus default animation time [ms] (0: no animation)*/
#ifndef LV_PAGE_DEF_ANIM_TIME
#  define LV_PAGE_DEF_ANIM_TIME     400
#endif
#endif

/*Preload (dependencies: lv_arc, lv_anim)*/
#ifndef LV_USE_SPINNER
#define LV_USE_SPINNER      1
#endif
#if LV_USE_SPINNER != 0
#ifndef LV_SPINNER_DEF_ARC_LENGTH
#  define LV_SPINNER_DEF_ARC_LENGTH   60      /*[deg]*/
#endif
#ifndef LV_SPINNER_DEF_SPIN_TIME
#  define LV_SPINNER_DEF_SPIN_TIME    1000    /*[ms]*/
#endif
#ifndef LV_SPINNER_DEF_ANIM
#  define LV_SPINNER_DEF_ANIM         LV_SPINNER_TYPE_SPINNING_ARC
#endif
#endif

/*Roller (dependencies: lv_ddlist)*/
#ifndef LV_USE_ROLLER
#define LV_USE_ROLLER    1
#endif
#if LV_USE_ROLLER != 0
/*Focus animation time [ms] (0: no animation)*/
#ifndef LV_ROLLER_DEF_ANIM_TIME
#  define LV_ROLLER_DEF_ANIM_TIME     200
#endif

/*Number of extra "pages" when the roller is infinite*/
#ifndef LV_ROLLER_INF_PAGES
#  define LV_ROLLER_INF_PAGES         7
#endif
#endif

/*Slider (dependencies: lv_bar)*/
#ifndef LV_USE_SLIDER
#define LV_USE_SLIDER    1
#endif

/*Spinbox (dependencies: lv_ta)*/
#ifndef LV_USE_SPINBOX
#define LV_USE_SPINBOX       1
#endif

/*Switch (dependencies: lv_slider)*/
#ifndef LV_USE_SWITCH
#define LV_USE_SWITCH       1
#endif

/*Text area (dependencies: lv_label, lv_page)*/
#ifndef LV_USE_TEXTAREA
#define LV_USE_TEXTAREA       1
#endif
#if LV_USE_TEXTAREA != 0
#ifndef LV_TEXTAREA_DEF_CURSOR_BLINK_TIME
#  define LV_TEXTAREA_DEF_CURSOR_BLINK_TIME 400     /*ms*/
#endif
#ifndef LV_TEXTAREA_DEF_PWD_SHOW_TIME
#  define LV_TEXTAREA_DEF_PWD_SHOW_TIME     1500    /*ms*/
#endif
#endif

/*Table (dependencies: lv_label)*/
#ifndef LV_USE_TABLE
#define LV_USE_TABLE    1
#endif
#if LV_USE_TABLE
#ifndef LV_TABLE_COL_MAX
#  define LV_TABLE_COL_MAX    12
#endif
#endif

/*Tab (dependencies: lv_page, lv_btnm)*/
#ifndef LV_USE_TABVIEW
#define LV_USE_TABVIEW      1
#endif
#  if LV_USE_TABVIEW != 0
/*Time of slide animation [ms] (0: no animation)*/
#ifndef LV_TABVIEW_DEF_ANIM_TIME
#  define LV_TABVIEW_DEF_ANIM_TIME    300
#endif
#endif

/*Tileview (dependencies: lv_page) */
#ifndef LV_USE_TILEVIEW
#define LV_USE_TILEVIEW     1
#endif
#if LV_USE_TILEVIEW
/*Time of slide animation [ms] (0: no animation)*/
#ifndef LV_TILEVIEW_DEF_ANIM_TIME
#  define LV_TILEVIEW_DEF_ANIM_TIME   300
#endif
#endif

/*Window (dependencies: lv_cont, lv_btn, lv_label, lv_img, lv_page)*/
#ifndef LV_USE_WIN
#define LV_USE_WIN      1
#endif

/*==================
 * Non-user section
 *==================*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)    /* Disable warnings for Visual Studio*/
#ifndef _CRT_SECURE_NO_WARNINGS
#  define _CRT_SECURE_NO_WARNINGS
#endif
#endif


#endif  /*LV_CONF_CHECKER_H*/
