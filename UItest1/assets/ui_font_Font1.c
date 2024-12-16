/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font F:/桌面/esp32pico169/UItest1/assets/字魂书雅宋-Heavy(商用需授权).ttf -o F:/桌面/esp32pico169/UItest1/assets\ui_font_Font1.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfe, 0x92, 0xb, 0xf0,

    /* U+0022 "\"" */
    0xff, 0xff, 0xd2, 0x48,

    /* U+0023 "#" */
    0x19, 0xc3, 0x30, 0xe6, 0x7f, 0xf3, 0x38, 0x66,
    0x3f, 0xf3, 0xb8, 0x67, 0xc, 0xe0,

    /* U+0024 "$" */
    0x8, 0x4, 0x1f, 0x9d, 0x3e, 0x8f, 0x47, 0xe0,
    0xfc, 0x3f, 0x7, 0xe2, 0xf1, 0x7c, 0xbd, 0xf8,
    0x20, 0x10,

    /* U+0025 "%" */
    0x7c, 0x1, 0xdc, 0x43, 0xb9, 0x7, 0x74, 0xe,
    0xe8, 0xd, 0xa7, 0xe, 0x9b, 0x1, 0x77, 0x4,
    0xee, 0x11, 0xdc, 0x43, 0xb8, 0x83, 0xe0,

    /* U+0026 "&" */
    0x7f, 0x1c, 0x73, 0x8e, 0x79, 0xc7, 0x70, 0x71,
    0xdf, 0x17, 0x72, 0xef, 0x9c, 0xf3, 0x8e, 0x3e,
    0xf0,

    /* U+0027 "'" */
    0xff, 0xa4,

    /* U+0028 "(" */
    0x8, 0xcc, 0xe6, 0x73, 0x9c, 0xe7, 0x38, 0xe3,
    0xc, 0x20,

    /* U+0029 ")" */
    0x86, 0x18, 0xe3, 0x1c, 0xe7, 0x39, 0xcc, 0xe6,
    0x62, 0x0,

    /* U+002A "*" */
    0x33, 0xff, 0xfe, 0xec, 0xc3, 0x0,

    /* U+002B "+" */
    0x1c, 0xe, 0x7, 0x3, 0x8f, 0xf8, 0xe0, 0x70,
    0x38,

    /* U+002C "," */
    0xff, 0xa4,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x22, 0x22, 0x44, 0x44, 0x88, 0x88,

    /* U+0030 "0" */
    0x1e, 0x1c, 0xe6, 0x1b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xd8, 0x67, 0x38, 0x78,

    /* U+0031 "1" */
    0x1b, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3,
    0xbf,

    /* U+0032 "2" */
    0x3c, 0xe6, 0xe7, 0xe7, 0x7, 0xe, 0xe, 0x18,
    0x30, 0x41, 0x41, 0xff,

    /* U+0033 "3" */
    0x3f, 0x31, 0xf8, 0xe0, 0x70, 0x70, 0xc0, 0x1c,
    0x7, 0x43, 0xf1, 0xf8, 0xef, 0xc0,

    /* U+0034 "4" */
    0x7, 0x3, 0xc1, 0x70, 0x5c, 0x27, 0x11, 0xc4,
    0x72, 0x1c, 0xff, 0xc1, 0xc0, 0x70, 0x3e,

    /* U+0035 "5" */
    0x3f, 0x3f, 0x90, 0x8, 0x5, 0xe3, 0x38, 0xe,
    0x7, 0x43, 0xf1, 0xf8, 0xcf, 0xc0,

    /* U+0036 "6" */
    0x1f, 0x39, 0xd8, 0x7c, 0xe, 0xe7, 0x9b, 0x8f,
    0xc7, 0xe3, 0xf1, 0xd8, 0xc7, 0xc0,

    /* U+0037 "7" */
    0xff, 0xff, 0x81, 0x2, 0x4, 0xc, 0x1c, 0x18,
    0x38, 0x38, 0x38, 0x38,

    /* U+0038 "8" */
    0x3e, 0x38, 0xee, 0x3b, 0xce, 0x7f, 0xf, 0x83,
    0xf9, 0x9f, 0xe3, 0xf8, 0x7e, 0x1c, 0xfc,

    /* U+0039 "9" */
    0x3e, 0x31, 0xb8, 0xdc, 0x7e, 0x3f, 0x1d, 0x9e,
    0x77, 0x3, 0xe1, 0xb9, 0xcf, 0x80,

    /* U+003A ":" */
    0xff, 0x81, 0xff,

    /* U+003B ";" */
    0xff, 0x80, 0x3f, 0x6a, 0x0,

    /* U+003C "<" */
    0x1, 0x6, 0x38, 0xc0, 0x60, 0x1c, 0x3,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x80, 0x60, 0x1c, 0x3, 0x6, 0x38, 0xc0,

    /* U+003F "?" */
    0x3e, 0xe7, 0xe7, 0xe7, 0x6, 0xc, 0x18, 0x10,
    0x10, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0xf, 0x83, 0x6, 0x4e, 0xf5, 0xd9, 0xb9, 0x9b,
    0x99, 0xb9, 0x9b, 0x9a, 0x9f, 0xc4, 0x0, 0x20,
    0x21, 0xfc,

    /* U+0041 "A" */
    0x3, 0x0, 0xe, 0x0, 0x58, 0x1, 0x60, 0x9,
    0xc0, 0x23, 0x1, 0xe, 0x3, 0xf8, 0x10, 0x60,
    0x81, 0xc2, 0x7, 0x1c, 0x3e,

    /* U+0042 "B" */
    0xff, 0x1c, 0x77, 0x1d, 0xc7, 0x71, 0x9f, 0x87,
    0x39, 0xc7, 0x71, 0xdc, 0x77, 0x1b, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x26, 0x1d, 0xc1, 0xf0, 0x1e, 0x1, 0xc0,
    0x38, 0x7, 0x0, 0xe0, 0xc, 0x8, 0xc1, 0xf,
    0xc0,

    /* U+0044 "D" */
    0xff, 0xe, 0x31, 0xc3, 0x38, 0x77, 0xe, 0xe1,
    0xdc, 0x3b, 0x87, 0x70, 0xee, 0x19, 0xc6, 0x7f,
    0x80,

    /* U+0045 "E" */
    0xff, 0xb8, 0x5c, 0xe, 0x7, 0xb, 0xfd, 0xc2,
    0xe1, 0x70, 0x38, 0x5c, 0x3f, 0xf0,

    /* U+0046 "F" */
    0xff, 0xb8, 0x5c, 0x2e, 0x7, 0x13, 0x89, 0xfc,
    0xe2, 0x70, 0x38, 0x1c, 0x1f, 0x0,

    /* U+0047 "G" */
    0x1f, 0x83, 0x6, 0x70, 0x2e, 0x2, 0xe0, 0xe,
    0x0, 0xe1, 0xfe, 0xe, 0xe0, 0xe6, 0xe, 0x30,
    0xe1, 0xf0,

    /* U+0048 "H" */
    0xf9, 0xf7, 0xe, 0x70, 0xe7, 0xe, 0x70, 0xe7,
    0xfe, 0x70, 0xe7, 0xe, 0x70, 0xe7, 0xe, 0x70,
    0xef, 0x9f,

    /* U+0049 "I" */
    0xfb, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9d, 0xf0,

    /* U+004A "J" */
    0xf, 0x83, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c,
    0xe, 0x7, 0x73, 0xb9, 0xcf, 0x80,

    /* U+004B "K" */
    0xf8, 0xf7, 0x4, 0x70, 0x87, 0x10, 0x73, 0x7,
    0x78, 0x7b, 0x87, 0x18, 0x71, 0xc7, 0x1c, 0x70,
    0xcf, 0x9f,

    /* U+004C "L" */
    0xfc, 0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1c, 0x7,
    0x1, 0xc0, 0x70, 0x1c, 0x27, 0xb, 0xfe,

    /* U+004D "M" */
    0xf0, 0x7b, 0x87, 0x9e, 0x3c, 0xf2, 0xe5, 0x97,
    0x2c, 0xb9, 0x75, 0xc9, 0xce, 0x4e, 0x72, 0x73,
    0x91, 0x1d, 0xc1, 0xf0,

    /* U+004E "N" */
    0xf1, 0xdc, 0x27, 0x89, 0x62, 0x5c, 0x93, 0xa4,
    0x69, 0x1e, 0x43, 0x90, 0xe4, 0x1b, 0x86,

    /* U+004F "O" */
    0x1f, 0x6, 0x31, 0x83, 0x70, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xec, 0x18, 0xc6, 0xf,
    0x80,

    /* U+0050 "P" */
    0xff, 0x1c, 0x67, 0x1d, 0xc7, 0x71, 0xdc, 0x77,
    0x39, 0xfc, 0x70, 0x1c, 0x7, 0x3, 0xe0,

    /* U+0051 "Q" */
    0x1f, 0x83, 0xc, 0x70, 0xee, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xee, 0x77, 0x66, 0x37,
    0xc1, 0xf8, 0x3, 0x80, 0x1e,

    /* U+0052 "R" */
    0xff, 0xe, 0x39, 0xc7, 0x38, 0xe7, 0x1c, 0xe7,
    0x1f, 0x83, 0x98, 0x73, 0xe, 0x71, 0xc6, 0x7c,
    0xe0,

    /* U+0053 "S" */
    0x3e, 0x70, 0xf8, 0x3c, 0x1f, 0x83, 0xf0, 0xfc,
    0x1f, 0x83, 0xc1, 0xf0, 0xf7, 0xc0,

    /* U+0054 "T" */
    0xff, 0xf1, 0xc6, 0x38, 0x87, 0x0, 0xe0, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38, 0xf,
    0x80,

    /* U+0055 "U" */
    0xf8, 0xee, 0x9, 0xc1, 0x38, 0x27, 0x4, 0xe0,
    0x9c, 0x13, 0x82, 0x70, 0x4e, 0x8, 0xe2, 0xf,
    0x80,

    /* U+0056 "V" */
    0xfc, 0x39, 0xc0, 0x8e, 0x8, 0x30, 0x41, 0xc4,
    0x6, 0x20, 0x39, 0x1, 0xd0, 0x6, 0x80, 0x38,
    0x0, 0xc0, 0x6, 0x0,

    /* U+0057 "W" */
    0xfb, 0xe3, 0xdc, 0x30, 0x43, 0xe, 0x10, 0xe3,
    0x88, 0x18, 0x62, 0x7, 0x3c, 0x81, 0xcf, 0x40,
    0x34, 0xd0, 0xf, 0x3c, 0x3, 0x8e, 0x0, 0x61,
    0x80, 0x18, 0x60,

    /* U+0058 "X" */
    0x7c, 0x79, 0xc1, 0x7, 0x10, 0x1d, 0x0, 0xe8,
    0x3, 0x80, 0xe, 0x0, 0xf0, 0x9, 0xc0, 0x87,
    0x8, 0x39, 0xe3, 0xf0,

    /* U+0059 "Y" */
    0xf8, 0x73, 0x2, 0x38, 0x41, 0xc4, 0x1c, 0x80,
    0xe8, 0xf, 0x0, 0x70, 0x7, 0x0, 0x70, 0x7,
    0x0, 0xf8,

    /* U+005A "Z" */
    0xff, 0xe0, 0xe8, 0x70, 0x1c, 0xe, 0x3, 0x1,
    0xc0, 0xe0, 0x38, 0x1c, 0x16, 0xb, 0xfe,

    /* U+005B "[" */
    0xff, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8f, 0xc0,

    /* U+005C "\\" */
    0x88, 0x88, 0x44, 0x44, 0x22, 0x22,

    /* U+005D "]" */
    0xfc, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x7f, 0xc0,

    /* U+005E "^" */
    0x71, 0xed, 0xa2, 0x0,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xd9, 0x80,

    /* U+0061 "a" */
    0x7e, 0x73, 0xb9, 0xc7, 0xee, 0x77, 0x3b, 0x9c,
    0xff,

    /* U+0062 "b" */
    0x10, 0x3c, 0x7, 0x1, 0xc0, 0x70, 0x1d, 0xc7,
    0x99, 0xc7, 0x71, 0xdc, 0x77, 0x1d, 0xc6, 0x6f,
    0x0,

    /* U+0063 "c" */
    0x3e, 0x63, 0xe3, 0xe0, 0xe0, 0xe0, 0x61, 0x3e,

    /* U+0064 "d" */
    0x0, 0x81, 0xe0, 0x38, 0xe, 0x3, 0x8f, 0xe6,
    0x3b, 0x8e, 0xe3, 0xb8, 0xee, 0x39, 0x8e, 0x3f,
    0xc0,

    /* U+0065 "e" */
    0x3e, 0x31, 0xb8, 0xff, 0xfe, 0x7, 0x5, 0x84,
    0x7c,

    /* U+0066 "f" */
    0x1e, 0x3f, 0x38, 0x38, 0xfe, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x78,

    /* U+0067 "g" */
    0x3d, 0xb1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1d, 0x8e,
    0x7f, 0x3, 0xf1, 0xf8, 0xcf, 0xc0,

    /* U+0068 "h" */
    0xf0, 0x1c, 0x7, 0x1, 0xc0, 0x77, 0x1e, 0xe7,
    0x39, 0xce, 0x73, 0x9c, 0xe7, 0x3b, 0xff,

    /* U+0069 "i" */
    0x73, 0x9c, 0x3, 0x39, 0xce, 0x73, 0x9d, 0xf0,

    /* U+006A "j" */
    0xe, 0x1c, 0x38, 0x0, 0x61, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xfd, 0xfb, 0xbe,

    /* U+006B "k" */
    0xf0, 0xe, 0x1, 0xc0, 0x38, 0x7, 0x1c, 0xe2,
    0x1c, 0xc3, 0xb8, 0x7b, 0xe, 0x71, 0xc6, 0x7d,
    0xe0,

    /* U+006C "l" */
    0xf3, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9d, 0xf0,

    /* U+006D "m" */
    0x77, 0x39, 0xf7, 0xb9, 0xce, 0x73, 0x9c, 0xe7,
    0x39, 0xce, 0x73, 0x9c, 0xe7, 0x7f, 0xff,

    /* U+006E "n" */
    0x77, 0x3e, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7,
    0x3b, 0xff,

    /* U+006F "o" */
    0x3e, 0x31, 0xb8, 0xfc, 0x7e, 0x3f, 0x1d, 0x8c,
    0x7c,

    /* U+0070 "p" */
    0x77, 0x3e, 0x67, 0x1d, 0xc7, 0x71, 0xdc, 0x77,
    0x19, 0xfc, 0x70, 0x1c, 0x7, 0x3, 0xe0,

    /* U+0071 "q" */
    0x3d, 0x98, 0xee, 0x3b, 0x8e, 0xe3, 0xb8, 0xe6,
    0x38, 0xfe, 0x3, 0x80, 0xe0, 0x38, 0x1f,

    /* U+0072 "r" */
    0x77, 0xfb, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8,

    /* U+0073 "s" */
    0x7d, 0xcf, 0xc7, 0xc7, 0xf3, 0xe3, 0xfe,

    /* U+0074 "t" */
    0x8, 0x78, 0x38, 0x38, 0xff, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x1e,

    /* U+0075 "u" */
    0xf7, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7,
    0x38, 0xff,

    /* U+0076 "v" */
    0xf9, 0xdc, 0x43, 0x10, 0xe4, 0x1a, 0x7, 0x81,
    0xe0, 0x30,

    /* U+0077 "w" */
    0xfb, 0xee, 0xe3, 0x88, 0xc7, 0x21, 0xce, 0x41,
    0xae, 0x83, 0xce, 0x7, 0x9c, 0x6, 0x38,

    /* U+0078 "x" */
    0xfd, 0xe7, 0x10, 0x74, 0x7, 0x0, 0xe0, 0x2e,
    0x8, 0xe7, 0xbf,

    /* U+0079 "y" */
    0xf9, 0xdc, 0x43, 0x90, 0xe4, 0x1a, 0x7, 0x80,
    0xe0, 0x30, 0x4, 0x2, 0x6, 0x81, 0xc0,

    /* U+007A "z" */
    0xff, 0x8e, 0x8e, 0x1c, 0x38, 0x71, 0x71, 0xff,

    /* U+007B "{" */
    0x3d, 0xc7, 0x1c, 0x71, 0xc7, 0x30, 0x61, 0xc7,
    0x1c, 0x71, 0xc1, 0xc0,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0xf0, 0xe3, 0x8e, 0x38, 0xe3, 0x83, 0x18, 0xe3,
    0x8e, 0x38, 0xee, 0x0,

    /* U+007E "~" */
    0x0, 0xff, 0x1e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 77, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 70, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 6, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 10, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 167, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 42, .adv_w = 268, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 202, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 63, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 84, .adv_w = 102, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 94, .adv_w = 102, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 104, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 110, .adv_w = 163, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 119, .adv_w = 74, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 121, .adv_w = 140, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 122, .adv_w = 74, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 130, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 145, .adv_w = 159, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 154, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 166, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 180, .adv_w = 168, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 195, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 209, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 223, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 235, .adv_w = 178, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 250, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 264, .adv_w = 74, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 267, .adv_w = 74, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 272, .adv_w = 150, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 140, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 150, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 303, .adv_w = 212, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 321, .adv_w = 225, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 342, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 357, .adv_w = 194, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 374, .adv_w = 195, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 391, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 405, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 419, .adv_w = 208, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 437, .adv_w = 212, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 455, .adv_w = 96, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 463, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 477, .adv_w = 204, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 495, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 510, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 530, .adv_w = 187, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 545, .adv_w = 203, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 562, .adv_w = 181, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 577, .adv_w = 208, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 598, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 615, .adv_w = 167, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 629, .adv_w = 189, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 646, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 663, .adv_w = 217, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 683, .adv_w = 295, .box_w = 18, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 710, .adv_w = 216, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 730, .adv_w = 205, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 748, .adv_w = 172, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 763, .adv_w = 113, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 775, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 781, .adv_w = 113, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 793, .adv_w = 120, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 797, .adv_w = 140, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 798, .adv_w = 70, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 800, .adv_w = 155, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 809, .adv_w = 169, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 826, .adv_w = 152, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 834, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 851, .adv_w = 159, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 860, .adv_w = 131, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 872, .adv_w = 160, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 886, .adv_w = 174, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 901, .adv_w = 84, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 909, .adv_w = 74, .box_w = 7, .box_h = 16, .ofs_x = -2, .ofs_y = -5},
    {.bitmap_index = 923, .adv_w = 175, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 940, .adv_w = 84, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 948, .adv_w = 250, .box_w = 15, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 963, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 973, .adv_w = 159, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 982, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 997, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1012, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1020, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1027, .adv_w = 121, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1039, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1049, .adv_w = 171, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1059, .adv_w = 255, .box_w = 15, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1074, .adv_w = 178, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1085, .adv_w = 172, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1100, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1108, .adv_w = 108, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1120, .adv_w = 34, .box_w = 1, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1122, .adv_w = 108, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1134, .adv_w = 158, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 2, 3, 4, 5, 6,
    7, 3, 1, 0, 0, 0, 0, 0,
    0, 0, 8, 9, 10, 11, 12, 13,
    14, 0, 0, 15, 16, 17, 0, 0,
    11, 18, 11, 19, 20, 21, 6, 22,
    23, 24, 25, 26, 0, 0, 0, 0,
    0, 0, 27, 28, 29, 30, 28, 31,
    32, 27, 30, 30, 33, 30, 27, 27,
    28, 28, 34, 35, 36, 37, 34, 38,
    39, 40, 41, 42, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 2, 3, 4, 5, 1,
    6, 7, 8, 0, 0, 0, 0, 0,
    0, 0, 9, 0, 10, 0, 0, 0,
    10, 0, 0, 11, 0, 0, 0, 0,
    12, 0, 10, 0, 13, 14, 15, 16,
    17, 18, 19, 20, 0, 0, 0, 0,
    0, 0, 21, 22, 23, 24, 24, 25,
    24, 22, 26, 22, 22, 22, 27, 27,
    24, 27, 24, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    -26, 0, 0, 0, 0, 0, 0, -15,
    -18, -13, -18, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -26, 0,
    0, 0, 0, 0, 0, -5, -18, -13,
    -18, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -14, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -26,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -31, 0, -20, 0, 0, 0,
    0, 8, 0, 0, 0, 0, -13, 0,
    -11, -11, 0, 0, -7, -8, 0, 0,
    0, 0, 0, 0, 0, -20, 0, -20,
    0, -8, -41, -20, -20, 0, -23, -13,
    -23, 0, -38, -26, -61, -51, 0, -54,
    0, -10, 0, -18, -18, 0, 0, 0,
    -5, -26, -20, -41, -36, 0, -33, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -15, 0, 0, 0, 0, 0, 0, -5,
    -8, -10, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -23, 0, 0, -3, 0,
    -5, 0, 0, 0, -5, 0, 0, 0,
    5, -3, -3, 0, 5, 0, -5, 3,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, -23, 8,
    0, 8, 0, -5, 0, -20, -20, -26,
    -18, 0, 0, 5, -3, -3, 0, 5,
    0, 0, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, -8, 0, 0, 0, 0, -13,
    0, 0, 0, 0, 0, -3, -36, -3,
    8, 0, 0, 0, 0, 0, 0, 0,
    -13, 0, -13, -13, 0, 0, -3, -5,
    0, -3, -5, -5, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -26,
    3, 0, 3, 0, -3, 0, -10, -10,
    -18, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -10, -8, -8,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -20, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -31, -10,
    -31, -5, 0, 0, 0, 0, 0, 0,
    0, -13, 0, -18, -18, 0, 0, 0,
    -10, -18, -23, -41, -38, 0, -36, 0,
    0, 0, 0, 0, 0, -23, 0, 0,
    0, -10, 0, -10, 0, -33, -10, -36,
    -41, 0, -41, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, -5, -33, -33,
    0, -33, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -44, 0, -41, 0, 3,
    0, 0, -5, -5, -8, -5, 0, -3,
    0, -10, -10, 0, 0, 0, 0, 0,
    0, 9, 8, 7, 13, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, -13, 0,
    -10, 0, -7, 0, -13, -13, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -5, -5, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, -6, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -38, -5, -33, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    -44, 0, -44, -49, -10, 0, -38, -41,
    0, -36, -41, -38, -36, -41, -31, -20,
    -8, -10, 0, 0, 0, -15, -13, -64,
    -20, -44, -20, -8, 0, 0, 0, 0,
    0, 0, 0, -41, 0, -44, -44, -23,
    0, -36, -38, -13, -31, -28, -23, -28,
    -28, -33, -20, -14, -15, -36, 0, 0,
    -20, -20, -56, -23, -46, -23, -13, 0,
    0, 0, 0, 0, 0, 0, -36, 0,
    -41, -41, -20, 0, -28, -33, -10, -28,
    -26, -26, -31, -28, -31, -15, 0, -15,
    0, 0, 0, -15, -15, 0, -26, -13,
    -26, -8, 0, 0, 0, 0, 0, 0,
    0, -13, 0, -23, -23, -5, 0, 0,
    -8, -18, -26, -36, -36, 0, -36, 0,
    -23, -15, -8, 0, 0, 0, -23, -23,
    -46, -26, -41, -26, -8, 0, 0, 0,
    0, 0, 0, 0, -44, 0, -49, -49,
    -20, 0, -41, -46, -18, -41, -31, -28,
    -28, -28, -33, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    -5, -13, -13, 0, -13, 0, 0, 0,
    0, 0, 0, -20, 0, 0, 0, 0,
    0, 0, 0, -41, 0, -46, -46, 0,
    -51, 0, 0, 0, 0, 0, -3, 0,
    0, 0, -10, 0, -18, -18, 0, -13,
    0, 0, 0, 0, 0, 0, -23, 0,
    0, -22, 0, 0, 0, 0, -49, 0,
    -41, -41, -23, -49, 0, 0, 0, 0,
    0, -2, 0, 0, 0, -10, 0, -16,
    -15, -18, -13, -2, 0, 0, 0, 0,
    0, -23, 0, 0, -22, 0, 0, 0,
    0, -49, 0, -41, -41, -23, -49, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    -10, 0, -16, -15, -13, -5, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 0, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -36, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -23, 0,
    -23, -23, 0, 0, -10, -18, 0, 0,
    -13, 0, 0, -6, -18, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 9, 0, 0, 10, 9, 13,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, -15, -8, -3, -36, 0, -33,
    -33, 0, -44, 0, -10, 0, -17, -17,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -13, 0, 0, 0, 0, 0, 0, 0,
    -36, 0, -38, -38, 0, -46, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -46, 0,
    0, 0, 0, -49, 0, -33, -31, -44,
    -46, -31, -5, -9, -10, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, -18, 0,
    0, -3, 0, 0, 0, 0, -41, 0,
    -38, -36, -8, -46, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, 0, -5,
    -8, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, 0, -28, -26, -5, -28, 0,
    -8, 0, -8, -15, 0, 0, 0, -13,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, -46,
    0, -33, 0, 0, -41, 0, -26, -28,
    -36, -31, -20, -12, 0, -17, -17, 0,
    0, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -38, 0, -33, 0, 0, -38,
    0, -28, -31, -36, -28, -20, -10, 0,
    -15, -15, 0, 0, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -10,
    0, 0, -36, 0, -28, -31, 0, -28,
    0, 0, 0, -18, -18, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -38, 0, -33, 0, 0, -41, 0, -28,
    -28, -36, -28, -20, -10, 0, -13, -13,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -31, 0, -31, -26, 0, -33, 0, 0,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 42,
    .right_class_cnt     = 35,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT1*/

