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
# 类内成员初始化
如果在类内成员定义时直接赋值，例如
```cpp
class A
{
public:
    int x = 100;
};
```
这种写法叫**类内成员初始化**，从C++11开始支持
它的效果是：当创建对象时，如果构造函数没有显式初始化该成员变量，就使用类内指定的初始值。
## 类内成员初始化的基本示例
如果构造函数没有初始化该成员变量，例如
```cpp
class A
{
public:
	A()
	{
	}
	int x = 100;
};


int main()
{
	A a1,a2;
	cout <<  a1.x << endl;
	cout << a2.x << endl;
	return 0;
}
```
这时候，打印结果为
```output
100
100
```
如果构造函数初始化了该成员变了，例如
```cpp
class A
{
public:
	A(int x)
	:x(x)
	{
	}
	int x = 100;
};

int main()
{
	A a1(50);
	A a2(150);
	cout << a1.x << endl;
	cout << a2.x << endl;
	return 0;
}
```
这时候，打印结果为
```output
50
150
```
## 这里要注意构造函数之间的区别
```cpp
class A
{
public:
	A(int x)
	:x(x)
	{}
	A(const A &a)
	{
	}
	int x = 100;
};

int main()
{
	A a1(20);
	A a2(a1);
	cout << a1.x << endl;
	cout << a2.x << endl;
	
	return 0;
}
```
这时候的输出是这样的：
```output
20
100
```
这是因为，`a1`在初始化时调用的构造函数`A(int x)`，这时候`x`被构造函数初始化为了20
而`a2`在初始化时调用了拷贝构造函数，拷贝构造函数并没有初始化`x`，所以这时候`x`的值使用了类内指定的`x`的初始值