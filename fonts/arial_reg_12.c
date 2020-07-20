/*
 * arial_reg_12.c
 *
 *  Created on: 20. 7. 2020
 *      Author: E9990291
 */

#include "lw_font.h"
#include "arial_reg_12_img.h"

#define FONT_ARIAL_REG_12_CNT  3
/*
 * !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ÄÖÜßäöü
 */
const lw_char_map_t chars_arial_reg_12[FONT_ARIAL_REG_12_CNT] = {
		{.char_key = L' ', .char_def = {.width = 4, .offset_x = 0, .offset_y = 15, .rect_x = 1, .rect_y = 14, .rect_w = 0, .rect_h = 0}},
		{.char_key = L'!', .char_def = {.width = 6, .offset_x = 2, .offset_y = 3, .rect_x = 2, .rect_y = 2, .rect_w = 1, .rect_h = 12}},
		{.char_key = L'#', .char_def = {.width = 11, .offset_x = 1, .offset_y = 3, .rect_x = 9, .rect_y = 2, .rect_w = 9, .rect_h = 12}},
};

const lw_font_t font_arial_reg_12 = {
	.family = "Arial",
	.size = 12,
	.height = 18,
	.style = "Regular",
	.chars_cnt = FONT_ARIAL_REG_12_CNT,
	.characters = chars_arial_reg_12,
	.pixmap_data = arial_reg_12_bits,
	.pixmap_width = ARIAL_REG_12_WIDTH,
	.pixmap_height = ARIAL_REG_12_HEIGHT,
	.pixmap_inv = true
};
