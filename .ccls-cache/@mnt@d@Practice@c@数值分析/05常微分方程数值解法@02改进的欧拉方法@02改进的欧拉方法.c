#include <stdio.h>
#include <math.h>
#define MAXSIZE 50
double f(double x, double y);

int main(int argc, char *argv[])
{
    double a, b, h, x[MAXSIZE], y[MAXSIZE];
    long i, n;
    printf("请输入求解区间a, b(中间用英文, 隔开): ");
    scanf("%lf, %lf", &a, &b);
    printf("请输入步长h: ");
    scanf("%lf", &h);
    n = (long)((b-a)/h);
    x[0] = a;
    printf("请输入起点x[0]=%lf处的纵坐标y[0]: ", x[0]);
    scanf("%lf", &y[0]);
    for (i = 0; i < n; i++) {
        x[i+1] = x[i] + h;
        // 预测
        y[i+1] = y[i] + h*f(x[i], y[i]);
        // 校正
        y[i+1] = y[i] + h*(f(x[i], y[i]) + f(x[i+1], y[i+1]))/2;
    }
    printf("计算结果为: \n");
    for (i = 0; i <= n; i++) {
      printf("x[%ld]=%lf, y[%ld]=%lf\n", i,x[i], i, y[i]);
    }
    
    return 0;
}


double f(double x, double y)
{
  // 函数内容
  return y - (2 * x)/(y);
}

