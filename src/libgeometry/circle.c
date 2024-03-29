#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"

int left_bracket(char* str)
{
    int j = str[6];
    if (j == ASCII_BRACKET_RIGHT) {
        return 1;
    }
    return 0;
}

int right_bracket(char* str)
{
    int j = ASCII_BRACKET_LEFT;
    for (int i = 9; i < ASCII_BRACKET_LEFT; i++) {
        if (str[i] == j)
            return i + 1;
    }
    return 0;
}

void str_to_lower(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

int is_arguments(char* str)
{
    int ret = 0;
    int count = 0;
    int j = 0;
    int z = 0;
    for (int i = 7; str[i] != ',' && i < strlen(str); i++) {
        if ((str[i] != '.' && str[i] != ' ')
            && !(str[i] >= ZERO && str[i] <= NINE)) {
            printf("Error at column %d: expected '<double>'\n", i + 1);
            j = i + 1;
            ret++;
            return 1;
        }
        if (str[i] >= ZERO && str[i] <= NINE && str[i + 1] == ' ') {
            count++;
            j = i + 1;
        }
        if (str[i] == '.' && str[i + 1] == ')') {
            count += 2;
            j = i + 1;
        }
    }
    if (count + 1 != 2) {
        printf("Error at column %d: expected '<double>'\n", j);
        ret++;
        return ret;
    }
    int index = 0;
    for (int i = 0; i != strlen(str); i++) {
        if (str[i] == ',') {
            index = i + 1;
            i = strlen(str) - 1;
        }
    }
    for (; str[index] != ')' && index < strlen(str); index++) {
        if ((str[index] != '.' && str[index] != ' ')
            && !(str[index] >= ZERO && str[index] <= NINE)) {
            printf("Error at column %d: expected radius '<double>'\n",
                   index + 1);
            z = index + 1;
            ret++;
            return 1;
        }
        if (str[index] >= ZERO && str[index] <= NINE && str[index + 1] == ' ') {
            count++;
            z = index + 1;
        }
        if (str[index] == '.' && str[index + 1] == ' ') {
            count += 2;
            z = index + 1;
        }
    }
    if (count != 1) {
        printf("Error at column %d: expected radius '<double>'\n", z);
        ret++;
    }
    return ret;
}

int is_end(char* str)
{
    int ret = 1;
    int firstBracket = 0;
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            firstBracket = i;
            break;
        }
    }
    if (firstBracket == endingSymbol)
        ret = 0;
    return ret;
}

int error_ending_symbol(char* str)
{
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
        }
    }
    return endingSymbol;
}

int is_object(char* str)
{
    int ret = 1;
    char rec[100];
    for (int i = 0; i < 6; i++) {
        rec[i] = str[i];
    }
    char figure[] = "circle";
    if (strcmp(rec, figure) == 0) {
        ret = 0;
    }
    return ret;
}

int print_errors(char* str, int countObj)
{
    int z = right_bracket(str);
    int s = error_ending_symbol(str) - 1;
    int count = 0;
    printf("Position %d:\n", countObj);
    if (is_object(str)) {
        count++;
        printf("Error at column 0: expected 'circle'\n");
    } else if (left_bracket(str)) {
        count++;
        printf("Error at column 7: expected '('\n");
    } else if (right_bracket(str)) {
        count++;
        printf("Error at column %d: expected ')'\n", z);
    } else if (is_arguments(str)) {
        count++;
        return count;
    } else if (is_end(str)) {
        count++;
        printf("Error at column %d: unexpected token\n", s);
    } else {
        if (countObj == 1) {
            printf("%s", str);
        }
        if (countObj > 1) {
            printf("%s\n", str);
        }
    }
    return count;
}

void init_array(char* mass)
{
    for (int i = 0; i < 10; i++) {
        mass[i] = 0;
    }
}
void calc_per_and_area(char* str)
{
    char radius[10];
    for (int i = 7; i != strlen(str); i++) {
        if (str[i] == ',') {
            int j = 0;
            i = i + 1;
            for (int z = i; str[z] != ')'; z++) {
                radius[j] = str[z];
                j++;
            }
        }
    }
    double rad = atof(radius);
    double per = 2 * M_PI * rad;
    double plosh = M_PI * rad * rad;
    printf(" perimetr = %.4lf\n", per);
    printf(" area = %.4lf\n", plosh);
    init_array(radius);
}