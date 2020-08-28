#ifndef HEADER_H_
#define HEADER_H_

#define num_of_types_tiles 14
#include <stdio.h>
struct tiles{
//int tileid;
char name[100];
int isTemple;
int crossRoads;
int bonus;
int top;
int right;
int left;
int bottom;
};

typedef struct {
    int id;
    int rotation;
} board_point;

FILE *tile_file, *board_file, *ftilesdef;
struct tiles tile[num_of_types_tiles];
int columns, rows, i, j,z ,number_of_tiles;
int howmany_of_each_tile[num_of_types_tiles+1];
char c;
int intlen(int x);

#endif
