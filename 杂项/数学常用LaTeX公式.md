以下是初等数学与高等数学中常用符号的 **LaTeX** 公式代码。所有代码均需在数学模式（如 `$...$` 或 `\[...\]`）中使用。对于矩阵等复杂环境，建议加载 `amsmath` 宏包。

## 1. 基本运算符号

|符号|LaTeX 代码|示例效果（描述）|
|---|---|---|
|加号|`+`|a+ba+b|
|减号|`-`|a−ba−b|
|乘号（点）|`\cdot`|a⋅ba⋅b|
|乘号（叉）|`\times`|a×ba×b|
|除号|`\div`|a÷ba÷b|
|分数|`\frac{a}{b}`|abba​|
|正负号|`\pm`|±a±a|
|负正号|`\mp`|∓a∓a|
|根号|`\sqrt{x}`|xx​|
|n次根号|`\sqrt[n]{x}`|xnnx​|

## 2. 关系运算符

|符号|LaTeX 代码|示例效果|
|---|---|---|
|等于|`=`|a=ba=b|
|不等于|`\ne` 或 `\neq`|a≠ba=b|
|约等于|`\approx`|a≈ba≈b|
|相似|`\sim`|a∼ba∼b|
|全等|`\cong`|△ABC≅△DEF△ABC≅△DEF|
|恒等于|`\equiv`|a≡ba≡b|
|小于等于|`\le` 或 `\leq`|a≤ba≤b|
|大于等于|`\ge` 或 `\geq`|a≥ba≥b|
|远小于|`\ll`|a≪ba≪b|
|远大于|`\gg`|a≫ba≫b|

## 3. 希腊字母（小写）

|符号|LaTeX 代码|符号|LaTeX 代码|
|---|---|---|---|
|α|`\alpha`|β|`\beta`|
|γ|`\gamma`|δ|`\delta`|
|ε|`\epsilon`|ζ|`\zeta`|
|η|`\eta`|θ|`\theta`|
|ι|`\iota`|κ|`\kappa`|
|λ|`\lambda`|μ|`\mu`|
|ν|`\nu`|ξ|`\xi`|
|ο|`\omicron`|π|`\pi`|
|ρ|`\rho`|σ|`\sigma`|
|τ|`\tau`|υ|`\upsilon`|
|φ|`\phi`|χ|`\chi`|
|ψ|`\psi`|ω|`\omega`|

> 大写希腊字母：将首字母大写，如 `\Gamma` → Γ，`\Delta` → Δ，`\Omega` → Ω。

## 4. 初等函数

|符号|LaTeX 代码|示例效果|
|---|---|---|
|正弦|`\sin`|sin⁡xsinx|
|余弦|`\cos`|cos⁡xcosx|
|正切|`\tan`|tan⁡xtanx|
|自然对数|`\ln`|ln⁡xlnx|
|常用对数|`\log`|log⁡xlogx|
|指数函数|`\exp`|exp⁡(x)exp(x)|
|最大值|`\max`|max⁡imaxi​|
|最小值|`\min`|min⁡imini​|
|极限|`\lim`|lim⁡x→0limx→0​|

## 5. 求和、积分、乘积

|符号|LaTeX 代码|示例效果|
|---|---|---|
|求和|`\sum_{i=1}^{n} a_i`|∑i=1nai∑i=1n​ai​|
|积分|`\int_{a}^{b} f(x)\,dx`|∫abf(x) dx∫ab​f(x)dx|
|二重积分|`\iint_{D}`|∬D∬D​|
|三重积分|`\iiint_{V}`|∭V∭V​|
|环路积分|`\oint_{C}`|∮C∮C​|
|乘积|`\prod_{i=1}^{n} x_i`|∏i=1nxi∏i=1n​xi​|
|并集|`\bigcup_{i=1}^{n} A_i`|⋃i=1nAi⋃i=1n​Ai​|
|交集|`\bigcap_{i=1}^{n} A_i`|⋂i=1nAi⋂i=1n​Ai​|

## 6. 微分与导数

|符号|LaTeX 代码|示例效果|
|---|---|---|
|微分算子 d|`\mathrm{d}`|∫f(x) dx∫f(x)dx|
|偏微分|`\partial`|∂f∂x∂x∂f​|
|梯度|`\nabla`|∇f∇f|
|一阶导数（点）|`\dot{y}`|y˙y˙​|
|二阶导数（点）|`\ddot{y}`|y¨y¨​|
|向量箭头|`\vec{v}`|v⃗v|
|估计值/平均值|`\hat{a}`|a^a^|
|长横线|`\bar{z}`|zˉzˉ|

## 7. 集合论与逻辑符号

|符号|LaTeX 代码|示例效果|
|---|---|---|
|属于|`\in`|a∈Aa∈A|
|不属于|`\notin`|a∉Aa∈/A|
|包含于|`\subset` 或 `\subseteq`|A⊆BA⊆B|
|包含|`\supset` 或 `\supseteq`|B⊇AB⊇A|
|并|`\cup`|A∪BA∪B|
|交|`\cap`|A∩BA∩B|
|空集|`\emptyset` 或 `\varnothing`|∅∅|
|任意|`\forall`|∀x∀x|
|存在|`\exists`|∃x∃x|
|非|`\neg` 或 `\lnot`|¬P¬P|
|蕴含|`\implies`|P  ⟹  QP⟹Q|
|等价|`\iff`|P  ⟺  QP⟺Q|

## 8. 常用数集（黑板粗体，需 `\mathbb`）

|符号|LaTeX 代码|含义|
|---|---|---|
|ℝ|`\mathbb{R}`|实数集|
|ℕ|`\mathbb{N}`|自然数集|
|ℤ|`\mathbb{Z}`|整数集|
|ℚ|`\mathbb{Q}`|有理数集|
|ℂ|`\mathbb{C}`|复数集|

## 9. 矩阵与行列式（需 `amsmath`）
```LaTex
% 矩阵（圆括号）
\begin{pmatrix}
a & b \\
c & d
\end{pmatrix}
% 矩阵（方括号）
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix}
% 行列式
\begin{vmatrix}
a & b \\
c & d
\end{vmatrix}

```

## 10. 其他常用符号

|符号|LaTeX 代码|示例效果|
|---|---|---|
|无穷大|`\infty`|∞∞|
|省略号（水平）|`\cdots`|a1,a2,⋯ ,ana1​,a2​,⋯,an​|
|省略号（竖直）|`\vdots`|⋮⋮|
|省略号（对角线）|`\ddots`|⋱⋱|
|二项式系数|`\binom{n}{k}`|(nk)(kn​)|
|上花括号|`\overbrace{a+b}^{\text{注}}`|a+b⏞注a+b​注​|
|下花括号|`\underbrace{a+b}_{\text{注}}`|a+b⏟注注a+b​​|
|可伸缩括号|`\left( \frac{a}{b} \right)`|(ab)(ba​)|