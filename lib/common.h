#pragma once

typedef unsigned short ushort;

typedef struct Complex {
    double real;
    double imag;
} Complex;

Complex divide_complex(const Complex a, const Complex b);

void print_complex(const Complex a, const ushort precision);

void calculate_circuit_1(Complex *num, Complex *denom, Complex *z, const double omega, const double r, const double l, const double c);

void calculate_circuit_2(Complex *num, Complex *denom, Complex *z, const double omega, const double r, const double l, const double c);

void calculate_circuit_3(Complex *num, Complex *denom, Complex *z, const double omega, const double r1, const double r2, const double l, const double c);

void calculate_circuit_4(Complex *num, Complex *denom, Complex *z, const double omega, const double r1, const double r2, const double l, const double c);
