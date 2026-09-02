# 什么是PWM方波
**PWM方波**，全称是**脉冲宽度调制方波**（Pulse Width Modulation Square Wave）。它本质上是一种**数字信号**，在固定的周期内，通过高速地“开”（高电平）和“关”（低电平）来模拟出不同的电压输出效果。
通俗的讲就是一种有周期的方波，按照高电平、低电平、高电平、低电平......的规律进行周期变化
类似下面这种波形
```
     ┌────────────┐              ┌────────────┐              ┌────────────
     │            │              │            │              |
─────┘            └──────────────┘            └──────────────┘
```
PWM最重要的三个参数：频率、高电平电压、占空比
频率就是一次高电平+一次低电平的时间
高电平电压就是高电平时具体的电压值，例如3.3V或者5V
**占空比**是PWM方波最核心的参数。就是一个周期内高电平的时间比上周期
PWM可以用来模拟输出电压
虽然PWM只有“开”和“关”两个状态，但如果我们把这个信号送给负载（比如电机或LED），由于机械惯性或人眼视觉暂留效应，设备感受到的**平均电压** = **高电平电压 × 占空比**。
举个例子（假设电压为5V）：
- **占空比 0%**：全程低电平，平均电压 = 0V（设备关闭）。
- **占空比 50%**：一半时间开，一半时间关，平均电压 ≈ 2.5V（电机半速转，LED半亮）。
- **占空比 100%**：全程高电平，平均电压 = 5V（设备全速运转）。
- **占空比 75%**：平均电压 ≈ 3.75V。
所以，**改变占空比就等于改变了输出的“等效模拟电压”**。这也是“脉宽调制”（调制脉冲的宽度）名字的由来。
# CubeMX配置产生PWM方波的方法
STM32 定时器内部有：
- **CNT（计数器）**：不断计数
- **ARR（自动重装载值）**：决定周期
- **CCR（捕获比较寄存器）**：决定高电平持续时间
我们打开STM32CubeMX，忽略其它的配置，专门看定时器生成PWM方波这一块的配置
我们在TIM2的Channel1选择PWM Generation CH1，这样STM32就会在TIM2-CH1对应的引脚按照我们配置的参数输出PWM方波
![](1.png)
下面就是我们可以配置的PWM方波的参数
![](2.png)
可以看到有Mode,Pulse(16 bits value),Output compare preload,Fast Mode,CH Polarity这五个选项，下面我们逐一介绍这几个选项
## Mode
这个有两个选项：
- PWM mode 1
- PWM mode 2
假设：
- 定时器CNT从0递增到ARR
- CCR是比较值
- 通道有效电平为高电平（`OCPolarity = High`）
### PWM mode 1
规则：
```
CNT < CCR：输出有效电平
CNT > CCR：输出无效电平
```
### PWM mode 2
规则：
```
CNT < CCR：输出无效电平
CNT > CCR：输出有效电平
```
---
这就是他们两个的区别

## Pulse(16 bits value)
这个就是PWM的比较值，也就是定时器的CCR寄存器存储的初始值，用于决定PWM的占空比
## Output compare preload
`Output Compare Preload` 是**输出比较寄存器预装载功能**，对应定时器通道的 `OCxPE` 位。它决定你修改 `Pulse/CCR` 后，新的比较值是**立即生效**，还是等到下一个 PWM 周期再生效。
### 不启用 Preload
```
OCxPE = Disable
```
写入 `CCR` 后，新的比较值会直接进入当前工作的比较寄存器。
例如当前正在输出 PWM，计数器已经计数到一半时修改：
```
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, new_pulse);
```
新值可能在当前周期中途生效，导致：
- 当前脉冲突然变长或变短
- 波形出现毛刺
- 周期边界不整齐
- 电机控制、功率控制中出现不希望的瞬态变化
---
### 启用 Preload
```
OCxPE = Enable
```
写入 `CCR` 时，新的值先进入**预装载寄存器**，不会立即影响当前周期。
等发生下一次**更新事件 Update Event** 时，预装载值才被复制到实际比较寄存器。
流程是：
```
写入 CCR
    ↓
进入预装载寄存器
    ↓
等待 Update Event
    ↓
新实际比较寄存器
    ↓
下一个 PWM 周期使用新值
```
这样可以保证占空比在周期边界统一更新，避免当前周期中途改变。
## Fast Mode
### Fast Mode 是什么
`Fast Mode` 是 STM32 定时器输出比较快速响应模式，对应输出比较寄存器中的 `OCxFE` 位。
它用于让输出比较通道对**定时器触发输入（TRGI）**更快响应。

---
### 关闭 Fast Mode
```text
Output Compare Fast Mode = Disable
```
关闭时，输出按照正常的输出比较逻辑工作：
```text
CNT 与 CCR 进行比较
        ↓
达到比较条件
        ↓
OCxREF 输出发生变化
```
PWM 输出主要由以下参数决定：
- PWM Mode 1 或 PWM Mode 2
- `CNT` 当前计数值
- `CCR/Pulse` 比较值
- `ARR/Counter Period` 自动重装载值
- 输出极性 `OC Polarity`

---
### 开启 Fast Mode
```text
Output Compare Fast Mode = Enable
```
开启后，当定时器收到触发输入时，输出比较信号可以更快地响应触发事件，从而减少触发信号到输出变化之间的延迟。
可能的触发来源包括：
- 另一个定时器的 TRGO
- 外部触发输入
- 定时器从模式控制器的触发信号
- 定时器同步控制信号
基本过程可以理解为：
```text
触发输入到来
    ↓
输出比较通道快速响应
    ↓
输出电平发生变化
```

---
### Fast Mode 不代表什么
`Fast Mode` 不表示：
- 提高 PWM 输出频率
- 提高定时器计数频率
- 加快 GPIO 翻转速度
- 自动增大或减小 PWM 占空比
- 让 `Pulse/CCR` 修改立即生效
- 替代 `Output Compare Preload`

---
### Fast Mode 与 Output Compare Preload 的区别

| 配置项 | 主要作用 |
|---|---|
| `Output Compare Preload` | 将新的 `CCR/Pulse` 值暂存起来，在更新事件时生效 |
| `Output Compare Fast Mode` | 让输出比较通道更快响应触发输入 |

例如：
```text
Preload → 决定新的占空比什么时候生效
Fast Mode → 决定触发输入到输出响应的延迟
```
二者解决的是不同问题。

---
### 普通 PWM 是否需要开启
对于以下普通 PWM 应用：
- LED 调光
- 电机调速
- 舵机控制
- 蜂鸣器
- 普通方波输出
通常配置为：
```text
Output Compare Fast Mode = Disable
```
常见的 PWM 配置可以是：
```text
PWM Mode              = PWM Mode 1
OC Polarity           = High
Output Compare Preload = Enable
Output Compare Fast Mode = Disable
```
普通 PWM 通常没有使用定时器触发输入，因此开启 Fast Mode 一般没有实际收益。

---
### 什么时候考虑开启

以下场景可能会使用 Fast Mode：
- 定时器工作在从模式
- PWM 由外部触发信号启动
- 多个定时器之间需要同步
- 需要尽可能缩短触发到输出的延迟
- 特殊脉冲控制
- 某些电机控制或同步控制场景
如果没有明确使用以下功能：
```text
TRGI
External Trigger
Slave Mode
Timer Synchronization
```
通常不建议开启 Fast Mode。

---
### 一句话总结
> `Fast Mode` 用于让输出比较通道更快响应定时器触发输入，不会提高 PWM 频率，也不会改变 PWM 占空比。普通 PWM 输出通常关闭，只有在使用触发同步并且需要降低触发响应延迟时才考虑开启。

## CH Polarity
`CH Polarity` 就是通道的**输出极性**，对应 `OCxP` 位，决定"有效电平"到底是高电平还是低电平。
核心就一句话：**它只翻转引脚最终输出的高低电平，不改变 PWM 的频率和占空比数值。**
- `High`：有效电平 = 高电平，输出正常。
- `Low`：有效电平 = 低电平，输出被硬件反相。