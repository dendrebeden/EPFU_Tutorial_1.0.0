#include <stdlib.h>
#include "header.h"
#include "interactive_mode.h"
#include <string.h>

void interactive_mode(){
    read_tiles();
    do {
    number_of_tiles = number_of_tiles_in_file();
    tile_file = fopen("available_tiles.txt", "r");
    print_available_tiles_from_file(tile_file, number_of_tiles);
    board_file = fopen("board.txt", "r");
    print_board_file(board_file);//someone should make board looks more user friendly
    put_tile();//Denis
    fclose(tile_file);
    fclose(board_file);
     } while (number_of_tiles > 0);
}
