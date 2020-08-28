#ifndef board_h
#define board_h
#define num_of_types_tiles 14

#include <stdio.h>

typedef struct {
    int id;
    int rotation;
} board_point;



void board_writting (board_point **board);
void print_board_file (FILE *fpin);
board_point **board;
board_point** generate_board(FILE *fpin);
board_point** extend_the_board(board_point** board);

#endif /* board_h */
