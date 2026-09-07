#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "utils.h"

int main(int argc, char **argv) {
    double vl = 0, vh = 1.2, tr = 18.6, tf = 18.6, p = 1000;
    char *timeunit = "p", *voltageunit = "";
    char *prefix = "V@ @ 0";
    char *prefixrep = (char*)malloc(slen(prefix)*sizeof(char));
    int pfxc = 0;
    double t = 0, voltage = 0, edge = 0;
    // 01100
    // 00110
    // char binarySeq[] = "01100";
    char binarySeq[] = "01100,00110";
    int i = 0;


    if ((vl == vh) || p == 0 || tr == 0 || tf == 0) {
        fprintf(stderr, "Cannot generate PWL string with those inputs\n");
    }

    if (binarySeq != NULL) {
        if (check_sequence(binarySeq) == 1) {
            fprintf(stderr, "Error: invalid binary sequence: %s\n", binarySeq);
            return 1;
        }
        while (binarySeq[i] != '\0') {
            if (i == 0 || binarySeq[i] == ',') {
                if (prefix != "") {
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
            printf("%g%s %g%s %g%s %g%s ", t + edge, timeunit, voltage, voltageunit, t + p, timeunit, voltage, voltageunit);
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

