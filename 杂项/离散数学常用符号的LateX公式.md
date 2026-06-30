### 一、逻辑符号

|符号|含义|LaTeX 命令|
|---|---|---|
|$\neg$|否定|`\neg` 或 `\lnot`|
|$\land$|合取|`\land` 或 `\wedge`|
|$\lor$|析取|`\lor` 或 `\vee`|
|$\to$|蕴含|`\to` 或 `\rightarrow`|
|$\leftrightarrow$|等价|`\leftrightarrow`|
|$\oplus$|异或|`\oplus`|
|$\top$|永真|`\top`|
|$\bot$|永假/矛盾|`\bot`|
|$\forall$|全称量词|`\forall`|
|$\exists$|存在量词|`\exists`|
|$\exists!$|唯一存在|`\exists!`|
|$\therefore$|所以|`\therefore`|
|$\because$|因为|`\because`|
|$\vdash$|推导|`\vdash`|
|$\vDash$|语义蕴含|`\vDash`|
|$\equiv$|逻辑等价|`\equiv`|

### 二、集合

| 符号               | 含义   | LaTeX 命令                    |
| ---------------- | ---- | --------------------------- |
| $\{ \}$          | 集合括号 | `\{` `\}`                   |
| $\emptyset$      | 空集   | `\emptyset` 或 `\varnothing` |
| $\in$            | 属于   | `\in`                       |
| $\notin$         | 不属于  | `\notin`                    |
| $\subseteq$      | 子集   | `\subseteq`                 |
| $\subset$        | 真子集  | `\subset`                   |
| $\supseteq$      | 超集   | `\supseteq`                 |
| $\cup$           | 并集   | `\cup`                      |
| $\cap$           | 交集   | `\cap`                      |
| $\setminus$      | 差集   | `\setminus`                 |
| $\triangle$      | 对称差  | `\triangle`                 |
| $\mathcal{P}(A)$ | 幂集   | `\mathcal{P}(A)`            |
| $\overline{A}$   | 补集   | `\overline{A}` 或 `A^c`      |
| $\mathbb{N}$     | 自然数集 | `\mathbb{N}`                |
| $\mathbb{Z}$     | 整数集  | `\mathbb{Z}`                |
| $\mathbb{Q}$     | 有理数集 | `\mathbb{Q}`                |
| $\mathbb{R}$     | 实数集  | `\mathbb{R}`                |
| $\mathbb{C}$     | 复数集  | `\mathbb{C}`                |
| $\aleph_0$       | 可数无穷 | `\aleph_0`                  |
### 三、关系与函数

|符号|含义|LaTeX 命令|
|---|---|---|
|$\sim$|等价关系|`\sim`|
|$\approx$|约等于/同构|`\approx`|
|$\cong$|同构|`\cong`|
|$\preceq$|偏序|`\preceq`|
|$\prec$|严格偏序|`\prec`|
|$\mid$|整除|`\mid`|
|$\nmid$|不整除|`\nmid`|
|$\pmod{n}$|模 n|`\pmod{n}`|
|$f: A \to B$|函数|`f: A \to B`|
|$f^{-1}$|反函数|`f^{-1}`|
|$\circ$|复合|`\circ`|
|$\mapsto$|映射|`\mapsto`|
|$\lfloor x \rfloor$|下取整|`\lfloor x \rfloor`|
|$\lceil x \rceil$|上取整|`\lceil x \rceil`|

### 四、图论

|符号|含义|LaTeX 命令|
|---|---|---|
|$G = (V, E)$|图|`G = (V, E)`|
|$\deg(v)$|度|`\deg(v)`|
|$\Delta(G)$|最大度|`\Delta(G)`|
|$\delta(G)$|最小度|`\delta(G)`|
|$K_n$|完全图|`K_n`|
|$C_n$|圈图|`C_n`|
|$P_n$|路图|`P_n`|
|$\overline{G}$|补图|`\overline{G}`|
|$\chi(G)$|色数|`\chi(G)`|
|$\kappa(G)$|点连通度|`\kappa(G)`|
|$\lambda(G)$|边连通度|`\lambda(G)`|

### 五、组合与数论

|符号|含义|LaTeX 命令|
|---|---|---|
|$n!$|阶乘|`n!`|
|$\binom{n}{k}$|二项式系数|`\binom{n}{k}`|
|$P(n, k)$|排列数|`P(n, k)`|
|$\dots$|省略号|`\dots`|
|$\sum$|求和|`\sum`|
|$\prod$|求积|`\prod`|
|$\gcd(a,b)$|最大公因数|`\gcd(a, b)`|
|$\operatorname{lcm}(a,b)$|最小公倍数|`\operatorname{lcm}(a, b)`|
|$a \equiv b \pmod{n}$|同余|`a \equiv b \pmod{n}`|

### 六、常见希腊字母

|符号|LaTeX|符号|LaTeX|
|---|---|---|---|
|$\alpha$|`\alpha`|$\beta$|`\beta`|
|$\gamma$|`\gamma`|$\delta$|`\delta`|
|$\epsilon$|`\epsilon`|$\varepsilon$|`\varepsilon`|
|$\theta$|`\theta`|$\lambda$|`\lambda`|
|$\mu$|`\mu`|$\pi$|`\pi`|
|$\sigma$|`\sigma`|$\tau$|`\tau`|
|$\phi$|`\phi`|$\varphi$|`\varphi`|
|$\omega$|`\omega`|$\Omega$|`\Omega`|

**使用时注意：**
- 需要加载 `amsmath`, `amssymb` 宏包。
- 空心字母需 `\mathbb{}`（配合 `amsfonts`）。
- 花体用 `\mathcal{}`。