#include <cstdint>
#include <cstdlib>

uint64_t get_rand_64(){
    uint16_t r1 = rand();
    uint16_t r2 = rand();
    uint16_t r3 = rand();
    uint16_t r4 = rand();
    uint16_t arr[] = {r1, r2, r3, r4};
    return * (uint64_t *) arr;
}


uint64_t hash_table[256][8]{};


void init_hash_table(int board_size, int max_types){
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < max_types; ++j) {
            hash_table[i][j] = get_rand_64();
        }
    }
}

uint64_t get_hash_for_cell(int x, int y, int col_count, int cell_type){
    int linear_pos = y * col_count + x;
    return hash_table[linear_pos][cell_type];
}
