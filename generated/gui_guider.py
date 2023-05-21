# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=480,h=272)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(480*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 480
disp_drv.ver_res = 272
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)


screen = lv.obj()
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_main_default.set_bg_opa(0)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_label0 = lv.label(screen)
screen_label0.set_pos(int(178),int(228))
screen_label0.set_size(100,20)
screen_label0.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label0.set_text("screen1")
screen_label0.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label0_main_main_default
style_screen_label0_main_main_default = lv.style_t()
style_screen_label0_main_main_default.init()
style_screen_label0_main_main_default.set_radius(0)
style_screen_label0_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_label0_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_label0_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_label0_main_main_default.set_bg_opa(0)
style_screen_label0_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_label0_main_main_default.set_text_font(lv.font_arial_12)
except AttributeError:
    try:
        style_screen_label0_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_label0_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label0_main_main_default.set_text_letter_space(2)
style_screen_label0_main_main_default.set_text_line_space(0)
style_screen_label0_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_label0_main_main_default.set_pad_left(0)
style_screen_label0_main_main_default.set_pad_right(0)
style_screen_label0_main_main_default.set_pad_top(0)
style_screen_label0_main_main_default.set_pad_bottom(0)

# add style for screen_label0
screen_label0.add_style(style_screen_label0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_btn1 = lv.btn(screen)
screen_btn1.set_pos(int(351),int(223))
screen_btn1.set_size(100,25)
screen_btn1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_btn1_label = lv.label(screen_btn1)
screen_btn1_label.set_text("Next Screen")
screen_btn1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn1_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_btn1_main_main_default
style_screen_btn1_main_main_default = lv.style_t()
style_screen_btn1_main_main_default.init()
style_screen_btn1_main_main_default.set_radius(50)
style_screen_btn1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_btn1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_btn1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_btn1_main_main_default.set_bg_opa(255)
style_screen_btn1_main_main_default.set_border_color(lv.color_make(0x01,0xa2,0xb1))
style_screen_btn1_main_main_default.set_border_width(2)
style_screen_btn1_main_main_default.set_border_opa(255)
style_screen_btn1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_btn1_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_btn1_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_btn1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_btn1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_btn1
screen_btn1.add_style(style_screen_btn1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_gauge2 = lv.meter(screen)
screen_gauge2.set_pos(int(128),int(11))
screen_gauge2.set_size(200,200)
screen_gauge2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_gauge2_scale_1 = screen_gauge2.add_scale()
screen_gauge2.set_scale_ticks(screen_gauge2_scale_1, 41, 2, 10,
    lv.color_make(0xff, 0x00, 0x00))
screen_gauge2.set_scale_major_ticks(screen_gauge2_scale_1, 8, 5, 15,
	lv.color_make(0xff, 0xff, 0x00), 10)
screen_gauge2.set_scale_range(screen_gauge2_scale_1, 0, 100, 300, 90)
# create style style_screen_gauge2_main_main_default
style_screen_gauge2_main_main_default = lv.style_t()
style_screen_gauge2_main_main_default.init()
style_screen_gauge2_main_main_default.set_radius(200)
style_screen_gauge2_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_gauge2_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_gauge2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_gauge2_main_main_default.set_bg_opa(255)
style_screen_gauge2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_gauge2_main_main_default.set_border_width(0)
style_screen_gauge2_main_main_default.set_border_opa(255)

# add style for screen_gauge2
screen_gauge2.add_style(style_screen_gauge2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_gauge2_main_ticks_default
style_screen_gauge2_main_ticks_default = lv.style_t()
style_screen_gauge2_main_ticks_default.init()
style_screen_gauge2_main_ticks_default.set_text_color(lv.color_make(0x58,0x55,0x55))
try:
    style_screen_gauge2_main_ticks_default.set_text_font(lv.font_arial_12)
except AttributeError:
    try:
        style_screen_gauge2_main_ticks_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_gauge2_main_ticks_default.set_text_font(lv.font_montserrat_16)

# add style for screen_gauge2
screen_gauge2.add_style(style_screen_gauge2_main_ticks_default, lv.PART.TICKS|lv.STATE.DEFAULT)

screen_btn_2 = lv.btn(screen)
screen_btn_2.set_pos(int(21),int(29))
screen_btn_2.set_size(100,50)
screen_btn_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_btn_2_label = lv.label(screen_btn_2)
screen_btn_2_label.set_text("hello")
screen_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_btn_2_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_btn_2_main_main_default
style_screen_btn_2_main_main_default = lv.style_t()
style_screen_btn_2_main_main_default.init()
style_screen_btn_2_main_main_default.set_radius(5)
style_screen_btn_2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_btn_2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_btn_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_btn_2_main_main_default.set_bg_opa(255)
style_screen_btn_2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_btn_2_main_main_default.set_border_width(0)
style_screen_btn_2_main_main_default.set_border_opa(255)
style_screen_btn_2_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_btn_2_main_main_default.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_btn_2_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_btn_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_btn_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_btn_2
screen_btn_2.add_style(style_screen_btn_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_cb_1 = lv.checkbox(screen)
screen_cb_1.set_pos(int(21),int(202))
screen_cb_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_cb_1.set_text("checkbox")
# create style style_screen_cb_1_main_main_default
style_screen_cb_1_main_main_default = lv.style_t()
style_screen_cb_1_main_main_default.init()
style_screen_cb_1_main_main_default.set_radius(6)
style_screen_cb_1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_cb_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_cb_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_cb_1_main_main_default.set_bg_opa(255)
style_screen_cb_1_main_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_screen_cb_1_main_main_default.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_cb_1_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_cb_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_cb_1_main_main_default.set_text_letter_space(2)

# add style for screen_cb_1
screen_cb_1.add_style(style_screen_cb_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_cb_1_main_indicator_default
style_screen_cb_1_main_indicator_default = lv.style_t()
style_screen_cb_1_main_indicator_default.init()
style_screen_cb_1_main_indicator_default.set_radius(6)
style_screen_cb_1_main_indicator_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_cb_1_main_indicator_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_cb_1_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_cb_1_main_indicator_default.set_bg_opa(255)
style_screen_cb_1_main_indicator_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_cb_1_main_indicator_default.set_border_width(2)
style_screen_cb_1_main_indicator_default.set_border_opa(255)

# add style for screen_cb_1
screen_cb_1.add_style(style_screen_cb_1_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

screen2 = lv.obj()
screen2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen2_main_main_default
style_screen2_main_main_default = lv.style_t()
style_screen2_main_main_default.init()
style_screen2_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen2_main_main_default.set_bg_opa(0)

# add style for screen2
screen2.add_style(style_screen2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen2_label0 = lv.label(screen2)
screen2_label0.set_pos(int(180),int(240))
screen2_label0.set_size(100,20)
screen2_label0.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen2_label0.set_text("screen2")
screen2_label0.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen2_label0_main_main_default
style_screen2_label0_main_main_default = lv.style_t()
style_screen2_label0_main_main_default.init()
style_screen2_label0_main_main_default.set_radius(0)
style_screen2_label0_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen2_label0_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen2_label0_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen2_label0_main_main_default.set_bg_opa(0)
style_screen2_label0_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen2_label0_main_main_default.set_text_font(lv.font_arial_12)
except AttributeError:
    try:
        style_screen2_label0_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen2_label0_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen2_label0_main_main_default.set_text_letter_space(2)
style_screen2_label0_main_main_default.set_text_line_space(0)
style_screen2_label0_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen2_label0_main_main_default.set_pad_left(0)
style_screen2_label0_main_main_default.set_pad_right(0)
style_screen2_label0_main_main_default.set_pad_top(0)
style_screen2_label0_main_main_default.set_pad_bottom(0)

# add style for screen2_label0
screen2_label0.add_style(style_screen2_label0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen2_btn1_1 = lv.btn(screen2)
screen2_btn1_1.set_pos(int(30),int(235))
screen2_btn1_1.set_size(100,25)
screen2_btn1_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen2_btn1_1_label = lv.label(screen2_btn1_1)
screen2_btn1_1_label.set_text("Previous Screen")
screen2_btn1_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen2_btn1_1_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen2_btn1_1_main_main_default
style_screen2_btn1_1_main_main_default = lv.style_t()
style_screen2_btn1_1_main_main_default.init()
style_screen2_btn1_1_main_main_default.set_radius(50)
style_screen2_btn1_1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen2_btn1_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen2_btn1_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen2_btn1_1_main_main_default.set_bg_opa(255)
style_screen2_btn1_1_main_main_default.set_border_color(lv.color_make(0x01,0xa2,0xb1))
style_screen2_btn1_1_main_main_default.set_border_width(2)
style_screen2_btn1_1_main_main_default.set_border_opa(255)
style_screen2_btn1_1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen2_btn1_1_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen2_btn1_1_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen2_btn1_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen2_btn1_1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen2_btn1_1
screen2_btn1_1.add_style(style_screen2_btn1_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen2_chart2 = lv.chart(screen2)
screen2_chart2.set_pos(int(129),int(36))
screen2_chart2.set_size(205,155)
screen2_chart2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen2_chart2.set_type(lv.chart.TYPE.LINE)
screen2_chart2.set_range(lv.chart.AXIS.PRIMARY_Y, 0, 100)
screen2_chart2.set_div_line_count(3, 5)
screen2_chart2.set_point_count(10)
chart_series_0 = lv.chart.add_series(screen2_chart2, lv.color_make(0x00,0x00,0x00), lv.chart.AXIS.PRIMARY_Y);
screen2_chart2.set_next_value(chart_series_0, 10)
screen2_chart2.set_next_value(chart_series_0, 20)
screen2_chart2.set_next_value(chart_series_0, 30)
screen2_chart2.set_next_value(chart_series_0, 40)
screen2_chart2.set_next_value(chart_series_0, 10)
screen2_chart2.set_next_value(chart_series_0, 50)
screen2_chart2.set_next_value(chart_series_0, 70)
screen2_chart2.set_next_value(chart_series_0, 30)
screen2_chart2.set_next_value(chart_series_0, 10)
screen2_chart2.set_next_value(chart_series_0, 30)
# create style style_screen2_chart2_main_main_default
style_screen2_chart2_main_main_default = lv.style_t()
style_screen2_chart2_main_main_default.init()
style_screen2_chart2_main_main_default.set_radius(0)
style_screen2_chart2_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen2_chart2_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen2_chart2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen2_chart2_main_main_default.set_bg_opa(255)
style_screen2_chart2_main_main_default.set_border_color(lv.color_make(0xe8,0xe8,0xe8))
style_screen2_chart2_main_main_default.set_border_width(1)
style_screen2_chart2_main_main_default.set_border_opa(255)
style_screen2_chart2_main_main_default.set_line_color(lv.color_make(0xe8,0xe8,0xe8))
style_screen2_chart2_main_main_default.set_line_width(2)
style_screen2_chart2_main_main_default.set_line_opa(255)

# add style for screen2_chart2
screen2_chart2.add_style(style_screen2_chart2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)



def screen_btn1_pressed_1_event_cb(e,screen2):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(screen2, lv.SCR_LOAD_ANIM.FADE_ON, 100, 100, False)
screen_btn1.add_event_cb(lambda e: screen_btn1_pressed_1_event_cb(e,screen2), lv.EVENT.PRESSED, None)


def screen2_btn1_1_pressed_1_event_cb(e,screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(screen, lv.SCR_LOAD_ANIM.FADE_ON, 100, 100, False)
screen2_btn1_1.add_event_cb(lambda e: screen2_btn1_1_pressed_1_event_cb(e,screen), lv.EVENT.PRESSED, None)



# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)
