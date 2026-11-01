# `static`关键字
`static`既能修饰局部变量，也能修饰全局变量，还能修饰函数
它的作用简单概括就两句话：
- 控制变量的生命周期（存活时间）
- 控制函数和全局变量的作用域（可见范围）
## `static`修饰局部变量
要解释`static`的作用，先看这个代码
```c
#include<stdio.h>

void func()
{
	int num = 5;
	num++;
	printf("num = %d\n",num);
}

int main(int argc, char **argv)
{
	func();
	func();
	func();
	return 0;
}
```
这个代码的输出是
```
num = 6
num = 6
num = 6
```
三次输出的`num`d的数值都是6，因为变量`num`的生命周期是所在的函数结束之后就被释放了。所以每次调用函数`func`都是一个新的变量`num`其值初始化为5。然后再自增得到6。
如果我们想要`num`不在函数结束之后被释放，那么我们可以使用`static`关键字，延长变量`num`的生命周期，如下：
```c
#include<stdio.h>

void func()
{
	static int num = 5;//初始化仅进行一次
	num++;
	printf("num = %d\n",num);
}

int main(int argc,int **argv)
{
	func();
	func();
	func();
	return 0;
}
```
可以看出，`static`关键字在修饰局部变量时，其作用为：
- 延长局部变量的生命周期直至整个程序结束之后再释放
另外一个例子：
```c
#include<stdio.h>

char* func1()
{
	char src[100] = "hello world";
	return src;
}

int main(int argc, char **argv)
{
	char *temp = func1();
	printf("temp = %s\n",temp);
}
```
在当前编译环境下，程序输出：（某些编译器可能不同）
```
temp = (null)
```
为什么不是`hello world`，因为`src` 是函数的局部变量，存储在栈帧中。当 `func1()` 返回后，`src` 的生命周期结束，其所占用的栈空间失效。此时返回的指针成为悬空指针（Dangling Pointer），继续使用该指针属于未定义行为。
```c
#include<stdio.h>

char* func1()
{
	static char src[100] = "hello world";
	return src;
}

int main(int argc,char **argv)
{
	char *temp = func1();
	printf("temp = %s\n",temp);
}
```
### 总结
```Plain text
static 修饰局部变量：
1. 生命周期变为整个程序运行期间
2. 作用域仍然是当前函数
3. 只初始化一次
4. 另外，静态存储区的变量默认初始化为0
```
注：关于**作用域**与**生命周期**，可以这样理解
- **作用域**是**“空间”**概念（编译时）：变量在**源代码的哪个区域**可以被访问（可见）。
- **生命周期**是**“时间”**概念（运行时）：变量在程序执行过程中，**在内存中存在并占用存储**的时间段
## `static`修饰全局变量
一句话：限制被修饰的全局变量只能在当前源文件（编译单元）中访问
## `static`修饰函数
一句话：限制被修饰的函数只能在当前源文件中被引用

---
# `extern`关键字
## 在`.h`中使用关键字`extern`
```c
//a.h
extern int a;
```
在 `.h` 头文件中，使用 `extern` 声明变量，
可以让所有包含该头文件的 `.c` 文件访问该变量，
但变量的定义必须在某一个 `.c` 文件中完成。
注意，这里一定不要这样写
```c
//a.h
extern int a = 10;
```
这不是单纯声明，而是带初始化的`extern`，本质上是定义
假如有：
```c
//main.c
#include"a.h"
```

```c
//other.c
#include"a.h"
```
那么在预处理阶段，头文件展开后会变成
```c
extern int a = 10;//在main.c里
extern int a = 10;//在other.c里
```
这会在链接阶段导致“multiple definition”错误。
**所以，不要在头文件中对 `extern` 声明的变量进行初始化，否则会导致多个源文件中出现重复定义。**
## 在`.c`中使用关键字`extern`
作用：在当前文件中“声明别人家的变量”
```c
//b.c
extern int g_val;
void func()
{
    printf("%d\n", g_val);
}
```
含义： 
> “我这个文件要用 g_val，但它定义在别的地方”
> 每个 .c 文件都会被独立编译，因此需要通过 extern 声明来告知编译器该变量在其他编译单元中定义。

## 对函数使用`extern`
函数默认就是`extern`，加和不加等价。
声明函数时加`extern`的意思就是函数被定义在别的文件里
## 一句话核心
`.h` 里的 extern 是“对外声明接口”，`.c` 里的 extern 是“临时使用声明”

# 两者结合来看
假如现在有两个文件一个`test1.c`，另外一个是`test2.c`
```c
//test1.c
int a = 5;
```

```c
//test2.c
#include<stdio.h>
extern int a;//声明变量a定义在别的.c文件中
int main(int argc,char **agrv)
{
	printf("a = %d\n",a);//正常
	return 0;
}
```
但是如果我们改成下面这样，就会出问题
```c
//test1.c
static int a = 5;
```

```c
//test2.c
#include<stdio.h>
extern int a;
int main(int argc,char **agrv)
{
	printf("a = %d\n",a);
	return 0;
}
```
通常会报错，因为`test1.c`中在定义变量`a`时使用了`static`关键字，限制了变量`a`仅可以在文件`test1.c`中使用，但是在`test2.c`中又用`extern`关键字声明了变量`a`在外部定义，这就会引发错误。
# 最后总结
```Plain Text
static 与 extern 的关系：

static：
    对符号“隐藏”
    只能在当前源文件中使用

extern：
    对符号“寻找”
    告诉编译器该符号定义在其他源文件

因此：

extern 和 static 在链接属性上是相反的。

一个负责隐藏符号，
一个负责跨文件访问符号。
```
在多人协作开发时，使用`static`关键字可以避免函数名冲突