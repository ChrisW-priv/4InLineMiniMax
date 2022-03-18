#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#include <string>
#include <iostream>
#include <ctime>
#include "FourInLine.h"
#include "MiniMax.h"

using std::cout, std::string;
#define TEST_GAME_STOPS 0
#define TEST_MINIMAX 1
#define TEST_MINIMAX_PERFORMANCE 0


int game_stops_test_case(int move, int expected, const string& filename, const string& description){
    FourInLine position{filename};
    int result = position.find4in_line(move);
    int as_expected = result == expected;
    if (as_expected){
        cout << "test passed!\n";
        return 0;
    } else {
        cout << '\n' + description + "' " + "failed to match expected result\n";
        cout << position << "last move: " << move << '\n';
        cout << "expected value: " << expected << "\ninstead function returned: " << result << "\n\n";
        return 1;
    }
}


int mini_max_test_case(int depth, int maximising_player, int expected, const string& filename, const string& description){
    // init position from file specified
    FourInLine position{filename};

    // get a eval form minimax algorithm
    int result = MiniMax(position, depth, maximising_player);

    if (result == expected){
        cout << "test passed!\n";
        return 0;
    } else {
        cout << '\n' + description + "' " + "failed to match expected result\n";
        cout << position;
        cout << "parameters of the test: " << depth << " " << maximising_player << " file_name: " << filename << '\n';
        cout << "expected value: " << expected << "\ninstead function returned: " << result << "\n\n";
        return 1;
    }
}


int mini_max_consecutive_depth_performance_test(int depth, int maximising_player, const string& filename){
    FourInLine position = FourInLine{filename};
    for (int i = 1; i <= depth; ++i) {
        clock_t start = clock();
        int value = MiniMax(position, i, maximising_player);
        clock_t end = clock();
        cout << "function took: " << float(end - start)/CLOCKS_PER_SEC << " for a depth of " << i << '\n';
        cout << "value of a base position: " << value << '\n';
    }
    cout << '\n';
    return 0;
}


void run_tests() {
#if TEST_GAME_STOPS
    string description, file_name;
    /// checking for the rows:
    file_name = "../TEST_BOARDS/test_board0.txt";
    description = "testing if function checking row is working ok (board from file '" + file_name + "') ";

    game_stops_test_case(2, 1, file_name, description + "(left)");
    game_stops_test_case(3, 0, file_name, description + "(wrong)");
    game_stops_test_case(4, 1, file_name, description + "(middle)");
    game_stops_test_case(5, 1, file_name, description + "(right)");


    /// checking the columns
    file_name = "../TEST_BOARDS/test_board2.txt";
    description = "testing if function checking column is working ok (board from file '" + file_name + "') ";

    game_stops_test_case(2, 0, file_name, description);
    game_stops_test_case(3, 1, file_name, description);

    file_name = "../TEST_BOARDS/test_board3.txt";
    description = "testing if function checking column is working ok (board from file '" + file_name + "')";
    game_stops_test_case(3, 0, file_name, description);

    /// checking the diagonals pt.1
    file_name = "../TEST_BOARDS/test_board4.txt";
    description = "testing if function checking diagonal1 is working ok (board from file '" + file_name + "') ";

    game_stops_test_case(0, 1, file_name, description + "(left)");
    game_stops_test_case(1, 1, file_name, description + "(wrong)");
    game_stops_test_case(2, 0, file_name, description + "(middle)");
    game_stops_test_case(3, 1, file_name, description + "(right)");

    /// checking the diagonals pt.2
    file_name = "../TEST_BOARDS/test_board1.txt";
    description = "testing if function checking diagonal2 is working ok (board from file '" + file_name + "') ";

    game_stops_test_case(0 + 3, 1, file_name, description + "(left)");
    game_stops_test_case(1 + 3, 0, file_name, description + "(wrong)");
    game_stops_test_case(2 + 3, 1, file_name, description + "(middle)");
    game_stops_test_case(3 + 3, 1, file_name, description + "(right)");

#endif
#if TEST_MINIMAX
//    mini_max_test_case(2,1, infinity, "../TEST_BOARDS/test_board10.txt", "test depth 2 for a winning player");
//    mini_max_test_case(2,0, infinity, "../TEST_BOARDS/test_board5.txt", "test depth 2 for a winning player");
//    mini_max_test_case(2,1, -2, "../TEST_BOARDS/test_board6.txt", "test depth 2 for a winning player");
    mini_max_test_case(2,1, -1, "../TEST_BOARDS/test_board7.txt", "test depth 2 for a winning player");
#endif
#if TEST_MINIMAX_PERFORMANCE
    // test empty position, worst case scenario
    FourInLine position{};
    int depth = 12;
    clock_t start = clock();
    int value = MiniMax(position, depth, 1);
    clock_t end = clock();
    cout << "function took: " << float(end - start)/CLOCKS_PER_SEC << " for a depth of " << depth << '\n';
    cout << "value of a base position: " << value << '\n';

    // currently, worthless - whatever value of depth, true test is from depth 1
    // mini_max_consecutive_depth_performance_test(9, 1, "../TEST_BOARDS/test_board7.txt");
#endif
}



#endif //TEST_FUNCTIONS
