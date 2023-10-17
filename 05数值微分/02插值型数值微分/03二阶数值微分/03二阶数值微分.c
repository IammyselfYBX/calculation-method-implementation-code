#include <stdio.h>
#include <math.h>
double f(double x)
{
    return x*x;
}

int main(int argc, char *argv[])
{
    printf("此算法利用3等距节点计算函数f(x)在某点处的二阶导数\n");
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

    printf("二阶导数值f''(xi)=%lf (i=0,1,2)\n", (f(x[0]) - 2 * f(x[1]) + f(x[2])) / (h * h));

    return 0;
}
