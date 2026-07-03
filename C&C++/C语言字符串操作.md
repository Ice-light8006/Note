常见字符串操作的函数：

| 函数         | 头文件                  | 原型                                                        | 功能                                   | 示例                                               |
| ---------- | -------------------- | --------------------------------------------------------- | ------------------------------------ | ------------------------------------------------ |
| `strlen`   | `<string.h>`         | `size_t strlen(const char *s)`                            | 返回字符串的长度（不含 `\0`）                    | `strlen("abc")` → `3`                            |
| `strcpy`   | `<string.h>`         | `char *strcpy(char *dest, const char *src)`               | 将 `src`（含 `\0`）复制到 `dest`            | `strcpy(buf, "hello")`                           |
| `strncpy`  | `<string.h>`         | `char *strncpy(char *dest, const char *src, size_t n)`    | 最多复制 `n` 个字符到 `dest`，不足补 `\0`        | `strncpy(buf, "hello", 3)` → `"hel"`             |
| `strcat`   | `<string.h>`         | `char *strcat(char *dest, const char *src)`               | 将 `src` 追加到 `dest` 末尾                | `strcat(buf, " world")`                          |
| `strncat`  | `<string.h>`         | `char *strncat(char *dest, const char *src, size_t n)`    | 最多追加 `n` 个字符到 `dest` 末尾              | `strncat(buf, "xyz", 2)` → 追加 `"xy"`             |
| `strcmp`   | `<string.h>`         | `int strcmp(const char *s1, const char *s2)`              | 比较两字符串，相等返回 `0`，`s1>s2` 返回正数         | `strcmp("abc","abc")` → `0`                      |
| `strncmp`  | `<string.h>`         | `int strncmp(const char *s1, const char *s2, size_t n)`   | 比较前 `n` 个字符                          | `strncmp("abcde","abcxy",3)` → `0`               |
| `strchr`   | `<string.h>`         | `char *strchr(const char *s, int c)`                      | 查找字符 `c` 第一次出现的位置                    | `strchr("hello", 'e')` → 指向 `"ello"` 的指针         |
| `strrchr`  | `<string.h>`         | `char *strrchr(const char *s, int c)`                     | 查找字符 `c` 最后一次出现的位置                   | `strrchr("hello", 'l')` → 指向最后一个 `"lo"`          |
| `strstr`   | `<string.h>`         | `char *strstr(const char *haystack, const char *needle)`  | 查找子串 `needle` 第一次出现的位置               | `strstr("hello world", "world")` → 指向 `"world"`  |
| `strspn`   | `<string.h>`         | `size_t strspn(const char *s, const char *accept)`        | 返回 `s` 开头连续包含 `accept` 中字符的个数        | `strspn("abc123", "abc")` → `3`                  |
| `strcspn`  | `<string.h>`         | `size_t strcspn(const char *s, const char *reject)`       | 返回 `s` 开头连续不包含 `reject` 中字符的个数       | `strcspn("abc123", "12")` → `3`                  |
| `strpbrk`  | `<string.h>`         | `char *strpbrk(const char *s, const char *accept)`        | 查找 `s` 中第一个出现在 `accept` 中的字符         | `strpbrk("hello", "aeiou")` → 指向 `"ello"`        |
| `strtok`   | `<string.h>`         | `char *strtok(char *str, const char *delim)`              | 按分隔符 `delim` 分割字符串（会修改原串）            | `strtok("a,b,c", ",")` 逐次返回 `"a"` `"b"` `"c"`    |
| `sprintf`  | `<stdio.h>`          | `int sprintf(char *buf, const char *fmt, ...)`            | 将格式化数据写入字符串 `buf`                    | `sprintf(buf, "%s %d", "age", 18)` → `"age 18"`  |
| `snprintf` | `<stdio.h>`          | `int snprintf(char *buf, size_t n, const char *fmt, ...)` | `sprintf` 的安全版，限制最大写入字节              | `snprintf(buf, 10, "%s", "very long string")` 截断 |
| `memcpy`   | `<string.h>`         | `void *memcpy(void *dest, const void *src, size_t n)`     | 从 `src` 复制 `n` 个字节到 `dest`（不处理 `\0`） | `memcpy(buf, data, 5)`                           |
| `memmove`  | `<string.h>`         | `void *memmove(void *dest, const void *src, size_t n)`    | 安全复制（允许内存重叠）                         | `memmove(buf+2, buf, 5)`                         |
| `memset`   | `<string.h>`         | `void *memset(void *s, int c, size_t n)`                  | 将前 `n` 个字节设置为字符 `c`                  | `memset(buf, 0, sizeof(buf))` 清空                 |
| `strdup`   | `<string.h>` (POSIX) | `char *strdup(const char *s)`                             | 复制字符串到新分配的内存（需 `free`）               | `char *p = strdup("hello");`                     |
| `atoi`     | `<stdlib.h>`         | `int atoi(const char *str)`                               | 将字符串转为整数                             | `atoi("123")` → `123`                            |
| `atof`     | `<stdlib.h>`         | `double atof(const char *str)`                            | 将字符串转为浮点数                            | `atof("3.14")` → `3.14`                          |
| `strtol`   | `<stdlib.h>`         | `long strtol(const char *str, char **endptr, int base)`   | 按进制将字符串转为长整数，支持错误检测                  | `strtol("0xFF", NULL, 0)` → `255`                |

关于字符串的一个细节：
```c
char name[32];
```
在这样定义字符串时，这里的32是包括字符串结尾的`'\0'`的，也就是说虽然定义的字符串长度为32，实际上有效最大长度只有31

在定义字符串时如果同时进行初始化，`[]`内可以不写长度，例如
```c
char str[] = "hello world";
```
此时编译器会自动给这个字符数组分配大小，即字符串的实际大小加上尾部的`'\0'`，所以这个字符数组`str`对应的实际大小为12
但是这样初始化之后，数组`str`的大小就直接锁定为12，后面不可以再修改，例如下面这个示例
```c
char str[] = "hello world";

strcpy(str, "hi");                     // 安全，内容变为 "hi"
strcpy(str, "hello world,hello world");// 危险！编译通过，但运行时缓冲区溢出（这才是真正的“超过长度”错误）
```
另外，我们也绝对不允许下面这样只写了一个没有指明长度的字符数组定义而不进行初始化
```c
char str[];
```
# `double`的占位符
## 1. 输入（`scanf`）：必须是 `%lf`
当你要把用户输入的数据存进一个 `double` 类型的变量时，**只能用 `%lf`**（小写的 l 和 f）。
- **为什么？** `scanf` 需要知道你要往内存里写几个字节。`float` 通常是 4 个字节，对应的占位符是 `%f`；而 `double` 通常是 8 个字节，对应的占位符是 `%lf`。如果你对一个 `double` 变量用了 `%f`，`scanf` 只会往里写 4 个字节，导致数据严重错乱。
## 2. 输出（`printf`）：标准是 `%f`，但写 `%lf` 也可以
当你要打印一个 `double` 变量时，标准的写法其实是 **`%f`**。
- **为什么？** 因为 C 语言有一个古老的规则叫“默认参数提升”。在像 `printf` 这种参数数量可变的函数中，所有的 `float` 都会被自动升级（提升）为 `double` 再传进去。也就是说，在 `printf` 眼里，根本没有 `float`，大家全都是 `double`。所以用 `%f` 就可以统一处理了。
- **写了 `%lf` 会怎样？** 在 C99 标准之后，官方明确规定了在 `printf` 中 `%lf` 和 `%f` 是完全等价的。所以如果你为了好记，输出时也写了 `%lf`，程序依然能完美运行，不会报错。