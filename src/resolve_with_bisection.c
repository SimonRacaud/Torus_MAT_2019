/*
** EPITECH PROJECT, 2020
** 105torus_2019
** File description:
** Resolve the equation with the bisection method
*/

#include "torus.h"

static void update_values(double *x0, double *x1, double xm, config_t *config)
{
    double result = 0;

    result += get_equation_result(config, *x0);
    result *= get_equation_result(config, xm);
    if (result < 0)
        *x1 = xm;
    else
        *x0 = xm;
}

void resolve_with_bisection(config_t *config)
{
    double x0 = 0;
    double x1 = 1;
    double xm = 0;
    double a;

    check_first_values(config);
    for (int i = 0; i < 100; i++) {
        xm = ABS(x1 + x0) / 2;
        printf("x = ");
        printf("%.*f\n", get_nb_decimal(xm, config->precision), xm);
        if (xm == 0) {
            write(2, "Division by zero\n", 17);
            exit(84);
        }
        a = ABS(get_equation_result(config, xm));
        if (a < pow(10, -config->precision)) {
            if (xm < 0 || xm > 1) {
                write(2, "No solution found\n", 18);
                exit(84);
            }
            exit(0);
        }
        update_values(&x0, &x1, xm, config);
    }
    write(2, "No solution found\n", 18);
    exit(84);
}
