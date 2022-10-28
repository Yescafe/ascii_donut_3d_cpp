# ASCII Donut 3D C++

<https://www.bilibili.com/video/BV1te4y1671n>

<https://www.a1k0n.net/2011/07/20/donut-math.html>

## Build

```bash
rm -rf build
mkdir build && cd build
cmake ..
make
```

## y-axis rotate, front view

$$
R_y = \begin{bmatrix}
\cos(\psi) & 0 & \sin(\psi)\\
0 & 1 & 0\\
-\sin(\psi) & 0 & \cos(\psi)
\end{bmatrix} 
$$

$$
(r_1 + r_2 \cos(\theta), r_2\sin(\theta), 0)
\begin{bmatrix}
\cos(\psi) & 0 & \sin(\psi)\\
0 & 1 & 0\\
-\sin(\psi) & 0 & \cos(\psi)
\end{bmatrix} =
(r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi), r_2\sin(\theta), -r_1\sin(\psi) - r_2\cos(\theta)\sin(\psi))
$$

Get `x` and `z` as `x` and `y`, they are defined in the inner loop:

```c++
Float x { r1 * cos_psi + r2 * cos_theta * cos_psi };
Float y { - r1 * sin_psi - r2 * cos_theta * sin_psi };
```

And `y` as `z` is irrelative to $\psi$, so it is defined in the outer loop:

```c++
Float z { r2 * sin_theta };
```

## with x-axis and z-axis rotation

The rotation matrices of x-axis and z-axis rotation are:

$$
R_x = \begin{bmatrix}
1 & 0 & 0\\
0 & \cos(\delta) & -\sin(\delta)\\
0 & \sin(\delta) & \cos(\delta)
\end{bmatrix}
$$

$$
R_z = \begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}
$$

$\delta$ and $\phi$ are variables which is relative to the current time $t$.

Then do multiplication:

$$
(r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi), r_2\sin(\theta), -r_1\sin(\psi) - r_2\cos(\theta)\sin(\psi))R_xR_z\\
= (r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi), r_2\sin(\theta), -r_1\sin(\psi) - r_2\cos(\theta)\sin(\psi))
\begin{bmatrix}
1 & 0 & 0\\
0 & \cos(\delta) & -\sin(\delta)\\
0 & \sin(\delta) & \cos(\delta)
\end{bmatrix}
\begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}\\
=\left(\begin{array}{cc}
r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi)\\
r_2\sin(\theta)\cos(\delta) + r_1\sin(\psi)\sin(\delta) + r_2\cos(\theta)\sin(\psi)\sin(\delta)\\
r_2\sin(\theta)\sin(\delta) - r_1\sin(\psi)\cos(\delta) - r_2\cos(\theta)\sin(\psi)\cos(\delta)
\end{array}\right)
\begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}\\
=\left(\begin{array}{cc}
(r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi)) \cdot \cos(\phi) - (r_2\sin(\theta)\cos(\delta) + r_1\sin(\psi)\sin(\delta) + r_2\cos(\theta)\sin(\psi)\sin(\delta)) \cdot \sin(\phi)\\
(r_1\cos(\psi)+r_2\cos(\theta)\cos(\psi)) \cdot \sin(\phi) + (r_2\sin(\theta)\cos(\delta) + r_1\sin(\psi)\sin(\delta) + r_2\cos(\theta)\sin(\psi)\sin(\delta)) \cdot \cos(\phi)\\
r_2\sin(\theta)\sin(\delta) - r_1\sin(\psi)\cos(\delta) - r_2\cos(\theta)\sin(\psi)\cos(\delta)
\end{array}\right)
$$

## Illumination

First, calculate the [surface normal](https://en.wikipedia.org/wiki/Normal_(geometry)), the direction perpendicular to the surface at each point:

$$
(N_x, N_y, N_z) = (\cos(\theta), \sin(\theta), 0) R_y R_x R_z\\
= (\cos(\theta), \sin(\theta), 0)
\begin{bmatrix}
\cos(\psi) & 0 & \sin(\psi)\\
0 & 1 & 0\\
-\sin(\psi) & 0 & \cos(\psi)
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0\\
0 & \cos(\delta) & -\sin(\delta)\\
0 & \sin(\delta) & \cos(\delta)
\end{bmatrix}
\begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}\\
= (\cos(\theta)\cos(\psi), \sin(\theta), -\cos(\theta)\sin(\psi))\begin{bmatrix}
1 & 0 & 0\\
0 & \cos(\delta) & -\sin(\delta)\\
0 & \sin(\delta) & \cos(\delta)
\end{bmatrix}
\begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}\\
= \left(\begin{array}{cc}
\cos(\theta)\cos(\psi)\\
\sin(\theta)\cos(\delta) + \cos(\theta)\sin(\psi)\sin(\delta)\\
\sin(\theta)\sin(\delta) - \cos(\theta)\sin(\psi)\cos(\delta)
\end{array}\right)
\begin{bmatrix}
\cos(\phi) & -\sin(\phi) & 0\\
\sin(\phi) & \cos(\phi) & 0\\
0 & 0 & 1
\end{bmatrix}\\
= \left(\begin{array}{cc}
(\cos(\theta)\cos(\psi)) \cdot \cos(\phi) - (\sin(\theta)\cos(\delta) + \cos(\theta)\sin(\psi)\sin(\delta) \cdot \sin(\phi))\\
(\cos(\theta)\cos(\psi)) \cdot \sin(\phi)+ (\sin(\theta)\cos(\delta) + \cos(\theta)\sin(\psi)\sin(\delta)) \cdot \cos(\phi)\\
\sin(\theta)\sin(\delta) - \cos(\theta)\sin(\psi)\cos(\delta)
\end{array}\right)
$$

Then take the dot product of the surface normal with the light direction:

$$
L = (N_x, N_y, N_z) \cdot (0, 1, -1)
$$