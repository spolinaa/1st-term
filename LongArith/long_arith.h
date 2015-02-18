/* Header file for Long Arithmetics
by Sokolova Polina */

typedef struct intlist {
    int v;
    struct intlist *next;
} intlist;
typedef struct longNum {
    int sign;
    int size;
    intlist *digits;
} longNum;

void longNum_operations(int sign_1, int size_1, intlist *list_1, int sign_2, int size_2, intlist *list_2, int *sign_res, int *size_res, intlist **list_res, int command); // Operations with numbers (+/-)
void longNum_add(int *sign_1, int *size_1, intlist **list_1, int *sign_2, int *size_2, intlist **list_2, int *sign_res, int *size_res, intlist **list_res, int *command); // Make a new SLL
void longNum_state(intlist *list_1, int sign_1);
void longNum_addition(int size_1, intlist *list_1, int size_2, intlist *list_2, int *size_res, intlist **list_res);// Addition of 2 numbers, writes in result
void longNum_substraction(int sign_1, int size_1, intlist *list_1, int sign_2, int size_2, intlist *list_2, int *sign_res, int *size_res, intlist **list_res, int command);// Substraction of 2 numbers, writes in result
void longNum_multiplication(intlist *list_1, intlist *list_2, int *size_res, intlist **list_res); // Multiplication of 2 numbers
void intlist_free(intlist **list_1); // Delete all information and quit
int longNum_max(int size_1, int size_2); // Choose maximum size
int longNum_min(int size_1, int size_2); // Choose minimum size
void longNum_sumformult(intlist *list_1, int *size_2, intlist **list_2); // Sum of 2 elements, writes in the second one
void intlist_swap(intlist **list_1); // Elements in result SLL change their places
void intlist_addzero(intlist **list_1, int j); // Add nulls in the head of SLL
void longNum_division(int size_1, intlist *list_1, int size_2, intlist *list_2, int *size_res, intlist **list_res); // Division of 2 numbers
int longNum_comparison(int size_1, intlist **list_1, int size_2, intlist **list_2); // Comparison between numbers of the same length
void diffordiv(int *size_1, intlist **list_1, intlist *list_2); // Substaction in division, writes in the first one
void intlist_delzero (intlist **list_1, int *size_1, int com);
void intlist_copy(intlist *list, intlist **list_clone);
