#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "utils.h"

int main(int argc, char **argv) {
    double vl = 0, vh = 1.08, tr = 0.3294, tf = 0.3294, p = 35;
    char timeunit = 'n', voltageunit = 0;
    char *prefix = "V@ @ 0";
    char *prefixrep = (char*)malloc(slen(prefix)*sizeof(char));
    int pfxc = 0;
    double t = 0, voltage = 0, edge = 0;
    // 01100
    // 00110
    // char binarySeq[] = "01100";
    char binarySeq[] = "01100,00110";
    int i = 0;
    int input_status = 1;
    input_status = verify_input(vl, vh, tr, tf, p, timeunit, voltageunit, binarySeq);

    if (input_status == 0) {
        while (binarySeq[i] != '\0') {
            if (i == 0 || binarySeq[i] == ',') {
                if (prefix != NULL) {
                    replace_symbol(prefix, prefixrep, pfxc);
                    pfxc = (pfxc + 1) % 26;
                }
                printf("%s ", prefixrep);
                printf("PWL( 0 0 ");
            }

            if (binarySeq[i] == ',') {
                i++;
                t = 0;
            }

            voltage = binarySeq[i] == '0' ? vl : vh;
            edge = binarySeq[i] == '0' ? tf : tr;
            printf("%g%c %g%c %g%c %g%c ", t + edge, timeunit, voltage, voltageunit, t + p, timeunit, voltage, voltageunit);
            t = t + p;
            i++;

            if(binarySeq[i] == ',' || binarySeq[i] == '\0')
                printf(")\n");
        }
        printf("\nPWL generated successfully\n");
    }
    free(prefixrep);
    return 0;
}

