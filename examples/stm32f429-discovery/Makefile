PROJECT=example-stm32f429-discovery

EXECUTABLE=$(PROJECT).elf
BIN_IMAGE=$(PROJECT).bin
HEX_IMAGE=$(PROJECT).hex

# set the path to your STM32F429I-Discovery_FW_V1.0.1 here: 
STDP=/home/ands/warpzone/arm-stm32/boards/stm32f429-discovery/STM32F429I-Discovery_FW_V1.0.1/

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

LIBS=-lm
CFLAGS=-g -std=c99 -O3 -mlittle-endian -mthumb
CFLAGS+=-mcpu=cortex-m4 -DSTM32F429_439xx
#CFLAGS+=-nostartfiles
#CFLAGS+=-ffreestanding
#CFLAGS+=-nostdlib
#CFLAGS+=--gc-sections

#FPU
CFLAGS+=-mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS+=-DARM_MATH_CM4 -D__FPU_PRESENT

# to run from FLASH
CFLAGS+=-DVECT_TAB_FLASH
CFLAGS+=-Wl,-T,stm32f429zi_flash.ld

#PROJECT SOURCE
CFLAGS+=-I.
SOURCE=*.c
#LIB r3d
CFLAGS+=-I../../libs/r3d/
SOURCE+=../../libs/r3d/*.c
#LIB r3dfb
CFLAGS+=-I../../libs/r3dfb-stm32f429-discovery/
SOURCE+=../../libs/r3dfb-stm32f429-discovery/*.c
#example data
CFLAGS+=-I../meshes/
CFLAGS+=-I../textures/
#L3GD20 default callback
#CFLAGS+=-DUSE_DEFAULT_TIMEOUT_CALLBACK

#STARTUP FILE
SOURCE+=startup_stm32f429_439xx.S

#CMSIS
CFLAGS+=-I$(STDP)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS+=-I$(STDP)/Libraries/CMSIS/Include
SOURCE+=$(STDP)/Libraries/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a

#STemWinLibrary522_4x9i
#CFLAGS+=-I$(STDP)/Libraries/STemWinLibrary522_4x9i/Config
#SOURCE+=$(STDP)/Libraries/STemWinLibrary522_4x9i/Config/*.c
CFLAGS+=-I$(STDP)/Libraries/STemWinLibrary522_4x9i/inc
SOURCE+=$(STDP)/Libraries/STemWinLibrary522_4x9i/Lib/STemWin522_4x9i_CM4_OS_GCC.a

#STM32F4xx_StdPeriph_Driver
CFLAGS+=-DUSE_STDPERIPH_DRIVER
CFLAGS+=-I$(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/inc
#SOURCE+=$(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c <-- compiled separately

#STM32_USB_Device_Library
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Core/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Core/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Class/audio/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Class/audio/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Class/cdc/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Class/cdc/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Class/dfu/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Class/dfu/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Class/hid/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Class/hid/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_Device_Library/Class/msc/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_Device_Library/Class/msc/src/*.c

#STM32_USB_HOST_Library
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_HOST_Library/Core/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_HOST_Library/Core/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_HOST_Library/Class/HID/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_HOST_Library/Class/HID/src/*.c
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_HOST_Library/Class/MSC/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_HOST_Library/Class/MSC/src/*.c

#STM32_USB_OTG_Driver
#CFLAGS+=-I$(STDP)/Libraries/STM32_USB_OTG_Driver/inc
#SOURCE+=$(STDP)/Libraries/STM32_USB_OTG_Driver/src/*.c

#Common Utilities
#CFLAGS+=-I$(STDP)/Utilities/Common
#SOURCE+=$(STDP)/Utilities/Common/*.c

#STM32F429I-Discovery Utilities
CFLAGS+=-I$(STDP)/Utilities/STM32F429I-Discovery
SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery.c
#SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_i2c_ee.c
#SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_ioe.c
SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_l3gd20.c
SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.c
SOURCE+=$(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.c

#Third_Party Utilities
#CFLAGS+=-I$(STDP)/Utilities/Third_Party/fat_fs/inc
#SOURCE+=$(STDP)/Utilities/Third_Party/fat_fs/src/*.c
#SOURCE+=$(STDP)/Utilities/Third_Party/fat_fs/src/option/*.c


all: libSTM32F4xx_StdPeriph_Driver.a $(BIN_IMAGE)

$(BIN_IMAGE): $(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@
	$(OBJCOPY) -O ihex $^ $(HEX_IMAGE)
	arm-none-eabi-objdump -h -S -D $(EXECUTABLE) > $(PROJECT).lst
	arm-none-eabi-size $(EXECUTABLE)
	
$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@ libSTM32F4xx_StdPeriph_Driver.a $(LIBS)
	
libSTM32F4xx_StdPeriph_Driver.a: 
	$(CC) $(CFLAGS) -c -D"assert_param(expr)=((void)0)" $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c
	@$(AR) cr $@ *.o 
	rm -rf *.o

clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
	rm -rf $(HEX_IMAGE)
	rm -rf *.{lst,a}

flash:
	st-flash write $(BIN_IMAGE) 0x8000000

.PHONY: clean
