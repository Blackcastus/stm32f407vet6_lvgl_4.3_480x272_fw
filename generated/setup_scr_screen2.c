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


void setup_scr_screen2(lv_ui *ui){

	//Write codes screen2
	ui->screen2 = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen2_main_main_default
	static lv_style_t style_screen2_main_main_default;
	if (style_screen2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen2_main_main_default);
	else
		lv_style_init(&style_screen2_main_main_default);
	lv_style_set_bg_color(&style_screen2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen2_main_main_default, 0);
	lv_obj_add_style(ui->screen2, &style_screen2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen2_label0
	ui->screen2_label0 = lv_label_create(ui->screen2);
	lv_obj_set_pos(ui->screen2_label0, 180, 240);
	lv_obj_set_size(ui->screen2_label0, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen2_label0, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen2_label0, "screen2");
	lv_label_set_long_mode(ui->screen2_label0, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen2_label0_main_main_default
	static lv_style_t style_screen2_label0_main_main_default;
	if (style_screen2_label0_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen2_label0_main_main_default);
	else
		lv_style_init(&style_screen2_label0_main_main_default);
	lv_style_set_radius(&style_screen2_label0_main_main_default, 0);
	lv_style_set_bg_color(&style_screen2_label0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_label0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_label0_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_label0_main_main_default, 0);
	lv_style_set_text_color(&style_screen2_label0_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_label0_main_main_default, &lv_font_arial_12);
	lv_style_set_text_letter_space(&style_screen2_label0_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen2_label0_main_main_default, 0);
	lv_style_set_text_align(&style_screen2_label0_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen2_label0_main_main_default, 0);
	lv_style_set_pad_right(&style_screen2_label0_main_main_default, 0);
	lv_style_set_pad_top(&style_screen2_label0_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen2_label0_main_main_default, 0);
	lv_obj_add_style(ui->screen2_label0, &style_screen2_label0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen2_btn1_1
	ui->screen2_btn1_1 = lv_btn_create(ui->screen2);
	lv_obj_set_pos(ui->screen2_btn1_1, 30, 235);
	lv_obj_set_size(ui->screen2_btn1_1, 100, 25);
	lv_obj_set_scrollbar_mode(ui->screen2_btn1_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen2_btn1_1_main_main_default
	static lv_style_t style_screen2_btn1_1_main_main_default;
	if (style_screen2_btn1_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen2_btn1_1_main_main_default);
	else
		lv_style_init(&style_screen2_btn1_1_main_main_default);
	lv_style_set_radius(&style_screen2_btn1_1_main_main_default, 50);
	lv_style_set_bg_color(&style_screen2_btn1_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_btn1_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_btn1_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_btn1_1_main_main_default, 255);
	lv_style_set_border_color(&style_screen2_btn1_1_main_main_default, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen2_btn1_1_main_main_default, 2);
	lv_style_set_border_opa(&style_screen2_btn1_1_main_main_default, 255);
	lv_style_set_text_color(&style_screen2_btn1_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_btn1_1_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen2_btn1_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen2_btn1_1, &style_screen2_btn1_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen2_btn1_1_label = lv_label_create(ui->screen2_btn1_1);
	lv_label_set_text(ui->screen2_btn1_1_label, "Previous Screen");
	lv_obj_set_style_pad_all(ui->screen2_btn1_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen2_btn1_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen2_chart2
	ui->screen2_chart2 = lv_chart_create(ui->screen2);
	lv_obj_set_pos(ui->screen2_chart2, 129, 36);
	lv_obj_set_size(ui->screen2_chart2, 205, 155);
	lv_obj_set_scrollbar_mode(ui->screen2_chart2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen2_chart2_main_main_default
	static lv_style_t style_screen2_chart2_main_main_default;
	if (style_screen2_chart2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen2_chart2_main_main_default);
	else
		lv_style_init(&style_screen2_chart2_main_main_default);
	lv_style_set_radius(&style_screen2_chart2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen2_chart2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_chart2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_chart2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_chart2_main_main_default, 255);
	lv_style_set_border_color(&style_screen2_chart2_main_main_default, lv_color_make(0xe8, 0xe8, 0xe8));
	lv_style_set_border_width(&style_screen2_chart2_main_main_default, 1);
	lv_style_set_border_opa(&style_screen2_chart2_main_main_default, 255);
	lv_style_set_line_color(&style_screen2_chart2_main_main_default, lv_color_make(0xe8, 0xe8, 0xe8));
	lv_style_set_line_width(&style_screen2_chart2_main_main_default, 2);
	lv_style_set_line_opa(&style_screen2_chart2_main_main_default, 255);
	lv_obj_add_style(ui->screen2_chart2, &style_screen2_chart2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_chart_set_type(ui->screen2_chart2, LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->screen2_chart2,LV_CHART_AXIS_PRIMARY_Y, 0, 100);
	lv_chart_set_div_line_count(ui->screen2_chart2, 3, 5);
	lv_chart_set_point_count(ui->screen2_chart2, 10);
	lv_chart_series_t * screen2_chart2_0 = lv_chart_add_series(ui->screen2_chart2, lv_color_make(0x00, 0x00, 0x00), LV_CHART_AXIS_PRIMARY_Y);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 10);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 20);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 30);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 40);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 10);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 50);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 70);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 30);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 10);
	lv_chart_set_next_value(ui->screen2_chart2, screen2_chart2_0, 30);

	//Init events for screen
	events_init_screen2(ui);
}