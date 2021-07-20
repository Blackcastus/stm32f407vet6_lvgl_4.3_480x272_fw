#include "main.h"
#include "can.h"
#include "fatfs.h"
#include "i2c.h"
#include "iwdg.h"
#include "lwip.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "fsmc.h"
#include "dma.h"
#include "ssd1963_fsmc.h"
#include "lv_driver.h"
#include "../lvgl/lvgl.h"
#include "../lv_demos/lv_demo.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "gt911.h"

/* Declare printf function */
int _write(int file, char *data, int len);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

GT911_Config_t sampleConfig = {.X_Resolution = 480, .Y_Resolution = 272, .Number_Of_Touch_Support = 1, .ReverseY = true, .ReverseX = true, .SwithX2Y = true, .SoftwareNoiseReduction = true};
TouchCordinate_t cordinate[5];
uint8_t number;
uint8_t touch_int = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0)
  {
    printf("touch interrupt \n");
    touch_int = 1;
  }
}


void touch_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  if(touch_int == 1)
  {
    data->point.x = cordinate[0].x;
    data->point.y = cordinate[0].y;
    data->state = LV_INDEV_STATE_PR;
    printf("(x, y) = (%d, %d) \n", data->point.x, data->point.y);
    touch_int = 0;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void lv_example_get_started_1(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    //lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_CAN1_Init();
  MX_FSMC_Init();
  MX_I2C1_Init();
  GT911_Init(sampleConfig);
  lv_init(); 
  //tft_init();
  //LCD_Init();
  tft_init();

  // static lv_disp_draw_buf_t disp_buf;
  // static lv_color_t buf_1[480 * 10];
  // static lv_color_t buf_2[480 * 10];
  // lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 480 * 10);

  // lv_disp_drv_t disp_drv;
  // lv_disp_drv_init(&disp_drv);
  // disp_drv.draw_buf = &disp_buf;
  // disp_drv.flush_cb = SSD1963_flush;
  // disp_drv.hor_res = 480;
  // disp_drv.ver_res = 272;
  // lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touch_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);
  //lv_example_get_started_1();
  lv_demo_widgets();
  //MX_I2C1_Init();
  //MX_I2C3_Init();
  //MX_IWDG_Init();
  //MX_RTC_Init();
  //MX_SPI1_Init();
  //MX_SPI2_Init();
  //MX_SPI3_Init();
  //MX_USART1_UART_Init();
  //MX_USART6_UART_Init();
  //MX_FATFS_Init();
  //MX_LWIP_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t tick = HAL_GetTick();
  uint8_t buff[2];
  uint32_t id;
  uint8_t status;
  while (1)
  {
    /* USER CODE END WHILE */
    if(HAL_GetTick() - tick >= 5)
    {
      GT911_ReadTouch(cordinate, &number);
      lv_task_handler();
      // printf("(x, y) = (%d, %d) \n", cordinate[0].x, cordinate[0].y);
      // printf("STT: %d\n", GT911_GetProductID(&id));
      // printf("id: %x \n", id);
      //printf("Hello World\n");
      tick = HAL_GetTick();
    }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int _write(int file, char *data, int len)
{
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
  {
    errno = EBADF;
    return -1;
  }
  uint8_t status = CDC_Transmit_FS((uint8_t *)data, len);
  return status;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
