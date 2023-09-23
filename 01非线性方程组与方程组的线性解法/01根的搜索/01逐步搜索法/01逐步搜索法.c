#include <stdio.h>
double f(double x);  // 定义函数f(x)

int main(int argc, char *argv[])
{
  double a, b, epsilon, x, h, begin, end;
  printf("输入x的精度要求\n");
  scanf("%lf", &epsilon);
  printf("输入搜索区间的边界a, b\n");
  scanf("%lf, %lf", &a, &b);
  h = 2* epsilon;

  if (0 == f(b)) {
    x = b;
  }else {
    for (begin = a, end = a+h; begin < b; begin = end, end +=h) {
           if (end > b) {
             end = b;
           }
           if (0 == f(begin)) {
             x = begin;
             break;
           }
           if(f(begin) * f(end) < 0 ){
             x = (begin + end)/2;
             break;
           }
       }
   }

    printf("方程f(x)=0 的根 x = %lf\n", x);

    return 0;
}

double f(double x){
    return x*x;
}
