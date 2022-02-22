// "Copyright 2021 Bubatu Claudiu Mihai"
#include "galactic_war.c"
#include "galactic_war.h"
#include <stdio.h>
#include <stdlib.h>
extern char* strdup(const char*);
#include <string.h>

#define MAX_STRING_SIZE 127

int main() {
    cdll_linked_list_t *galaxy;
    galaxy = cdll_create_galaxy(sizeof(planet_t));
    int m;
    scanf("%d\n", &m);
    for (int i = 0; i < m; i++) {
        char command[16], name[MAX_STRING_SIZE];
        char direction;
        scanf("%s", command);
        int planet_index, planet_index2, number_of_shields,
                shield_index, upp_value, shield_value, units;
        if (strcmp(command, "ADD") == 0) {
            scanf("%s", name);
            scanf("%d", &planet_index);
            scanf("%d", &number_of_shields);
            ADD(galaxy, name, planet_index, number_of_shields);
        } else if (strcmp(command, "BLH") == 0) {
            scanf("%d", &planet_index);
            BLH(galaxy, planet_index, 0);
        } else if (strcmp(command, "UPG") == 0) {
            scanf("%d", &planet_index);
            scanf("%d", &shield_index);
            scanf("%d\n", &upp_value);
            UPG(galaxy, planet_index, shield_index, upp_value);
        } else if (strcmp(command, "EXP") == 0) {
            scanf("%d", &planet_index);
            scanf("%d", &shield_value);
            EXP(galaxy, planet_index, shield_value);
        } else if (strcmp(command, "RMV") == 0) {
            scanf("%d", &planet_index);
            scanf("%d\n", &shield_index);
            RMV(galaxy, planet_index, shield_index);
        } else if (strcmp(command, "COL") == 0) {
            scanf("%d", &planet_index);
            scanf("%d", &planet_index2);
            COL(galaxy, planet_index, planet_index2);
        } else if (strcmp(command, "ROT") == 0) {
            scanf("%d", &planet_index);
            scanf(" %c", &direction);
            scanf("%d", &units);
            ROT(galaxy, planet_index, direction, units);
        } else if (strcmp(command, "SHW") == 0) {
            scanf("%d", &planet_index);
            SHW(galaxy, planet_index);
        }
    }
    FREE(&galaxy);
    return 0;
}
