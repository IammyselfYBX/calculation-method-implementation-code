#include <stdio.h>
#include <math.h>

struct Point{
    double x;
    double y;
};

double CentralDifference(struct Point *p, int n, double x){
    double result = 0;
    long forward_point, next_point, current_point;
    forward_point = next_point = current_point = 0;

    for(int i = 0; i <n;i++){
        if(p[forward_point].x < x){
            if(p[i].x < x && p[forward_point].x <= p[i].x){
                forward_point = i;
            }
        }else{
            if(p[i].x < x && p[forward_point].x >= p[i].x){
                forward_point = i;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (p[i].x == x) {
            current_point = i;
        }
    }

    for(int i = 0; i <n;i++){
        if(p[next_point].x > x){
            if(p[i].x > x && p[next_point].x >= p[i].x){
                next_point = i;
            }
        }else{
            if(p[i].x > x && p[next_point].x <= p[i].x){
                next_point = i;
            }
        }
    }

    printf("forward_point = %ld, current_point = %ld, next_point = %ld\n", forward_point, current_point, next_point);
    double h = p[next_point].x - p[forward_point].x;
    result = (p[next_point].y - p[forward_point].y) / h;
    return result;
}

void input(struct Point *p, int n){
    for(int i = 0; i < n; i++){
        printf("请输入第%d个插值点的x和y坐标(使用' '隔开)：", i + 1);
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
}

int main(int argc, char *argv[])
{
    printf("请输入插值点的个数：");
    long n;
    scanf("%ld", &n);
    struct Point p[n];
    input(p, n);
    printf("请输入待求的差商的x坐标：");
    double x;
    scanf("%lf", &x);
    printf("插值点处的差商为：%lf\n", CentralDifference(p, n, x));

    return 0;
}
