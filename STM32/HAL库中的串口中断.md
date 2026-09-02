```c
HAL_UART_Receive_IT(&huart1, &rx_data, 1U);
```
这个函数中的每一个参数的含义如下
```
huart1:传入的UART句柄
rx_data:输入的数据存储在这个指针指向的内存空间
1U:读入1个字节的数据。如果是2U那么就是读入2个字节的数据
```
这里这个`IT`的意思就是
```
Interrupt
```
即“中断”的英文
假如我们调用
```c
HAL_UART_Receive_IT(&huart1, &rx_data, 1U);
```
程序就会启动等待输入一个字节的数据，如果成功读入到一个字节的数据，那么就会调用回调函数
```c
HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
```
同时这个回调函数的参数就是你当时传给函数`HAL_UART_Receive_IT`的参数
这个函数是非阻塞的，即使上位机没有发送数据，主循环仍会运行
假如有串口USART1
我们写一个简单的串口硬件中断的示例
```c
static uint8_t rx_data;

void bsp_init(void)
{
	HAL_UART_Receive_IT(&huart1,&rx_data,1U);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		if(rx_data=='A')
		{
			led_toggle(LED1);
		}
		
		HAL_UART_Receive_IT(&huart1,&rx_data,1U);
	}
}
```
这个就简单了实现了这个功能：
```
一旦上位机输入一个字符A，那么就翻转灯泡LED1的状态（亮就变为灭，灭就变为亮）
```
注意，这里在回调函数最后一定要加上
```c
HAL_UART_Receive_IT(&huart1,&rx_data,1U);
```
否则，你输入一次A之后，再从上位机输入A就没有任何反应了。
但是`HAL_UART_Receive_IT(&huart1,&rx_data,1U);`这个函数只能接收固定长度的数据。
如果想要接收不确定长度的数据，可以利用下面这个函数
```c
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(
    UART_HandleTypeDef *huart,
    uint8_t *pData,
    uint16_t Size,
    uint16_t *RxLen,
    uint32_t Timeout
);
```
这个函数会在满足下面三个条件的某一个的时候返回
- 超时
- 达到最大长度`Size`
- 检测到IDLE空闲
另外，这个函数是**阻塞的**
如果想非阻塞，就要用这个函数
```c
HAL_UARTEx_ReceiveToIdle_IT(
    &huart1,
    rx_buffer,
    sizeof(rx_buffer)
);
```
它对应的回调函数是
```c
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size);
```
回调函数是本次实际接收到的数据数量
利用`HAL_UARTEx_ReceiveToIdle_IT`函数的具体示例可以看这个例子
```c
uint8_t buf[1024];

void bsp_init()
{
	HAL_UARTEx_ReceiveToIdle_IT(&huart1,buf,sizeof(buf)-1);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
	if(huart->Instance == USART1)
	{
		buf[Size] = '\0';
		if(!strcmp((char*)buf,"AAA"))
		{
			led_toggle(LED1);
		}
		if(!strcmp((char*)buf,"AAAA"))
		{
			led_toggle(LED2);
		}
		
		HAL_UARTEx_ReceiveToIdle_IT(&huart1,buf,sizeof(buf)-1);
	}
}
```