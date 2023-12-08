#include <stdio.h>

void gaussQuadrature(int n, double x[], double w[]) {
    // 定义角频率
    double omega = 1.0 / (2.0 * n);
    // 初始化权重
    double w0 = 1.0, w1 = 1.0;
    // 计算主要循环
    for(int i = 1; i < n; i++) {
        // 计算当前节点的x值
        x[i] = cos((2.0 * i - 1.0) * omega);
        // 计算当前节点的权重
        w[i] = (2.0 / ((4.0 * i - 1.0) * (4.0 * i - 3.0))) * (w0 - w1);
        // 更新初始权重
        w0 = w1;
        w1 = w[i];
    }
    // 对x值进行归一化处理
    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += x[i] * x[i];
    }
    double normalize = sqrt(1.0 / (4.0 * n * sum));
    // 对x值和权重进行归一化处理
    for(int i = 0; i < n; i++) {
        x[i] *= normalize;
        w[i] *= normalize;
    }
}

int main() {
    // 指定求积公式节点数
    int n = 4;
    // 用于存储节点的x值和权重
    double x[n], w[n];
    // 调用求积函数
    gaussQuadrature(n, x, w);
    // 打印结果
    printf("Gauss型求积公式的节点x值：");
    for(int i = 0; i < n; i++) {
        printf("%f ", x[i]);
    }
    printf("\n节点x值对应的权重：");
    for(int i = 0; i < n; i++) {
        printf("%f ", w[i]);
    }
    return 0;
}