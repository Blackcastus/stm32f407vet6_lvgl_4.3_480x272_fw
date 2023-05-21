#include "lv_bio_safety_main.h"
#include "lvgl.h"

typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
}disp_size_t;

/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size;
static lv_obj_t * tv;
static lv_obj_t * calendar;
static lv_obj_t * calendar_header;
static lv_style_t style_text_muted;
static lv_style_t style_title;
static lv_style_t style_icon;
static lv_style_t style_bullet;

static lv_obj_t * meter1;
static lv_obj_t * meter2;
static lv_obj_t * meter3;

static lv_obj_t * chart1;
static lv_obj_t * chart2;
static lv_obj_t * chart3;

static lv_chart_series_t * ser1;
static lv_chart_series_t * ser2;
static lv_chart_series_t * ser3;
static lv_chart_series_t * ser4;
static const lv_font_t * font_large;
static const lv_font_t * font_normal;

static void home_create(lv_obj_t * parent);

void lv_bio_safety(void)
{
	if(LV_HOR_RES <= 320) disp_size = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size = DISP_MEDIUM;
    else disp_size = DISP_LARGE;

    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;
    lv_coord_t tab_h;
    if(disp_size == DISP_LARGE) 
    {
    	tab_h = 70;
#if LV_FONT_MONTSERRAT_24
        font_large     =  &lv_font_montserrat_24;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_24 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
#if LV_FONT_MONTSERRAT_16
        font_normal    =  &lv_font_montserrat_16;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_16 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
    } 
    else if(disp_size == DISP_MEDIUM) 
    {
        tab_h = 45;
#if LV_FONT_MONTSERRAT_20
        font_large     =  &lv_font_montserrat_20;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_20 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
#if LV_FONT_MONTSERRAT_14
        font_normal    =  &lv_font_montserrat_14;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_14 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
    } 
    else 
    { /* disp_size == DISP_SMALL */
        tab_h = 45;
#if LV_FONT_MONTSERRAT_18
        font_large     =  &lv_font_montserrat_18;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_18 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
#if LV_FONT_MONTSERRAT_12
        font_normal    =  &lv_font_montserrat_12;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_12 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.")
#endif
    }
#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, font_normal);
#endif
    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_large);

    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_large);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);

    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tab_h);

    lv_obj_set_style_text_font(lv_scr_act(), font_normal, 0);

    if(disp_size == DISP_LARGE) {
        lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tv);
        lv_obj_set_style_pad_left(tab_btns, LV_HOR_RES / 2, 0);
        lv_obj_t * logo = lv_img_create(tab_btns);
        LV_IMG_DECLARE(img_lvgl_logo);
        lv_img_set_src(logo, &img_lvgl_logo);
        lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

        lv_obj_t * label = lv_label_create(tab_btns);
        lv_obj_add_style(label, &style_title, 0);
        lv_label_set_text(label, "LVGL v8");
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

        label = lv_label_create(tab_btns);
        lv_label_set_text(label, "Widgets demo");
        lv_obj_add_style(label, &style_text_muted, 0);
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
    }
    //lv_obj_t * t1 = lv_tabview_add_tab(tv, "Home");
    //lv_obj_t * t2 = lv_tabview_add_tab(tv, "Settings");
    //lv_obj_t * t3 = lv_tabview_add_tab(tv, "Visuals");
    home_create(lv_scr_act());
}

static void home_create(lv_obj_t * parent)
{
	lv_obj_t * cont_row = lv_obj_create(parent);
	lv_obj_set_size(cont_row, 480, 100);
	lv_obj_align(cont_row, LV_ALIGN_BOTTOM_MID, 0, 5);
	lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

	/* Create a container with COLUMN flex direction*/
	// lv_obj_t * cont_col = lv_obj_create(parent);
	// lv_obj_set_size(cont_col, 200, 150);
	// lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
	// lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

	for(int i = 0; i < 5; i++)
	{
		lv_obj_t * obj;
		lv_obj_t * label;
		/*Add items to row*/
		obj = lv_btn_create(cont_row);
		lv_obj_set_size(obj, 80, LV_PCT(100));

		label = lv_label_create(obj);
		lv_label_set_text_fmt(label, "Item: %d", i);
		lv_obj_center(label);

		// /* Add items to the column*/
		// obj = lv_btn_create(cont_col);
		// lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

		// label = lv_label_create(obj);
		// lv_label_set_text_fmt(label, "Item: %d", i);
		// lv_obj_center(label);
	}
    
}