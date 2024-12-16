#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "lib/common.h"
#include "lib/validation.h"

#define RESET       "\033[0m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"

#define NP_ERR "Error: the value is not positive.\n"

int main(void) {

    printf("This application calculates the complex impedance of a given circuit depending on the current frequency.\n");

    do {
        ushort circuit = 0;
        get_input(TYPE_USHORT, &circuit, "Choose circuit [1, 4]:\n", is_circuit_valid, "Error: circuit not in range [1, 4].\n");

        double r1 = 0, r2 = 0;
        switch (circuit) {
            case 1:
            case 2: {
                get_input(TYPE_DOUBLE, &r1, "Enter R(Ohm):\n", is_positive, NP_ERR);
            } break;
            case 3:
            case 4: {
                get_input(TYPE_DOUBLE, &r1, "Enter R1(Ohm):\n", is_positive, NP_ERR);
                get_input(TYPE_DOUBLE, &r2, "Enter R2(Ohm):\n", is_positive, NP_ERR);
            } break;
            default: {
                printf("Error: there is no such circuit.");
            } break;
        }

        double l = 0;
        get_input(TYPE_DOUBLE, &l, "Enter L(mHn):\n", is_positive, NP_ERR);

        double c = 0;
        get_input(TYPE_DOUBLE, &c, "Enter C(mcF):\n", is_positive, NP_ERR);

        double fmin = 0;
        get_input(TYPE_DOUBLE, &fmin, "Enter Fmin:\n", is_positive, NP_ERR);

        double fmax = 0;
        do {
            get_input(TYPE_DOUBLE, &fmax, "Enter Fmax:\n", is_positive, NP_ERR);
            if (fmin > fmax) {
                printf("Error: Fmin is greater than Fmax.\n");
            }
        } while (fmin > fmax);

        double step = 0;
        get_input(TYPE_DOUBLE, &step, "Enter step:\n", is_positive, NP_ERR);

        Complex numerator = {0, 0}, denominator = {0, 0}, z = {0,0};

        const double res_freq = 1.0/(2.0*M_PI*sqrt(l*c));
        printf(CYAN"Resonant frequency: %.15lf\n"RESET, res_freq);

        double f = fmin;
        int i = 0;
        do {
            const double omega = 2.0*M_PI*f;
            switch (circuit) {
                case 1: {
                    calculate_circuit_1(&numerator,&denominator,&z,omega,r1,l,c);
                } break;
                case 2: {
                    calculate_circuit_2(&numerator,&denominator,&z,omega,r1,l,c);
                } break;
                case 3: {
                    calculate_circuit_3(&numerator,&denominator,&z,omega,r1,r2,l,c);
                } break;
                case 4: {
                    calculate_circuit_4(&numerator,&denominator,&z,omega,r1,r2,l,c);
                } break;
                default: {
                    printf("Error: there is no such circuit.\n");
                } break;
            }
            printf(CYAN"  f%d=%g\t"RESET, i+1, f);
            printf(YELLOW);
            printf("Z%d=", i+1);
            print_complex(z, 15);
            printf(RESET);
            f+=step;
            i++;
        } while (f <= fmax);

        printf("Press ENTER to restart, any other key to exit.\n");
    } while (getch() == 13);


    return 0;
}
