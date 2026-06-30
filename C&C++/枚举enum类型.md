# C++11之前枚举

## `enum`语法
``` cpp
enum 枚举类型名
{
	枚举值1,//默认从0开始
	枚举值2,//每一个加1
	枚举值3,//2
	枚举值4 = 5,//可以赋值
	枚举值5//从上面的五开始再加一为6
};
```
## 访问方式
```cpp
枚举类型名 var = 枚举值1;
if(var == 枚举值1)
std::cout << 枚举值1 << std::endl;
```
# 枚举的应用场景
- 消息类型
- 日志级别
枚举是整数可以做大小比较
# C++11之后
```cpp
enum class LogLevel//日志级别
{
	DEBUG,
	INFO,
	ERROR,
	FATAL
};
```
## 访问方式
- `cout << (int)LogLevel::DEBUG << endl;`，这里与C++11之前的枚举的区别就是这里必须要加两个冒号写出类型名
- 无法直接当做整数使用，防止混淆，但是可以进行强制转换获取其对应的整数值
- 访问值必须加类型，减少冲突

# 使用示例
## C++11传统的枚举类型
### 例1

```cpp
#include<iostream>
using namespace std;
//测试枚举类型

//传统枚举类型
enum 枚举类姓名
{
	枚举值1,//默认0
	枚举值2,//1
	枚举值3,//2
	枚举值4,//3
	枚举值5//4
};

int main()
{
	//枚举类型名 evl{0};这样会报错
	//大括号内不能用对应的整数，必须要用枚举名
	枚举类型名 ev1{枚举值1};
	cout << "ev1 = " << ev1 << endl;//输出为"ev1 = 0"，因为枚举值1对应的整数为0
	cout << "枚举值2 = " << 枚举值2 << endl;//也可以直接打印，输出为"枚举值2 = 1"
	cout << "枚举值3 = " << 枚举值3 << endl;//也可以直接打印，输出为"枚举值3 = 2"
	return 0;
}
```

### 例2
```cpp
#include<iostream>
using namespace std;
//测试枚举类型

//传统枚举类型
enum 枚举类姓名
{
	枚举值1,//默认0
	枚举值2,//1
	枚举值3,//2
	
	//可以赋值初始值
	枚举值4 = 1000,
	//注意，这里枚举值5是1001，因为每一个枚举值对应的整数都是完全根据上一个枚举值加一得到的
	枚举值5//1001
};

int main()
{
	//枚举类型名 evl{0};这样会报错
	//大括号内不能用对应的整数，必须要用枚举名
	枚举类型名 ev1{枚举值1};
	cout << "ev1 = " << ev1 << endl;//输出为"ev1 = 0"，因为枚举值1对应的整数为0
	cout << "枚举值2 = " << 枚举值2 << endl;//也可以直接打印，输出为"枚举值2 = 1"
	cout << "枚举值3 = " << 枚举值3 << endl;//输出为"枚举值3 = 2"
	cout << "枚举值4 = " << 枚举值4 << endl;//"枚举值4 = 1000"
	cout << "枚举值5 = " << 枚举值5 << endl;//"枚举值5 = 1001"
	return 0;
}
```

### 例3
```cpp
#include<iostream>
using namespace std;

enum Status
{
	PLAY,
	PAUSE,
	STOP
};

int main()
{
	Status status{STOP};
	if(status==STOP)
	{
		status = PLAY;
	}
	cout << "status = " << status << endl;//"status = 0"
	if(status == PLAY)//成立，会执行内部的cout语句
	{
		cout << "Playing" << endl;
	}
	return 0;
}
```

## C++11之后新的枚举
### 例1
```cpp
#include<iostream>
using namespace std;

enum class LogLevel
{
	DEBUG,
	INFO,
	ERROR,
	FATAL
};

int main()
{
	//LogLevel level{DEBUG};
	//这个会报错！因为C++11之后的枚举要求必须要把枚举类名称加进来
	//下面的这个是正确的
	LogLevel level{LogLevel::DEBUG};
	
	//这样输出会报错！
	//cout << "level = " << level << endl;
	//C++11之后的枚举要求必须要强制转换为整型之后才可以直接输出
	//下面的这个是正确的
	
	//结果为"level = 0"
	cout << "level = " << (int)level << endl;
	
	//结果为"3"
	cout << (int)LogLevel::FATAL << endl;
	
	level = LogLevel::FATAL;
	
	//这个if语句内部的东西会执行，打印出"FATAL"
	if(LogLevel::FATAL==level)
	{
		cout << "FATAL" << endl;
	}
	
	LogLevel confLevel{LogLevel::INFO};
	
	//比较两个枚举类型的时候可以直接比较，不需要强制转换
	if(level>=confLevel)
	{
		cout << "log view" << endl;
	}
	return 0;
}
```