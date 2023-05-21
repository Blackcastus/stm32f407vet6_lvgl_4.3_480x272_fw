/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "../custom/custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label0
	ui->screen_label0 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label0, 178, 228);
	lv_obj_set_size(ui->screen_label0, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen_label0, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label0, "screen1");
	lv_label_set_long_mode(ui->screen_label0, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_label0_main_main_default
	static lv_style_t style_screen_label0_main_main_default;
	if (style_screen_label0_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_label0_main_main_default);
	else
		lv_style_init(&style_screen_label0_main_main_default);
	lv_style_set_radius(&style_screen_label0_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_label0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label0_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label0_main_main_default, 0);
	lv_style_set_text_color(&style_screen_label0_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label0_main_main_default, &lv_font_arial_12);
	lv_style_set_text_letter_space(&style_screen_label0_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_label0_main_main_default, 0);
	lv_style_set_text_align(&style_screen_label0_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_label0_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_label0_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_label0_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_label0_main_main_default, 0);
	lv_obj_add_style(ui->screen_label0, &style_screen_label0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn1
	ui->screen_btn1 = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn1, 351, 223);
	lv_obj_set_size(ui->screen_btn1, 100, 25);
	lv_obj_set_scrollbar_mode(ui->screen_btn1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn1_main_main_default
	static lv_style_t style_screen_btn1_main_main_default;
	if (style_screen_btn1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_btn1_main_main_default);
	else
		lv_style_init(&style_screen_btn1_main_main_default);
	lv_style_set_radius(&style_screen_btn1_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_btn1_main_main_default, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn1_main_main_default, 2);
	lv_style_set_border_opa(&style_screen_btn1_main_main_default, 255);
	lv_style_set_text_color(&style_screen_btn1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_btn1_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_btn1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_btn1, &style_screen_btn1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_btn1_label = lv_label_create(ui->screen_btn1);
	lv_label_set_text(ui->screen_btn1_label, "Next Screen");
	lv_obj_set_style_pad_all(ui->screen_btn1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_btn_2
	ui->screen_btn_2 = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn_2, 190, 120);
	lv_obj_set_size(ui->screen_btn_2, 100, 25);
	lv_obj_set_scrollbar_mode(ui->screen_btn_2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn_2_main_main_default
	static lv_style_t style_screen_btn_2_main_main_default;
	if (style_screen_btn_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_btn_2_main_main_default);
	else
		lv_style_init(&style_screen_btn_2_main_main_default);
	lv_style_set_radius(&style_screen_btn_2_main_main_default, 10);
	lv_style_set_bg_color(&style_screen_btn_2_main_main_default, lv_color_make(0x84, 0xc2, 0xf5));
	lv_style_set_bg_grad_color(&style_screen_btn_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_btn_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_btn_2_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_btn_2_main_main_default, 2);
	lv_style_set_shadow_color(&style_screen_btn_2_main_main_default, lv_color_make(0x64, 0x69, 0x6d));
	lv_style_set_shadow_opa(&style_screen_btn_2_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_btn_2_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_screen_btn_2_main_main_default, 2);
	lv_style_set_shadow_ofs_y(&style_screen_btn_2_main_main_default, 3);
	lv_style_set_border_color(&style_screen_btn_2_main_main_default, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn_2_main_main_default, 2);
	lv_style_set_border_opa(&style_screen_btn_2_main_main_default, 255);
	lv_style_set_text_color(&style_screen_btn_2_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_btn_2_main_main_default, &lv_font_simsun_16);
	lv_style_set_text_align(&style_screen_btn_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_btn_2, &style_screen_btn_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_btn_2_label = lv_label_create(ui->screen_btn_2);
	lv_label_set_text(ui->screen_btn_2_label, "Send");
	lv_obj_set_style_pad_all(ui->screen_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_1, 190, 38);
	lv_obj_set_size(ui->screen_label_1, 100, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_1, "");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_1_main_main_default
	static lv_style_t style_screen_label_1_main_main_default;
	if (style_screen_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_label_1_main_main_default);
	else
		lv_style_init(&style_screen_label_1_main_main_default);
	lv_style_set_radius(&style_screen_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_label_1_main_main_default, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_bg_grad_color(&style_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_label_1_main_main_default, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_label_1_main_main_default, 255);
	lv_style_set_text_color(&style_screen_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_letter_space(&style_screen_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_label_1_main_main_default, 4);
	lv_style_set_text_align(&style_screen_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_label_1_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_label_1_main_main_default, 5);
	lv_style_set_pad_top(&style_screen_label_1_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_label_1_main_main_default, 5);
	lv_obj_add_style(ui->screen_label_1, &style_screen_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_screen(ui);
}