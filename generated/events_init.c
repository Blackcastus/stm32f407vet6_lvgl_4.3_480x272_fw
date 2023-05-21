/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

uint8_t text1 = 1;
void events_init(lv_ui *ui)
{
}

static void screen_btn1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_PRESSED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen2_del == true)
				setup_scr_screen2(&guider_ui);
			lv_scr_load_anim(guider_ui.screen2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
		}
		guider_ui.screen_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_PRESSED:
	{
		lv_obj_set_style_text_font(guider_ui.screen_label_1, &lv_font_simsun_12, 0);
		lv_label_set_text(guider_ui.screen_label_1, text1);
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_btn1, screen_btn1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_btn_2, screen_btn_2_event_handler, LV_EVENT_ALL, NULL);
}

static void screen2_btn1_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_PRESSED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_del == true)
				setup_scr_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.screen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
		}
		guider_ui.screen2_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen2(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen2_btn1_1, screen2_btn1_1_event_handler, LV_EVENT_ALL, NULL);
}
