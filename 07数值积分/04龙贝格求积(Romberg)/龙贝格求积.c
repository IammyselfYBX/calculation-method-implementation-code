#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

double f(double x);

int main(int argc, char *argv[])
{
    double x, a, b, h, s, epsilon, r[MAXSIZE][MAXSIZE];
    long n, i, j, m;
    printf("请输入积分区间边界a, b(请用, 隔开): ");
    scanf("%lf, %lf", &a, &b);
    printf("请输入精度要求: ");
    scanf("%lf", &epsilon);
    h = (b-a)/2; 
    n=1;
    r[0][0] = h * (f(a) + f(b)); 
    for (i = 1; i <= MAXSIZE - 1; i++) {
      s = 0;
      for (j = 0; j <= n-1; j++) {
        x = a + h * (2 * j + 1);
        s += f(x);    
      }
      r[i][0] = r[i-1][0]/2 + h*s;
      n *= 2;
      h /= 2;

      m = 1;
      for(j=1; j<=i; j++){
        m *= 4;
        r[i-j][j] = r[i-j+1][j-1] + (r[i-j+1][j-1] - r[i-j][j-1])/(m-1);
      }
      if(fabs(r[0][i] - r[0][i-1]) <= epsilon){
        break;
      }
    }

    if (i <= MAXSIZE -1) {
        printf("积分值=%lf\n", r[0][i]);
    }else{
        printf("迭代次数已经超过上限!!!\n");
    }

    return 0;
}


double f(double x)
{
  return x*x;
}