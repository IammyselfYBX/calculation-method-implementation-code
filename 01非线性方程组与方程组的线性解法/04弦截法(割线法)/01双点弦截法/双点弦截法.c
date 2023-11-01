#include <stdio.h>
#include <math.h>

double f(double x);

int main(int argc, char *argv[])
{
      double a, b, epsilon, x0, x1, fa, fb, fx1;
      long i, maxi;
      printf("请输入x的精度要求:");
      scanf("%lf", &epsilon);
      printf("请输入最大迭代次数:");
      scanf("%lf", &maxi);
      printf("请输入有根区间的边界a, b(中间用' '隔开):");
      scanf("%lf %lf", &a, &b);

      for (i = 0; i <maxi; i++) {
        x0 = x1;
        x1 = b - fb*(b-a)/(fb - fa);
        fx1 = f(x1);
        if(0 == fx1) break;
        if(i>0 && fabs(x1-x0)<= epsilon) break;
        if (fx1 * fa <0) {
          b = x1;
          fb = fx1;
        }else{
          a = x1;
          fa = fx1;
        }
      }
      if(i < maxi){
        printf("方程f(x)=0的根 x = %lf。\n", x1);
      }else{
        printf("迭代次数已经超过上限");
      }

      return 0;
}

double f(double x)
{
  return x*x;
}