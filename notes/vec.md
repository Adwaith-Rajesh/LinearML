### notes on vector arithmetic

#### Cross product

$$
\overrightarrow{a} = a_1i + a_2j + a_3k
$$

$$
\overrightarrow{b} = b_1i+ b_2j + b_3k
$$

$$
\overrightarrow{a} \times \overrightarrow{b} =
\begin{vmatrix}
a_2 & a_3 \\
b_2 & b_3
\end{vmatrix}i-
\begin{vmatrix}
a_1 & a_3 \\
b_1 & b_3
\end{vmatrix}j
+
\begin{vmatrix}
a_1 & a_2 \\
b_1 & b_3
\end{vmatrix}k
$$

$$
\overrightarrow{a} \times \overrightarrow{b} = (a_2b_3 - a_3b_2)i - (a_1b_3 - a_3b_1)j + (a_1b_2 - a_2b_1)k
$$

Using Vec type

```c
v1 = Vec{.dim=3, .elems=[a1, a2, a3]}
v2 = Vec{.dim=3, .elems=[b1, b2, b3]}

i = (v1.elems[1] * v2.elems[2]) - (v1.elems[2] * v2.elems[1])
j = (v1.elems[0] * v2.elems[2]) - (v1.elems[2] * v2.elems[0])
k = (v1.elems[0] * v2.elems[1]) - (v1.elems[1] * v2.elems[0])

new_v = Vec{.dim=3, .elems=[i, -j, k]}
```

#### Unit Vector

$$
\overrightarrow{a} = \langle \ a_1,\ a_2,\ a_3,\ \dots, \ a_n\ \rangle
$$

$$
unit \ vector, \hat{a} = \frac{\overrightarrow{a}}{\vert a \vert}
$$

$$
where, \  \vert a \vert = \sqrt{a_1^2 + a_2^2 + a_3^2 + \dots + a_n^2}
$$

$$
\hat{a} = \langle \
    \frac{a_1}{\vert a \vert},\
    \frac{a_2}{\vert a \vert},\
    \frac{a_3}{\vert a \vert},\
    \dots,\
    \frac{a_n}{\vert a \vert} \
\rangle
$$

#### Angle between vectors

$
Angle \ between two vectors \overrightarrow{a} \ and \  \overrightarrow{b} ,\  \theta
$

$$
\theta = \cos^{-1} \left(
    \frac{\overrightarrow{a} \cdot \overrightarrow{b}}{\vert \overrightarrow{a} \vert \ \vert \overrightarrow{b} \vert}
\right)
$$
