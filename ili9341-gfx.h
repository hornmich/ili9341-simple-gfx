/*
 * Simple and slow graphic library without frame buffer.
 *
 * Author: Michal Horn
 */

#ifndef ILI9341_GFX_H_
#define ILI9341_GFX_H_

#include <ili9341.h>

/**
 * Definition of brush.
 */
typedef struct {
	uint16_t bg_color; ///< Color used as background (clearing, filling)
	uint16_t fg_color; ///< Color used for drawing (lines, borders)
	uint8_t size; ///< Thickness of the line
} ili_sgfx_brush_t;

typedef struct {
	uint8_t* data;	///< Glib pixmap data
	uint8_t width;	///< Image width
	uint8_t height; ///< Image height
	bool inverted;  ///< Pixmap data inverted
} ili_sgfx_pixmap_t;

typedef struct {
	uint8_t* data;
	uint8_t width;
	uint8_t height;
} ili_sgfx_rgb565_bmp_t;

typedef struct {

} ili_sgfx_font_t;

/**
 * Clear the screen with background color.
 *
 * Line thickness does not have any effect.
 * Background color defines screen filling color.
 * Foreground color does not have any effect.
 *
 * @param [in] desc Display driver instalce.
 * @param [in] brush Brush to clear the screen.
 */
void ili_sgfx_clear_screen(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush);

/**
 * Draw vertical line with foreground color.
 *
 * Line thickness defines thickness of the line.
 * Background color does not have any effect.
 * Foreground color defines line color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] start Starting coordinates.
 * @param [in] length Length of the line.
 */
void ili_sgfx_draw_v_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, int16_t lenght);

/**
 * Draw horizontal line with foreground color.
 *
 * Line thickness defines thickness of the line.
 * Background color does not have any effect.
 * Foreground color defines line color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] start Starting coordinates.
 * @param [in] length Length of the line.
 */
void ili_sgfx_draw_h_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, int16_t lenght);

/**
 * Draw line with foreground color.
 *
 * This is very slow, use cautiously.
 *
 * Line thickness does not have any effect.
 * Background color does not have any effect.
 * Foreground color defines line color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] start Starting coordinates.
 * @param [in] end Ending coordinates.
 */
void ili_sgfx_draw_line(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t start, coord_2d_t end);

/**
 * Draw rectangle with foreground color.
 *
 * The function is tolerant to swapping the coordinates. It always draws rectangle defined
 * Sby the coordinates even when top/bottom/left/right is mixed.
 *
 * Line thickness defines thickness of the border.
 * Background color does not have any effect.
 * Foreground color defines border color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] top_left Top left corner of the rectangle
 * @param [in] bottom_right Bottom right corner of the rectangle
 */
void ili_sgfx_draw_rect(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t top_left, coord_2d_t bottom_right);

/**
 * Draw rectangle by foreground color, filled by background color.
 *
 * The function is tolerant to swapping the coordinates. It always draws rectangle defined
 * Sby the coordinates even when top/bottom/left/right is mixed.
 *
 * Line thickness defines thickness of the border.
 * Background color defines filling color.
 * Foreground color defines border color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] top_left Top left corner of the rectangle
 * @param [in] bottom_right Bottom right corner of the rectangle
 */
void ili_sgfx_draw_filled_rect(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t top_left, coord_2d_t bottom_right);

/**
 * Draw rectangle by foreground color, with round corners.
 *
 * The function is tolerant to swapping the coordinates. It always draws rectangle defined
 * Sby the coordinates even when top/bottom/left/right is mixed.
 *
 * NOT YET IMPLEMENTED
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] radius Corners radius.
 * @param [in] top_left Top left corner of the rectangle
 * @param [in] bottom_right Bottom right corner of the rectangle
 */
void ili_sgfx_draw_rect_round(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t radius, coord_2d_t start, coord_2d_t end);

/**
 * Draw circle by foreground color
 *
 * NOT YET IMPLEMENTED
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] radius Corners radius.
 * @param [in] center Center
 */
void ili_sgfx_draw_circle(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t radius, coord_2d_t center);

/**
 * Draw circle by foreground color, filled by background color
 *
 * NOT YET IMPLEMENTED
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] radius Corners radius.
 * @param [in] center Center
 */
void ili_sgfx_draw_filled_circle(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, uint8_t radius, coord_2d_t center);

/**
 * Draw single pixel by foreground color.
 *
 * Line thickness does not have any effect.
 * Background color does not have any effect.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw the line screen.
 * @param [in] coord Pixel coordinates
 */
void ili_sgfx_draw_pixel(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord);

/**
 * Draw pixmap (1b depth bitmap) image.
 *
 * Function draws pixmap to specified position with brush foreground color.
 *
 * The expected bitmap format is GLIB pixmap. Check out https://www.silabs.com/community/wireless/proprietary/knowledge-base.entry.html/2019/02/14/creating_monochrome-ICUo
 * to learn how to generate pixmap sources.
 *
 * NOTE: The inverted parameter of the ili_sgfx_pixmap_t can be used to invert "on/off" pixels.
 *
 * If transparent parameter is set to True, The drawing will be much slower, but the pixels that should
 * be "off" or "low" will be ignored, thus preserving the previously drawn images in that area.
 * If the transparent parameter is set to False, the "off" or "low" pixels will be drawn with the background
 * color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw pixmap. Foreground color used for "on/high" pixels, Background color used for "off/low" pixels, if transparent is not True.
 * @param [in] coord Top left corner from where the pixmap is drawn.
 * @param [in] bmp Pixmap to be drawn.
 * @param [in] transparent If True, then only "on/high" pixels will be drawn, which will make the procedure time consuming, but will preserve original background. If False, the foreground brush color will be used to draw "off/low" pixels.
 */
void ili_sgfx_draw_pixmap(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_pixmap_t* pixm, bool transparent);

/**
 * Draw rectangular part of larger pixmap.
 *
 * Function draws rectangular clip of larger pixmap to specified position with brush foreground color.
 *
 * If the clip size does not fit into the original image, the remainig image data will be filled with the last fitting pixel.
 *
 * The maximal size of the clip is defined by MAX_RECT_SIZE macro.
 *
 * The expected bitmap format is GLIB pixmap. Check out https://www.silabs.com/community/wireless/proprietary/knowledge-base.entry.html/2019/02/14/creating_monochrome-ICUo
 * to learn how to generate pixmap sources.
 *
 * NOTE: The inverted parameter of the ili_sgfx_pixmap_t can be used to invert "on/off" pixels.
 *
 * If transparent parameter is set to True, The drawing will be much slower, but the pixels that should
 * be "off" or "low" will be ignored, thus preserving the previously drawn images in that area.
 * If the transparent parameter is set to False, the "off" or "low" pixels will be drawn with the background
 * color.
 *
 * @param [in] desc Display driver instance.
 * @param [in] brush Brush to draw pixmap. Foreground color used for "on/high" pixels, Background color used for "off/low" pixels, if transparent is not True.
 * @param [in] coord Top left corner from where the pixmap is drawn.
 * @param [in] bmp Pixmap to be drawn.
 * @param [in] transparent If True, then only "on/high" pixels will be drawn, which will make the procedure time consuming, but will preserve original background. If False, the foreground brush color will be used to draw "off/low" pixels.
 */
void ili_sgfx_draw_pixmap_rect(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, const ili_sgfx_pixmap_t* pixm, bool transparent, coord_2d_t dest_coord, coord_2d_t src_coord, uint16_t width, uint16_t height);

/**
 *
 */
void ili_sgfx_draw_RGB565_bitmap(const ili9341_desc_ptr_t desc, coord_2d_t coord, const ili_sgfx_rgb565_bmp_t* bmp);

/**
 * NOT YET IMPLEMENTED
 */
uint8_t ili_sgfx_putc(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_font_t* font, bool transparent, wchar_t c);

/**
 * NOT YET IMPLEMENTED
 */
uint8_t ili_sgfx_printf(const ili9341_desc_ptr_t desc, const ili_sgfx_brush_t* brush, coord_2d_t coord, const ili_sgfx_font_t* font, bool transparent, const wchar_t *format, ...);

#endif /* ILI9341_GFX_H_ */
