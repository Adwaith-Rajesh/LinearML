### notes on vector arithmetic

#### Cross product

$$
\overrightarrow{a} = a_1i + a_2j + a_3k
$$

$$
\overrightarrow{b} = b_1i+ b_2j + b_3k
$$

$$
\begin{align}

\overrightarrow{a} \times \overrightarrow{b} & =
\begin{vmatrix}
a_2 & a_3 \\
b_2 & b_3
\end{vmatrix}i
-
\begin{vmatrix}
a_1 & a_3 \\
b_1 & b_3
\end{vmatrix}j
+
\begin{vmatrix}
a_1 & a_2 \\
b_1 & b_3
\end{vmatrix}k \\


& = (a_2b_3 - a_3b_2)i - (a_1b_3 - a_3b_1)j + (a_1b_2 - a_2b_1)k

\end{align}
$$

Using Vec type

```c
v1 = Vec{.dim=3, .elems=[a1, a2, a3]}
v2 = Vec{.dim=3, .elems=[b1, b2, b3]}

i = (v1.elems[1] * v2.elems[2]) - (v1.elems[2] * v2.elems[1])
j = (v1.elems[0] * v2.elems[2]) - (v1.elems[2] * v2.elems[0])
k = (v1.elems[0] * v2.elems[1]) - (v1.elems[1] * v2.elems[1])

new_v = Vec{.dim=3, .elems=[i, -j, k]}
```
