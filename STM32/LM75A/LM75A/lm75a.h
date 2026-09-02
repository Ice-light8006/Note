#ifndef __LM75A_H__
#define __LM75A_H__

#include "main.h"
#include <stdio.h>

// 设备地址（A2-A0=111）
#define LM75A_ADDR     0x4F    // 7位地址
#define LM75A_WRITE    ((LM75A_ADDR << 1) | 0)  // 0x9E
#define LM75A_READ     ((LM75A_ADDR << 1) | 1)  // 0x9F

#define LM75A_TEMP_REG     0x00
#define LM75A_CONFIG_REG   0x01



float LM75A_ReadTemperature(void);
void LM75A_EnterShutdown(void);
void LM75A_ExitShutdown(void);

#endif


