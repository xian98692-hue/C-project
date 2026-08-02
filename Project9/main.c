#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_TERMS 10

/* 多项式项: coef * x^exp */
typedef struct {
    double coef;
    int exp;
} Term;

/* 清空输入缓冲区 */
static void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* 读取多项式, 返回项数, 失败返回 -1 */
static int readPoly(Term poly[]) {
    int n;
    printf("请输入多项式项数(1-%d): ", MAX_TERMS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_TERMS) {
        printf("项数无效\n");
        clearInput();
        return -1;
    }
    for (int i = 0; i < n; i++) {
        printf("第%d项 系数和指数(空格分隔): ", i + 1);
        if (scanf("%lf %d", &poly[i].coef, &poly[i].exp) != 2) {
            printf("输入无效\n");
            clearInput();
            return -1;
        }
    }
    return n;
}

/* 多项式在 x 处的值 */
static double polyValue(const Term poly[], int n, double x) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += poly[i].coef * pow(x, poly[i].exp);
    }
    return sum;
}

/* 求导: 多项式在 x 处的导数值 */
static double derivative(const Term poly[], int n, double x) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        if (poly[i].exp != 0) {
            sum += poly[i].coef * poly[i].exp * pow(x, poly[i].exp - 1);
        }
    }
    return sum;
}

/* 积分: 多项式在 [a, b] 上的定积分(解析法) */
static double integral(const Term poly[], int n, double a, double b) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        if (poly[i].exp == -1) {
            /* ∫ coef/x dx = coef * ln|x| */
            result += poly[i].coef * (log(fabs(b)) - log(fabs(a)));
        } else {
            result += poly[i].coef / (poly[i].exp + 1) *
                      (pow(b, poly[i].exp + 1) - pow(a, poly[i].exp + 1));
        }
    }
    return result;
}

static void showMenu(void) {
    printf("\n===== 计算器 =====\n");
    printf("1. 加法\n");
    printf("2. 减法\n");
    printf("3. 乘法\n");
    printf("4. 除法\n");
    printf("5. 根号\n");
    printf("6. 求导\n");
    printf("7. 积分\n");
    printf("8. 百分比\n");
    printf("0. 退出\n");
    printf("==================\n");
    printf("请选择: ");
}

int main(void) {
    int choice;
    double a, b, x, lo, hi;
    Term poly[MAX_TERMS];
    int n;

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("输入无效\n");
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                printf("请输入两个数(空格分隔): ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("结果: %.4f\n", a + b);
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 2:
                printf("请输入两个数(空格分隔): ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("结果: %.4f\n", a - b);
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 3:
                printf("请输入两个数(空格分隔): ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("结果: %.4f\n", a * b);
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 4:
                printf("请输入两个数(空格分隔): ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    if (b == 0.0) {
                        printf("错误: 除数为0\n");
                    } else {
                        printf("结果: %.4f\n", a / b);
                    }
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 5:
                printf("请输入一个数: ");
                if (scanf("%lf", &a) == 1) {
                    if (a < 0.0) {
                        printf("错误: 负数不能开根号\n");
                    } else {
                        printf("结果: %.4f\n", sqrt(a));
                    }
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 6:
                n = readPoly(poly);
                if (n > 0) {
                    printf("请输入求导点 x: ");
                    if (scanf("%lf", &x) == 1) {
                        printf("导数值: %.4f\n", derivative(poly, n, x));
                    } else { printf("输入无效\n"); clearInput(); }
                }
                break;
            case 7:
                n = readPoly(poly);
                if (n > 0) {
                    printf("请输入积分下限和上限(空格分隔): ");
                    if (scanf("%lf %lf", &lo, &hi) == 2) {
                        printf("积分值: %.4f\n", integral(poly, n, lo, hi));
                    } else { printf("输入无效\n"); clearInput(); }
                }
                break;
            case 8:
                printf("请输入数值和百分比(空格分隔): ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("结果: %.4f\n", a * b / 100.0);
                } else { printf("输入无效\n"); clearInput(); }
                break;
            case 0:
                printf("已退出\n");
                return 0;
            default:
                printf("无效选择\n");
                break;
        }
    }
}
