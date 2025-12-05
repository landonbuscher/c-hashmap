#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 107

typedef struct map_node {
    int key;
    int value;
    struct map_node* next;
} map_node_t;

typedef struct map {
    map_node_t* map_table[MAP_SIZE];
} map_t;

int hash(int key) {
    return key % MAP_SIZE;
}

void hash_put(map_t* map, int key, int value) {
    int index = hash(key);
    map_node_t* curr = map->map_table[index];
    while (curr!=NULL) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    map_node_t* new_node = malloc(sizeof(map_node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->map_table[index];

    map->map_table[index] = new_node;
}

map_node_t* hash_get(map_t* map, int key) {
    int index = hash(key);
    map_node_t* curr = map->map_table[index];
    while (curr!=NULL) {
        if (curr->key==key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void hash_delete(map_t* map, int key) {
    int index = hash(key);
    map_node_t* curr = map->map_table[index];
    map_node_t* prev = NULL;
    while (curr!=NULL) {
        if (curr->key==key) {
            if (prev==NULL) {
                map->map_table[index] = curr->next;
            } else {
                prev->next=curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void hash_print(map_node_t* node) {
    if (node==NULL) printf("NULL\n");
    else printf("%d\n",node->value);
}

void hash_free(map_t* map) {
    for (int i=0; i<MAP_SIZE; i++) {
        map_node_t* curr = map->map_table[i];
        while (curr!=NULL) {
            map_node_t* next = curr->next;
            free(curr);
            curr=next;
        }
        map->map_table[i] = NULL;
    }
}

int main() {

    map_t map = {0};
    
    hash_put(&map, 5, 10);
    hash_put(&map, 5, 15);
    hash_put(&map, 112, 20);
    hash_put(&map, 1, 22);
    hash_put(&map, 9, 12);
    hash_print(hash_get(&map,5));
    hash_print(hash_get(&map,112));
    hash_print(hash_get(&map,1));
    hash_print(hash_get(&map,9));
    hash_delete(&map, 9);
    hash_print(hash_get(&map,9));

    hash_free(&map);

    return 0;
}