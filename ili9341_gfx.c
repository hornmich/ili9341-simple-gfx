/*
 * Simple and slow graphic library without frame buffer.
 *
 * Author: Michal Horn
 */

#include "ili9341-gfx.h"

bool _ili_sgfx_is_pos_correct(const coord_2d_t* top_left, const coord_2d_t* bottom_right) {
	return top_left->x <= bottom_right->x && top_left->y <= bottom_right->y;
}

bool _ili_sgfx_fits_to_screen() {
	return true;
}

void _ili_sgfx_swap_coords(coord_2d_t* c1, coord_2d_t* c2) {
	coord_2d_t tmp;
	tmp.x = c1->x;
	tmp.y = c1->y;
	c1->x = c2->x;
	c1->y = c2->y;
	c2->x = tmp.x;
	c2->y = tmp.y;
}

/* Public functions definition */

void ili_sgfx_clear_screen(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush) {
	coord_2d_t top_left, bottom_right;
	top_left.x = 0;
	top_left.y = 0;
	bottom_right.x = ili9341_get_screen_width(desc);
	bottom_right.y = ili9341_get_screen_height(desc);
	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_fill_region(desc, brush->bg_color);
}


void ili_sgfx_draw_v_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, int16_t lenght) {
	coord_2d_t top_left, bottom_right;
	if (lenght > 0) {
		lenght -= 1;
	}
	else {
		lenght += 1;
	}
	if (brush->size > 1) {
		if (brush->size%2) {
			top_left.x = start.x - brush->size/2;
		}
		else {
			top_left.x = start.x - (brush->size/2-1);
		}
	}
	else {
		top_left.x = start.x;
	}
	top_left.y = start.y;

	bottom_right.x = start.x + brush->size/2;
	bottom_right.y = start.y + lenght;

	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_fill_region(desc, brush->fg_color);
}

void ili_sgfx_draw_h_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, int16_t lenght) {
	coord_2d_t top_left, bottom_right;
	if (lenght > 0) {
		lenght -= 1;
	}
	else {
		lenght += 1;
	}

	top_left.x = start.x;
	if (brush->size > 1) {
		if (brush->size%2) {
			top_left.y = start.y - brush->size/2;
		}
		else {
			top_left.y = start.y - (brush->size/2-1);
		}
	}
	else {
		top_left.y = start.y;
	}
	bottom_right.x = start.x + lenght;
	bottom_right.y = start.y + brush->size/2;

	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_fill_region(desc, brush->fg_color);
}

void ili_sgfx_draw_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, coord_2d_t end) {
	coord_2d_t coord = start;
	if (start.x > end.x) {
		uint16_t tmp = start.x;
		start.x = end.x;
		end.x = tmp;
	}
	if (start.y > end.y) {
		uint16_t tmp = start.y;
		start.y = end.y;
		end.y = tmp;
	}

	int dx = end.x - start.x;
	int dy = end.y - start.y;
	for (coord.x = start.x; coord.x < end.x; coord.x++) {
		coord.y = start.y + dy*(coord.x - start.x) / dx;
		ili_sgfx_draw_pixel(desc, brush, coord);
	}
}

void ili_sgfx_draw_rect(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t top_left, coord_2d_t bottom_right) {
	uint8_t width = bottom_right.x - top_left.x+1;
	uint8_t height = bottom_right.y - top_left.y+1;

	ili_sgfx_draw_v_line(desc, brush, top_left, height);
	ili_sgfx_draw_v_line(desc, brush, bottom_right, -height);

	if (brush->size > 1) {
		if (brush->size%2) {
			top_left.x -= brush->size / 2;
			bottom_right.x += brush->size / 2;

		}
		else {
			top_left.x -= (brush->size / 2 - 1);
			bottom_right.x += (brush->size / 2);
		}
	}
	width = bottom_right.x - top_left.x+1;
	height = bottom_right.y - top_left.y+1;
	ili_sgfx_draw_h_line(desc, brush, top_left, width);
	ili_sgfx_draw_h_line(desc, brush, bottom_right, -width);
}


void ili_sgfx_draw_filled_rect(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t top_left, coord_2d_t bottom_right) {
	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_fill_region(desc, brush->fg_color);
	top_left.x += brush->size;
	top_left.y += brush->size;
	bottom_right.x -= brush->size;
	bottom_right.y -= brush->size;
	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_fill_region(desc, brush->bg_color);
}


void ili_sgfx_draw_rect_round(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t radius, coord_2d_t start, coord_2d_t end) {

}


void ili_sgfx_draw_circle(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t radius, coord_2d_t center) {

}


void ili_sgfx_draw_filled_circle(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t border, uint8_t radius, coord_2d_t start) {

}


void ili_sgfx_draw_pixel(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord) {
	ili9341_set_region(desc, coord, coord);
	ili9341_fill_region(desc, brush->fg_color);
}


void ili_sgfx_draw_mono_bitmap(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_mono_bmp_t* bmp, bool transparent) {

	uint32_t size = bmp->height*bmp->width;

	if (transparent) {
		/* Slow, but will act as transparent. */
		coord_2d_t position = coord;
		for (uint32_t i = 0; i < size; i++) {
			uint8_t offset = i%8;
			uint32_t index = i/8;
			bool is_pixel = bmp->data[index] & (1<<(offset));
			if (is_pixel) {
				ili_sgfx_draw_pixel(desc, brush, position);
			}
			if (position.x >= coord.x + bmp->width) {
				position.x = coord.x;
				position.y++;
			}
		}
	}
	else {
		const uint32_t BUFFER_SIZE = 1024;
		uint8_t buffer[BUFFER_SIZE];
		coord_2d_t top_left, bottom_right;
		top_left = coord;
		bottom_right.x = top_left.x + bmp->width;
		bottom_right.y = top_left.y + bmp->height;
		uint8_t bg_color_lsb = brush->bg_color&0xFF;
		uint8_t bg_color_msb = (brush->bg_color>>8)&0xFF;
		uint8_t fg_color_lsb = brush->fg_color&0xFF;
		uint8_t fg_color_msb = (brush->fg_color>>8)&0xFF;

		ili9341_set_region(desc, top_left, bottom_right);
		uint32_t segments_cnt = size / BUFFER_SIZE;
		uint32_t remaining_size = size % BUFFER_SIZE;
		uint32_t imi = 0;

		for (uint32_t segment = 0; segment < segments_cnt; segment++) {
			for (uint32_t bi = 0; bi < BUFFER_SIZE; bi+=2, imi++) {
				uint8_t offset = imi%8;
				uint32_t index = imi/8;
				bool is_pixel = bmp->data[index] & (1<<(offset));
				if (is_pixel) {
					buffer[bi] = fg_color_msb;
					buffer[bi+1] = fg_color_lsb;
				}
				else {
					buffer[bi] = bg_color_msb;
					buffer[bi+1] = bg_color_lsb;
				}
			}
			ili9341_draw_RGB565_dma(desc, buffer, BUFFER_SIZE);
		}
		for (uint32_t bi = 0; bi < remaining_size; bi+=2, imi++) {
			uint8_t offset = imi%8;
			uint32_t index = imi/8;
			bool is_pixel = bmp->data[index] & (1<<(offset));
			if (is_pixel) {
				buffer[bi] = fg_color_msb;
				buffer[bi+1] = fg_color_lsb;
			}
			else {
				buffer[bi] = bg_color_msb;
				buffer[bi+1] = bg_color_lsb;
			}
		}
		ili9341_draw_RGB565_dma(desc, buffer, remaining_size);
	}
}


void ili_sgfx_draw_RGB565_bitmap(const ili9341_desc_ptr_t desc, coord_2d_t coord, const ili_sgfx_rgb565_bmp_t* bmp) {
	coord_2d_t top_left, bottom_right;
	top_left = coord;
	bottom_right.x = top_left.x + bmp->width;
	bottom_right.y = top_left.y + bmp->height;
	uint32_t size = bmp->height*bmp->width;

	ili9341_set_region(desc, top_left, bottom_right);
	ili9341_draw_RGB565_dma(desc, bmp->data, size);
}


uint8_t ili_sgfx_putc(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_font_t* font, bool transparent, wchar_t c) {

}


uint8_t ili_sgfx_printf(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_font_t* font, bool transparent, const wchar_t *format, ...) {

}

