#ifndef  __BR00X_CONFIG_H_
#define  __BR00X_CONFIG_H_


#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#define UART1_DEBUG_LOG

//Basic information output macro definition
#define DEBUG_LOG

#define BASE_DEBUG_LOG
#define GPIO_DEBUG_LOG
#define RTC_DEBUG_LOG
#define DMA_DEBUG_LOG
#define WDT_DEBUG_LOG
#define UART_DEBUG_LOG
#define MESSAGE_DEBUG_LOG
#define TIMERS_DEBUG_LOG
#define I2C_DEBUG_LOG
#define I2S_DEBUG_LOG
#define SPI_DEBUG_LOG
#define MESSAGE_OFFS_DEBUG_LOG
#define VRGH_DEBUG_LOG
#define SCU_DEBUG_LOG
#define USB_DEBUG_LOG

#ifdef BR002
#include "BR002.h"
#endif

#ifdef BR003
#include "BR003.h"
#endif


#ifdef BR1051Axx
#include "BR1051Axx.h"
#endif

#ifdef BR005
#include "BR005.h"
#endif



#endif //__BR00X_CONFIG_H_

