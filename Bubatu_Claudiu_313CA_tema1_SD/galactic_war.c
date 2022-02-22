// "Copyright 2021 Bubatu Claudiu Mihai"
#include "galactic_war.h"
#include <stdio.h>
#include <stdlib.h>
extern char* strdup(const char*);
#include <string.h>

// aceasta functie creeaza galaxia si ne-o returneaza
cdll_linked_list_t *cdll_create_galaxy(unsigned int data) {
    cdll_linked_list_t *galaxy = calloc(1, sizeof(cdll_linked_list_t));
    galaxy->head = NULL;
    galaxy->tail = NULL;
    galaxy->size = 0;
    galaxy->data_size = data;
    return galaxy;
}
// aceasta functie creeaza lista de scuturi a unei planete
cdll_linked_list_t* planet_create(int number_of_shields) {
    cdll_linked_list_t *planet = cdll_create_galaxy(sizeof(int));
    planet->size = number_of_shields;
    int i = 0;
    while (i != number_of_shields) {
        cdll_node_t *aux = malloc(sizeof(cdll_node_t));
        aux->data = malloc(sizeof(int));
        *(int *)aux->data = 1;
        // cand lista de scuturi e goala
        if (planet->head == NULL) {
            planet->head = aux;
            planet->tail = aux;
            aux->prev = planet->tail;
            aux->next = planet->head;
        } else {
            // adaug cate un scut la finalul listei de scuturi
            aux->prev = planet->tail;
            planet->tail->next = aux;
            aux->next = planet->head;
            planet->head->prev = aux;
            planet->tail = aux;
        }
        i++;
    }
    return planet;
}

void ADD(cdll_linked_list_t *galaxy, char *name,
        int planet_index, int number_of_shields) {
    if (planet_index > galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else if (galaxy->size == 0) {
        // vrem sa adaugam prima planeta in galaxie
        cdll_node_t *aux = calloc(1, sizeof(cdll_node_t));
        aux->data = calloc(1, sizeof(planet_t));
        ((planet_t *)(aux->data))->name = strdup(name);
        ((planet_t *)(aux->data))->kills = 0;
        ((planet_t *)(aux->data))->number_of_shields = number_of_shields;
        ((planet_t *)(aux->data))->shields = planet_create(number_of_shields);
        galaxy->head = aux;
        galaxy->tail = aux;
        aux->next = galaxy->head;
        aux->prev = galaxy->tail;
        galaxy->size++;
        printf("The planet %s has joined the galaxy.\n",
                ((planet_t *)aux->data)->name);
    } else if (planet_index == 0) {
        // vrem sa adaugam pe prima pozitie a galaxiei o planeta
        cdll_node_t *planet = galaxy->head;
        cdll_node_t *aux = calloc(1, sizeof(cdll_node_t));
        aux->data = calloc(1, sizeof(planet_t));
        ((planet_t *)(aux->data))->name = strdup(name);
        ((planet_t *)(aux->data))->kills = 0;
        ((planet_t *)(aux->data))->number_of_shields = number_of_shields;
        ((planet_t *)(aux->data))->shields = planet_create(number_of_shields);
        planet->prev->next = aux;
        aux->prev = galaxy->head->prev;
        aux->next = planet;
        planet->prev = aux;
        galaxy->head = aux;
        galaxy->size++;
        printf("The planet %s has joined the galaxy.\n",
                ((planet_t *)aux->data)->name);
    } else if (planet_index == galaxy->size) {
        // vrem sa adaugam o planeta pe ultima pozitie a galaxiei
        cdll_node_t *aux = calloc(1, sizeof(cdll_node_t));
        aux->data = calloc(1, sizeof(planet_t));
        ((planet_t *)(aux->data))->name = strdup(name);
        ((planet_t *)(aux->data))->kills = 0;
        ((planet_t *)(aux->data))->number_of_shields = number_of_shields;
        ((planet_t *)(aux->data))->shields = planet_create(number_of_shields);
        cdll_node_t *planet = galaxy->head;
        planet->prev->next = aux;
        aux->prev = planet->prev;
        aux->next = galaxy->head;
        galaxy->head->prev = aux;
        galaxy->size++;
        printf("The planet %s has joined the galaxy.\n",
                ((planet_t *)aux->data)->name);
    } else {
        // vrem sa adaugam o planeta pe o pozitie arbitrara in galaxie
        cdll_node_t *planet = galaxy->head;
        cdll_node_t *aux = calloc(1, sizeof(cdll_node_t));
        aux->data = calloc(1, sizeof(planet_t));
        ((planet_t *)(aux->data))->name = strdup(name);
        ((planet_t *)(aux->data))->kills = 0;
        ((planet_t *)(aux->data))->number_of_shields = number_of_shields;
        ((planet_t *)(aux->data))->shields = planet_create(number_of_shields);
        int i = 0;
        while (i != planet_index-1) {
            planet = planet->next;
            i++;
        }
        planet->next->prev = aux;
        aux->next = planet->next;
        planet->next = aux;
        aux->prev = planet;
        galaxy->size++;
        printf("The planet %s has joined the galaxy.\n",
                 ((planet_t *)aux->data)->name);
    }
}

cdll_node_t* cdll_remove_nth_node(cdll_linked_list_t* list, int n)
{
    int i = 0;
    cdll_node_t *node = list->head;
    cdll_node_t *aux;
    if (n >= list->size-1) {
        if (list->size == 0) {
            // lista este goala, nu avem ce sa stergem
            exit(-1);
        } else {
            // ne dorim sa stergem ultimul nod
            aux = node->prev;
            list->head->prev = list->head->prev->prev;
            list->head->prev->next = list->head;
            list->size--;
        }
    } else if (n == 0) {
        // ne dorim sa eliminam nodul de pe prima pozitie
        aux = list->head;
        list->head = list->head->next;
        list->head->prev = node->prev;
        node->prev->next = list->head;
        list->size--;
    } else {
        // ne dorim sa stergem un nod de pe o pozitie arbitrara
        while (i != (int)n) {
            node = node->next;
            i++;
        }
        aux = node;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        list->size--;
    }
    return aux;
}

void SHW(cdll_linked_list_t *galaxy, int planet_index) {
    if (galaxy->size == 0) {
        printf("Planet out of bounds!\n");
        return;
    } else if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        int i = 0;
        cdll_node_t *planet = galaxy->head;
        while (i != planet_index) {
            planet = planet->next;
            i++;
        }
        printf("NAME: %s\n", ((planet_t *)planet->data)->name);
        if (galaxy->size == 2) {
            printf("CLOSEST: %s\n", ((planet_t *)planet->next->data)->name);
        } else if (galaxy->size == 1) {
            printf("CLOSEST: none\n");
        } else {
            printf("CLOSEST: %s and %s\n",
                    ((planet_t *)(planet->prev)->data)->name,
                    ((planet_t *)(planet->next)->data)->name);
        }
        printf("SHIELDS: ");
        int j = 0;
        while (j != ((planet_t *)planet->data)->number_of_shields) {
            printf("%d ",
            *(int *)(((planet_t *)planet->data)->shields->head->data));
            ((planet_t *)planet->data)->shields->head =
                ((planet_t *)planet->data)->shields->head->next;
            j++;
        }
        printf("\n");
        printf("KILLED: %d\n", ((planet_t *)planet->data)->kills);
    }
}

void BLH(cdll_linked_list_t *galaxy, int planet_index, int show) {
    if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        // consideram un nod in care salvam planeta stearsa din galaxie
        cdll_node_t *remove = cdll_remove_nth_node(galaxy, planet_index);
        if (show == 0) {
            // mesaj de eroare pentru functia BLH
            printf("The planet %s has been eaten by the vortex.\n",
                    ((planet_t *)remove->data)->name);
        } else if (show == 1) {
            // mesaj de eroare pentru functia COL
            printf("The planet %s has imploded.\n",
                    ((planet_t *)remove->data)->name);
        }
        // facem cast la nodul scos din galaxie
        // pentru a elibera scuturile si continutul acestora
        while (((planet_t *)remove->data)->shields->size != 0) {
            // consideram un nod in care salvam scutul sters din planeta
            cdll_node_t *shield =
                cdll_remove_nth_node(((planet_t *)remove->data)->shields, 0);
            free(shield->data);
            free(shield);
        }
        // eliberez lista de scuturi, numele, continutul planetei si planeta
        free(((planet_t *)remove->data)->shields);
        free(((planet_t *)remove->data)->name);
        free(remove->data);
        free(remove);
    }
}

void UPG(cdll_linked_list_t *galaxy, int planet_index,
                int shield_index, int upp_value) {
    cdll_node_t *planet = galaxy->head;
    cdll_node_t *shield;
    int i = 0;
    if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        // parcurg galaxia pana la planeta dorita
        while (i != planet_index) {
            planet = planet->next;
            i++;
        }
        int j = 0;
        // fac cast nodului planet la o structura de tip planeta
        if (shield_index >= ((planet_t *)planet->data)->shields->size) {
            printf("Shield out of bounds!\n");
            return;
        } else {
            shield = ((planet_t *)(planet->data))->shields->head;
            // parcurg lista de scuturi pana la pozitia dorita
            while (j != shield_index) {
                shield = shield->next;
                j++;
            }
            // upgradez scutul de pe pozitia dorita cu upp_value
            *(int *)shield->data = *(int *)shield->data + upp_value;
        }
    }
}
void EXP(cdll_linked_list_t *galaxy, int planet_index, int shield_value) {
    if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        int i = 0;
        cdll_node_t *planet = galaxy->head;
        // declar scutul pe care vreau sa il adaug in lista de scuturi
        // precum si continutul acestuia (data)
        cdll_node_t *aux = malloc(sizeof(cdll_node_t));
        aux->data = malloc(sizeof(int));
        *(int *)aux->data = shield_value;
        // parcurg galaxia pana la planeta dorita
        while (i != planet_index) {
            planet = planet->next;
            i++;
        }
        cdll_node_t *node = ((planet_t *)planet->data)->shields->head;
        // parcurg scuturile pana la final
        while (node->next != ((planet_t *)planet->data)->shields->head) {
            node = node->next;
        }
        // cand am ajuns pe ultima pozitie, mai leg un scut la sfarsitul listei
        node->next = aux;
        ((planet_t *)planet->data)->shields->head->prev = aux;
        aux->prev = node;
        aux->next = ((planet_t *)planet->data)->shields->head;
        ((planet_t *)planet->data)->number_of_shields++;
        ((planet_t *)planet->data)->shields->size++;
    }
}

void RMV(cdll_linked_list_t *galaxy, int planet_index, int shield_index) {
    cdll_node_t *planet = galaxy->head;
    int i = 0;
    if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        // parcurg galaxia pana la planeta dorita
        while (i != planet_index) {
            planet = planet->next;
            i++;
        }
        if (shield_index >= ((planet_t *)planet->data)->shields->size) {
            printf("Shield out of bounds!\n");
            return;
        } else if (((planet_t *)planet->data)->number_of_shields == 4) {
            printf("A planet cannot have less than 4 shields!\n");
            return;
        } else {
            // folosesc functia cdll_remove_nth_node pentru a scoate un scut
            // din lista de scuturi si il salvez
            // intr-un nod remove pentru a-l elibera
            cdll_node_t *remove =
                cdll_remove_nth_node(((planet_t *)planet->data)->shields,
                    shield_index);
            ((planet_t *)planet->data)->number_of_shields--;
            free(remove->data);
            free(remove);
        }
    }
}

void COL(cdll_linked_list_t *galaxy, int planet_index1, int planet_index2) {
    if (planet_index1 >= galaxy->size || planet_index2 >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        int i = 0, j = 0, k = 0;
        // plec cu planetele din capul galaxiei
        cdll_node_t *planet1 = galaxy->head;
        cdll_node_t *planet2 = galaxy->head;
        // parcurg galaxia pana ajung la index-ul primei planete
        while (i != planet_index1) {
            planet1 = planet1->next;
            i++;
        }
        // parcurg galaxia pana ajung la index-ul celeilalte planete
        i = 0;
        while (i != planet_index2) {
            planet2 = planet2->next;
            i++;
        }
        // fac cast fiecarui nod planeta la o structura de tip planeta
        // si iau head-ul fiecarei liste
        // de scuturi si il pun intr-un nod
        cdll_node_t *node1 = ((planet_t *)planet1->data)->shields->head;
        cdll_node_t *node2 = ((planet_t *)planet2->data)->shields->head;
        // parcurg lista de scuturi a primei planete pana la pozitia dorita
        while (j !=
                ((int)(((planet_t *)planet1->data)->number_of_shields) / 4)) {
            node1 = node1->next;
            j++;
        }
        // parcurg lista de scuturi a celeilalte planete pana la pozitia dorita
        while (k !=
                3 *
                (((int)((planet_t *)planet2->data)->number_of_shields) / 4)) {
            node2 = node2->next;
            k++;
        }
        // scad valorile scuturilor de la pozitiile determinate anterior
        (*(int *)(node1->data))--;
        (*(int *)(node2->data))--;
        // folosesc functia BLH pentru a le elimina din galaxie
        // in cazul in care o planeta are un scut < 0.
        // In cazul in care o planeta distruge alta planeta
        // ii cresc numarul de kill-uri.
        if ((*(int *)(node1->data)) < 0 && (*(int *)(node2->data)) < 0) {
            BLH(galaxy, planet_index1, 1);
            BLH(galaxy, planet_index2-1, 1);
        } else if ((*(int *)(node1->data)) < 0) {
            BLH(galaxy, planet_index1, 1);
            ((planet_t *)planet2->data)->kills++;
        } else if ((*(int *)(node2->data)) < 0) {
            BLH(galaxy, planet_index2, 1);
            ((planet_t *)planet1->data)->kills++;
        }
    }
}

void ROT(cdll_linked_list_t *galaxy, int planet_index,
                char direction, int units) {
    if (planet_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        if (direction != 'c' && direction != 't') {
            printf("Not a valid direction!\n");
            return;
        } else {
            int i = 0, j = 0;
            cdll_node_t *planet = galaxy->head;
            // parcurg galaxia pana la pozitia planetei dorite
            while (i != planet_index) {
                planet = planet->next;
                i++;
            }
            cdll_node_t *node = ((planet_t *)planet->data)->shields->head;
            // cazul in care shield-urile se muta in sens trigonometric
            if (direction == 't') {
                // r-ul este folosit pentru a ne misca eficient
                // in lista de scuturi
                int r = units % ((planet_t *)planet->data)->number_of_shields;
                while (j != r) {
                    node = node->next;
                    j++;
                }
                // ma mut cu head-ul cu r unitati
                ((planet_t *)planet->data)->shields->head = node;
            } else if (direction == 'c') {
                // cazul in care shield-urile
                // se muta in sensul acelor de ceasornic
                // r-ul este folosit pentru a ne misca
                // eficient in lista de scuturi
                int r = units % ((planet_t *)planet->data)->number_of_shields;
                while (j != r) {
                    node = node->prev;
                    j++;
                }
                // ma mut cu head-ul cu r unitati
                ((planet_t *)planet->data)->shields->head = node;
            }
        }
    }
}

void FREE(cdll_linked_list_t **galaxy) {
    while ((*galaxy)->size != 0) {
        // sterg cate o planeta pana cand galaxia nu mai are planete
        cdll_node_t *planet = cdll_remove_nth_node((*galaxy), 0);
        while (((planet_t *)planet->data)->shields->size != 0) {
            // sterg cate un scut pana cand lista de scuturi devine goala
            cdll_node_t *shield =
                cdll_remove_nth_node(
                    ((planet_t *)planet->data)->shields, 0);
            // eliberez continutul unui scut si scutul
            free(shield->data);
            free(shield);
        }
        // eliberez lista de scuturi, numele, continutul unei planete si planeta
        free(((planet_t *)planet->data)->shields);
        free(((planet_t *)planet->data)->name);
        free(planet->data);
        free(planet);
    }
    // eliberez galaxia
    free((*galaxy));
}
