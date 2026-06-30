`const`关键字只能修饰变量，包括全局变量和局部变量
被`const`修饰的变量称为**只读变量**
```c
#include<stdio.h>

int main(int argc,char **argv)
{
	int cnt = 5;
	cnt++;
	return 0;
}
```
这个代码编译会通过，没有任何问题。
但是如果改成下面这样
```c
#include<stdio.h>

int main(int argc,char **argv)
{
	const int cnt = 5;
	cnt++;
	return 0;
}
```
这时候编译就会报错。因为对`const`修饰的变量`cnt`被`cnt++`这个语句修改了
**但是不是完全不可以改！！**
看下面这个例子，是可以修改的
```c
#include<stdio.h>

int main(int argc,char **argv)
{
	const int cnt = 5;
	int* p = &cnt;
	*p = 10;
	printf("cnt = %d",cnt);
	return 0;
}
```
这个代码会编译通过，并且会有输出结果：
```out
10
```
可以发现成功修改了变量`cnt`
这里我们可以这样认为：
```Plain Text
const int cnt = 5;
这里表示不能通过变量名cnt去修改变量的值，但是对应的内存空间是可变的
```
只读变量的性质就是：对应的内存空间可变，但是不能通过变量名来修改