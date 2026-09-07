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

