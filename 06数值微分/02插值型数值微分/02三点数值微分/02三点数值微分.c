#include <stdio.h>
#include <math.h>
double f(double x)
{
    return x * x;
}

int main(int argc, char *argv[])
{
    printf("此程序利用3等距节点计算函数f(x)在某点处的导数\n");
    double x[3], h;
    printf("请输入3个点的x坐标(中间用' '隔开)：");
    scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);
    //3个数排序
    double tmp;
    for(int i = 0; i < 3; i++)
    {
        for(int j = i; j < 3; j++)
        {
            if(x[i] > x[j])
            {
                tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
            }
        }
    }
    if(fabs(x[1]-x[0]) == fabs(x[2]-x[1]))
    {
        h = fabs(x[1]-x[0]);
    }else{
        printf("输入的3个点不是等距节点，请重新输入\n");
        return 0;
    }
    printf("第1个点处 %lf 的导数值为: %lf \n", x[0], ((-3)*f(x[0]) + 4*f(x[1]) + (-1)*f(x[2]))/(2 * h) );
    printf("第2个点处 %lf 的导数值为: %lf \n", x[1], ((-1)*f(x[0]) + 1*f(x[2]))/(2 * h) );
    printf("第3个点处 %lf 的导数值为: %lf \n", x[2], (f(x[0]) + (-4)*f(x[1]) + (3)*f(x[2]))/(2 * h) );

    return 0;
}
