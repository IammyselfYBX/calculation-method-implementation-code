#include <stdio.h>
#define MAXSIZE 50
double f(double x, double y);

int main(int argc, char *argv[])
{
    double a, b, h, k1, k2, k3, k4, x[MAXSIZE], y[MAXSIZE];
    long i, n;
    printf("请输入求解区间a, b(请用英文, 隔开) :");
    scanf("%lf, %lf", &a, &b);
    printf("请输入步长h: ");
    scanf("%lf", &h);
    n = (long)((b-a)/h);
    x[0] = a;
    printf("请输入起点 x[0]=%lf处的纵坐标y[0]: ", x[0]);
    scanf("%lf", &y[0]);
    for (i = 0; i < n; i++) {
      x[i+1] = x[i] + h;
      k1 = f(x[i], y[i]);
      k2 = f(x[i]+h/2, y[i] + k1 * h/2);
      k3 = f(x[i]+h/2, y[i] + k2 * h/2);
      k4 = f(x[i]+h, y[i] + k3*h);
      y[i+1] = y[i] + h * (k1 + 2*k2 + 2*k3 + k4)/6;
    }
    printf("计算结果为: \n");
    for (i = 0; i <= n; i++) {
      printf("x[%ld]=%lf, y[%ld]=%lf\n", i, x[i], i, y[i]);
    }

    return 0;
}


double f(double x, double y)
{
  return y - 2*x /y;
}

