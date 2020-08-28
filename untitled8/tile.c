#include "board.h"
#include "header.h"


board_point** generate_board(FILE *fpin)
{
    int end_of_row = 0;
    columns = 1;
    rows = 0;
    
    ///////////////rows and columns counting//////////////////
    while((c=fgetc(fpin))!=EOF) {
        
        if ((c == ',')&&!end_of_row) columns++;
        else if (c == '\n') {
            rows++;
            end_of_row = 1;
        }
    }
    
    ///////////////memory allocation//////////////////
    board_point **arr = (board_point **)malloc(rows * sizeof(board_point *));
    for (i=0; i < rows; i++){
        arr[i] = (board_point *)malloc(columns * sizeof(board_point));
    }
    
    ///////////////setting initial values//////////////////
    for (i = 0; i <  rows; i++) {
        for (j = 0; j < columns; j++) {
            arr[i][j].id = 0;
            arr[i][j].rotation = 0;
        }
    }
    
    ///////////////reading board from a file (board.txt)//////////////////
    fpin = fopen("board.txt", "r");
    
    for (i = 0; i < rows; i++) {
        j = 0;
        while((c = fgetc(fpin)) != '\n') {
            if (c != ',') {
                arr[i][j].id = atoi(&c);
                if ((c = fgetc(fpin)) != '_') {
                    arr[i][j].id = arr[i][j].id*10 + atoi(&c);
                };
                c = fgetc(fpin);  //to skip a '_'
                c = fgetc(fpin);
                arr[i][j].rotation = atoi(&c);
            } else {
                j++;
            }
        }
    }
    
    arr = extend_the_board(arr);
    
    fclose(fpin);
    return arr;
}

void print_board_file (FILE *fpin)
{
    board = generate_board(fpin);
    
    for (i = 0; i <  rows; i++)
    {
        if (i%2!=0)     printf("%*s", 5, "");
        for (j = 0; j < columns; j++)
        {
            
            if (board[i][j].id > 3)
                printf("%d(%d,%d)%*s", board[i][j].id, i, j, 10-intlen(i)-intlen(j)-intlen(board[i][j].id/10)-4, "");
            else
                printf("%d(%d,%d)%*s", board[i][j].id, i, j, 10-intlen(i)-intlen(j)-intlen(board[i][j].id)-3, "");
        }
        printf("\n\n");
    }
}

void board_writting (board_point **board) {
    board_file = fopen("board.txt", "w");
    
    for (i = 0; i <  rows; i++) {
        for (j = 0; j < columns; j++) {
            if (board[i][j].id != 0) {
                fprintf(board_file, "%d", board[i][j].id);
                putc('_', board_file);
                fprintf(board_file, "%d", board[i][j].rotation);
            }
            if (j != (columns - 1))putc(',', board_file);
        }
        putc('\n', board_file);
    }
    
    fclose(board_file);
}

board_point** extend_the_board(board_point** board) {
    board_point **arr;
    board_point **board_answer = board;
    
    int x = -1, y = -1, tile_by_the_boarder = 0;
    
    for (i = 0; i < columns; i++) {
        if (board[0][i].id != 0){
            x = i;
            y = 0;
            tile_by_the_boarder = 1;
            break;
        }
    }
    
    for (i = 0; i < rows; i++) {
        if (board[i][0].id != 0){
            x = 0;
            y = i;
            tile_by_the_boarder = 1;
            break;
        }
    }
    
    for (i = 0; i < columns; i++) {
        if (board[rows - 1][i].id != 0){
            x = i;
            y = rows - 1;
            tile_by_the_boarder = 1;
            break;
        }
    }
    
    for (i = 0; i < rows; i++) {
        if (board[i][columns - 1].id != 0){
            x = columns - 1;
            y = i;
            tile_by_the_boarder = 1;
            break;
        }
    }
    
    if (tile_by_the_boarder == 0) return board_answer;
    //////////////////////////////////////
    
    if (x == (columns - 1)) {
        
        for (i = 0; i < rows; i++){
            board_answer[i][columns] = *(board_point *)malloc(sizeof(board_point));
            board_answer[i][columns].id = 0;
            board_answer[i][columns].rotation = 0;
        }
        
        columns++;
    }
    
    if (x == 0) {
        columns++;
        
        arr = (board_point **)malloc(rows * sizeof(board_point *));
        for (i=0; i < rows; i++){
            arr[i] = (board_point *)malloc(columns * sizeof(board_point));
        }
        
        for (i = 0; i < rows; i++) {
            for (j = 1; j < columns; j++){
                arr[i][j].id = board_answer[i][j-1].id;
                arr[i][j].rotation = board_answer[i][j-1].rotation;
            }
        }
        board_answer = arr;
    }
    
    
    if (y == (rows - 1)) {
        board_answer[rows] = (board_point *)malloc(columns * sizeof(board_point));
        
        for (i = 0; i < columns; i++){
            board_answer[rows][i].id = 0;
            board_answer[rows][i].rotation = 0;
        }
        
        rows++;
    }
    
    if (y == 0) {
        rows++;
        
        board_point **arr_2 = (board_point **)malloc(rows * sizeof(board_point *));
        for (i=0; i < rows; i++){
            arr_2[i] = (board_point *)malloc(columns * sizeof(board_point));
        }
        
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++){
                arr_2[i][j].id = 0;
                arr_2[i][j].rotation = 0;
            }
        }
        
        for (i = 1; i < rows; i++) {
            for (j = 0; j < columns; j++){
                arr_2[i][j].id = board_answer[i-1][j].id;
                arr_2[i][j].rotation = board_answer[i-1][j].rotation;
            }
        }
        board_answer = arr_2;
    }
    
    
    return board_answer;
}
