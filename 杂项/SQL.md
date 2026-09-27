# SQL 常见语法与关键字速查

> SQL（Structured Query Language）用于操作关系型数据库。
>
> 本文以通用 SQL 为主，同时兼顾 SQLite 常用语法。

---

# 目录

- [一、SQL 基础](#一sql-基础)
- [二、数据库与表](#二数据库与表)
- [三、数据类型](#三数据类型)
- [四、INSERT 插入数据](#四insert-插入数据)
- [五、SELECT 查询数据](#五select-查询数据)
- [六、WHERE 条件查询](#六where-条件查询)
- [七、排序 ORDER BY](#七排序-order-by)
- [八、LIMIT 与 OFFSET](#八limit-与-offset)
- [九、UPDATE 修改数据](#九update-修改数据)
- [十、DELETE 删除数据](#十delete-删除数据)
- [十一、聚合函数](#十一聚合函数)
- [十二、GROUP BY 分组](#十二group-by-分组)
- [十三、HAVING](#十三having)
- [十四、JOIN 多表连接](#十四join-多表连接)
- [十五、子查询](#十五子查询)
- [十六、DISTINCT 去重](#十六distinct-去重)
- [十七、LIKE 模糊查询](#十七like-模糊查询)
- [十八、NULL](#十八null)
- [十九、CASE 条件表达式](#十九case-条件表达式)
- [二十、约束 Constraints](#二十约束-constraints)
- [二十一、主键 PRIMARY KEY](#二十一主键-primary-key)
- [二十二、外键 FOREIGN KEY](#二十二外键-foreign-key)
- [二十三、索引 INDEX](#二十三索引-index)
- [二十四、视图 VIEW](#二十四视图-view)
- [二十五、事务 Transaction](#二十五事务-transaction)
- [二十六、常见运算符](#二十六常见运算符)
- [二十七、常见关键字](#二十七常见关键字)
- [二十八、SQL 执行顺序](#二十八sql-执行顺序)
- [二十九、SQLite 常用命令](#二十九sqlite-常用命令)
- [三十、实际项目示例](#三十实际项目示例)

---

# 一、SQL 基础

SQL 主要用于：

```text
创建数据库结构
    ↓
创建表
    ↓
插入数据
    ↓
查询数据
    ↓
修改数据
    ↓
删除数据
````

SQL 常见操作可以分为：

|类型|作用|常见关键字|
|---|---|---|
|DDL|定义数据库结构|CREATE、ALTER、DROP|
|DML|操作数据|INSERT、UPDATE、DELETE|
|DQL|查询数据|SELECT|
|DCL|权限控制|GRANT、REVOKE|
|TCL|事务控制|BEGIN、COMMIT、ROLLBACK|

---

# 二、数据库与表

## 2.1 创建表

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name TEXT,
    age INTEGER
);
```

基本结构：

```
CREATE TABLE 表名 (
    列名 数据类型,
    列名 数据类型,
    ...
);
```

---

## 2.2 删除表

```
DROP TABLE users;
```

如果表不存在不报错：

```
DROP TABLE IF EXISTS users;
```

---

## 2.3 修改表

添加列：

```
ALTER TABLE users
ADD COLUMN email TEXT;
```

SQLite 对 `ALTER TABLE` 的支持相对有限。

---

## 2.4 查看表

SQLite：

```
.schema users
```

或者：

```
PRAGMA table_info(users);
```

---

# 三、数据类型

不同数据库的数据类型存在差异。

SQLite 常见类型：

|类型|说明|
|---|---|
|INTEGER|整数|
|REAL|浮点数|
|TEXT|文本|
|BLOB|二进制数据|
|NULL|空值|

例如：

```
CREATE TABLE student (
    id INTEGER,
    name TEXT,
    score REAL,
    photo BLOB
);
```

---

# 四、INSERT 插入数据

## 4.1 插入一条数据

```
INSERT INTO users (name, age)
VALUES ('Tom', 20);
```

---

## 4.2 插入多条数据

```
INSERT INTO users (name, age)
VALUES
    ('Tom', 20),
    ('Jack', 21),
    ('Alice', 19);
```

---

## 4.3 不指定列名

```
INSERT INTO users
VALUES (1, 'Tom', 20);
```

不推荐。

因为必须严格按照表的字段顺序填写。

推荐：

```
INSERT INTO users (id, name, age)
VALUES (1, 'Tom', 20);
```

---

# 五、SELECT 查询数据

## 5.1 查询所有数据

```
SELECT *
FROM users;
```

`*` 表示所有列。

---

## 5.2 查询指定列

```
SELECT name, age
FROM users;
```

---

## 5.3 给列设置别名

```
SELECT
    name AS username,
    age AS user_age
FROM users;
```

`AS` 可以省略：

```
SELECT
    name username,
    age user_age
FROM users;
```

---

## 5.4 给表设置别名

```
SELECT u.name
FROM users AS u;
```

也可以：

```
SELECT u.name
FROM users u;
```

---

# 六、WHERE 条件查询

基本语法：

```
SELECT *
FROM users
WHERE 条件;
```

例如：

```
SELECT *
FROM users
WHERE age > 18;
```

---

## 6.1 多条件

### AND

```
SELECT *
FROM users
WHERE age >= 18
  AND age <= 30;
```

### OR

```
SELECT *
FROM users
WHERE age < 18
   OR age > 60;
```

### NOT

```
SELECT *
FROM users
WHERE NOT age = 18;
```

---

## 6.2 BETWEEN

```
SELECT *
FROM users
WHERE age BETWEEN 18 AND 30;
```

等价于：

```
WHERE age >= 18
  AND age <= 30
```

---

## 6.3 IN

```
SELECT *
FROM users
WHERE age IN (18, 20, 25);
```

相当于：

```
WHERE age = 18
   OR age = 20
   OR age = 25
```

---

## 6.4 NOT IN

```
SELECT *
FROM users
WHERE age NOT IN (18, 20, 25);
```

---

# 七、排序 ORDER BY

升序：

```
SELECT *
FROM users
ORDER BY age ASC;
```

降序：

```
SELECT *
FROM users
ORDER BY age DESC;
```

其中：

```
ASC  = Ascending   升序
DESC = Descending  降序
```

---

## 多字段排序

```
SELECT *
FROM users
ORDER BY age DESC, name ASC;
```

先按照 `age` 排序。

如果年龄相同，再按照 `name` 排序。

---

# 八、LIMIT 与 OFFSET

## LIMIT

只获取前 10 条：

```
SELECT *
FROM users
LIMIT 10;
```

---

## OFFSET

跳过前 10 条：

```
SELECT *
FROM users
LIMIT 10 OFFSET 10;
```

常用于分页。

例如：

```
第 1 页：
LIMIT 10 OFFSET 0

第 2 页：
LIMIT 10 OFFSET 10

第 3 页：
LIMIT 10 OFFSET 20
```

---

# 九、UPDATE 修改数据

基本语法：

```
UPDATE users
SET age = 21
WHERE id = 1;
```

---

## 修改多个字段

```
UPDATE users
SET
    name = 'Jack',
    age = 22
WHERE id = 1;
```

---

## 根据原来的值修改

```
UPDATE users
SET age = age + 1
WHERE id = 1;
```

---

> ⚠️ 注意：
> 
> 如果没有 `WHERE`：

```
UPDATE users
SET age = 18;
```

会修改整个表的所有记录。

---

# 十、DELETE 删除数据

删除指定数据：

```
DELETE FROM users
WHERE id = 1;
```

删除满足条件的数据：

```
DELETE FROM users
WHERE age < 18;
```

---

## 删除整个表的数据

```
DELETE FROM users;
```

注意：

```
DELETE FROM users;
```

只是删除数据。

而：

```
DROP TABLE users;
```

是把整个表结构也删除。

---

# 十一、聚合函数

SQL 常见聚合函数：

|函数|作用|
|---|---|
|COUNT()|统计数量|
|SUM()|求和|
|AVG()|平均值|
|MAX()|最大值|
|MIN()|最小值|

---

## COUNT

统计用户数量：

```
SELECT COUNT(*)
FROM users;
```

---

## SUM

```
SELECT SUM(score)
FROM students;
```

---

## AVG

```
SELECT AVG(score)
FROM students;
```

---

## MAX

```
SELECT MAX(score)
FROM students;
```

---

## MIN

```
SELECT MIN(score)
FROM students;
```

---

## 给聚合结果起名字

```
SELECT COUNT(*) AS user_count
FROM users;
```

---

# 十二、GROUP BY 分组

例如：

```
users

id    name    department
1     Tom     IT
2     Jack    IT
3     Alice   HR
4     Bob     HR
```

统计每个部门有多少人：

```
SELECT
    department,
    COUNT(*) AS count
FROM users
GROUP BY department;
```

结果：

```
IT    2
HR    2
```

---

## GROUP BY 多字段

```
SELECT
    department,
    gender,
    COUNT(*)
FROM users
GROUP BY department, gender;
```

---

# 十三、HAVING

`HAVING` 用于对分组后的结果进行筛选。

例如：

```
SELECT
    department,
    COUNT(*) AS count
FROM users
GROUP BY department
HAVING COUNT(*) > 10;
```

---

## WHERE 和 HAVING 的区别

### WHERE

分组之前过滤：

```
WHERE age >= 18
```

### HAVING

分组之后过滤：

```
HAVING COUNT(*) > 10
```

可以简单理解：

```
WHERE
    ↓
先过滤数据

GROUP BY
    ↓
进行分组

HAVING
    ↓
过滤分组结果
```

---

# 十四、JOIN 多表连接

假设有：

```
users

id    name
1     Tom
2     Jack
```

以及：

```
orders

id    user_id    price
1     1          100
2     1          200
3     2          300
```

---

## 14.1 INNER JOIN

查询用户和订单：

```
SELECT
    users.name,
    orders.price
FROM users
INNER JOIN orders
ON users.id = orders.user_id;
```

结果：

```
Tom     100
Tom     200
Jack    300
```

---

## 14.2 LEFT JOIN

```
SELECT
    users.name,
    orders.price
FROM users
LEFT JOIN orders
ON users.id = orders.user_id;
```

`LEFT JOIN` 会保留左表的所有数据。

即使某个用户没有订单，也会显示。

---

## JOIN 核心区别

```
INNER JOIN
    ↓
只保留两张表能够匹配的数据

LEFT JOIN
    ↓
左表全部保留
右表匹配不到 → NULL
```

---

# 十五、子查询

查询年龄大于平均年龄的人：

```
SELECT *
FROM users
WHERE age > (
    SELECT AVG(age)
    FROM users
);
```

内部：

```
SELECT AVG(age)
FROM users;
```

先计算平均年龄。

外部：

```
SELECT *
FROM users
WHERE age > 平均年龄;
```

---

# 十六、DISTINCT 去重

例如：

```
SELECT department
FROM users;
```

可能得到：

```
IT
IT
HR
HR
HR
```

使用：

```
SELECT DISTINCT department
FROM users;
```

得到：

```
IT
HR
```

---

# 十七、LIKE 模糊查询

## `%`

表示任意数量的字符。

```
SELECT *
FROM users
WHERE name LIKE 'Tom%';
```

匹配：

```
Tom
Tom123
TomABC
```

---

## `_`

表示一个字符。

```
SELECT *
FROM users
WHERE name LIKE 'T_m';
```

可以匹配：

```
Tom
Tim
Tam
```

---

## 常见写法

以 Tom 开头：

```
LIKE 'Tom%'
```

以 Tom 结尾：

```
LIKE '%Tom'
```

包含 Tom：

```
LIKE '%Tom%'
```

---

# 十八、NULL

`NULL` 表示没有值。

注意：

```
NULL != 0
```

也不能写：

```
WHERE name = NULL;
```

正确：

```
WHERE name IS NULL;
```

---

## IS NOT NULL

```
SELECT *
FROM users
WHERE name IS NOT NULL;
```

---

# 十九、CASE 条件表达式

类似 C++ 的：

```
if / else if / else
```

例如：

```
SELECT
    name,
    age,
    CASE
        WHEN age < 18 THEN '未成年'
        WHEN age < 60 THEN '成年人'
        ELSE '老年人'
    END AS age_group
FROM users;
```

---

# 二十、约束 Constraints

创建表时，可以给字段添加约束。

常见约束：

|约束|作用|
|---|---|
|PRIMARY KEY|主键|
|FOREIGN KEY|外键|
|NOT NULL|不允许 NULL|
|UNIQUE|不允许重复|
|DEFAULT|默认值|
|CHECK|检查条件|

例如：

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    age INTEGER CHECK(age >= 0),
    email TEXT UNIQUE,
    status INTEGER DEFAULT 1
);
```

---

# 二十一、主键 PRIMARY KEY

主键用于唯一标识一条记录。

例如：

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name TEXT
);
```

通常：

```
id
 ↓
唯一标识一个用户
```

例如：

```
1 → Tom
2 → Jack
3 → Alice
```

---

## SQLite 自增 ID

常见写法：

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT
);
```

插入：

```
INSERT INTO users (name)
VALUES ('Tom');
```

SQLite 会自动生成：

```
id = 1
```

---

# 二十二、外键 FOREIGN KEY

用于建立表之间的关系。

例如：

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name TEXT
);
```

订单：

```
CREATE TABLE orders (
    id INTEGER PRIMARY KEY,
    user_id INTEGER,
    price REAL,

    FOREIGN KEY (user_id)
    REFERENCES users(id)
);
```

关系：

```
users
  │
  │ id
  ↓
orders.user_id
```

---

# 二十三、索引 INDEX

索引用于提高查询效率。

创建：

```
CREATE INDEX idx_users_name
ON users(name);
```

删除：

```
DROP INDEX idx_users_name;
```

例如经常：

```
SELECT *
FROM users
WHERE name = 'Tom';
```

那么可以考虑：

```
CREATE INDEX idx_users_name
ON users(name);
```

---

> ⚠️ 索引不是越多越好。
> 
> 索引会提高查询速度，但会增加：
> 
> - 磁盘空间
> - INSERT 成本
> - UPDATE 成本
> - DELETE 成本

---

# 二十四、视图 VIEW

视图可以理解成：

> 保存起来的一条查询语句。

创建：

```
CREATE VIEW user_orders AS
SELECT
    users.name,
    orders.price
FROM users
JOIN orders
ON users.id = orders.user_id;
```

之后可以：

```
SELECT *
FROM user_orders;
```

删除：

```
DROP VIEW user_orders;
```

---

# 二十五、事务 Transaction

事务用于保证一组 SQL 操作要么全部成功，要么全部失败。

开始事务：

```
BEGIN TRANSACTION;
```

提交：

```
COMMIT;
```

回滚：

```
ROLLBACK;
```

例如：

```
BEGIN TRANSACTION;

UPDATE accounts
SET money = money - 100
WHERE id = 1;

UPDATE accounts
SET money = money + 100
WHERE id = 2;

COMMIT;
```

如果中途出现错误：

```
ROLLBACK;
```

就可以撤销事务中的修改。

---

# 二十六、常见运算符

## 比较运算符

|运算符|含义|
|---|---|
|=|等于|
|!=|不等于|
|<>|不等于|
|>|大于|
|<|小于|
|>=|大于等于|
|<=|小于等于|

---

## 逻辑运算符

|运算符|含义|
|---|---|
|AND|并且|
|OR|或者|
|NOT|非|

---

## 特殊运算符

|运算符|用途|
|---|---|
|IN|是否属于集合|
|NOT IN|不属于集合|
|BETWEEN|范围|
|LIKE|模糊匹配|
|IS NULL|判断 NULL|
|IS NOT NULL|判断非 NULL|

---

# 二十七、常见关键字

## 数据库结构

```
CREATE
ALTER
DROP
TABLE
INDEX
VIEW
```

---

## 数据操作

```
INSERT
UPDATE
DELETE
```

---

## 数据查询

```
SELECT
FROM
WHERE
DISTINCT
GROUP BY
HAVING
ORDER BY
LIMIT
OFFSET
```

---

## 多表查询

```
JOIN
INNER JOIN
LEFT JOIN
RIGHT JOIN
FULL JOIN
ON
```

---

## 条件

```
AND
OR
NOT
IN
BETWEEN
LIKE
IS
NULL
```

---

## 聚合

```
COUNT
SUM
AVG
MAX
MIN
```

---

## 约束

```
PRIMARY KEY
FOREIGN KEY
NOT NULL
UNIQUE
DEFAULT
CHECK
```

---

## 事务

```
BEGIN
COMMIT
ROLLBACK
```

---

# 二十八、SQL 执行顺序

虽然 SQL 写的时候是：

```
SELECT
FROM
WHERE
GROUP BY
HAVING
ORDER BY
LIMIT;
```

但逻辑执行顺序通常可以理解为：

```
FROM
 ↓
JOIN
 ↓
WHERE
 ↓
GROUP BY
 ↓
HAVING
 ↓
SELECT
 ↓
DISTINCT
 ↓
ORDER BY
 ↓
LIMIT
```

这是理解复杂 SQL 非常重要的一点。

例如：

```
SELECT department, COUNT(*)
FROM users
WHERE age >= 18
GROUP BY department
HAVING COUNT(*) > 5
ORDER BY COUNT(*) DESC
LIMIT 10;
```

可以理解为：

```
1. FROM
   找到 users

2. WHERE
   只保留 age >= 18

3. GROUP BY
   按 department 分组

4. HAVING
   只保留人数 > 5 的部门

5. SELECT
   输出 department 和 COUNT(*)

6. ORDER BY
   按人数降序

7. LIMIT
   只取前 10 个
```

---

# 二十九、SQLite 常用命令

> 以下部分主要针对 SQLite 命令行工具。

查看所有表：

```
.tables
```

查看表结构：

```
.schema users
```

查看数据库：

```
.databases
```

查看 SQLite 帮助：

```
.help
```

退出：

```
.quit
```

---

## PRAGMA

SQLite 有大量 `PRAGMA` 命令。

查看表结构：

```
PRAGMA table_info(users);
```

查看外键状态：

```
PRAGMA foreign_keys;
```

开启外键：

```
PRAGMA foreign_keys = ON;
```

---

# 三十、实际项目示例

假设我们正在做一个考勤系统。

---

## 30.1 用户表

```
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    employee_id TEXT UNIQUE NOT NULL,
    department TEXT,
    created_at TEXT DEFAULT CURRENT_TIMESTAMP
);
```

---

## 30.2 添加用户

```
INSERT INTO users (
    name,
    employee_id,
    department
)
VALUES (
    '张三',
    '10001',
    '研发部'
);
```

---

## 30.3 查询所有用户

```
SELECT *
FROM users;
```

---

## 30.4 根据工号查询

```
SELECT *
FROM users
WHERE employee_id = '10001';
```

---

## 30.5 根据姓名模糊查询

```
SELECT *
FROM users
WHERE name LIKE '%张%';
```

---

## 30.6 修改部门

```
UPDATE users
SET department = '测试部'
WHERE employee_id = '10001';
```

---

## 30.7 删除用户

```
DELETE FROM users
WHERE employee_id = '10001';
```

---

# 三十一、SQL 常用模板

## 查询

```
SELECT 列
FROM 表
WHERE 条件
GROUP BY 分组字段
HAVING 分组条件
ORDER BY 排序字段 ASC/DESC
LIMIT 数量
OFFSET 偏移量;
```

---

## 插入

```
INSERT INTO 表名 (字段1, 字段2)
VALUES (值1, 值2);
```

---

## 修改

```
UPDATE 表名
SET
    字段1 = 值1,
    字段2 = 值2
WHERE 条件;
```

---

## 删除

```
DELETE FROM 表名
WHERE 条件;
```

---

## 创建表

```
CREATE TABLE 表名 (
    字段1 数据类型 约束,
    字段2 数据类型 约束,
    ...
);
```

---

# 三十二、SQL 最核心的 10 个关键字

如果刚开始学习 SQL，优先掌握：

```
SELECT
FROM
WHERE
INSERT
UPDATE
DELETE
JOIN
GROUP BY
ORDER BY
CREATE TABLE
```

其中最重要的是：

```
SELECT
FROM
WHERE
```

因为绝大多数查询都建立在这三个关键字上：

```
SELECT 要什么
FROM   从哪里要
WHERE  什么条件
```

例如：

```
SELECT name, age
FROM users
WHERE age >= 18;
```

翻译成人话：

```
从 users 表中
找到年龄 >= 18 的记录
然后把 name 和 age 给我
```

---

# 三十三、SQL 与 Qt 的对应关系

在 Qt + SQLite 项目中，经常会看到：

```
QSqlQuery query;
```

执行 SQL：

```
query.exec(
    "SELECT name, age "
    "FROM users "
    "WHERE age >= 18"
);
```

带参数时推荐使用绑定：

```
QSqlQuery query;

query.prepare(
    "SELECT * FROM users "
    "WHERE employee_id = :id"
);

query.bindValue(":id", "10001");

query.exec();
```

插入：

```
QSqlQuery query;

query.prepare(
    "INSERT INTO users "
    "(name, employee_id) "
    "VALUES (:name, :id)"
);

query.bindValue(":name", "张三");
query.bindValue(":id", "10001");

query.exec();
```

---

# 三十四、SQL 学习路线

建议按照下面的顺序学习：

```
1. SELECT
      ↓
2. WHERE
      ↓
3. INSERT / UPDATE / DELETE
      ↓
4. ORDER BY
      ↓
5. LIMIT / OFFSET
      ↓
6. 聚合函数
      ↓
7. GROUP BY
      ↓
8. HAVING
      ↓
9. JOIN
      ↓
10. 子查询
      ↓
11. PRIMARY KEY / FOREIGN KEY
      ↓
12. INDEX
      ↓
13. TRANSACTION
      ↓
14. 数据库设计
      ↓
15. SQL 性能优化
```

---

# 三十五、一句话理解 SQL

```
SELECT  → 我要什么
FROM    → 从哪里拿
WHERE   → 满足什么条件
GROUP BY → 怎么分组
HAVING  → 分组后留下什么
ORDER BY → 怎么排序
LIMIT   → 要多少
JOIN    → 怎么把多张表关联起来
INSERT  → 添加数据
UPDATE  → 修改数据
DELETE  → 删除数据
CREATE  → 创建数据库对象
DROP    → 删除数据库对象
```

```

如果你主要是为了**Qt + SQLite 项目**使用，这份里最值得你现在重点掌握的是：

**`CREATE TABLE → INSERT → SELECT → WHERE → UPDATE → DELETE → ORDER BY → JOIN → GROUP BY → TRANSACTION`**。

其他高级 SQL 可以等你实际遇到需求再补。
```