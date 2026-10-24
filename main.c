#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "utils.h"

const char* STYKKEVIS_VERSION = "0.0";

int main(int argc, char **argv) {
    // default argument values
    double vl = 0, vh = 1.2, tr = 1, tf = 1, p = 100;
    char timeunit = 0, voltageunit = 0;

    // init
    char *prefix = (char*)malloc(sizeof(char)*2), *prefixrep = NULL;
    char *binarySeq = (char*)malloc(sizeof(char)*2);
    double t = 0, voltage = 0, edge = 0;
    int i = 0, input_status = 1, pfxc = 0;

    binarySeq[0] = '?';
    binarySeq[1] = '\0';
    prefix[0] = '?';
    prefix[1] = '\0';

    // * argument parsing
    if (argc == 2) {
        if (scmp(argv[1], "-h") == 0) {
            printhelp();
            exit(EXIT_SUCCESS);
        }
        if (scmp(argv[1], "-v") == 0) {
            printf("%s\n", STYKKEVIS_VERSION);
            exit(EXIT_SUCCESS);
        }
    }

    if (argc > 2 && argc % 2 == 0) {
        printf("Incorrect number of arguments\n");
        exit(EXIT_FAILURE);
    }

    for (int i=1 ; i<argc-1 ; i+=2) {
        char *ep = NULL;
        
        if (scmp(argv[i], "-vl") == 0) {
            vl = strtod(argv[i+1], &ep);
        }

        if (scmp(argv[i], "-vh") == 0) {
            vh = strtod(argv[i+1], &ep);
        }

        if (scmp(argv[i], "-tf") == 0) {
            tf = strtod(argv[i+1], &ep);
        }

        if (scmp(argv[i], "-tr") == 0) {
            tr = strtod(argv[i+1], &ep);
        }

        if (scmp(argv[i], "-p") == 0) {
            p = strtod(argv[i+1], &ep);
        }
        
        if (scmp(ep, argv[i+1]) == 0) {
            printf("Incorrect number in %s=%s\n", argv[i], argv[i+1]);
            exit(EXIT_FAILURE);
        }

        if (scmp(argv[i], "-vu") == 0) {
            voltageunit = argv[i+1][0];
        }

        if (scmp(argv[i], "-tu") == 0) {
            timeunit = argv[i+1][0];
        }

        if (scmp(argv[i], "-pf") == 0 && slen(argv[i+1]) > 0) {
            prefix = (char*)realloc(prefix, (slen(argv[i+1])+1)*sizeof(char));
            prefixrep = (char*)malloc((slen(argv[i+1])+1)*sizeof(char));
            scpy(prefix, argv[i+1]);
        }

        if (scmp(argv[i], "-bs") == 0 && slen(argv[i+1]) > 0) {
            binarySeq = (char*)realloc(binarySeq, (slen(argv[i+1])+1)*sizeof(char));
            if (binarySeq == NULL) {
                printf("Error allocating memory.\n");
                exit(EXIT_FAILURE);
            }
            scpy(binarySeq, argv[i+1]);
        }
    }

    // verify supplied values
    input_status = verify_input(vl, vh, tr, tf, p, timeunit, voltageunit, binarySeq);

    if (input_status != 0) {
        free(prefix);
        free(prefixrep);
        free(binarySeq);
        exit(EXIT_FAILURE);
    }

    // generate strings
    while (binarySeq[i] != '\0') {
        if (i == 0 || binarySeq[i] == ',') {
            if(replace_symbol(prefix, prefixrep, pfxc) == 0) {
                pfxc = (pfxc + 1) % 26;
                printf("%s ", prefixrep);
            }
            printf("PWL( 0%c 0%c ", timeunit, voltageunit);
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

    free(prefix);
    free(prefixrep);
    free(binarySeq);
    exit(EXIT_SUCCESS);
}

