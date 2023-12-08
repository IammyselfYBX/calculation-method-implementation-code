#include <stdio.h>
#include <math.h>

// 定义函数类型
typedef double (*func_ptr)(double x);

// 定义求导函数
double differentiate(func_ptr func, double x, double h) {
    // 使用前进差商法求函数在x点的导数值
    return (func(x + h) - func(x)) / h;
}

// 定义求函数在闭区间[a, b]上的定积分值
double integrate(func_ptr func, double a, double b) {
    double h = 0.001;  // 隔距
    int n = (int)(b - a) / h;  // 区间分点数
    double sum = 0.0;
    double x;
    for (int i = 0; i < n; i++) {
        x = a + i * h;
        sum += func(x) * h;
    }
    return sum;
}

// 定义求解二阶常微分方程的边值问题的函数
void solve_bvp(func_ptr f, double a, double b, double y_a, double y_b) {
    double h = 0.1;  // 步长
    double x = a;  // 当前点
    double y = y_a;  // 初始条件
    double k1 = 0.0, k2 = 0.0;
    printf("%f %f\n", x, y);
    while (x < b) {
        k1 = f(x, y);  // 计算k1
        k2 = f(x + h / 2, y + h * k1 / 2);  // 计算k2
        y += h * (k1 + k2) / 2;  // 更新y
        x += h;  // 更新x
        printf("%f %f\n", x, y);
    }
}

int main() {
    // 定义函数f(x, y) = x^2 + y
    func_ptr f = ^(double x, double y) {
        return 2 * x + 1;
    };

    // 求解边值问题
    solve_bvp(f, 0, 1, 0, 0);

    return 0;
}