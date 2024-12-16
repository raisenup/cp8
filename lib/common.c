#include <stdio.h>
#include "common.h"

#include <stdlib.h>

Complex divide_complex(const Complex a, const Complex b) {
    Complex result = {0,0};
    const double denominator = b.real * b.real + b.imag * b.imag;
    result.real = (a.real * b.real + a.imag * b.imag) / denominator;
    result.imag = (a.imag * b.real - a.real * b.imag) / denominator;
    return result;
}

void print_complex(const Complex a, const ushort precision) {
    printf("%.*g %+.*e*i\n", precision,  a.real, precision, a.imag);
}

void calculate_circuit_1(Complex *num, Complex *denom, Complex *z, const double omega, const double r, const double l, const double c) {
    num->real = l/c;
    num->imag = -r/(omega*c);
    denom->real = r;
    denom->imag = omega*l-1.0/(omega*c);
    *z = divide_complex(*num, *denom);
}

void calculate_circuit_2(Complex *num, Complex *denom, Complex *z, const double omega, const double r, const double l, const double c) {
    num->real = l/c;
    num->imag = r/(omega*c);
    denom->real = r;
    denom->imag = omega*l-1.0/(omega*c);
    *z = divide_complex(*num, *denom);
}

void calculate_circuit_3(Complex *num, Complex *denom, Complex *z, const double omega, const double r1, const double r2, const double l, const double c) {
    num->real = r1*r2;
    num->imag = r1*(omega*l-1.0/(omega*c));
    denom->real = r1+r2;
    denom->imag = omega*l-1.0/(omega*c);
    *z = divide_complex(*num, *denom);
}

void calculate_circuit_4(Complex *num, Complex *denom, Complex *z, const double omega, const double r1, const double r2, const double l, const double c) {
    num->real = r1*r2+l/c;
    num->imag = omega*l*r1-r2/(omega*c);
    denom->real = r1+r2;
    denom->imag = omega*l-1.0/(omega*c);
    *z = divide_complex(*num, *denom);
}
