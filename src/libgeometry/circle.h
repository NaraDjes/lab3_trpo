#define ASCII_BRACKET_LEFT 40
#define ASCII_BRACKET_RIGHT 41
#define ZERO 48
#define NINE 57
#define M_PI 3.14159265358979323846
typedef struct point {
    double x;
    double y;
} point;

typedef struct circle {
    point center;
    double radius;
} circle;
int left_bracket(char* str);
int right_bracket(char* str);
void str_to_lower(char* str);
int is_arguments(char* str);
int is_end(char* str);
int error_ending_symbol(char* str);
int is_object(char* str);
int print_errors(char* str, int countObj);
void init_array(char* mass);
void calc_per_and_area(char* str);