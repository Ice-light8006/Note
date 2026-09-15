#include "lm75a.h"
#include "i2c.h"

float LM75A_ReadTemperature(void)
{
    uint8_t buffer[2];
    I2C_ReadReg(LM75A_ADDR, LM75A_TEMP_REG, buffer, 2);
#if 0
    //先假写：讲从设备指定的地址写
    if(HAL_I2C_Master_Transmit(&hi2c1, LM75A_WRITE, (uint8_t *)LM75A_TEMP_REG, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("write to reg addr error!\n");
        return -99.0;
    }
 
    //读
    if(HAL_I2C_Master_Receive(&hi2c1, LM75A_READ, buffer, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("read from lm75a error!\n");
        return -99.0;
    }
#endif

    // 组合数据（正确方式）
    uint16_t temp_data = (buffer[0] << 8) | buffer[1];

    // 正确解析温度（使用带符号整数）
    int16_t temp_val = (int16_t)temp_data;
    temp_val >>= 5; // 移除低5位无效数据
    float result;
    // 处理负数温度（二进制补码转换）
    if (temp_val & 0x400)
    {   
        // 检查第10位（11位数据中的符号位）
        // 负温度：转换为原始数值
        result = (float)(temp_val | 0xF800) * 0.125; // 符号扩展
    }
    else
    {
        // 正温度
        result = (float)temp_val * 0.125;
    }

    return result;
}

void LM75A_EnterShutdown(void)
{
    uint8_t config = 0x01;
    uint8_t reg;
    I2C_ReadReg(LM75A_ADDR, LM75A_CONFIG_REG, &reg, 1);
    config = reg | config;
    I2C_WriteReg(LM75A_ADDR, LM75A_CONFIG_REG, &config, 1);
#if 0
    if(HAL_I2C_Master_Transmit(&hi2c1, LM75A_WRITE, (uint8_t *)LM75A_CONFIG_REG, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("write to reg addr error!\n");
    }
 
    //读
    if(HAL_I2C_Master_Transmit(&hi2c1, LM75A_WRITE, &config, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("write to lm75a error!\n");
    }
#endif
}
void LM75A_ExitShutdown(void)
{
    uint8_t config = 0xfE;
    uint8_t reg;
    I2C_ReadReg(LM75A_ADDR, LM75A_CONFIG_REG, &reg, 1);
    config = reg & config;
    I2C_WriteReg(LM75A_ADDR, LM75A_CONFIG_REG, &config, 1);
    HAL_Delay(2000);

#if 0
    if(HAL_I2C_Master_Transmit(&hi2c1, LM75A_WRITE, (uint8_t *)LM75A_CONFIG_REG, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("write to reg addr error!\n");
    }
 
    if(HAL_I2C_Master_Transmit(&hi2c1, LM75A_WRITE, &config, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("write to lm75a error!\n");
    }
#endif
}
