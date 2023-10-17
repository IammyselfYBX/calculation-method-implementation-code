#include <stdio.h>
#include <math.h>
double f(double x)
{
    return x * x;
}

int main(int argc, char *argv[])
{
    printf("此程序利用3等距节点计算函数f(x)在某点处的导数\n");
    double x1, x2, x3, h;
    printf("请输入3个点的x坐标(中间用' '隔开)：");
    scanf("%lf %lf %lf", &x1, &x2, &x3);
    if( fabs(x1 - x2) == fabs(x3 - x2) && 2 * fabs(x1 - x2) == fabs(x3 - x1) 
            || fabs(x2 - x3) == fabs(x1 - x3) && 2 *fabs(x2 - x3) == fabs(x2 - x1)
            || fabs(x1 - x3) == fabs(x1 - x2) && 2 *fabs(x1 - x3) == fabs(x2 - x3))
    {
        h = fabs(x2 - x1);
    }else{
        printf("输入的3个点不是等距节点，请重新输入\n");
        return 0;
    }
    printf("第1个点处的导数值为: %lf \n", ((-3)*f(x1) + 4*f(x2) + (-1)*f(x3))/(2 * h) );
    printf("第2个点处的导数值为: %lf \n", ((-1)*f(x1) + 1*f(x3))/(2 * h) );
    printf("第3个点处的导数值为: %lf \n", (f(x1) + (-4)*f(x2) + (3)*f(x3))/(2 * h) );

    return 0;
}
