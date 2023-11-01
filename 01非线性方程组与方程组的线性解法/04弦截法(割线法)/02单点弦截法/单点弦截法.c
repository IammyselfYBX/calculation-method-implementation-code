#include <stdio.h>
#include <math.h>

double f(double x);

int main(int argc, char *argv[])
{
    double a, b, epsilon, x0, fa, fb;
    long i, maxi;
    printf("请输入x的精度要求:");
    scanf("%lf", &epsilon);
    printf("请输入有根区间的不动边界点:");
    scanf("%lf", &a);
    fa = f(a);
    printf("请输入有根区间的另一侧不动边界点:");
    scanf("%lf", &b);
    fb = f(b);
    printf("请输入最大迭代次数:");
    scanf("%lf", &maxi);

    for (i = 0; i <maxi; i++) {
      x0 = b;
      b = b - fb * (b-a)/(fb - fa);
      fb = f(b);
      if(0 == fb) break;
      if(fabs(b - x0) <= epsilon) break;
    }
    if(i < maxi){
      printf("方程f(x)=0的根 x= %lf", b);
    }else{
      printf("迭代次数已经超过上限");
    }

    return 0;
}

double f(double x)
{
  return ;
}