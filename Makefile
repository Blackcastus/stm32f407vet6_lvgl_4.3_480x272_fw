######################################
# target
######################################
TARGET = stm32f407vet6_lvgl_4.3_480x272_fw


#######################################
# check platform and add DIR
#######################################
ifeq ($(OS),Windows_NT)
	OPENOCD_DIR ?= /d/2_Tool/OpenOCD-20211118-0.11.0
	LIB_DIR ?= /c/Users/Black_Life/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2
	CC_PATH ?= "/tools/stm32/gcc/bin"
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OPENOCD_DIR ?= /usr/local
		LIB_DIR ?= /Users/nhantt/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.0
		CC_PATH ?= /Users/nhantt/tools/stm32/gcc-arm-none-eabi-9-2019-q4-major/bin
	endif
	ifeq ($(UNAME_S),Linux)
		OPENOCD_DIR ?= /usr/local
		LIB_DIR ?= /home/smartth/STM32Cube/Repository/stm32cube_fw_f4_v1270/STM32Cube_FW_F4_V1.27.0
		CC_PATH ?= /Users/nhantt/tools/stm32/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
	endif
endif

#Check openocd install global
ISOCD_EXIST := $(shell command -v openocd 2> /dev/null)
ifndef ISOCD_EXIST
	OPENOCD    = $(OPENOCD_DIR)/bin/openocd
else
	OPENOCD    = openocd
endif

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Src/main.c \
Src/ssd1963_fsmc.c \
Src/lv_driver.c \
Src/gt911.c \
Src/gpio.c \
Src/can.c \
Src/dma.c \
Src/fsmc.c \
Src/i2c.c \
Src/iwdg.c \
Src/rtc.c \
Src/spi.c \
Src/usart.c \
Src/stm32f4xx_it.c \
Src/stm32f4xx_hal_msp.c \
FATFS/App/fatfs.c \
FATFS/Target/user_diskio.c \
USB_DEVICE/App/usb_device.c \
USB_DEVICE/App/usbd_desc.c \
USB_DEVICE/App/usbd_cdc_if.c \
USB_DEVICE/Target/usbd_conf.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Core/Src/system_stm32f4xx.c \
$(LIB_DIR)/Middlewares/Third_Party/FatFs/src/diskio.c \
$(LIB_DIR)/Middlewares/Third_Party/FatFs/src/ff.c \
$(LIB_DIR)/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
$(LIB_DIR)/Middlewares/Third_Party/FatFs/src/option/syscall.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/auth.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/ccp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/chap_ms.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/chap-md5.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/chap-new.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/demand.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/eap.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/eui64.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/ipv6cp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/magic.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/mppe.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/multilink.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/pppapi.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/pppcrypt.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/pppoe.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/pppol2tp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/pppos.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/upap.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/utils.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/vj.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/bridgeif.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/lowpan6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/slipif.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/zepif.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/netif/ppp/ecp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/sockets.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/if_api.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/netdb.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/tcpip.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/err.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/netifapi.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/api_lib.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/api_msg.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/api/netbuf.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/memp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/sys.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/inet_chksum.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/raw.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/tcp_out.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ip.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/dns.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/init.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/mem.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/altcp_alloc.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/def.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/udp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/stats.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/tcp_in.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/netif.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/altcp_tcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/tcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/pbuf.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/timeouts.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/altcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/apps/mqtt/mqtt.c \
$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c  \
lvgl/src/core/lv_disp.c \
lvgl/src/core/lv_event.c \
lvgl/src/core/lv_group.c \
lvgl/src/core/lv_indev.c \
lvgl/src/core/lv_indev_scroll.c \
lvgl/src/core/lv_obj.c \
lvgl/src/core/lv_obj_class.c \
lvgl/src/core/lv_obj_draw.c \
lvgl/src/core/lv_obj_pos.c \
lvgl/src/core/lv_obj_scroll.c \
lvgl/src/core/lv_obj_style.c \
lvgl/src/core/lv_obj_style_gen.c \
lvgl/src/core/lv_obj_tree.c \
lvgl/src/core/lv_refr.c \
lvgl/src/core/lv_theme.c \
lvgl/src/draw/lv_draw_arc.c \
lvgl/src/draw/lv_draw_blend.c \
lvgl/src/draw/lv_draw_img.c \
lvgl/src/draw/lv_draw_label.c \
lvgl/src/draw/lv_draw_line.c \
lvgl/src/draw/lv_draw_mask.c \
lvgl/src/draw/lv_draw_rect.c \
lvgl/src/draw/lv_draw_triangle.c \
lvgl/src/draw/lv_img_buf.c \
lvgl/src/draw/lv_img_cache.c \
lvgl/src/draw/lv_img_decoder.c \
lvgl/src/extra/lv_extra.c \
lvgl/src/extra/layouts/flex/lv_flex.c \
lvgl/src/extra/layouts/grid/lv_grid.c \
lvgl/src/extra/themes/basic/lv_theme_basic.c \
lvgl/src/extra/themes/default/lv_theme_default.c \
lvgl/src/extra/themes/mono/lv_theme_mono.c \
lvgl/src/extra/widgets/animimg/lv_animimg.c \
lvgl/src/extra/widgets/calendar/lv_calendar.c \
lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
lvgl/src/extra/widgets/chart/lv_chart.c \
lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c \
lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c \
lvgl/src/extra/widgets/keyboard/lv_keyboard.c \
lvgl/src/extra/widgets/led/lv_led.c \
lvgl/src/extra/widgets/list/lv_list.c \
lvgl/src/extra/widgets/meter/lv_meter.c \
lvgl/src/extra/widgets/msgbox/lv_msgbox.c \
lvgl/src/extra/widgets/span/lv_span.c \
lvgl/src/extra/widgets/spinbox/lv_spinbox.c \
lvgl/src/extra/widgets/spinner/lv_spinner.c \
lvgl/src/extra/widgets/tabview/lv_tabview.c \
lvgl/src/extra/widgets/tileview/lv_tileview.c \
lvgl/src/extra/widgets/win/lv_win.c \
lvgl/src/font/lv_font.c \
lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c \
lvgl/src/font/lv_font_fmt_txt.c \
lvgl/src/font/lv_font_loader.c \
lvgl/src/font/lv_font_montserrat_10.c \
lvgl/src/font/lv_font_montserrat_12.c \
lvgl/src/font/lv_font_montserrat_12_subpx.c \
lvgl/src/font/lv_font_montserrat_14.c \
lvgl/src/font/lv_font_montserrat_16.c \
lvgl/src/font/lv_font_montserrat_18.c \
lvgl/src/font/lv_font_montserrat_20.c \
lvgl/src/font/lv_font_montserrat_22.c \
lvgl/src/font/lv_font_montserrat_24.c \
lvgl/src/font/lv_font_montserrat_26.c \
lvgl/src/font/lv_font_montserrat_28.c \
lvgl/src/font/lv_font_montserrat_28_compressed.c \
lvgl/src/font/lv_font_montserrat_30.c \
lvgl/src/font/lv_font_montserrat_32.c \
lvgl/src/font/lv_font_montserrat_34.c \
lvgl/src/font/lv_font_montserrat_36.c \
lvgl/src/font/lv_font_montserrat_38.c \
lvgl/src/font/lv_font_montserrat_40.c \
lvgl/src/font/lv_font_montserrat_42.c \
lvgl/src/font/lv_font_montserrat_44.c \
lvgl/src/font/lv_font_montserrat_46.c \
lvgl/src/font/lv_font_montserrat_48.c \
lvgl/src/font/lv_font_montserrat_8.c \
lvgl/src/font/lv_font_simsun_16_cjk.c \
lvgl/src/font/lv_font_unscii_16.c \
lvgl/src/font/lv_font_unscii_8.c \
lvgl/src/hal/lv_hal_disp.c \
lvgl/src/hal/lv_hal_indev.c \
lvgl/src/hal/lv_hal_tick.c \
lvgl/src/misc/lv_anim.c \
lvgl/src/misc/lv_area.c \
lvgl/src/misc/lv_async.c \
lvgl/src/misc/lv_bidi.c \
lvgl/src/misc/lv_color.c \
lvgl/src/misc/lv_fs.c \
lvgl/src/misc/lv_gc.c \
lvgl/src/misc/lv_ll.c \
lvgl/src/misc/lv_log.c \
lvgl/src/misc/lv_math.c \
lvgl/src/misc/lv_mem.c \
lvgl/src/misc/lv_printf.c \
lvgl/src/misc/lv_style.c \
lvgl/src/misc/lv_style_gen.c \
lvgl/src/misc/lv_templ.c \
lvgl/src/misc/lv_timer.c \
lvgl/src/misc/lv_tlsf.c \
lvgl/src/misc/lv_txt.c \
lvgl/src/misc/lv_txt_ap.c \
lvgl/src/misc/lv_utils.c \
lvgl/src/widgets/lv_arc.c \
lvgl/src/widgets/lv_bar.c \
lvgl/src/widgets/lv_btn.c \
lvgl/src/widgets/lv_btnmatrix.c \
lvgl/src/widgets/lv_canvas.c \
lvgl/src/widgets/lv_checkbox.c \
lvgl/src/widgets/lv_dropdown.c \
lvgl/src/widgets/lv_img.c \
lvgl/src/widgets/lv_label.c \
lvgl/src/widgets/lv_line.c \
lvgl/src/widgets/lv_objx_templ.c \
lvgl/src/widgets/lv_roller.c \
lvgl/src/widgets/lv_slider.c \
lvgl/src/widgets/lv_switch.c \
lvgl/src/widgets/lv_table.c \
lvgl/src/widgets/lv_textarea.c \
lv_demos/src/lv_demo_widgets/lv_demo_widgets.c \
lv_demos/src/lv_demo_widgets/assets/img_clothes.c \
lv_demos/src/lv_demo_widgets/assets/img_demo_widgets_avatar.c \
lv_demos/src/lv_demo_widgets/assets/img_lvgl_logo.c \
lv_bio_safety/lv_bio_safety_main.c \
custom/custom.c \
generated/gui_guider.c \
generated/events_init.c \
generated/setup_scr_screen.c \
generated/setup_scr_screen2.c \
generated/guider_fonts/lv_font_arial_12.c \
generated/guider_fonts/lv_font_simsun_12.c \
generated/guider_fonts/lv_font_simsun_16.c \

# ASM sources
ASM_SOURCES =  \
startup_stm32f407xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx \
-DLV_CONF_INCLUDE_SIMPLE


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IInc \
-IFATFS/Target \
-IFATFS/App \
-ILWIP/App \
-ILWIP/Target \
-IUSB_DEVICE/App \
-IUSB_DEVICE/Target \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/system \
-I$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Inc \
-I$(LIB_DIR)/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-I$(LIB_DIR)/Middlewares/Third_Party/FatFs/src \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/netif/ppp \
-I$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
-I$(LIB_DIR)/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-I$(LIB_DIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/lwip \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/lwip/apps \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/lwip/priv \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/lwip/prot \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/netif \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/compat/posix \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/compat/posix/net \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/src/include/compat/stdc \
-I$(LIB_DIR)/Middlewares/Third_Party/LwIP/system/arch \
-I$(LIB_DIR)/Drivers/CMSIS/Include \
-I$(LIB_DIR)/Drivers/CMSIS/Include \
-Ilvgl \
-Ilvgl/src \
-Ilvgl/src/core \
-Ilvgl/src/draw \
-Ilvgl/src/extra \
-Ilvgl/src/extra/layouts \
-Ilvgl/src/extra/layouts/flex \
-Ilvgl/src/extra/layouts/grid \
-Ilvgl/src/extra/themes \
-Ilvgl/src/extra/themes/basic \
-Ilvgl/src/extra/themes/default \
-Ilvgl/src/extra/themes/mono \
-Ilvgl/src/extra/widgets \
-Ilvgl/src/extra/widgets/animimg \
-Ilvgl/src/extra/widgets/calendar \
-Ilvgl/src/extra/widgets/chart \
-Ilvgl/src/extra/widgets/colorwheel \
-Ilvgl/src/extra/widgets/imgbtn \
-Ilvgl/src/extra/widgets/keyboard \
-Ilvgl/src/extra/widgets/led \
-Ilvgl/src/extra/widgets/list \
-Ilvgl/src/extra/widgets/meter \
-Ilvgl/src/extra/widgets/msgbox \
-Ilvgl/src/extra/widgets/span \
-Ilvgl/src/extra/widgets/spinbox \
-Ilvgl/src/extra/widgets/spinner \
-Ilvgl/src/extra/widgets/tabview \
-Ilvgl/src/extra/widgets/tileview \
-Ilvgl/src/extra/widgets/win \
-Ilvgl/font \
-Ilvgl/hal \
-Ilvgl/misc \
-Iwidgets \
-Ilv_demos \
-Ilv_demos/src \
-Ilv_demos/src/lv_demo_widgets \
-Ilv_bio_safety \



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F407VGTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# flash
#######################################

# flash:
# 	openocd 	-f interface/stlink-v2.cfg \
# 				-f target/stm32f4x.cfg \
# 		        -c init -c targets -c "reset halt" \
# 		        -c "flash write_image erase $(BUILD_DIR)/$(TARGET).hex" \
# 		        -c "verify_image $(BUILD_DIR)/$(TARGET).hex" \
# 		        -c "reset run" -c shutdown

flash:
	$(OPENOCD) 	-f interface/stlink-v2.cfg \
				-f target/stm32f1x.cfg \
		        -c init -c targets -c "reset halt" \
		        -c "flash write_image erase $(BUILD_DIR)/$(TARGET).hex" \
		        -c "verify_image $(BUILD_DIR)/$(TARGET).hex" \
		        -c "reset run" -c shutdowns
				
#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***