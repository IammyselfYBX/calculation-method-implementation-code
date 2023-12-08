/**
 * 这段代码实现了Gauss-Legendre求积公式。首先，它定义了一个名为gauss_legendre的函数，该函数接受两个参数（表示积分的下限和上限），并返回积分的值。然后，它使用一个循环来计算积分的值，其中每一项是权重乘以函数在相应点的值。最后，它将计算得到的积分值输出。注意，这里使用的是n=5的Gauss-Legendre权重和节点，你可以根据需要修改这些值。
*/

#include <stdio.h>
#include <math.h>

// Gauss-Legendre weights and abscissas for n=5
double w[5] = {0.2369268850, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268850};
double x[5] = {-0.9061798459, -0.5384693101, 0.0, 0.5384693101, 0.9061798459};

// Function to integrate
double f(double x) {
    return x*x; // Change this to your function
}

// Gauss-Legendre Quadrature
double gauss_legendre(double a, double b) {
    double sum = 0.0;
    for (int i = 0; i < 5; i++) {
        sum += w[i] * f((b-a)/2.0 * x[i] + (b+a)/2.0);
    }
    return sum * (b-a)/2.0;
}

int main() {
    double a, b;
    printf("Enter the lower limit of integration: ");
    scanf("%lf", &a);
    printf("Enter the upper limit of integration: ");
    scanf("%lf", &b);
    double result = gauss_legendre(a, b);
    printf("The integral is: %f\n", result);
    return 0;
}