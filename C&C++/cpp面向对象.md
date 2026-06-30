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