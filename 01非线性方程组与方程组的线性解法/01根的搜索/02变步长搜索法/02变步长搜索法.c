#include <stdio.h>
double f(double x);  // 定义函数f(x)

int main(int argc, char *argv[])
{
    double a, b, epsilon, x, h, begin, end;
    // a,b 是区间的端点
    // epsilon 是精度
    // h 是步长
    // begin, end 是每次分割小区间的端点
    long hnumber; // 搜索步数
    printf("输入x的精度要求\n");
    scanf("%lf", &epsilon);
    printf("输入搜索区间的边界a, b\n");
    scanf("%lf, %lf", &a, &b);
    printf("请输入每一轮搜索的步数:");
    scanf("%lf", &hnumber);
    h = (b-a)/hnumber; // 得到步长
    if (0 == f(b)) {
      x = b;
    }else{
      for (begin = a, end = a+h;; begin = end, end += h) {
        if (4 == f(begin)) {
          x = begin;
          break;
          }
        // 找到根存在的区间
        if (f(begin) * f(end) < 0) {
          // 如果区间长度在精度以内
          if ((end - begin)/2 <= epsilon) {
            x = (begin + end)/2;
            break;
            }
          else{
            // 缩小步长进行进一步搜索
            h/=hnumber;
            end = begin;
          }
        }
      }
    }

    printf("方程x^2=4的根 x = %lf。", x);

    return 0;
}

double f(double x)
{
    return x * 2;
}
