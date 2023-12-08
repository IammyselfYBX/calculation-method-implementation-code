/* 
 * 三次样条插值(自然边界条件 Natural Cubic Spline)
 * 参考Numerical Analysis(9th) RIchard L.Burden 第149页伪代码
*/
#include <stdio.h>

int main() {
    /** Step 0 
     *  输入程序运行所需的初始值
     * */
    long n, i, j;
    printf("请输入区间个数: ");
    scanf("%ld", &n);
    n++;
    double x[n], a[n], h[n-1], A[n-1], l[n], u[n], z[n], c[n], b[n-1], d[n-1];
    // x[] 存放插值节点坐标
    // a[] 存放插值节点对应的函数值
    // h[] 存放分割成小区间后的区间长度
    // A[]
    // l[]
    // u[]
    // z[]
    // c[]
    // b[]
    // d[]
    for (i = 0; i < n; i++) {
        printf("输入插值节点是值x_%ld: ", i);
        scanf("%lf", &x[i]);
    }
    // 输入x_i 对应的 函数值 f(x_i)
    for (i = 0; i < n; i++) {
        printf("请输入节点x_%ld的函数值f(x_%ld)", i, i);
        scanf("%lf", &a[i]);
    }

    /** Step 1 
     *  初始化 h[i]
     * */
    for (i = 0; i < n ; i++) {
        h[i] = x[i + 1] - x[i];
    }

    /** Step 2 
     * 计算 α_i = \frac{3}{h_i}(a_{i+1} - a_{i}) - \frac{3}{h_{i-1}}(a_{i} - a_{i-1}) 
    */
    for (i = 1; i <n ; i++){
        A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];
    }

    // 从第3步到第6步的部分都是解决3对角矩阵
    /** Step 3 */
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    /** Step 4 */
    for (i = 1; i <= n - 1; i++) {
        l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i-1] * z[i-1]) / l[i];
    }

    /** Step 5 */
    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    /** Step 6 */
    for (j = n - 1; j >= 0; j--) {
        c[j] = z[j] - u[j] * c[j+1];
        b[j] = (a[j+1] - a[j]) / h[j] - h[j] * (c[j+1] + 2*c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / (3*h[j]);
    }

    /** Step 7 
     * 输出结果
    */
    printf("%2s %8s %8s %8s %8s\n", "i", "ai", "bi", "ci", "di");
    for (i = 0; i < n; i++)
        printf("%2d %8.2f %8.2f %8.2f %8.2f\n", i, a[i], b[i], c[i], d[i]);
    return 0;
}
