#include <stdio.h>
#include <math.h>
#define MAXSIZE 50
// 输入增广矩阵
void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n);
// 输出结果
void output(double x[MAXSIZE], long n);

int main(int argc, char *argv[]){
  double a[MAXSIZE][MAXSIZE], b[MAXSIZE], x[MAXSIZE];//, oldx[MAXSIZE];
   // a[][]  存放系数矩阵
   // b[]    存放常数
   // x[]    存放解向量
  double epsilon, e, s, oldx;
   // epsilon 存放误差上限
   // e 存放两次迭代结果误差
   // s 存放迭代公式中 \sum_{j=1}^{n}a_{ij} x_k 的值
   long n, i, j, k, maxk;
   // n 存放原方程组的阶数
   // maxk 存放最大迭代次数
   printf("请输入原方程组的阶数: ");
   scanf("%ld" , &n);
   input(a, b, n);
   printf("请输入迭代初始向量(中间用‘ ’隔开): ");
   for(i =0; i <= n-1; i++){
     scanf("%lf", &x[i]);
   }
   printf("请输入最大迭代次数\n");
   scanf("%ld", &maxk);
   printf("请输入误差上限: ");
   scanf("%lf", &epsilon);

   // 循环1次 G-S 迭代
   for(k=1; k <= maxk; k++){
     e = 0;
     for(i=0; i<= n-1; i++){
       oldx = x[i];
       s = 0;
       for(j=0; j <= n-1; j++){
         if(j!=i){
           s += a[i][j] * x[j];
         }
       }
       x[i] = (b[i] - s)/a[i][i];
       // 重新计算精度
       if(e < fabs(oldx - x[i])){
         e = fabs(oldx - x[i]);
       }
     }
     
     // 满足精度要求，退出循环
     if( e< epsilon){
       break;
     }
   }
   if( k <= maxk){
     output(x, n);
   }else{
     printf("迭代次数已经超过上限\n");
   }
 
   return 0;
}


void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n){
 long i, j;
 printf("请输入原方程的增广矩阵(每一行用' '隔开)\n");
 for(i=0; i <= n-1; i++){
   for(j=0; j<= n-1; j++){
     scanf("%lf", &a[i][j]);
   }
   scanf("%lf", &b[i]);
 }
}

void output(double x[MAXSIZE], long n){
 long i;
 printf("原方程组的解为: \n");
 for(i = 0; i <= n-1; i++){
   printf("%lf\n", x[i]);
 }
}
