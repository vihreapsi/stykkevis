#ifndef UTILS_H
#define UTILS_H

int check_sequence(const char *seq);
int check_comma(const char *seq);
int replace_symbol(const char *str, char* strnew, int index);
int slen(const char *str);
int has_char(const char *str, const char c);
int verify_input(const double vl, const double vh, const double tr, const double tf, const double p, const char timeunit, const char voltageunit, const char *bseq);

#endif //UTILS_H
