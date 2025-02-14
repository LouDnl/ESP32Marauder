#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\lv_arduino\\src\\src\\lv_gpu\\lv_gpu_stm32_dma2d.h"
/**
 * @file lv_gpu_stm32_dma2d.h
 *
 */

#ifndef LV_GPU_STM32_DMA2D_H
#define LV_GPU_STM32_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_misc/lv_area.h"
#include "../lv_misc/lv_color.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Fill an area in the buffer with a color
 * @param buf a buffer which should be filled
 * @param buf_w width of the buffer in pixels
 * @param color fill color
 * @param fill_w width to fill in pixels (<= buf_w)
 * @param fill_h height to fill in pixels
 * @note `buf_w - fill_w` is offset to the next line after fill
 */
void lv_gpu_stm32_dma2d_fill(lv_color_t * buf, lv_coord_t buf_w, lv_color_t color, lv_coord_t fill_w,
                             lv_coord_t fill_h);


/**
 * Fill an area in the buffer with a color but take into account a mask which describes the opacity of each pixel
 * @param buf a buffer which should be filled using a mask
 * @param buf_w width of the buffer in pixels
 * @param color fill color
 * @param mask 0..255 values describing the opacity of the corresponding pixel. It's width is `fill_w`
 * @param opa overall opacity. 255 in `mask` should mean this opacity.
 * @param fill_w width to fill in pixels (<= buf_w)
 * @param fill_h height to fill in pixels
 * @note `buf_w - fill_w` is offset to the next line after fill
 */
void lv_gpu_stm32_dma2d_fill_mask(lv_color_t * buf, lv_coord_t buf_w, lv_color_t color, const lv_opa_t * mask,
                                  lv_opa_t opa, lv_coord_t fill_w, lv_coord_t fill_h);

/**
 * Copy a map (typically RGB image) to a buffer
 * @param buf a buffer where map should be copied
 * @param buf_w width of the buffer in pixels
 * @param map an "image" to copy
 * @param map_w width of the map in pixels
 * @param copy_w width of the area to copy in pixels (<= buf_w)
 * @param copy_h height of the area to copy in pixels
 * @note `map_w - fill_w` is offset to the next line after copy
 */
void lv_gpu_stm32_dma2d_copy(lv_color_t * buf, lv_coord_t buf_w, const lv_color_t * map, lv_coord_t map_w,
                             lv_coord_t copy_w, lv_coord_t copy_h);
/**
 * Blend a map (e.g. ARGB image or RGB image with opacity) to a buffer
 * @param buf a buffer where `map` should be copied
 * @param buf_w width of the buffer in pixels
 * @param map an "image" to copy
 * @param opa opacity of `map`
 * @param map_w width of the map in pixels
 * @param copy_w width of the area to copy in pixels (<= buf_w)
 * @param copy_h height of the area to copy in pixels
 * @note `map_w - fill_w` is offset to the next line after copy
 */
void lv_gpu_stm32_dma2d_blend(lv_color_t * buf, lv_coord_t buf_w, const lv_color_t * map, lv_opa_t opa,
                              lv_coord_t map_w, lv_coord_t copy_w, lv_coord_t copy_h);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GPU_STM32_DMA2D_H*/
