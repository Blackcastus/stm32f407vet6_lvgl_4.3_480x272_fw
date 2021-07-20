#include "../lvgl/lvgl.h"
#include "../lv_conf.h"

//void ILI9341_flush(struct _disp_drv_t *, const lv_area_t * , lv_color_t * );
//void ILI9341_flush(lv_disp_drv_t *, const lv_area_t * , lv_color_t * );
void tft_init(void);
void SSD1963_flush(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map);