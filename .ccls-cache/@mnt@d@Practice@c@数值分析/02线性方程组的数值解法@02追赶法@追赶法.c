#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[], double b[], double c[], double d[], long n);
void output(double x[], long n);

int main(int argc, char *argv[])
{
    double a[MAXSIZE], b[MAXSIZE], c[MAXSIZE], d[MAXSIZE], x[MAXSIZE];
    // b[] 是主对角线的元素
    // a[] 是主对角线左下的一排元素
    // c[] 是主对角线右上的一排元素
    // d[] 是存放方程组等号右侧的常数向量
    // x[] 是存放方程组的解
    long n, i;
    // n 是原方程的阶数
    // i 是第i行
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, b, c, d, n);
    // 循环一次消去1行
    for (i = 1; i < n; i++) {
        // 因为最后本来 主对角线 左下的部分a[]都被消为0，为了节省空间
        // a[] 就是存放每行所需乘的算子(行系数)
        a[i] /= -b[i-1];       // 得到每行消元所需乘的值
        b[i] += c[i-1] * a[i]; // 利用行系数消元主对角线
        d[i] += d[i-1] * a[i]; // 利用行系数消元常数向量
    }

    /* 回代过程
     * 先从最后一行(n-1行) 开始，从下往上进行带入求解
     */
    x[n-1] = d[n-1] / b[n-1]; // 得到第n-1行的解
    // 从下往上一次计算求解
    for(i = n-2; i>= 0; i--){
      x[i] = (d[i] - c[i] * x[i+1])/b[i];
    }
    output(x, n);
    printf("\n");
      
    return 0;
}

void input(double a[], double b[], double c[], double d[], long n)
{
  long i;
  printf("请输入原方程组的增广矩阵:\n");
  /* 入录方程的增广矩阵需要特殊处理第1行和最后1行
   * 因为第1行没有 a[] 的元素
   * 最后1行没有 c[] 的元素
   *------------------------------------------------
   * 矩阵存储结构如下
   * b1    c1                    | d1
   * a2    b2     c2             | d2
   * ... ... ...                 | ...
   *     a_{n-1} b_{n-1} c_{n-1} | d_{n-1}
   *             a_{n}   b_{n}   | d_{n}
   */
  // 第1行需要单独处理
  printf("b1, c1, d1: ");
  scanf("%lf, %lf, %lf", &b[0], &c[0], &d[0]);
  // 接下来开始正常进行循环
  for (i = 1; i < n-1; i++) {
    printf("a%ld, b%ld, c%ld, d%ld: ", i, i, i, i);
    scanf("%lf, %lf, %lf, %lf", &a[i-1], &b[i-1], &c[i-1], &d[i-1]);
  }
  // 最后1行也需要单独处理
  printf("a%ld, b%ld, d%ld: ", n, n, n);
  scanf("%lf, %lf, %lf", &a[n-1], &b[n-1], &d[n-1]);
}

void output(double x[], long n)
{
  long i;
  printf("方程组的解为:\n");
  for (i = 1; i <= n; i++) {
    printf(" %lf", x[i-1]);
  }

}
