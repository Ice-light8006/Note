# Git入门
Git的核心思想可以理解为：
在本地保存项目的多个版本，然后通过提交（commit）记录每一次修改，必要时可以回退、分支开发、多人协作。
git的使用流程如下
```
创建项目
   ↓
git init
   ↓
修改代码
   ↓
git add
   ↓
git commit
   ↓
连接远程仓库
   ↓
git push
```
# 配置Git身份
Git 本身是一个分布式版本控制系统，它不会自动知道“这个代码是谁改的”，所以需要你在提交时附带作者信息
在第一次安装Git之后，要先配置身份
```bash
git config --global user.name "你的名字"
git config --global user.email "你的邮箱"
```
假如说我执行
```bash
git config --global user.name "Ice light"
git config --global user.emaill "xxx@gmail.com"
```
那么，在一次提交中，如果执行
```bash
git commit -m "添加RC522驱动"
```
则Git会在提交记录中保存
```git
commit a83f91d

Author: Ice light <xxx@gmail.com>

**添加RC522驱动**
```

---

另外，邮箱也可以用来关联GitHub身份
虽然 Git 本地不验证邮箱，但是 GitHub/Gitee 会根据：
```
commit里的邮箱
        ↓
匹配
账号绑定邮箱
        ↓
显示贡献记录
```
例如：
你的 GitHub 账号绑定：
```
xxx@gmail.com
```
你本地：
```
git config --global user.email "xxx@gmail.com"
```
那么你的 commit：
```
Author: Huang <xxx@gmail.com>
```
上传 GitHub 后，GitHub 可以识别：
> 这个提交属于 Huang 这个账号。

于是你的贡献图（绿格子）会增加。

---
Git配置命令的格式
```
git config [作用范围] 配置项 配置值
```
这里作用范围如果写`--global`就是全局配置，如果不写那就是项目配置
全局配置，意思就是你所有的项目全都使用一个用户名和邮箱。而项目配置则是针对某一个项目的身份信息的配置。如果同时配置了全局配置和项目配置，那么在使用Git推送这个项目时，则会优先使用项目配置

# 创建Git仓库
假设一个项目的项目目录的结构如下
```
STM32_Project
├── Core
├── Drivers
├── main.c
└── README.md
```
那么，在这个项目目录内执行初始化命令
```bash
git init
```
此时会生成一个名为`.git`的文件夹，这就是Git数据库
```
STM32_Project
│
├── .git   ← Git数据库
├── Core
├── Drivers
└── main.c
```
`.git` 是 Git 的核心，里面保存：
- 历史版本
- 提交记录
- 分支信息
- 配置信息
# 查看当前状态
```bash
git status
```
如果控制台输出了
```
Untracked files:
    main.c
```
意思就是：Git发现了新文件，名为`main.c`，但是Git还没有跟踪它
# Git的三个区域
Git有三个区域：工作区，暂存区，版本库
```
工作区
  |
  | git add
  ↓
暂存区
  |
  | git commit
  ↓
版本库
```
可以使用
```bash
git add .
```
把项目中所有文件添加到暂存区
然后再使用
```bash
git commit
```
把暂存区中所有文件推送到版本库。

---
例如如果我们执行
```bash
git status
```
如果看到
```
Untracked files:
    main.c
```
然后我们执行
```bash
git add main.c
```
这时候再执行
```bash
git commit
```
然后再执行
```bash
git status
```
我们看到的就是
```
Changes to be committed:
    new file: main.c
```
表示这些修改已经准备提交
# 查看提交历史
命令
```bash
git log
```
可以查看所有的commit的历史，每次commit都对应唯一一个ID，例如
```
commit a83f91d
Author: Ice light

完成第一次编写

commit b73221a

完成第二次编写
```

# 远程仓库的使用
这是Git使用最重要的部分，我们一定要学会熟练使用GitHub，这有助于我们进行多人协作开发
我们先在GitHub上创建一个名为Project的仓库
然后本地关联
```bash
git remote add origin 仓库地址
```
在这里，仓库地址就是
```URL
https://github.com/user/project.git
```
这里的`user`就是你GitHub的用户名，地址后面的`project.git`就是`user`用户下的一个名为 `project`的仓库
然后这里`origin`是给这个远程仓库起的别名。
对于一个项目，可以有很多个远程仓库
例如如果执行
```
git remote add origin https://github.com/user/project.git
git remote add other https://github.com/user/other.git
```
那么就会有两个远程仓库，一个名为`origin`，另一个名为`other`
```
origin -> https://github.com/user/project.git
other -> https://github.com/user/other.git
```

---
在第一次创建远程仓库的时候，首先需要执行
```bash
git branch -M main
```
这个的作用是把当前分支命名为`main`
然后再执行
```bash
git push origin main
```
意思就是把当前项目推送到origin指向的远程仓库的main分支
但是这样写，每次都要写全推送到哪个仓库，推送到哪个分支
如果加一个`-u`
```bash
git push -u origin main
```
它的作用是把本地`main`分支推送到远程仓库`origin`，并建立关联
以后每次执行
```bash
git push
```
就会被当成
```bash
git push origin main
```
这样就简化了操作

---
如果我在执行了
```bash
git push -u origin main
```
之后执行
```bash
git push other main
```
那么就会把当前代码推送到other仓库的main分支
如果执行
```bash
git push
```
那么就会把当前代码推送到origin仓库的main分支
可以这样理解：
```bash
git push -u origin main
```
这里这个`-u`定义了origin是main分支是默认的推送位置，而`git push`就是把代码推送到默认的位置
如果参数明确指定了仓库名和分支名，那么还是按照参数给的仓库和分支来
# 拉取别人更新
```bash
git pull
```
作用：把远程仓库同步到本地代码，常用于拉取别人更新的文件
# 分支（branch）
分支用于开发新功能。
该命令可以查看当前所有的分支列表
```bash
git branch
```
创建一个新的分支，取名为dev：
```bash
git branch dev
```
切换到名为dev的分支：
```bash
git checkout dev
```
假如已经有了main分支，在创建dev分支之后，现在：
```
main
 |
 |
dev
```
那么完全可以：
```
main:
稳定版本


dev:
开发新功能
```
完成后合并：
切回 main：
```bash
git checkout main
```
然后执行这个命令，把dev分支合并到当前分支（刚才切回到main，那么当前分支是main，就是把dev合并到main分支内）
```bash
git merge dev
```
---
`git merge` 的核心工作是将两个独立分支的提交历史和文件状态“缝合”到一起。当你执行合并时（例如在 `main` 分支执行 `git merge dev`）
另外，执行
```bash
git merge dev
```
之后，只是把dev的commit全部复制到了main分支中，dev不会被删除，而dev原有的commit依然存在绝对不会消失
可以这样理解：合并完成的一瞬间，`main` 吸收了 `dev` 的所有成果，此时两个分支包含了完全一样的代码。只不过 `main` 带着这些新成果继续往前走，而 `dev` 停留在原地，等待你决定它的去留。
# `.gitignore`文件的介绍与注意事项
在创建一个git仓库之后，会在这个仓库的根目录内生成一个文件夹，名为.git
同时，每次执行`commit`、`add`等操作时，会根据仓库中的 `.gitignore` 文件规则判断哪些未被跟踪的文件需要被忽略。`.gitignore` 可以存在于仓库根目录或任意子目录中。如果没有`.gitignore`文件，那么则在执行相关操作时不会忽略任何文件
对于一个项目，有些文件（例如编译输出的文件）不应该上传到GitHub上，这时候我们就可以通过编写`.gitignore`文件来实现
另外要注意一个细节，`.gitignore`的作用范围是**它所在目录及其所有子目录**
也就是说，假如有项目根目录是`/`
然后项目的结构如下
```
Project/
│
├── .gitignore
│
├── main.c
│
└── src/
    ├── .gitignore
    ├── test.c
    └── driver/
        └── xxx.c
```
这时候，`src`内部的`.gitignore`只会负责`src`内部的文件是否忽略
如果说我在`src`内的`.gitignore`中写了`*.c`而没有在项目根目录中的`.gitignore`中写`*.c`，那么项目根目录中的`*.c`就不会被忽略，而`src`内部的`*.c`就会被忽略
现在我将讲解一些`.gitignore`的一些常用语法
## 1. 注释
注释的语法是
```gitignore
# + 注释内容
```
`#` 开头的这一行都是注释。和C语言中的注释一样，注释会被忽略
## 2. `*.后缀`
例如
```gitigore
*.py
```
这时候会忽略所有后缀为`py`的文件，即Python代码文件
如果我们的项目中有一些辅助开发而写的Python的脚本，并且这些脚本本身与项目无关，我们就可以在`.gitignore`中写上`*.py`，这时候就会忽略这些Python脚本
另外一定要注意，如果写`*.py`，只会忽略所有后缀为`py`的文件，而不会忽略符合`*.py`的文件夹，例如有一个文件夹名为`m.py`，其不会被忽略
## 3. 文件目录
`/`表示**仓库根目录**
如果你写
```gitignore
/Objects/
```
这时候就会忽略项目根目录下的Object文件夹和这个文件夹内部的所有文件。但是，如果项目根目录的二级目录或者更高级目录有文件夹名为Object，那么这个文件夹和这个文件夹内部的所有文件就不会被忽略
如果我们想忽略所有名为`Objects`的文件夹和内部所有的文件，就可以写
```gitignore
Objects/
```
它的含义是：任意位置的`Objects`文件夹
也可以写
```gitignore
**/Objects/
```
这里`**`表示：任意数量的目录层级
另外一定要注意`Objects`与`Objects/`的区别：
`Objects`表示所有名为`Objects`的**文件或文件夹**，`Objects/`表示所有名为`Objects`的**文件夹**
还有这种写法
```gitignore
src/Objects/
```
意思是，匹配任意一个名为`src`的目录内部的`Objects`文件夹
注意，这里这个`src`不一定是根目录内部的`src`，可以是项目内部任意一个目录内部的`src`
如果是
```gitignore
/src/Objects/
```
这时候就会仅匹配根目录内部的`src`目录内的`Objects`文件夹
总结：

| 写法             | 含义                             |
| -------------- | ------------------------------ |
| `Objects/`     | 任意位置的 Objects 目录               |
| `/Objects/`    | 项目根目录下的 Objects                |
| `src/Objects/` | 任意一个 src 目录下的 Objects          |
| `**/Objects/`  | 任意层级 Objects（和 `Objects/`效果接近） |
## 4. 取消忽略
```gitignore
*.txt
!m.txt
```
这个的意思是：忽略所有`.txt`文件，但是保留文件`m.txt`
另外要注意
```gitignore
!m.txt
```
这个表示的是保留所有名为`m.txt`的**文件或目录**，也就是说不仅仅是文件，如果有目录名为`m.txt`，也会被保留