# 提示符
例如你打开 Linux 终端，可能看到：
```
$
```
或者：
```
#
```
或者：
```
tom@ubuntu:~$
```
这里最后的：
```
$
```
就是提示符的一部分。
它的意思是：
```
Shell 已经准备好了
请用户输入命令
```
# 什么是Shell?
你打开一个终端：
```
$
```
实际上背后运行着一个程序，例如：
```
bash
```
或者：
```
zsh
```
这个程序就叫 **Shell（命令解释器）**。
它负责：
```
你输入命令
↓
Shell 解析命令
↓
执行命令
↓
返回结果
```
# 通配符`*`与`?`
`*`表示任意长度的字符串
`?`表示任意单个字符（注意，仅表示单个字符而不是多个字符）
## `*`的示例
- `*.txt`
	- 匹配：
		- `a.txt`
		- `123.txt`
		- `doc.txt`
	- 不匹配：
		- `a.doc`
		- `m.c`
		- `main.c`
- `data*`
	- 匹配：
		- `datadatadata`
		- `data1235213`
		- `data.txt`
	- 不匹配
		- `123data`
		- `lllldatalll`
## `?`的示例
- `a?.txt`
	- 匹配：
		- `ab.txt`
		- `a11.txt`
		- `a?.txt`
	- 不匹配：
		- `ba.txt`
		- `aa.doc`
		- `a11.txt`
# 常用命令
## `echo`
`echo`的作用就一句话：
· 把指定的内容输出到终端（标准输出）或者文件。
最简单的例子：
```bash
echo Hello
```
输出：
```
Hello
```
### 输出字符串
```bash
echo "Hello World"
```
输出：
```
Hello World
```
也可以不加引号：
```
echo Hello World
```
效果是一样的
### 输出变量
例如
```bash
name="Alice"
echo name
```
输出：
```
Alice
```
或者
```
echo "My name is $name"
```
输出：
```
My name is Alice
```
### 示环境变量
例如显示当前用户：
```bash
echo $USER
```
显示当前目录：
```bash
echo $PWD
```
显示家目录：
```bash
echo $HOME
```
## `cat`,`more`,`less`-查看文件内容
主要看看它们三个之间的区别

| 命令     | 特点           | 适合场景 |
| ------ | ------------ | ---- |
| `cat`  | 一次性输出全部内容    | 小文件  |
| `more` | 分页查看，只能向下翻   | 中等文件 |
| `less` | 分页查看，可上下翻、搜索 | 大文件  |
## `export`-设置环境变量
最常见的用法：
```bash
export NAME=Tom
```
此时创建了一个环境变量`NAME`
```bash
NAME
```
输出：
```
Tom
```
### export 和普通变量有什么区别？
先看什么是子Shell
在一个 Shell 里面再启动一个 Shell：
```
bash
```
例如：
```
$ bash
$
```
你会发现提示符没什么变化，但实际上已经进入了一个新的 Bash 进程。
此时：
```
原来的 Shell
    │    
    └── 新启动的 Bash
```
新的 Bash 就是 **子 Shell（Child Shell）**。
#### 普通变量
```
NAME=Tom
```
查看：
```
echo $NAME
```
输出：
```
Tom
```
但是如果启动一个子 Shell：
```
bash
```
再查看：
```
echo $NAME
```
结果：
没有值。
因为普通变量只属于当前 Shell。

---
#### export 变量
```
export NAME=Tom
```
启动子 Shell：
```
bash
```
再查看：
```
echo $NAME
```
输出：
```
Tom
```
因为：
```
export
↓
把变量加入环境变量表
↓
子进程也能继承
``` 
---
# 系统管理和进程管理常用指令
## `top`-Linux的任务管理器
运行后会不断刷新：
```
top - 15:30:21
Tasks: 256 total
Cpu(s): 12.5% us
MiB Mem : 7972 total

PID   USER   %CPU   %MEM   COMMAND
1234  root   35.2   2.1    nginx
5678  tom    10.1   1.5    python
```

| 字段      | 含义    |
| ------- | ----- |
| PID     | 进程号   |
| USER    | 所属用户  |
| %CPU    | CPU占用 |
| %MEM    | 内存占用  |
| COMMAND | 进程名称  |
常用操作：
```
q 退出
P 按CPU排序
M 按内存排序
```
---
## `ps aux` - 查看进程列表
查看当前系统所有进程：
```bash
ps aux
```
输出：
```
USER      PID %CPU %MEM COMMAND
root        1  0.0  0.1 systemd
root      500  0.3  1.2 nginx
tom      3000  5.5  3.4 python
```
### 配合`grep`搜索
查看nginx
```bash
ps aux | grep nginx
```
查看python
```
ps aux | grep python
```
这些是很常用的写法

---
## `kill` - 终止进程
先找到PID：
```bash
ps aux | grep python
```
例如：
```
tom 3000 5.5 3.4 python
```
PID是：
```
3000
```
结束进程：
```bash
kill 3000
```

---
## `useradd` - 添加用户
创建用户
```bash
sudo useradd tom
```
查看：
```bash
cat /etc/passwd
```
会发现：
```
tom:x:1001:1001::/home/tom:/bin/bash
```
### 自动创建家目录
很多系统推荐：
```bash
sudo useradd -m tom
```
创建：
```
/home/tom
```
目录。

---
## `passwd` - 设置密码
给用户设置密码：
```bash
sudo passwd tom
```
系统显示：
```
New password:
Retype new password:
```
输入两次即可。
修改自己的密码：
```bash
passwd
```
无需指定用户名

---
## `chmod` - 修改文件权限
先介绍一下Linux文件权限：
```
r = 读（read）
w = 写（write）
x = 执行（eXecute）
```
查看权限
```bash
ls -l
```
先介绍一下这个命令的输出结果
例如：
```
-rw-r--r-- 1 tom tom 1234 Jun 15 10:00 test.txt
```
这一行可以拆成这几个部分：
```
-rw-r--r--   1   tom    tom   1234   Jun 15 10:00   test.txt
│            │    │     │      │          │             │
权限信息     链接数 所有者 所属组 大小       修改时间      文件名
```
我们这里重点介绍权限信息
### 第一个字符
```
-rw-r--r--
↑
```
表示文件类型
- `-`：表示普通文件
- `d`：表示目录（文件夹）
- `l`：表示软链接
例如：
```
drwxr-xr-x
```
开头是d，说明是目录
### 后面九个字符
```
rw-r--r--
```
分成三组：
```
rw- | r-- | r--
```
分别表示：
```
所有者 | 同组用户 | 其他用户
```

| 字符  | 含义          |
| --- | ----------- |
| r   | read（读）     |
| w   | write（写）    |
| x   | execute（执行） |
| -   | 没有权限        |
例如：
```
rw-
```
表示：
```
可读
可写
不可执行
```
### 具体分析
```
-rw-r--r--
```
拆开：
```
- | rw- | r-- | r--
```
#### 所有者权限
```
rw-
```
表示：
```
可读
可写
不可执行
```
#### 同组用户权限
```
r--
```
表示：
```
可读
不可写
不可执行
```
#### 其他用户权限
```
r--
```
表示：
```
可读不可写不可执行
```
所以这行权限的意思是：
```
文件拥有者：
    可以看
    可以改
其他所有人：
    只能看
    不能改
```
#### 数字方式
#### 644
```
chmod 644 test.txt
```
等价：
```
rw- r-- r--
```
数字含义：
```
r = 4
w = 2
x = 1
```
所以：
```
rw- = 4+2 = 6
r-- = 4
r-- = 4
```
得到：
```
644
```
#### 755
```
chmod 755 script.sh
```
结果：
```
rwx r-x r-x
```
适合脚本。
#### 符号方式
增加执行权限：
```
chmod +x script.sh
```
去掉执行权限：
```
chmod -x script.sh
```
---
## `df -h` —— 查看磁盘使用情况
```
df -h
```
输出：
```
Filesystem      Size Used Avail Use%
/dev/sda1        50G  20G   28G 40%
```
字段：

|字段|含义|
|---|---|
|Size|总容量|
|Used|已使用|
|Avail|剩余|
|Use%|使用率|

为什么加 `-h`？
```
df
```
显示：
```
52428800
```
单位是字节，很难看。
```
df -h
```
显示：
```
50G
```
更友好。

---
## `free -m` —— 查看内存使用情况

```
free -m
```
输出：
```
              total used free
Mem:           7972 3210 4762
Swap:          2048    0 2048
```
单位：
```
MB
```
因为：
```
-m
```
表示：
```
Megabyte
```
常见参数：
```
free -h
```
自动显示：
```
7.8Gi
512Mi
```
更推荐。

---
# 常用文件操作命令
对于文件操作，我们先要理解路径中`/`的含义：
- 路径以 `/` 开头 → **绝对路径**（从根目录开始找）
- 路径不以 `/` 开头 → **相对路径**（从当前工作目录开始找）
## `cp`,`mv`,`rm`
这三个是最常用的文件操作指令

| 命令   | 英文     | 作用        |     |
| ---- | ------ | --------- | --- |
| `cp` | copy   | 复制文件或者目录  |     |
| `mv` | move   | 移动文件或者重命名 |     |
| `rm` | remove | 删除文件或者目录  |     |
常见格式：
```bash
cp 源路径 目标路径
mv 源路径 目标路径
rm 路径
```
### `cp`指令
#### 复制文件
假设当前目录有
```
a.txt
```
使用这个命令
```bash
cp a.txt b.txt
```
结果，会把`a.txt`复制一份并重命名为`b.txt`，然后放在与`a.txt`相同的目录下
```
a.txt
b.txt
```
#### 复制到另一个目录
```bash
cp a.txt /home/user/
```
效果：
```
/home/user/a.txt
```
#### 复制多个文件
```bash
cp a.txt b.txt /backup/
```
相当于：
```
把a.txt与b.txt都复制到backup目录
```
#### 复制目录
直接像下面这样复制目录会报错
```bash
cp mydir backup
```
需要添加递归选项
```bash
cp -r mydir backup
```
但是仅仅针对于这个代码，其实有好几种情况。
要看 `backup` 是否已经存在，以及它是什么类型。
假设当前目录是：
```
/home/ice
```
---
##### 情况1：backup 不存在
当前：
```
/home/ice
└── mydir
```
执行：
```bash
cp -r mydir backup
```
结果：
```
/home/ice
├── mydir
└── backup
```
这里的 `backup` 是**新复制出来的目录**，内容和 `mydir` 一模一样。
相当于：
```
复制一份 mydir改名叫 backup
```
---
##### 情况2：backup 已存在，并且是目录
当前：
```
/home/ice
├── mydir
└── backup
```
执行：
```bash
cp -r mydir backup
```
结果：

```
/home/ice
├── mydir
└── backup
    └── mydir
```
此时会把 `mydir` 整个复制到 `backup` 里面。
相当于：
```
cp -r mydir backup/mydir
```
---
##### 情况3：backup 已存在，并且是普通文件
例如：
```
/home/ice
├── mydir/
└── backup
```
其中 `backup` 是文件而不是目录。
执行：
```
cp -r mydir backup
```
通常会报错：
```
cp: cannot overwrite non-directory 'backup' with directory 'mydir'
```
因为目录不能直接覆盖普通文件。

---
### `mv`指令
移动、重命名。
#### 重命名
```bash
mv old.txt new.txt
```
效果就是文件`old.txt`的名字改为了`new.txt`

>mv 的本质是修改目录项。
>如果源路径和目标路径位于同一个文件系统中，
>通常不会真的复制数据，
>而是直接修改文件名或目录记录，
>因此速度非常快。
#### 移动文件
```bash
mv a.txt docs/
```
效果：
当前工作目录下的`a.txt`文件被移动到了当前工作目录下的`docs`文件夹内部
#### 移动多个文件
```bash
mv a.txt b.txt docs/
```
结果：
```
docs/
 ├── a.txt
 └── b.txt
```
#### 重命名目录
```bash
mv olddir newdir
```
效果：
```
olddir
↓
newdir
```
#### 常见参数
##### `-i`
覆盖前询问
```bash
mv -i a.txt b.txt
```
`-v`
显示过程
```bash
mv -v a.txt docs/
```
输出
```
renamed 'a.txt' -> 'docs/a.txt'
```
---
### `rm`指令
这是Linux最危险的命令之一
#### 删除文件
```bash
rm a.txt
```
直接删除，没有回收站
#### 删除多个文件
```bash
rm a.txt b.txt c.txt
```
全部删除
#### 删除目录
```
rm mydir
```
直接这样通常会报错，要加上递归删除`-r`
```
rm -r mydir
```
#### 强制删除
```bash
rm -f a.txt
```
即使只读文件也删除，不会询问。
#### 递归强制删除
```bash
rm -rf mydir
```
这是LInux圈子最著名的命令之一
效果：把整个目录树全部删掉，不做任何询问
使用这个命令一定要谨慎！！！

---
## `wc`
`wc`命令的全称是：
```
word count
```
意思是：
- 统计文本的信息
它可以统计
- 行数（line）
- 单词数（word）
- 字节数（byte）
- 字符数（character）
### 先看一个例子
文件 `data.txt`：
```
hello
world
linux
```
执行：
```
wc data.txt
```
可能输出：
```
3 3 18 data.txt
```
含义：
```
3行 3个单词 18个字节 文件名
```
因为：
```
hello
world
linux
```
有：
- 3 行
- 3 个单词
- 共 18 个字节（包括换行符）
### `-l` 是什么意思？
`l` 表示：
```
line（行）
```
所以：
```
wc -l data.txt
```
只统计行数：
```
3
```
# 输入输出与重定向
## 什么是重定向？
当一个命令运行时，会有三个默认通道

| 名称     | 缩写     | 默认连接 |
| ------ | ------ | ---- |
| 标准输入   | stdin  | 键盘   |
| 标准输出   | stdout | 屏幕   |
| 标准错误输出 | stderr | 屏幕   |
重定向就是，当执行命令时，不让它从键盘读，也不让它往屏幕写，而是从文件读从文件写
## 输入重定向(`<`)
语法：
```bash
命令 < 文件名
```
### 举例
假设有文件：
```data.txt
hello
world
linux
```
执行：
```
wc -l < data.txt
```
意思：
```
把 data.txt 的内容作为 wc 的输入
```
结果：
```
3
```
因为有 3 行。
### 不用重定向怎么办？
如果直接运行：
```
wc -l
```
系统会等待你输入：
```
hello
world
linux
```
输入结束后按：
```
Ctrl+D
```
才会统计。
所以：
```
wc -l < data.txt
```
等价于：
```
人工输入文件里的内容
```
只是自动完成了。
### Here Document（<<）
这部分最容易让人懵。
## 语法
```
命令 << 标记内容内容内容标记
```
## 示例
```
cat << EOF
Hello
Linux
Shell
EOF
```
输出：
```
Hello
Linux
Shell
```
系统理解为：
```
把 EOF 与 EOF 之间的内容

Hello
Linux
Shell

作为 cat 的输入
```
相当于：
```
cat < 文件
```
只是这个文件是临时写出来的。
### 为什么叫 Here Document
Here：
```
这里
```
Document：
```
文档
```
意思：
```
输入内容就在这里
```
而不是在外部文件里。
### 但是输入重定向不常用
因为大多数命令已经支持直接指定文件。
例如：
```
cat data.txt
```
而不是：
```
cat < data.txt
```
---
再比如：
```
sort data.txt
```
而不是：
```
sort < data.txt
```
---
还有：
```
wc data.txt
```
而不是：
```
wc < data.txt
```
所以很多时候：
```
命令 文件名
```
就够了。
## 输出重定向
这是最常用的
### 作用
把输出结果写入到文件，而不是写入到屏幕
### 示例
```
ls > list.txt
```
原本：
```
ls
```
结果显示在屏幕：
```
a.txt
b.txt
c.txt
```
---
重定向后：
```
ls > list.txt
```
屏幕不显示。
而是写进：
```list.txt
a.txt
b.txt
c.txt
```
如果这个`list.txt`不存在，系统会自动创建，具体创建在哪看下面的例子就知道了
```bash
$ pwd
/home/user
$ ls > list.txt          # 创建 /home/user/list.txt
$ ls > /tmp/list.txt     # 创建 /tmp/list.txt
```
### 为什么输出重定向很常用？
#### 情况1：输出太长
例如：
```
ls -R /
```
输出几千行。
屏幕看不过来。
可以：
```
ls -R / > result.txt
```
然后：
```
vim result.txt
```
慢慢看。
## 情况2：保存结果
例如：
```
date > time.txt
```
文件里：
```
Thu Mar 20 12:00:00
```
以后还能查看。
## 情况3：生成日志
```
program > log.txt
```
程序运行信息全部保存。
## 覆盖问题（>）
很多新手容易踩坑。
假设：
```test.txt
AAABBB
```
执行：
```
echo Hello > test.txt
```
原本 `echo Hello` 是**输出到屏幕**，但加了 `> test.txt` 后，shell 就把输出“拐走”了，**不显示在屏幕上，直接写入文件**。
关键点：`>` 是**覆盖写入**，它会先把文件清空，再写入新内容。
结果`test.txt`变为：
```
Hello
```
原来的：
```
AAABBB
```
全部消失。
也不会输出`Hello`
因为：
```
>
```
是覆盖写入。
## 追加重定向（>>）
为了解决覆盖问题。
语法：
```
命令 >> 文件名
```
### 示例
第一次：
```
echo AAA > test.txt
```
文件：
```
AAA
```
第二次：
```
echo BBB >> test.txt
```
文件：
```
AAA
BBB
```
第三次：
```
echo CCC >> test.txt
```
文件：
```
AAA
BBB
CCC
```
所以：
```
>
```
= 覆盖
```
>>
```
= 追加
并且这个追加会新起一行追加
## 输出重定向可以用于把一个命令的输出当作另一个命令的输入。
例如：
```
ls > tmp.txt
sort < tmp.txt
```
过程：
```
ls
 ↓
tmp.txt
 ↓
sort
```
但这种方式麻烦。
所以后来出现：
```
ls | sort
```
这里：
```
|
```
叫管道（pipe）。
直接把前一个命令输出送给后一个命令。
更常用。