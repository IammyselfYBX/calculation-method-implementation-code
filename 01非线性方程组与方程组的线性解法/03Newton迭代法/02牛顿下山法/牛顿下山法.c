#include <stdio.h>
#include <math.h>

#define MAX_ITERATIONS 100 
#define TINY 1e-6 

double function(double x); 
double derivative(double x); 
void newton_iteration(double initial_guess, double accuracy, double lambda, int max_iterations);                              
void error(int cond); 

int main(int argc, char *argv[]){
    double initial_guess, accuracy, lambda, x1;
    accuracy = TINY;
    lambda = 1.0;
    int max_iterations,i ,max_downhill_iterations;
    max_iterations = MAX_ITERATIONS;
    printf("请输入初始猜测值：");
    scanf("%lf", &initial_guess);
    printf("请输入最大下山次数：");
    scanf("%d", &max_downhill_iterations);

    for (i = 0; i < max_downhill_iterations; i++)
    {
        x1 = initial_guess - lambda * function(initial_guess) / derivative(initial_guess);
        printf("initial_guess=%lf\t x1：%lf\n",initial_guess, x1);
        if(fabs(x1) <= fabs(initial_guess)) {
            newton_iteration(x1, accuracy, lambda, max_iterations);
            break;
            }else {
                lambda = lambda / 2;
        }
    }
    if(i >= max_downhill_iterations) { 
        error(1);
    }
    
    return 0;
}

double function(double x) {
    return x * x - 4; 
}

double derivative(double x) {
    return 2 * x; 
}

void newton_iteration(double initial_guess, double accuracy, double lambda, int max_iterations){
    int i=0;
    double x1;
    
    for (i = 0; i < max_iterations; i++) {
        x1 = initial_guess - lambda * function(initial_guess) / derivative(initial_guess);
        if(fabs(0 - x1) < TINY) {
            printf("已找到函数的根：%lf\n", x1);
            break;
        }
        if (fabs(x1 - initial_guess) < accuracy) {
            printf("迭代次数：%d\n", i+1);
            printf("已找到迭代后函数的值：%lf\n", x1);
            break;
        }
        initial_guess = x1;
    }
    if (i >= max_iterations) {
        error(2);
    }
}

void error(int cond) {
    switch (cond) {
        case 1:
            printf("请更换初始猜测值\n");
            break;
        case 2:
            printf("迭代次数超出给定上限\n");
            break;
        default:
            printf("未知错误\n");
            break;
    }
}


