#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"

#define MAX_NAME_SZ 256 

fighters* Add(char *player, fighters* array, int f_or_i) {
    char *t;
    int i = 0;
    int val, j;
    for ( j = 0; array[j].name != NULL;j++);
    fighters* newarray = realloc(array, (j + 2) * sizeof(fighters) +1 );
    // Lajitellaan annettu hahmo käyttämällä strtok_r käskyä//
    while ((t = __strtok_r(player, " ", &player))) {
        if (i == 1) {
            newarray[j].name = calloc(strlen(t) + 1, sizeof(char));
            strcpy(newarray[j].name, t);
            newarray[j].name[strlen(t)] = '\0';
        }
        else if (i == 2) {
            //atoi käsky muuttaa str muodossa olevan numeron int muotoon//
            val = atoi(t); //jos t on jokin muu kuin numero char muodossa, tällöin val:in arvo on 0//
            if (strcmp(t, "0") != 0) { //tässä tarkistetaan onko annettu arvo oikeasti 0 vai väärin annettu stringi//
                if (val == 0) {
                    printf("Error has occured. The value you had inputed was not an integer\n");
                    printf("Please try again\n");
                    free(newarray[j].name);
                    newarray[j].name = NULL;
                    return newarray;
            }
            }
            newarray[j].HP = val;
        }
        else if (i == 3) {
            newarray[j].weapon = calloc(strlen(t) + 1, sizeof(char));
            strcpy(newarray[j].weapon, t);
            newarray[j].weapon[strlen(t)] = '\0';
        }
        else if (i == 4) {
            val = atoi(t);
            t[strlen(t) - 1] = 0;
            if (strcmp(t, "0") != 0) {
                if (val == 0) {
                    printf("Error has occured. The value you had inputed was not an integer\n");
                    printf("Please try again\n");
                    free(newarray[j].name);
                    free(newarray[j].weapon);
                    newarray[j].name = NULL;
                    return newarray;
                
            }
            }
            newarray[j].ATK = val;
        }
        //koska pelaajan antama syöte on muodoltaan "A Nimi HP Weapon ATK",//
        //while looppimme käy läpi vain 5 kertaa. Mutta kun ladataan "tiedosto" hahmoja, heidän muodostama rivi stringi taas sisältää EXP:n määrän.//
        //Tällöin looppi toimii yhden kerran enemmän kuin pelaajan syötteessä. Tästä syystä olen lisännyt ala kohdan//
        else if (i == 5 && f_or_i == 1) {
            val = atoi(t);
            newarray[j].EXP = val;
        }
        i++;
    }
    if (f_or_i == 0)
        newarray[j].EXP = 0;
    if (i < 5) {
        printf("Error has occuder\n");
        printf("You did not input a proper amount of correct information about a character\n");
        if (i > 1)
        free(newarray[j].name);
        if (i > 3)
        free(newarray[j].weapon);
        newarray[j].name = NULL;
        newarray = realloc(newarray, (j + 1) * sizeof(fighters) + 1 );
        return newarray;
    }
    newarray[j + 1].name = NULL; // laittamalla viimeisen listan nimeni NULL arvoksi, // 
    //jotta saamme tietää listan pituuden helposti for()-funktiolla muissa koodin kohdissa //
    printf("Character %s has been added\n", newarray[j].name);
    return newarray;
}

int EXP_compare(const void* a, const void *b) {
    const fighters *f_a = a;
    const fighters *f_b = b;
    int comparison = f_b->EXP - f_a->EXP; // vertaamme a ja b hahmojen EXP määrää //
    if (comparison == 0) {
        return strcmp(f_a->name, f_b->name); // jos EXP:t ovat samat, päätämme järjestyksen nimien mukaan //
    }
    // seuraavassa kohdassa tarkistamme a ja b taistelijoiden HP määrät//
    // jos kumpikaan tai molemmat ovat nollissa, tällöin muutamme palautuksen arvoa//
    if (f_a->HP == 0) {
        if (f_b->HP == 0) {
            return strcmp(f_a->name, f_b->name);
        }
        return 1;
    }
    if (f_b->HP == 0) {
        return -1;
    }
    return comparison;
}

void print_array(fighters *array) {
    int j;
    for (j = 0; array[j].name != NULL;j++);
    if (j < 1) {
        printf("Error\n");
        printf("There are no characters to print\n");
        return;
    }
    // lajitellaan hahmot EXP:n mukaan käyttämällä oma tehtyä EXP_compare funktiota//
    qsort(array, j, sizeof(fighters), EXP_compare);
    for (int i = 0; array[i].name != NULL; i++) {
        printf("Name: %s HP: %d Weapon: %s ATK: %d EXP %d\n", array[i].name, array[i].HP, array[i].weapon, array[i].ATK, array[i].EXP);
    }
}

void Attack(char *player, fighters* array) {
    char *t;
    int i = 0;
    int atk_damag, def_hp;
    int atk = -1;
    int def = -1;
    char *attacker; 
    char *defender;
    // Lajitellaan annettu hyökkääjä ja puollustaja käyttämällä strtok_r käskyä//
    while ((t = __strtok_r(player, " ", &player))) {
        if (i == 1) {
            attacker = t;
        }
        if (i == 2) {
            t[strlen(t) -1] = 0; //muutamme puolustajan stringin viimeistä arvoa, (joka on pelaajan syötteessä '\n')//
            defender = t; // jotta defender stringiä voidaan verratta seuraavassa kohdassa //
        }
        i++;
    }
    //etsitään annetut hahmot listastamme//
    for (int j = 0; array[j].name != NULL; j++) {
        if (strcmp(attacker, array[j].name) == 0) {
            atk = j;
            atk_damag = array[j].ATK;
            }
        if (strcmp(defender, array[j].name) == 0) {
            def = j;
            def_hp = array[j].HP;
            }

        }
    //tarkistetaan, että syötety hahmot löytyvät muististamme ja he ovat vielä elossa//
    if (atk == -1) {
        if (def == -1) {
            printf("Error has occurred\n");
            printf("The attacker and defender you have inputed, were not found in the database\n");
            return;
        }
        printf("Error has occurred\n");
        printf("The attacker you have inputed, was not found in the database\n");
        return;
    }
    if (def == -1) {
        printf("Error has occurred\n");
        printf("The defender you have inputed, was not found in the database\n");
        return;
    }
    if (def_hp == 0) {
        printf("Error has occurred\n");
        printf("%s is already dead!\n", array[def].name);
        return;
    }
    if (array[atk].HP == 0) {
        printf("Error has occurred\n");
        printf("%s is already dead!\n", array[atk].name);
        return;
    }
    if ((def_hp - atk_damag) < 0) {
        array[atk].EXP = def_hp; // annetaan hyökkäyksen vahingon määrä EXP:nä //
        array[def].HP = 0;
        }
    else {
        array[atk].EXP = atk_damag;
        array[def].HP = def_hp - atk_damag; 
        }
    printf("The attack was successful\n");
}

void Save(fighters* array, const char *filename) {
    int i;
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error!\n");
        printf("Could not open %s\n", filename);
        fclose(fp);
        return;
    }
    for (i = 0; array[i].name != NULL; i++) {
        fprintf(fp, "A %s %d %s %d %d\n", array[i].name, array[i].HP, array[i].weapon, array[i].ATK, array[i].EXP);
    } // laitamme ensimmäiseksi merkiksi A:n ja toiseksi välimerkin//
    //jotta strtok_r funktio saadaan toimiaan kunnolla, kun tiedostosta ladataan hahmojen tiedot//
    printf("Your file has been succesfully saved\n");
    fclose(fp);
}

fighters* Load(fighters* array, const char *filename) {
    int j, k;
    int i = 0;
    int f_or_i = 1;
    char c;
    char *f_file = malloc(MAX_NAME_SZ);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error!\n");
        printf("Could not open %s\n", filename);
        fclose(fp);
        return array;
    }
    for( j = 0; array[j].name != NULL; j++) {
        free(array[j].name);
        free(array[j].weapon);
    }
    free(array);
    fighters* newarray =(fighters *) malloc(sizeof(fighters));
    newarray[0].name = NULL;
    while(1) {
        c = fgetc(fp);
        if (feof(fp)) {
            free(f_file);
            fclose(fp);
            return newarray;
        }
        f_file[i] = c;
        k = i;
        i++;
        if(c == '\n') {
            f_file[k + 1] = 0;
            newarray = Add(f_file, newarray, f_or_i);
            i = 0;
            memset(f_file, 0, strlen(f_file));
        }
        
    }

}

int main(void){
    int count = 0;
    int f_or_i = 0;
    fighters* array =(fighters *) malloc(sizeof(fighters));
    array[0].name = NULL;
    printf("Hello and welcome to the Game version 1.0!\n");
    printf("What would you like to do?\n");
    char *input = calloc(MAX_NAME_SZ, sizeof(char));
    if (input == NULL) {
        free(input);
        return 1;
    }
    fgets(input, MAX_NAME_SZ, stdin);
    while(input[0] != 'Q'){
            if (input[0] == 'A') { 
                array = Add(input, array, f_or_i);
                }
            else if (input[0] == 'H'){
                Attack(input, array);
                }
            else if (input[0] == 'L'){
                print_array(array);
                }
            else if (input[0] == 'W'){
                input[strlen(input) - 1] = 0;
                const char *filename = strtok(input, " ");
                filename = strtok(NULL, " ");
                if (filename != NULL)
                Save(array, filename);
                else {
                    printf("Error!\n");
                    printf("Please input a proper filename\n");
                    }
            }
            else if (input[0] == 'O'){
                input[strlen(input) - 1] = 0;
                const char *filename = strtok(input, " ");
                filename = strtok(NULL, " "); // otetaan annetun tiedoston nimi strtok funktiolla//
                if (filename != NULL) {
                    
                array = Load(array, filename);
                for (int k = 0; array[k].name != NULL; k++)
                    count++;
                printf("%d number of characters were succesfully downloaded from %s\n", count, filename);
                }
                else {
                    printf("Error has occured\n");
                    printf("Please input a correct filename to load\n");
                }
                }
            else
            {
                printf("Error!\n");
                printf("Please input a correct command\n");
                }
        fgets(input, MAX_NAME_SZ, stdin);

    }
    printf("Shutting the Game version 1.0 down\n");
    printf("Thanks for playing\n");
    free(input);
    for( int i = 0; array[i].name != NULL; i++) {
        free(array[i].name);
        free(array[i].weapon);
    }
    free(array);
}