#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\lv_arduino\\src\\src\\lv_draw\\lv_draw_arc.h"
/**
 * @file lv_draw_arc.h
 *
 */

#ifndef LV_DRAW_ARC_H
#define LV_DRAW_ARC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_line.h"

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
 * Draw an arc. (Can draw pie too with great thickness.)
 * @param center_x the x coordinate of the center of the arc
 * @param center_y the y coordinate of the center of the arc
 * @param radius the radius of the arc
 * @param mask the arc will be drawn only in this mask
 * @param start_angle the start angle of the arc (0 deg on the bottom, 90 deg on the right)
 * @param end_angle the end angle of the arc
 * @param style style of the arc (`body.thickness`, `body.main_color`, `body.opa` is used)
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_arc(lv_coord_t center_x, lv_coord_t center_y, uint16_t radius,  uint16_t start_angle, uint16_t end_angle,
                 const lv_area_t * clip_area, lv_draw_line_dsc_t * dsc);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_ARC*/
