#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

double apply_operator(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}

double evaluate_expression(char *expr) {
    double operands[MAX_EXPR_LENGTH];
    char operators[MAX_EXPR_LENGTH];
    int op_top = -1, opd_top = -1;
    int i = 0;

    while (expr[i] != '\0') {
        if (isdigit(expr[i]) || (i == 0 && expr[i] == '-')) {
            double num = atof(&expr[i]);
            operands[++opd_top] = num;
            while (isdigit(expr[i]) || expr[i] == '.') {
                i++;
            }
            i--;
        } else if (is_operator(expr[i])) {
            while (op_top >= 0 && precedence(operators[op_top]) >= precedence(expr[i])) {
                double b = operands[opd_top--];
                double a = operands[opd_top--];
                char op = operators[op_top--];
                double res = apply_operator(a, b, op);
                operands[++opd_top] = res;
            }
            operators[++op_top] = expr[i];
        } else if (expr[i] == '(') {
            operators[++op_top] = expr[i];
        } else if (expr[i] == ')') {
            while (op_top >= 0 && operators[op_top] != '(') {
                double b = operands[opd_top--];
                double a = operands[opd_top--];
                char op = operators[op_top--];
                double res = apply_operator(a, b, op);
                operands[++opd_top] = res;
            }
            op_top--;
        }
        i++;
    }

    while (op_top >= 0) {
        double b = operands[opd_top--];
        double a = operands[opd_top--];
        char op = operators[op_top--];
        double res = apply_operator(a, b, op);
        operands[++opd_top] = res;
    }

    return operands[opd_top];
}

int main() {
    char expr[MAX_EXPR_LENGTH];
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_EXPR_LENGTH, stdin);
    double result = evaluate_expression(expr);
    printf("Result: %lf\n", result);
    return 0;
}
