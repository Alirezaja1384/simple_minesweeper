#ifndef ms_utils
#define ms_utils

void clear_screen(void);

char rt_getchar(void);
char *dyn_gets(void);
char *get_valid_string(void);

bool **create_bool_matrix(int n);
int sum_bool_matrix(bool **matrix, int n);
int count_active_cells(bool **matrix, int from_i, int to_i, int from_j, int to_j);

void allocation_fault();

#endif