#include <stdio.h>
#include <math.h>
double picard(double x); // 定义函数f

int main(int argc, char *argv[])
{
  double epsilon, x0, x1, y1, z1;
  long i, maxi;
  printf("请输入x的精度要求:");
  scanf("%lf", &epsilon);
  printf("请输入迭代初值:");
  scanf("%lf", &x1);
  printf("请输入最大迭代次数:");
  scanf("%lf", &maxi);

  for (i = 0; i <maxi; i++) {
    x0 = x1;
    y1 = picard(x1);
    z1 = picard(y1);
    x1 = x0 - (y1 - x0) * (y1 - x0)/(z1 - 2*y1 + x0);
    if (fabs(x1 - x0) <= epsilon) {
      break;
    }
  }
  if(i < maxi){
    printf("方程f(x)=0的根x = %lf", x1);
  }else{
    printf("迭代次数已经超过上限");
  }


  return 0;
}

double picard(double x)
{
  return ;
}