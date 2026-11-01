- `main`函数有下面两种重载
`int main(){body}`
`int main(int argc, char* argv[]）{body}`

# `argc`
表示我们的参数传了多少个。比如我们在命令行调用程序的时候，在这个命令的后面加了一个空格，空格后面再加一串内容再加一个空格，这后面的内容就是我们传给`main`函数的参数。如果一个参数不传，这里argc就等于1，这时候以程序的名称作为第一个参数，后面的内容才是接着第二个参数，也就是说从第二个开始才是真的用户传过来的参数
# `argv`
字符串数组，可以理解为，在控制台调用程序之后，每一个参数以空格作为分割，存在字符串数组`argv`里面，可以通过下标进行访问
```cpp
#include<iostream>

using namespace std;

int main(int argc,char *argv[])
{
	cout << "argc = " << argc << endl;
	//访问argv字符串数组中的内容
	//从0开始是第一个字符串
	//第一个参数是执行程序的完整路径或者程序名，第二个参数是用户传递的
	
	//如果是Windows，这里会输出你所运行的可执行程序的完整路径
	//如果是Linux，通常是程序名（通常不包含后缀）
	//这个依赖具体操作系统和具体shell行为
	cout << "argv[0]=" << argv[0] << endl;

	//注意，如果用户没有传参，使用argv[1]程序会直接报错
	//所以下面我们可以利用argc进行判断
	if(argc>1)
	{
		cout << "argv[1]=" << argv[1] << endl;
	}
	
	//另外，C++保证argv[argc]是空指针，所以也可以这样遍历argv数组
	for(char **p = argv;*p!=nullptr;p++)
	{
		cout << "argv[" << p-argv << "]=" << *p << endl;
	}
}
```
- 我们在传参的时候如果参数包含空格，可以用双引号包裹，例如:
```bash
./program "hello world" foo
# argv[1] = "hello world"(不含引号)
# argv[2] = foo
```
