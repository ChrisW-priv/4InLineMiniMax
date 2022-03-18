#ifndef INC_4INLINE_TRANSPOSITIONTABLE_H
#define INC_4INLINE_TRANSPOSITIONTABLE_H

#include <unordered_map>


struct TranspositionTable{
    std::unordered_map<uint64_t, int> transposition_table{};

    TranspositionTable() = default;


    bool position_in_table(uint64_t hash){
        return transposition_table.find(hash) != transposition_table.end();
    }

    int get(uint64_t hash){
        return transposition_table.at(hash);
    }

    void put(uint64_t hash, int value){
        transposition_table[hash] = value;
    }
};

#endif //INC_4INLINE_TRANSPOSITIONTABLE_H
