#include <stdio.h>
#define MAXSIZE 50
void input(double f[MAXSIZE], double a, double h, long n);

int main(int argc, char *argv[])
{
    double a, b, h, f[MAXSIZE], integral, s, s1, s2;
    long n, i;
    printf("请输入积分区间边界a, b(请用, 分割): ");
    scanf("%lf, %lf", &a, &b);
    printf("请输入求积节点的个数: ");
    scanf("%ld", &n);
    h = (b-a)/(n-1);
    input(f, a, h, n);
    s = s1 = s2 = 0;
    for(i =4; i < n-1; i += 4){
      s += f[i];
    }
    for (i = 0; i < n-1; i += 4) {
        s1 += f[i+1] + f[i+3];
        s2 += f[i+2];
    }
    integral = 7 * (f[0] + f[n-1]) + 14 * s + 32 * s1 + 12 * s2;
    integral *= 1 * h/45;
    printf("积分值 = %lf\n", integral);

    return 0;
}


void input(double f[MAXSIZE], double a, double h, long n)
{
  long i;
  printf("请输入求积节点的纵坐标: ");
  for (i = 0; i <= n-1; i++) {
    printf("x[%ld]=%lf, f[%ld]=", i, a+i*h, i);
    scanf("%lf", &f[i]);
  }
}
