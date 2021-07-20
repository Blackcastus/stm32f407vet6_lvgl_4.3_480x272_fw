#include "ssd1963_fsmc.h"
#include "lv_driver.h"
#include <stdio.h>
#include "dma.h"

static void tft_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_p);
void monitor_cb(lv_disp_drv_t * d, uint32_t time, uint32_t px);
static lv_disp_drv_t disp_drv;
static volatile int32_t x1_flush;
static volatile int32_t y1_flush;
static volatile int32_t x2_flush;
static volatile int32_t y2_flush;
static volatile int32_t y_flush_act;
static volatile const lv_color_t * buf_to_flush;

static volatile bool refr_qry;
static volatile uint32_t t_last = 0;

static void DMA_TransferComplete(DMA_HandleTypeDef *han);
static void DMA_TransferError(DMA_HandleTypeDef *han);

void tft_init(void)
{
  	MX_DMA_Init();
  	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferComplete);
  	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_ERROR_CB_ID, DMA_TransferError);

  	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
 	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  	
  	LCD_Init();
  	static lv_disp_draw_buf_t disp_buf;
  	static lv_color_t buf_1[480 * 10];
 	static lv_color_t buf_2[480 * 10];
  	lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 480 * 10);
  	lv_disp_drv_init(&disp_drv);
  	disp_drv.draw_buf = &disp_buf;
  	disp_drv.monitor_cb = monitor_cb;
  	disp_drv.flush_cb = SSD1963_flush;
  	disp_drv.hor_res = 480;
  	disp_drv.ver_res = 272;
  	lv_disp_drv_register(&disp_drv);
}

/* TFT DMA buffsize: 480 */

// static void tft_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_p)
// {
// 	int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
// 	int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
// 	int32_t act_x2 = area->x2 > (480-1) ? (480-1) : area->x2;
// 	int32_t act_y2 = area->y2 > (272-1) ? (272-1) : area->y2;

// 	x1_flush = act_x1;
// 	y1_flush = act_y1;
// 	x2_flush = act_x2;
// 	y2_flush = act_y2;
// 	y_flush_act = act_y1;
// 	buf_to_flush = color_p;
// 	HAL_StatusTypeDef err;

// 	LCD_Window(y_flush_act, x1_flush, y_flush_act+1, x2_flush);

// 	// uint32_t size = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);
// 	// err = HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)buf_to_flush, (uint32_t)&DAT, size);
// 	err = HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)buf_to_flush, (uint32_t)&DAT, (x2_flush - x1_flush + 1));
// 	printf("size: %d\n", (x2_flush - x1_flush + 1));
// 	if(err != HAL_OK)
// 	{
// 		while(1);
// 	}

// }

// static void DMA_TransferComplete(DMA_HandleTypeDef *han)
// {
// 	y_flush_act++;
// 	if(y_flush_act > y2_flush) {
// 		lv_disp_flush_ready(&disp_drv);
// 	} else {
// 		buf_to_flush += x2_flush - x1_flush + 1;
// 		HAL_StatusTypeDef err;
// 		LCD_Window(y_flush_act, x1_flush, y_flush_act + 1, x2_flush);
// 		err = HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)buf_to_flush, (uint32_t)&DAT, (x2_flush - x1_flush + 1));
// 		if(err != HAL_OK)
// 		{
// 			while(1);
// 		}
// 	}
// }

static void DMA_TransferComplete(DMA_HandleTypeDef *han)
{
	lv_disp_flush_ready(&disp_drv);
}

static void DMA_TransferError(DMA_HandleTypeDef *han)
{
	while(1);
}

void DMA_STREAM_IRQHANDLER(void)
{
    /* Check the interrupt and clear flag */
    HAL_DMA_IRQHandler(&hdma_memtomem_dma2_stream0);
}

void SSD1963_flush(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map)
{
	LCD_Window((uint16_t)area->y1, (uint16_t)area->x1, (uint16_t)area->y2, (uint16_t)area->x2);
	uint32_t size = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);
	//printf("size: %d\n", size);
	buf_to_flush = color_map;
	/* Flush color data used DMA */
	HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)buf_to_flush, (uint32_t)&DAT, size);

	/* Flush color data not used DMA */
	// for(uint32_t i = 0; i < size; i++)
	// {
	// 	//LCD_Send_Dat(H24_RGB565(1, *(color_map+i)));
	// 	LCD_Send_Dat(*(color_map+i));
	// }
    // lv_disp_flush_ready(drv);
}

void monitor_cb(lv_disp_drv_t * d, uint32_t time, uint32_t px)
{
	printf("%d px refreshed in %d ms\n", px, time);
}
