# ili9341-simple-gfx
Basic graphics library for [ILI9341 SPI]() driven displays, using no frame buffer.

## Features

This is a basic library for drawing simple shapes and images. The library is designed 
to be used together with the [ili9341-spi-driver]().

The library is using a concept called *brush*. Brush defines the colors used for foreground
and background and line thickness.

The following features are implemented:

* Clear screen
* Draw horizotal/vertical line
* Draw rectangle
* Draw filled rectangle
* Draw single pixel
* Draw general line (other then horizotal/vertical)
* Draw pixmap (1b color depth image)
* Draw RGB565 bitmap (16b color depth image)
* Put UTF-8 characters on screen
* Print UTF-8 strings on screen

### Clear screen

Clears the whole screen with the brush background color.

### Draw horizotal/vertical line 

Draws straight vertical or horizontal line with the brush foreground color.
For horizotal/vertical lines this is preferable over slow **Draw general line**

### Draw rectangle

Draws rectangle (not filled, border only) with the brush foreground color and line thickness.
The filling of the rectangle is left untouched - is transparent to the background.

### Draw filled rectangle

Draws rectangle with border lines of foreground color and brush thickness, filled with the background color.

### Draw single pixel

Draws a single pixel with the brush foreground color.

### Draw general line

Draws straight line from one point to another. Is suitable for a general line, but is quite slow.
For horizontal/vertical lines much faster **Draw horizotal/vertical line** is preferable.

### Draw pixmap

Draws pixmap. ON pixels are drawn with the foreground color, OFF pixel can be either drawn by background
color (fast) or left as transparent (slow).

### Draw RGB565 bitmap

Draws 16b RGB565 bitmap.

### Put UTF-8 character

Draws lw-font generated pixmap character on the screen coordinates.

### Print UTF-8 strings

Prints formated string in a C printf fashion from lw-font generated pixmap font on the screen coordinates.

## Usage

Installing and running the driver consists of the follwing steps:
* Install and setup the [ili9341-spi-driver](https://github.com/hornmich/ili9341-spi-driver)
* Clone the repository to your project, possibly as a submodule for easy updating.
* Register the path to the *ili9341-gfx.h* header file to your toolchain
* Include the main header file ili9341-gfx.h
* Use it.

The possible usage may look like that:

    #include "ili9341.h"
    #include "ili9341-gfx.h"


    /* Handler functions required by ILI9341 driver */
    ...

    int main(void)
    {
        ili9341_desc_ptr_t display;
        const ili9341_cfg_t display_cfg = {
            ...
        };

        const ili9341_hw_cfg_t hw_cfg = ili9341_get_default_hw_cfg();

        ... Some other init code needed by your target ...

        display = ili9341_init(&display_cfg, &hw_cfg);
        if (display == NULL) {
            Error_Handler();
        }
		
		/* Define brush */
		ili_sgfx_brush_t brush = {
			.bg_color = BLACK,
			.fg_color = GREEN,
			.size = 1
		};
		
		/* Draw filled rectangle 20x20 to the center of the screen */
		coord_2d_t top_left, bottom_right;
		top_left.x = ili9341_get_screen_width(desc)/2 - 10;
		top_left.y = ili9341_get_screen_height(desc)/2 - 10;
		bottom_right.x = ili9341_get_screen_width(desc)/2 + 10;
		bottom_right.y = ili9341_get_screen_height(desc)/2 + 10;
		ili_sgfx_draw_filled_rect(desc, &brush, top_left, bottom_right);

        while (1) {
            ... Some application code ...
        }
    }

## Examples

[ili9341-simple-gfx](https://github.com/hornmich/ili9341-simple-gfx)
