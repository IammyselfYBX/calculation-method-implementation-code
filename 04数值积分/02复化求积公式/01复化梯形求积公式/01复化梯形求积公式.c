#include <stdio.h>
#define MAXSIZE 50

void input(double f[MAXSIZE], double a, double h, long n);

int main(int argc, char *argv[])
{
    double a, b, h, f[MAXSIZE], integral;
    long n, i;
    printf("请输入积分区间边界a, b: ");
    scanf("%lf, %lf", &a, &b);
    printf("请输入求积节点的个数: ");
    scanf("%ld", &n);
    h = (b-a)/(n-1);
    input(f, a, h, n);
    integral = (f[0] + f[n-1])/2;
    for (i =1; i < n-1; i++) {
      integral += f[i];
    }
    integral *= h;
    printf("积分值=%lf\n", integral);
  
    return 0;
}


void input(double f[MAXSIZE], double a, double h, long n)
{
  long i;
  printf("请输入求积节点的纵坐标:\n");
  for (i = 0; i <= n-1; i++) {
    printf("x[%ld]=%lf, f[%ld]=", i, a+i*h, i);
    scanf("%lf", &f[i]);
  }

}
