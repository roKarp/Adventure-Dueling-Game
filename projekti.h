#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char *name;
    int HP;
    char *weapon;
    int ATK;
    int EXP;
} fighters;


fighters* Add(char *player, fighters* array, int f_or_i);
void Attack(char *player, fighters* array);
int EXP_compare(const void* a, const void *b);
void print_array(fighters *array);
void Save(fighters *array, const char *filename);
fighters* Load(fighters *array, const char *filename);