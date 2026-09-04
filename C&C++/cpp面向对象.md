# 访问权限
访问权限有三种：
- public          公共权限
- protected    保护权限
- private         私有权限
```
public      类内可以访问，类外可以访问
protected   类内可以访问，类外不可以访问
private     类内可以访问，类外不可以访问
```
但是这里看起来`protected`和`private`貌似看起来没有区别。这里的区别在于派生类对其父类成员变量的访问权限上。下面会详细讲这个。
首先需要默认一件事情：
任何类，其成员函数都可以访问自己所在的类内部的成员变量
## `public`
现在有这个类
```cpp
class People
{
public:
	int age;
};
```
如果这样写
```cpp
int main()
{
	People p;
	p.age = 18;
}
```
完全合法。因为`public`的成员变量可以在任何地方通过对象访问
## `private`
现在有这个类
```cpp
class People
{
private:
	int age;
};
```
如果这样写
```cpp
int main()
{
	People p;
	p.age = 1;//报错
}
```
因为这个`age`变量是私有成员变量，这时候就会报错。
同时，如果有一个类继承这个类
```cpp
class Asian_People:public People
{
public:
	void func()
	{
		cout << age << endl;
	}
};

int main()
{
	Asian_People a_p;
	a_p.func();//报错
}
```
代码会在 `Asian_People::func()` 中访问 `age` 的位置编译失败。因为该类的派生类也没有访问该类成员变量的权限
## `protected`
现在有这个类
```cpp
class People
{
protected:
	int age;
};
```
`protected`也是类内可以访问，类外不可访问。但是，`protected`与`private`的不同点在于，一个类的`protected`的成员变量，在这个类的派生类中也可以被访问和修改。
```cpp
class Asian_People:public People
{
public:
	void func()
	{
		cout << age << endl;
	}
};

int main()
{
	Asian_People a_p;
	a_p.func();
}
```
这里这个`a_p.func()`就不会发生报错了。
但是外部依然不可以直接访问
# 内联函数
看下面的代码
```cpp
class MyClass
{
public:
	int x{0};//cpp11开始可以在声明时赋初始值
	int y{0};
	
	//定义直接写在函数内部，称为内联函数
	void testIn(int v)
	{
		x+=v;
		y+=v;
	}
	
	//非内联函数
	void test(int v);
};

void MyClass::test(int v)
{
	x+=v;
	y+=v;
}
```
内联函数会影响编译速度，比非内联函数编译要花更长时间
普通函数在调用时会去读取这个函数的内存地址，去调用这个地址的函数
而内联函数在使用时会直接把内联函数内的函数代码直接复制过来，从调用角度来看这个复制过来的方式没有了出栈入栈的过程，效率会高一些，但是编译速度会慢一些，编译出来的文件大小会大一些
这里
```cpp
int x{0};
int y{0};
```
的意思是，在创建MyClass变量时，如果构造函数没有另外指定`x`和`y`的初始值，那么它们默认初始化为0
# 成员变量的内存空间
```cpp
#include<iostream>

using namespace std;

class MyClass
{
public:
    int x{0};
    int y{0};
    char name[16]{"My class name"};
};
  
int main()
{
    MyClass myclass;
    cout << sizeof(myclass) << "|" << sizeof(MyClass) << endl;
    return 0;
}
```
输出结果为
```
24|24
```
因为类`MyClass`内有两个`int`与一个长度为16的`name`，加在一起为24个字节

# this指针
指向当前实例化类对象的地址
```cpp
class MyClass
{
public:
	int x{0};
	int y{0};
	void testIn(int v)
	{
		x+=v;
		y+=v;
	}
	void test(int v);
	void thistest()
	{
		std::cout << "this addr:" << (long long)this << std::endl;
	}
};
void MyClass::test(int v)
{
	x+=v;
	y+=v;
}

int main()
{
	MyClass mcf;
	
	//下面这两个的输出结果是一样的
	std::cout << "mcf addr:" << &mcf << std::endl;
	mcf.thistest();
	
	
}
```

# 静态成员
## 静态成员变量
## 静态成员函数