#include <stdlib.h>
#include "header.h"
#include "rotation.h"
#include <string.h>

void rotation(int tile_id,int tile_rotation, struct tiles *answer)
    {
        int tmp;

        answer->tileid = tile[tile_id].tileid;
        strcpy(answer->name,tile[tile_id].name );
        answer->isTemple = tile[tile_id].isTemple;
        answer->crossRoads = tile[tile_id].crossRoads;
        answer->bonus = tile[tile_id].bonus;
        answer->top = tile[tile_id].top;
        answer->right = tile[tile_id].right;
        answer->left = tile[tile_id].left;
        answer->bottom = tile[tile_id].bottom;
            
        for (int i = 1; i < tile_rotation; i++) {
            tmp = answer->top;
            answer->top = answer->left;
            answer->left = answer->bottom;
            answer->bottom = answer->right;
            answer->right = tmp;
        }
}
