# ASCII Donut 3D C++

## z-axis rotate, front view

$$
(r_1 + r_2 \cos(\theta), r_2\sin(\theta), 0)
\begin{bmatrix}
\cos(\psi) & 0 & \sin(\psi)\\
0 & 1 & 0\\
-\sin(\psi) & 0 & \cos(\psi)
\end{bmatrix}
 = 
(r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi), r_2\sin(\theta), -r_1\sin(\psi) - r_2\cos(\theta)\sin(\psi))

$$

Get `x` and `z` as `x` and `y`, they are defined in the inner loop:

```c++
Float x { r1 * cos_psi + r2 * cos_theta * cos_psi };
Float y { - r1 * sin_psi - r2 * cos_theta * sin_psi };
```

And `y` as `z` is irrelative with $\psi$, so it is defined in the outer loop:

```c++
Float z { r2 * sin_theta };
```
