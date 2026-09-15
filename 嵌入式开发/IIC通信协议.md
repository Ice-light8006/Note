首先要认识SDA和SCL这两个传输线
这两个线默认都是上拉
有一个设备，称为主设备
主设备连接了A，B，C，....个设备，这些设备称为从设备
# 起始标志
在SCL为高电平的时候，当主机把SDA拉低，这时候就是开始的标志，即：

注意这里一定是主机把SDA拉低
因为I²C 总线是**主机主导**的协议：
- **只有主机**才有权产生起始条件和停止条件，控制总线的通信节奏。
- **从机（Slave）** 只能被动响应，它唯一主动拉低 SDA 的时刻，是在被主机选中后、第9个时钟周期拉低 SDA 作为 **ACK** 应答。从机永远不能主动发起起始条件。
# 停止标志
在SCL为高电平期间，主机把SDA从低电平拉到高电平，这时候就触发停止标志
>再强调一下，只有主机才有权限发送起始标志和停止标志，从机没有发送起始标志和停止标志的权限

# ACK与NACK
在SCL为高电平期间，从机把SDA从

首先假定PA0和PA1为SCL、SDA
定义
```c
#define SCL_PORT GPIOA
#define SDA_PORT GPIOA
#define SCL_PIN GPIO_PIN_0
#define SDA_PIN GPIO_PIN_1
```
再定义两个宏函数
```c
#define SCL(x)\
do{x?:HAL_GPIO_WritePin(SCL_PORT,SCL_PIN,GPIO_PIN_SET):\
HAL_GPIO_WritePin(SCL_PORT,SCL_PIN,GPIO_PIN_RESET)}while(0)
```

主设备从从机指定寄存器写数据就是：开始标志、发送从机地址、等待ACK、发送寄存器地址、等待ACK、发送数据、等待ACK、结束标志对吗
