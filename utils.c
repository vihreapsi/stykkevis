#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "utils.h"

int check_sequence(const char *seq) {
    if (seq == NULL)
        return 1;

    if (check_comma(seq) == 1)
        return 1;

    int i = 0;
    while (seq[i] != '\0') {
        if (seq[i] != '0' && seq[i] != '1' && seq[i] != ',') {
            return 1;
        }
        i++;
    }
    return 0;
}

int check_comma(const char *seq) {
    if (seq == NULL)
        return 1;

    if (seq[0] == ',')
        return 1;

    int i = 0;
    char pc = '~';
    while (seq[i] != '\0') {        
        if (seq[i] == ',' && pc == ',') {
            return 1;
        }
        pc = seq[i];
        i++;
    }

    if (pc == ',')
        return 1;

    return 0;
}

int replace_symbol(const char *str, char* strnew, int index) {
    if (str == NULL)
        return 1;

    // printf("%d - %d", slen(strnew), slen(str));
    // if (slen(strnew) < slen(str))
    //     return 2;
    
    int i = 0;
    int ii = (index % 26) + 65;
    while (str[i] != '\0') {
        strnew[i] = str[i] == '@' ? ii : str[i];
        i++;
    }
    strnew[i] = '\0';
    return 0;
}

int slen(const char *str) {
    if (str == NULL)
        return 0;

    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int has_char(const char *str, const char c) {
    if (str == NULL || c == 0)
        return 1;
    
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return 0;
        }
        i++;
    }
    return 1;
}

int verify_input(const double vl, const double vh, const double tr, const double tf, const double p, const char timeunit, const char voltageunit, const char *bseq) {
    
    int error_status = 0;
    char* units = "TGMkmunpf";

    if (vl > vh) {
        fprintf(stderr, "Parameter error: vl=%g cannot be greater than vh=%g\n", vl, vh);
        error_status = 1;
    }

    if (vl == vh) {
        fprintf(stderr, "Parameter error: vl=%g cannot be equal to vh=%g\n", vl, vh);
        error_status = 1;
    }

    if (tr == 0) {
        fprintf(stderr, "Parameter error: tr=%g cannot be null\n", tr);
        error_status = 1;
    }
    
    if (tf == 0) {
        fprintf(stderr, "Parameter error: tf=%g cannot be null\n", tf);
        error_status = 1;
    }

    if (p == 0) {
        fprintf(stderr, "Parameter error: p=%g cannot be null\n", tf);
        error_status = 1;
    }

    if (p < (tf+tr)) {
        fprintf(stderr, "Parameter error: tr and tf cannot fit into one period p. Try to  increase period p.\n");
        error_status = 1;
    }

    if (has_char(units, timeunit) != 0 && timeunit != 0) {
        fprintf(stderr, "Parameter error: invalid timeunit=%c\n", timeunit);
        error_status = 1;
    }
    
    if (has_char(units, voltageunit) != 0 && voltageunit != 0) {
        fprintf(stderr, "Parameter error: invalid voltageunit=%c\n", voltageunit);
        error_status = 1;
    }

    if (check_sequence(bseq) == 1) {
        fprintf(stderr, "Parameter error: invalid binary sequence: %s.\n", bseq);
        error_status = 1;
    }

    return error_status;
}
