#ifndef __UTIL_H__
#define __UTIL_H__


#define MAX_INFO_LEN 30

//¥ ∑®¥ÌŒÛ
#define ILLEGALIDEN 101
#define UNRE_COG_SYMBOL 102

//”Ô“Â¥ÌŒÛ
#define UNDEF_SIM_VAR 103
#define UNDEF_ARRAY 104
#define UNDEFINE_VAR 110

#define TYPE_INT_TO_REAL_ERROR 105
#define TYPE_REAL_TO_INT_ERROR 106
#define REDEFINE_ARRAY   107
#define REDEFINE_SIM_VAR  108

//”Ô∑®¥ÌŒÛ
#define SYNTAXERROR 109


#define NON_ERROR 0
extern int line_number;
extern int error_number;
extern char errir_info[MAX_INFO_LEN];

#endif