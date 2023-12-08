#include <stdio.h>
#include <math.h>

// 定义存储插值点的结构体
struct Point{
    double x;
    double y;
};

// 求出两个点之间的斜率
double getK(struct Point p1, struct Point p2){
    return (p2.y - p1.y) / (p2.x - p1.x);
}

// 分段线性插值
double interpolate(double x, struct Point points[], int numPoints)
{
    double result = 0;

    // 遍历所有的点
    for (int i = 0; i < numPoints - 1; i++)
    {
        // 判断x是否在两个点之间
        if (x >= points[i].x && x <= points[i + 1].x)
        {
            // 求出两个点之间的斜率
            double k = getK(points[i], points[i + 1]);
            // 求出y值
            result = k * (x - points[i].x) + points[i].y;
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    long numPoints;
    printf("请输入需要插值的点的个数：");
    scanf("%ld", &numPoints);
    struct Point points[numPoints];
    for (int i = 0; i < numPoints; i++)
    {
        printf("请输入第%d个点的x值：", i + 1);
        scanf("%lf", &points[i].x);
        printf("请输入第%d个点的y值：", i + 1);
        scanf("%lf", &points[i].y);
    }
    printf("请输入需要插值的x值：");
    double x;
    scanf("%lf", &x);
    double result = interpolate(x, points, numPoints);
    printf("插值结果为：%lf\n", result);

    return 0;
}
