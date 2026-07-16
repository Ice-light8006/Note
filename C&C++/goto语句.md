# 1. 基本语法
`goto` 是C语言中的无条件跳转关键字。它由两部分组成：
- **标签（Label）**：定义一个位置，后面跟冒号 `:`
- **跳转（Jump）**：执行 `goto 标签名;` 后，程序会直接跳转到该标签处继续执行。
```c
// 定义标签
err_handler:
    printf("发生错误，正在清理...\n");
// 跳转到标签
if (error) {
    goto err_handler;
}
```
# 2. 核心规则（务必遵守）
- **作用域限制**：`goto` 只能**在同一个函数内部**跳转，不能跨函数跳转。
- **变量初始化风险（重点）**：`goto` 会跳过变量的**初始化**，但不会跳过变量的**声明**。
```c
goto skip;
int a = 10;   // 这行初始化会被跳过！
skip:
printf("%d", a); // 严重错误：a 未初始化就被使用
    
   
```
 _解决办法：将变量声明放在所有 `goto` 之前，或者将跳转代码放在变量初始化之后。_
# 3. 唯一推荐的两种使用场景（千万别滥用）
## 场景一：集中式资源清理（最经典，工程必备）
当函数中申请了多个资源（动态内存 `malloc`、文件指针 `fopen`、锁等）时，`goto` 能避免层层嵌套 `if`，实现**“一处写释放，多处跳转用”**。
```c
int foo() {
    FILE *fp = NULL;
    char *buf = NULL;
    int ret = 0; // 0成功，非0失败
    fp = fopen("data.txt", "r");
    if (!fp) {
        ret = 1;
        goto cleanup; // 跳转至统一出口
    }
    buf = (char*)malloc(1024);
    if (!buf) {
        ret = 2;
        goto cleanup; // 跳转时 fp 依然会被关闭，避免泄漏
    }
    // ... 正常业务逻辑 ...
cleanup:
    // 统一回收：逆序释放（先申请的后释放，后申请的先释放）
    if (buf) free(buf);
    if (fp) fclose(fp);
    return ret;
}
```
## 场景二：跳出深层嵌套循环
使用 `break` 只能跳出一层循环，而 `goto` 可以一次性跳出所有循环。
```c
for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
        for (int k = 0; k < 100; k++) {
            if (found) {
                goto end_loop; // 一次性跳出三层循环
            }
        }
    }
}
end_loop:
    printf("已退出所有循环\n");
```

