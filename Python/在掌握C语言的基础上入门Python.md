# 基本数据类型
## Python的动态类型机制
在 Python 中，变量可以随时引用不同类型的对象。
```Python
a = 10          # int
a = 3.14        # float
a = "Hello"     # str
a = [1, 2, 3]   # list
a = None        # NoneType
```
Python 不需要事先声明变量类型。
可以使用 `type()` 查看对象的类型：
```Python
a = 10
print(type(a))     # <class 'int'>

a = "Hello"
print(type(a))     # <class 'str'>
```
可以这样说，Python的变量名更像是贴在内存上的一个标签，当你写下 `x = 10` 时，Python 在内存中创建了一个整数对象 `10`，然后把标签 `x` 贴在这个对象上。如果你接着写 `x = "Hello"`，就会在内存中创建一个字符串对象`"Hello"`，标签 `x` 就会从原来的整数对象上撕下来，重新贴到这个字符串对象上。
## 数值类型
### `int`：任意精度整数
Python 的 `int` 不存在固定的 8 位、16 位、32 位或 64 位限制。
例如：
```Python
a = 1 << 100
print(a)
```
可以正常计算，不存在C语言中的整型溢出的问题
此外，Python 3 的普通整数只有 `int` 这一种内置类型，没有独立的 `short`、`long long`、`unsigned int` 等类型。
### `float`：浮点数
Python 内置 `float` 通常采用 IEEE 754 双精度浮点格式，与 C 语言的 `double` 精度相当，而不是 C 的 `float`。
```Python
a = 3.14
print(type(a))   # <class 'float'>
```
Python 不提供独立的内置单精度浮点类型。
另外：
```Python
a = 5 / 2

print(a)          # 2.5
print(type(a))    # <class 'float'>
```
### complex：复数
Python原生支持复数，使用`j`表示虚数单位
```Python
a = 3 + 4j

print(a.real)    # 3.0
print(a.imag)    # 4.0
print(abs(a))    # 5.0
```
其中：
- `real`：获取实部。
- `imag`：获取虚部。
- `abs()`：计算复数模长。
### `bool`：布尔类型
Python 中的布尔值是 `True` 和 `False`，**首字母必须大写**。
特别的事：Python的`bool`是`int`的子类
```Python
print(isinstance(True, int))   # True

print(True + True)             # 2
print(True == 1)               # True
print(False == 0)              # True
```
此外，Python中以下对象在布尔判断中都属于假值
```Python
None
0
0.0
0j
""
[]
()
{}
set()
```
但这些对象并不因此变成 `False` 对象。
## 字符串
Python的字符串与C语言的字符串存在非常明显的区别
### Python没有`char`类型
Python没有字符类型
```Python
a = 'A'
b = "A"

print(type(a))   # <class 'str'>
print(type(b))   # <class 'str'>
```
单引号和双引号是一样的，都是表示字符串
### 字符串是不可变对象
```Python
s = "Hello"

s[0] = 'h'   # TypeError
```
字符串在创建之后不可以修改其中某一个字符
但是可以创建新的字符串并重新赋值：
```Python
s = "Hello"

s = "hello"

print(s)  # hello
```
### 字符串的切片操作
看这个例子
```Python
s = "Hello"

s = s[1:]

print(s) # ello
```
这里这个`[1:]`称为切片操作，用来截取序列（如列表、字符串、元组等）的一部分。
它的通用语法是：```
```Python
[start:end:step]
```
当省略某些参数时，会使用默认值。
具体规则：
- `start`：起始索引，包含该位置。
- `end`：结束索引，不包含该位置。
- `step`：步长，负数表示从右向左遍历。
- 负数表示从末尾开始定位。例如如果`start`为-2，则从倒数第二个字符开始截取。如果`end`为-5，则表示截取到倒数第五个字符结束（开区间，不包括倒数第五个字符）
对于 `[1:]` 来说：
- **`start` = 1**：从索引为 `1` 的元素开始（即**第二个**元素，因为 Python 的索引从 `0` 开始）。
- **`end` 被省略**：表示一直截取到序列的末尾。
- **`step` 被省略**：默认步长为 `1`。
如果`start`被省略，则表示从字符串的开头开始
示例：
```Python
s = "123456789"

print(s[:5]) # 12345
print(s[-3:]) # 789
print(s[-5:-3]) # 56
print(s[0::2]) # 13579
print(s[::-2])# 97531
```
# 运算符
## `/`与`//`运算符
与C语言不同
这里`/`是普通除法（True Division），计算结果为一个浮点数
而`//`是向下取整除法（Floor Division），结算商后，向负无穷方向取整
例如，
```Python
5 / 2
```
的结果是2.5
而
```Python
5 // 2
```
的结果是2
## `**`幂运算运算符
它的功能是**幂运算**
```Python
print(2 ** 3)     # 8
print(2 ** 0.5)   # 1.4142135623730951
```
注意：`^` 在 Python 中与 C 语言一样是按位异或，不是乘方。
此外，幂运算优先级高于左侧的一元负号：
```Python
print(-2 ** 2)     # -4
print((-2) ** 2)   # 4
```
## `%`取模运算符
Python 与 C 的取模规则存在区别。
```Python
print(7 % 3)     # 1
print(-7 % 3)    # 2
print(7 % -3)    # -2
print(-7 % -3)   # -1
```
对于整数 `a`、非零整数 `b`：
Python 满足：
$$a=(a//b)\times b+(a\%b)$$
例如：
$$-7=(-3)\times3+2$$
Python 的余数与除数同号（余数为零除外），而 C 语言的余数与被除数同号。
## 链式比较
Python 允许这样写：
```Python
x = 5

print(1 < x < 10)     # True
print(1 < x <= 5)     # True
```
其中
```Python
1 < x < 10
```
相当于C语言中的
```c
1 < x && x < 10
```
## 逻辑运算符
Python 不使用 C 语言的 `&&`、`||`、`!`。

| C 语言   | Python | 功能  |
| ------ | ------ | --- |
| `&&`   | `and`  | 逻辑与 |
| `\|\|` | `or`   | 逻辑或 |
| `!`    | `not`  | 逻辑非 |
例如：
```Python
a = 5
b = 10

print(a > 0 and b > 0)  # True
print(a > 0 or b < 0)   # True
print(not a > 0)        # False
```
### 重要区别：`and` 和 `or` 不一定返回布尔值
这是 Python 非常值得注意的特点。这一点与C语言有很大不同
```Python
print(3 and 5)   # 5
print(0 and 5)   # 0

print(3 or 5)    # 3
print(0 or 5)    # 5
```
原因：
- `a and b`：若 `a` 为假，返回 `a`；否则返回 `b`。
- `a or b`：若 `a` 为真，返回 `a`；否则返回 `b`。
实际上这就是短路求值的特性
而 `not` 始终返回 `bool`，也就是布尔值。
Python 中，`0`、`None`、空字符串、空列表等通常都被视为假。
例如：
```Python
print("" or "Hello")   # Hello
print([] or [1, 2])    # [1, 2]
```

## Python没有自增和自减运算符
Python没有自增和自减运算符
但是，值得注意
```Python
a = 5
--a
```
这里不会报错
因为
```Python
--a
```
会被Python解释器理解为
```Python
-(-a)
```
因此`a`的值不会改变
## Python支持连续赋值
例如
```Python
a = b = c = 10
```
## `:=`：赋值表达式运算符
这是 Python 3.8 引入的运算符，又称**海象运算符**（Walrus Operator）。
Python 普通的 `=` 赋值是语句，不能像 C 语言的赋值表达式一样随意嵌入条件中。
但是可以使用 `:=`：
```Python
if (n := len([1, 2, 3])) > 2:
    print(n)
```
输出：
```
3
```
上述代码相当于
```Python
n = len([1, 2, 3])

if n > 2:
    print(n)
```
## 成员运算符
Python的成员运算符有`in`和`not in`
用于判断某个元素是否属于某个容器
```Python
a = [1, 2, 3, 4]

print(2 in a)        # True
print(5 in a)        # False
print(5 not in a)    # True
```
也可以用于字符串，判断某个字符串是否是某个字符串的连续子串
```Python
s = "Hello World"

print("Hello" in s)  # True
print("abc" in s)    # False
```
用于字典时，默认判断的是键，而不是值。
## 身份运算符
这个概念特别重要。
- `==`：判断两个对象的值是否相等。
- `is`：判断两个变量是否引用同一个对象。
例如：
```Python
a = [1, 2, 3]
b = [1, 2, 3]

print(a == b)   # True
print(a is b)   # False
```
`a`和`b`两者在内存中的关系示意
<svg font-family="-apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, sans-serif" font-weight="430" data-d-component="svg" fill="currentColor" style="color:rgb(255, 255, 255)" viewBox="0 0 340 164" width="100%" xmlns="http://www.w3.org/2000/svg"><rect x="15" y="12" width="85" height="52" rx="7" fill="#64748b" fill-opacity=".12" stroke="#64748b" stroke-width="1.2"/><text x="57" y="32" font-size="12" text-anchor="middle" fill="currentColor">变量 a</text><text x="57" y="51" font-size="13" font-weight="600" text-anchor="middle" fill="currentColor">a</text><rect x="15" y="94" width="85" height="52" rx="7" fill="#64748b" fill-opacity=".12" stroke="#64748b" stroke-width="1.2"/><text x="57" y="114" font-size="12" text-anchor="middle" fill="currentColor">变量 b</text><text x="57" y="133" font-size="13" font-weight="600" text-anchor="middle" fill="currentColor">b</text><g stroke="#64748b" stroke-width="1.7" fill="none" stroke-linecap="round"><path d="M100 38 L203 38"/><path d="M100 120 L203 120"/></g><g fill="#64748b"><path d="M203 38 l-7 -4 v8z"/><path d="M203 120 l-7 -4 v8z"/></g><rect x="207" y="12" width="117" height="52" rx="7" fill="#0d9488" fill-opacity=".1" stroke="#0d9488" stroke-width="1.2"/><text x="265" y="32" text-anchor="middle" font-size="11" fill="currentColor">列表对象</text><text x="265" y="51" font-size="14" font-weight="600" text-anchor="middle" fill="currentColor">[1, 2, 3]</text><rect x="207" y="94" width="117" height="52" rx="7" fill="#0d9488" fill-opacity=".1" stroke="#0d9488" stroke-width="1.2"/><text x="265" y="114" text-anchor="middle" font-size="11" fill="currentColor">列表对象</text><text x="265" y="133" font-size="14" font-weight="600" text-anchor="middle" fill="currentColor">[1, 2, 3]</text></svg>
如果：
```Python
a = [1, 2, 3]
b = a

print(a == b)   # True
print(a is b)   # True
```
那么两个变量就引用了同一个列表对象。
对于空值判断，推荐：
```Python
if a is None:
    ...
```
而不是使用 `a == None`。
这里简单介绍一下`None`
`None`是Python的一个特殊的对象（单例对象）。它所属的类型是`NoneType`
`NoneType` 只有一个实例，就是 `None`。所以`NoneType`是单例对象
可以把`None`类比成C语言中的`NULL`，但有所不同，可以这样理解：
> C语言中的NULL仅仅表示指针变量是空的，而None是一个独立的对象，可以用来表示任意变量当前没有有效值。
## 条件表达式
```Python
result = a if a > b else b
```
## `@`：矩阵乘法运算符
Python 还有一个比较特殊的运算符：
```Python
A @ B
```
用于支持矩阵乘法等操作的对象，常见于 NumPy。
它不能直接用于普通的 Python 列表：
```Python
[1, 2] @ [3, 4]   # TypeError
```
## Python对运算符的重载
例如
```Python
print("Hello" + "World")
# HelloWorld

print("abc" * 3)
# abcabcabc

print([1, 2] + [3, 4])
# [1, 2, 3, 4]

print([1, 2] * 3)
# [1, 2, 1, 2, 1, 2]
```
在 Python 中，运算符的具体行为通常由操作数所属类型决定。
例如，对于自定义类，可以通过定义 `__add__()`、`__mul__()` 等特殊方法重载相应运算符。
另外，Python 的 `+=` 对可变对象可能进行原地修改，而不只是创建一个新对象：
```Python
a = [1, 2]
b = a

a += [3]

print(b)    # [1, 2, 3]
```
## 对于C程序员，最需要记住的区别
| 特性     | C 语言         | Python 3        |
| ------ | ------------ | --------------- |
| 整数相除   | `/` 截断小数     | `/` 返回浮点数       |
| 整数商    | `/` 向零截断     | `//` 向下取整       |
| 负数取模   | 余数随被除数符号     | 余数随除数符号         |
| 幂运算    | 通常使用 `pow()` | `**`            |
| 逻辑与    | `&&`         | `and`           |
| 逻辑或    | `\|\|`       | `or`            |
| 逻辑非    | `!`          | `not`           |
| 自增、自减  | `++`、`--`    | 不支持             |
| 三元运算   | `a ? b : c`  | `b if a else c` |
| 链式比较   | 不具有数学式语义     | `a < b < c`     |
| 赋值表达式  | `=`          | `:=`            |
| 成员判断   | 无通用运算符       | `in`、`not in`   |
| 对象身份判断 | 可通过指针比较地址    | `is`、`is not`   |
| 整数宽度   | 通常固定宽度       | 任意精度，受内存限制      |
