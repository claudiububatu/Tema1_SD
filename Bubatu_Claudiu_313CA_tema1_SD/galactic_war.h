// "Copyright 2021 Bubatu Claudiu Mihai"
#ifndef GALACTIC_WAR_H_
#define GALACTIC_WAR_H_

typedef struct cdll_node_t cdll_node_t;
struct cdll_node_t
{
    void *data;
    cdll_node_t *next;
    cdll_node_t *prev;
};

typedef struct cdll_linked_list_t cdll_linked_list_t;
struct cdll_linked_list_t
{
    cdll_node_t *head;
    cdll_node_t *tail;
    int data_size;
    int size;
};

typedef struct planet_t planet_t;
struct planet_t
{
    int kills;
    char *name;
    int number_of_shields;
    cdll_linked_list_t *shields;
};

cdll_linked_list_t *cdll_create_galaxy(unsigned int data);

cdll_linked_list_t* planet_create(int number_of_shields);

void ADD(cdll_linked_list_t *galaxy, char *name,
        int planet_index, int number_of_shields);

cdll_node_t* cdll_remove_nth_node(cdll_linked_list_t* list, int n);

void SHW(cdll_linked_list_t *galaxy, int planet_index);

void BLH(cdll_linked_list_t *galaxy, int planet_index, int show);

void UPG(cdll_linked_list_t *galaxy, int planet_index,
                int shield_index, int upp_value);

void EXP(cdll_linked_list_t *galaxy, int planet_index, int shield_value);

void RMV(cdll_linked_list_t *galaxy, int planet_index, int shield_index);

void COL(cdll_linked_list_t *galaxy, int planet_index1, int planet_index2);

void ROT(cdll_linked_list_t *galaxy, int planet_index,
                char direction, int units);

void FREE(cdll_linked_list_t **galaxy);

#endif  // GALACTIC_WAR_H_
