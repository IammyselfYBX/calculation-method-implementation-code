/*
 * 编写程序，对给定的 n 个插值节点 (x1,y1),(x2,y2),⋯,(xn,yn) 进行三次样条插值，
 * 并对于给定的 m 个待求节点 x1,x2,⋯,xm 计算其三次样条插值函数值 y1,y2,⋯,ym 。
 * 其中，边界条件取自然边界条件 S′′(x1)=S′′(xn)=0。
 * 由于不能预先知道插值节点个数和待求节点的个数，请使用malloc函数申请诸数组，并在使用完毕后使用free函数释放。
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *spline(double *x, double *y, int n, double *xs, int m) {
    double *a = (double *) malloc(sizeof(double) * (n+1));
    double *b = (double *) malloc(sizeof(double) * (n+1));
    double *c = (double *) malloc(sizeof(double) * (n+1));
    double *d = (double *) malloc(sizeof(double) * (n+1));
    double *h = (double *) malloc(sizeof(double) * (n+1));
    double *alpha = (double *) malloc(sizeof(double) * (n+1));
    double *l = (double *) malloc(sizeof(double) * (n+1));
    double *mu = (double *) malloc(sizeof(double) * (n+1));
    double *z = (double *) malloc(sizeof(double) * (n+1));
    double *ys = (double *) malloc(sizeof(double) * m);
    for (int i = 1; i <= n; i++) {
        h[i] = x[i] - x[i-1];
        alpha[i] = 3.0 / h[i] * (y[i] - y[i-1]) - 3.0 / h[i-1] * (y[i-1] - y[i-2]);
    }
    l[1] = 1.0;
    mu[1] = 0.0;
    z[1] = 0.0;
    for (int i = 2; i <= n-1; i++) {
        l[i] = 2.0 * (x[i+1] - x[i-1]) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }
    l[n] = 1.0;
    z[n] = 0.0;
    c[n] = 0.0;
    for (int j = n-1; j >= 1; j--) {
        c[j] = z[j] - mu[j] * c[j+1];
        b[j] = (y[j+1] - y[j]) / h[j] - h[j] * (c[j+1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j+1] - c[j]) / (3.0 * h[j]);
        a[j] = y[j];
    }
    for (int i = 0; i < m; i++) {
        int k = 1;
        while (xs[i] > x[k]) {
            k++;
        }
        double t = (xs[i] - x[k-1]) / h[k];
        ys[i] = a[k] + b[k] * t + c[k] * t * t + d[k] * t * t * t;
    }
    free(a);
    free(b);
    free(c);
    free(d);
    free(h);
    free(alpha);
    free(l);
    free(mu);
    free(z);
    return ys;
}

int main() {
    int n, m;
    printf("请输入插值节点个数：");
    scanf("%d", &n);
    double *x = (double *) malloc(sizeof(double) * (n+1));
    double *y = (double *) malloc(sizeof(double) * (n+1));
    printf("请输入插值节点：\n");
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    
    printf("请输入待求节点个数：");
    scanf("%d", &m);
    double *xs = (double *) malloc(sizeof(double) * m);
    printf("请输入待求节点：\n");
    for (int i = 0; i < m; i++) {
        scanf("%lf", &xs[i]);
    }
    double *ys = spline(x, y, n, xs, m);
    printf("插值函数值为：\n");
    for (int i = 0; i < m; i++) {
        printf("f(%f) = %f\n", xs[i], ys[i]);
    }
    free(x);
    free(y);
    free(xs);
    free(ys);
    return 0;
}