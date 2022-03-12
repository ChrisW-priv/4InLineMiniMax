#ifndef ZOBRISTHASHING
#define ZOBRISTHASHING

#include <cstdint>
#include <cstdlib>

uint64_t get_rand_64(){
    return
            (((uint64_t) rand() <<  0) & 0x000000000000FFFFull) |
            (((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) |
            (((uint64_t) rand() << 32) & 0x0000FFFF00000000ull) |
            (((uint64_t) rand() << 48) & 0xFFFF000000000000ull);
}


uint64_t hash_table[6][7][3]{};


void init_hash_table(){
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 3; ++k) {
                hash_table[i][j][k] = get_rand_64();
            }
        }
    }
}

#endif
