# 基本运算符
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
## 整型溢出的问题
这一点要注意：Python 的 `int` 不受 C 语言 `int` 固定字长的限制。
例如：
```Python
a = 1 << 100
print(a)
```
可以正常计算，不存在C语言中的整型溢出的问题
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
## 条件表达式
```Python
result = a if a > b else b
```
## `@`：矩阵乘法运算符
