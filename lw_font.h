/*
 * ili9341_font.h
 *
 *  Created on: 20. 7. 2020
 *      Author: E9990291
 */

#ifndef LW_FONT_H_
#define LW_FONT_H_

#include "stdint.h"
#include "stdbool.h"
#include "wchar.h"

typedef struct {
	const uint8_t width;
	const uint8_t offset_x;
	const uint8_t offset_y;
	const uint8_t rect_x;
	const uint8_t rect_y;
	const uint8_t rect_w;
	const uint8_t rect_h;
} lw_char_def_t;

typedef struct {
	const wchar_t char_key;
	const lw_char_def_t char_def;
} lw_char_map_t;

typedef struct {
	const char* family;
	const char* style;
	const uint8_t size;
	const uint8_t height;
	const lw_char_map_t* characters;
	const uint16_t chars_cnt;
	const uint8_t* pixmap_data;
	const uint16_t pixmap_width;
	const uint16_t pixmap_height;
	const bool pixmap_inv;
} lw_font_t;

#endif /* LW_FONT_H_ */
