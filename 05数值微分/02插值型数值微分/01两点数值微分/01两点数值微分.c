#include <stdio.h>

double f(double x)
{
    return x * x;
}

int main(int argc, char *argv[])
{
    double x1, x2;
    printf("此算法是用两点数值微分法求函数f(x)在某点处的导数值\n");
    printf("请输入x1的值：");
    scanf("%lf", &x1);
    printf("请输入x2的值：");
    scanf("%lf", &x2);
    double h = x2 - x1;
    printf("函数f(x)在x1处的导数值为：%lf\n", (f(x2) - f(x1)) / h);
    printf("函数f(x)在x2处的导数值为：%lf\n", (f(x2) - f(x1)) / h);

    return 0;
}
