针对STM32F103RCT6
首先要了解一下**页**（Page）的概念，一个页的大小是2KB，页是擦除操作的最小单位
字写入是一次写入一个字（四个字节），半字写入是一次写入一个半字（两个字节）
STM32F103RCT6的Flash写入时只能进行半字写入，Flash在写入的时候只能把某一位的1变成0，不能把某一位的0变成1。并且必须要求半字对齐，也就是半字写入必须写入偶数地址，绝对不能写入奇数地址。写入Flash的过程一般称为**编程**（Programme）
如果你想要把0变成1，就需要一个操作，称为**擦除**（Erase），而擦除的最小单位是页。不可以一个bit一个bit的擦除，也不可以一个半字一个半字的擦除。这是由Flash的硬件特性决定的。
# 操作示例
现在有如下场景：
我在制作一个RFID卡片读取系统，每次读取到的卡片都要把这个卡片的UID存储到Flash中，并实现增删改查的功能
而一个卡片的UID为固定四个字节
由于我们烧写的程序都是烧录在Flash前面的，所以我们为了防止存储卡片信息的Flash和程序的Flash冲突，我们可以把UID信息存储到Flash的最后几页，这里用最后一页存储UID信息
这一页的大小是2KB，也就是2048个字节，可以每八个字节一个栅格，把这一页分为256个栅格
## 存储结构
每一个栅格的结构如下
<div style="width:100%; max-width:774px; margin:16px auto; padding:16px; display:flex; gap:6px; align-items:stretch; border:1px solid var(--background-modifier-border); border-radius:16px; box-sizing:border-box;">

<div style="flex:2; min-width:0; min-height:90px; padding:12px 4px; display:flex; flex-direction:column; align-items:center; justify-content:center; gap:8px; border-radius:12px; background:#DCE9FC; color:#20252C; text-align:center; font-weight:700; box-sizing:border-box;"> <div style="font-size:17px;">字节 0～3</div> <div style="font-size:15px; font-weight:400; color:#2058A9;">UID（4 字节）</div> </div>

<div style="flex:1.2; min-width:0; min-height:90px; padding:12px 4px; display:flex; flex-direction:column; align-items:center; justify-content:center; gap:8px; border-radius:12px; background:#DCF4E5; color:#20252C; text-align:center; font-weight:700; box-sizing:border-box;"> <div style="font-size:16px;">字节 4～5</div> <div style="font-size:14px; font-weight:400; color:#167343;">提交标记</div> </div>

<div style="flex:1; min-width:0; min-height:90px; padding:12px 4px; display:flex; flex-direction:column; align-items:center; justify-content:center; gap:8px; border-radius:12px; background:var(--background-secondary); color:var(--text-normal); text-align:center; font-weight:700; box-sizing:border-box;"> <div style="font-size:16px;">字节 6～7</div> <div style="font-size:14px; font-weight:400; color:var(--text-muted);">预留</div> </div>

</div>
### UID：**卡片唯一标识**
保存 RFID 卡的 4 字节 UID 原始数据。
例如，一张卡的 UID 为 `12 34 AB CD`，那么：

|地址偏移|存储内容|
|---|---|
|`+0`|`0x12`|
|`+1`|`0x34`|
|`+2`|`0xAB`|
|`+3`|`0xCD`|

读取卡片时，将读到的 UID 与这里保存的 UID 比较，即可判断这张卡是否已经注册。
### 提交标记：判断记录是否有效
例如，约定`0xA55A`为有效记录的提交标记。
假设现在要登记一张 UID 为 `12 34 AB CD` 的卡片。
你可能会觉得：只要把这四个字节写入 Flash，登记操作就完成了。但这里存在一个问题：Flash 写入不是一个不可分割的整体操作。STM32F1 的 Flash 通常以 16 位半字为单位进行编程。你的 4 字节 UID 至少需要两次半字编程，而每次编程都可能失败。如果在两次写入之间突然断电，Flash 里就可能只保存了部分 UID。
例如：

|时刻|UID 区域|提交标记|实际情况|
|---|---|---|---|
|初始状态|`FF FF FF FF`|`FFFF`|空白记录|
|第一次写入后|`12 34 FF FF`|`FFFF`|UID 只写了一部分|
|第二次写入后|`12 34 AB CD`|`FFFF`|UID 已写完，但记录尚未提交|
|最后写入后|`12 34 AB CD`|`5A A5`|记录已提交|

约定提交标记的逻辑值是 `0xA55A`，STM32F1 按小端字节顺序观察时，对应字节为 `5A A5`。
问题来了：如果程序重启后，只检查 UID 区域，怎么判断一条记录是完整写入的，还是只写了一半？这就是提交标记存在的原因。
整个写入过程其实分为三个阶段
- 阶段 1：写入 UID：把 `12 34 AB CD` 写入字节 0～3。此时提交标记仍为 `0xFFFF`，程序不能把这条记录视为有效。
- 阶段 2：检查前面的写入结果：检查 UID 写入操作是否成功。只有在前面的数据写入成功后，才继续写提交标记。
- 阶段 3：写入提交标记：将 `0xA55A` 写入字节 4～5。标记成功写入后，程序才将该记录视为已提交。
关键点是：提交标记必须最后写入，不能在 UID 写入之前就写入。
#### 如果中途断电，会发生什么？
我们分别看三种情况。
##### 情况 A：UID 还没写完就断电
```
UID：    12 34 FF FF
标记：   FF FF
```
程序重启后，发现提交标记不是 `0xA55A`，就跳过这条记录，不会把残缺的 UID 当成已登记的卡。
##### 情况 B：UID 已写完，但标记还没写入就断电
```
UID：    12 34 AB CD
标记：   FF FF
```
虽然 UID 看起来完整，但按照软件定义的规则，这条记录仍然无效。
这是一个重要设计：数据看起来完整，不代表写入事务已经正式完成。
##### 情况 C：提交标记已经成功写入
```
UID：    12 34 AB CD
标记：   5A A5
```
程序重启后，检查标记，确认它等于 `0xA55A`，再将 UID 视为有效记录。
注意，这个判断依赖于提交标记写入确实成功。如果在标记编程过程中断电，标记也可能处于异常状态，因此仍然需要检查实际写入结果，并考虑异常记录的处理策略。
提交标记相当于记录的“完成印章”。它让程序能够在重启后区分已提交记录和未提交记录。但是提交标记具有局限性，要实现可靠的 Flash 存储系统，还必须配合错误处理、数据校验以及页管理机制。
### 预留区域：为后续扩展留空间
当前不存储业务数据，可以暂时不使用。
以后可以用来存储：
- 简单校验值或 CRC 的一部分。
- 卡片类型、权限等级等附加信息。
- 记录版本或其他状态信息。
目前保留这两个字节，可以避免未来增加字段时立即修改记录长度。
---
有了这些东西，每一个卡片的UID用一个栅格来写入Flash进行存储，我们就成功实现了Flash能够写入、增加卡片UID，同时也可以查询
## 双页存储
但是，修改和删除如何实现呢？
事实上，只要实现了删除，就已经实现了修改。修改A就相当于把A拿出来修改A得到B，然后删除A，然后再把B写入。
所以我们就需要实现删除。但是，Flash在写入时只能把1变成0，不能把0变成1
如果想要把0变成1，只能把这一整页的0变成1。如果把这一整页的位全变成1，那么其它的UID数据也会跟着遭殃。那我们该怎么办呢
这时候就可以尝试使用双页存储解决。
假如我们使用Flash的两个Page分别是Page 1和Page 2
假如当前使用的页为Page 1，现在Page 1已经有了4个UID信息
```
UID1 UID2 UID3 UID4
```
这时候我们想要删除UID3
就可以这样做：
```
把UID1，UID2，UID4直接拷贝到Page 2中，然后把当前使用的页切换到Page 2，然后把Page 1擦除
```
然后如果在Page 2中还想要删除，就执行类似的操作：
```
把Page 2中除了要删除的数据之外的数据拷贝到Page 1中，然后把当前使用的页切换到Page 1，然后把Page 2擦除
```
但是我们该如何确定当前使用的是哪个页面？
## 页面状态
可以给每个Page定义页面状态，例如：
`ERASE`：空白页，可以写入
`RECEIVING`：正在接收迁移过来的数据。
`VALID`：数据完整，当前可用。
这样启动时，程序可以通过读取页面状态判断哪一页是有效页
