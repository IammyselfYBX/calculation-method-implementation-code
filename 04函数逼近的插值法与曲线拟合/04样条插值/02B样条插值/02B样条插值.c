/*
 * 编写程序，对函数f(x)=cos(πx) 在区间 [−1,1] 做三次样条插值，边界条件取周期边界条件，对于给定的待求节点 xs 求出其插值函数值 ys 。
 * 设定等分区间为 32 个。
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 32 // 等分区间数
#define PI 3.14159265358979323846

double f(double x) {
    return cos(PI * x);
}

double spline(double x, double *a, double *b, double *c, double *d) {
    int k = (int) ((x + 1.0) * N / 2.0); // 计算所在区间
    double dx = 2.0 / N;
    double t = (x - (-1.0 + k * dx)) / dx; // 归一化
    double y = a[k] + b[k] * t + c[k] * t * t + d[k] * t * t * t; // 计算插值函数值
    return y;
}

int main() {
    double a[N+1], b[N+1], c[N+1], d[N+1];
    double h = 2.0 / N;
    double x[N+1];
    for (int i = 0; i <= N; i++) {
        x[i] = -1.0 + i * h;
        a[i] = f(x[i]);
    }
    c[0] = c[N] = 0.0; // 周期边界条件
    for (int i = 1; i < N; i++) {
        double hi = x[i] - x[i-1];
        double hi1 = x[i+1] - x[i];
        double A = hi;
        double B = hi1;
        double C = 2.0 * (hi + hi1);
        double F = 6.0 * ((a[i+1] - a[i]) / hi1 - (a[i] - a[i-1]) / hi);
        double z = (A * c[i-1] + C + B * c[i+1]) / B;
        c[i] = -A / z;
        d[i] = (F - A * d[i-1]) / z;
    }
    for (int i = N-1; i >= 0; i--) {
        c[i] = c[i] * c[i+1] + d[i];
    }
    double xs = 0.333333; // 待求节点
    double ys = spline(xs, a, b, c, d);
    printf("f(%f) = %f\n", xs, ys);
    return 0;
}