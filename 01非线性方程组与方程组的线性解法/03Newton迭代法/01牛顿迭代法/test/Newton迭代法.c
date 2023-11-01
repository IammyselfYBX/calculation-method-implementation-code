/*
 * 编写程序，用牛顿迭代法求方程 ax^3 + b x^2 + c x + d = 0 在 x 附近的一个实根。
 * 其中，系数a、b、c、d由主函数输入，求出的根由主函数输出。
 * */

#include<stdio.h>
#include<math.h>

double iterate(double x, double a, double b, double c, double d);		//迭代函数
double f(double x, double a, double b, double c, double d);		//定义原函数
double df(double x, double a, double b, double c); //定义导函数

int main(){
	double x, a, b, c, d; // 代求方程的系数 
  // x 存放的是迭代初值
  // a,b,c,d 分别存储的是方程前的系数
  printf("请输入x, a, b, c, d (中间用空格 隔开):");
	scanf("%lf %lf %lf %lf %lf", &x, &a, &b, &c, &d);
  //printf("x0 = %lf, a = %lf, b=%lf, c=%lf, d=%lf\n", x, a, b, c, d);

  // 输出计算结果
	printf("方程f(x)=0的根x = %lf\n", iterate(x, a, b, c, d));
  //printf("%lf", iterate(x, a, b, c, d));

  return 0;
}

double iterate(double x, double a, double b, double c, double d)
{
  double epsilon, x0,  fx0, dfx0;
  //epsilon 是精度
  //x0是暂存的部分
  //printf("请输入x的精度要求:");
  //scanf("%lf", &epsilon);
  epsilon = 0.000001;
  //printf("epsilon = %lf\n", epsilon);
  for (int i = 0; i<= 100; i++) {
      x0 = x;
      //printf("x0 = %lf, a = %lf, b=%lf, c=%lf, d=%lf\n", x0, a, b, c, d);
      fx0 = f(x0, a, b, c, d);
      dfx0 = df(x0, a, b, c);
      x = x0 - fx0/dfx0;
      //printf("x = %lf, x0 = %lf\n", x, x0);
      //printf("fx0 = %lf, dfx0 = %lf\n", fx0, dfx0);
      //printf("|x-x0| = %lf\n", fabs(x-x0));
      //printf("------------------------\n");
      if(fabs(x - x0) <= epsilon){
          break;
      }
  }
  return x;
}

double f(double x, double a, double b, double c, double d){
    // 利用秦九韶算法，减少乘法运算，加快时间
    return x * (x*(a*x + b) + c) + d;
}

double df(double x, double a, double b, double c) //定义导函数
{
    return x * (3 * a* x + 2 * b) + c;
}
