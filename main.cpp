#include "FourInLine.h"
#include "MiniMax.h"
#include "zobristhashing.h"
#include <iostream>
#include "auto_tests.h"
using std::cout;

#define TEST 1

int main() {
    init_hash_table(42, 3);

#if TEST
    run_tests();
    system("pause");
#endif
}
