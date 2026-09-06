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
## 成员属性设为私有
在实际开发中，应该尽量避免在操作对象时直接操作对象的成员属性。而是把成员属性设置为`private`，然后在`public`中提供接口来操作成员属性。
同时有些字段在初始化之后就不应该变化，这时候就可以不提供任何修改这些成员属性的接口。
# 构造函数和析构函数
### 1. 构造函数 (Constructor)
构造函数是在对象创建时被自动调用的特殊成员函数。它的主要任务是**初始化对象的数据成员**。
- **特征**：
    - 函数名与类名完全相同。
    - 没有返回值类型（连 `void` 也不写）。
    - 通常为 `public`，以便外部创建对象。
- **构造函数的种类**：
    - **默认构造函数**：没有参数，或者所有参数都有默认值。如果类中没有定义任何构造函数，编译器会自动生成一个（但什么都不做）。
    - **参数化构造函数**：接受参数，允许在创建对象时指定初始值。
    - **拷贝构造函数**：参数为类自身的引用（通常是 `const T&`），用于通过现有对象创建新对象。
    - **移动构造函数** (C++11)：参数为右值引用（`T&&`），用于高效地“窃取”临时对象的资源，避免不必要的深拷贝。
- **关键机制：初始化列表 (Member Initializer List)**
    - 这是最佳实践。它在构造函数体执行之前初始化成员变量。
    - **必要性**：对于 `const` 成员、引用成员，或者没有默认构造函数的类成员，必须使用初始化列表。
    - 语法示例：`MyClass() : m_val(10), m_ref(other) { /* ... */ }`
### 2. 析构函数 (Destructor)
析构函数是在对象生命周期结束（超出作用域或被 `delete`）时被自动调用的特殊成员函数。它的主要任务是**释放对象占用的资源**（如堆内存、文件句柄、网络连接等）。
- **特征**：
    - 函数名是类名前加波浪号 `~`（例如 `~MyClass()`）。
    - 没有返回值，没有参数（因此**不能重载**）。
    - 一个类只能有一个析构函数。
- **关键机制：虚析构函数 (Virtual Destructor)**
    - **这是 OOP 中的高频考点**：如果类打算被继承，并且可能通过基类指针删除派生类对象，**基类的析构函数必须声明为 `virtual`**。
    - 如果不声明为 `virtual`，通过基类指针删除派生类对象时，只会调用基类的析构函数，导致派生类的资源泄漏。
### 3. RAII 思想 (资源获取即初始化)
这里先介绍一下RAII思想
**RAII** 是 C++ 编程中最核心、最优雅的编程思想之一。全称为**Resource Acquisition Is Initialization**（资源获取即初始化）
构造函数和析构函数是 C++ **RAII** 编程理念的基石：
- **资源获取 (Constructor)**：在构造函数中分配资源（或加锁）。
- **资源释放 (Destructor)**：在析构函数中释放资源（或解锁）。
- **优势**：利用 C++ 的栈对象生命周期管理机制，即使程序中途抛出异常，析构函数也能保证资源被自动释放，从而有效防止内存泄漏。
### 4. 常见的工程化细节与坑
1. **构造顺序**：
    - 按声明顺序初始化成员变量（与初始化列表的顺序无关）。
    - 基类先于派生类构造。
2. **析构顺序**：
    - 与构造顺序恰好相反：派生类先析构，基类后析构。
3. **禁止拷贝/移动**：
    - 如果你管理的是唯一资源（如独占文件句柄），应使用 `= delete` 显式禁用拷贝构造函数和拷贝赋值运算符。
4. **异常安全**：
    - 尽量不要在析构函数中抛出异常，因为如果对象本身在处理另一个异常时调用了析构函数，再次抛出异常会导致程序直接调用 `std::terminate()` 终止。
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