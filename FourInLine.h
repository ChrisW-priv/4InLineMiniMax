#ifndef FOURINLINE
#define FOURINLINE


#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

#ifndef infinity
    #define infinity INT_MAX
#endif

enum BOARD_CELL{
    EMPTY,   // no player on the board
    PLAYER1, // maximising player
    PLAYER2, // minimising player
};

#define MAX_X 7
#define MAX_Y 6
#define DEFAULT_ORDER {3,2,4,1,5,0,6}


BOARD_CELL convert_char_to_board_cell(char cell){
    switch (cell) {
        case ' ':
            return BOARD_CELL::EMPTY;
        case 'X':
            return BOARD_CELL::PLAYER1;
        case 'O':
            return BOARD_CELL::PLAYER2;
        default:
            cout << "invalid cell type! (not equal to one of {' ', 'X', 'O'})";
            exit(-1);
    }
}


char convert_board_cell_to_char(BOARD_CELL cell){
    switch (cell) {
        case BOARD_CELL::EMPTY:
            return ' ';
        case BOARD_CELL::PLAYER1:
            return 'X';
        case BOARD_CELL::PLAYER2:
            return 'O';
        default:
            cout << "unknown board cell type!";
            exit(-1);
    }
}


/// returns the type of cell corresponding with first player
BOARD_CELL get_cell_type_for_player(int player){
    return player ? BOARD_CELL::PLAYER1 : BOARD_CELL::PLAYER2;
}


struct FourInLine {
    BOARD_CELL board[6][7]{};

    FourInLine(){
        memset(board, BOARD_CELL::EMPTY, sizeof(board));
    };

    /// Constructor from a 2d char array
    explicit FourInLine(char board[6][7]){
        for (int j = 0; j < MAX_Y; ++j) {
            for (int i = 0; i < MAX_X; ++i) {
                char cell = board[j][i];
                this->board[j][i] = convert_char_to_board_cell(cell);
            }
        }
    }

    /// Constructor taking the filename as an input allowing to import a board from file
    explicit FourInLine(const string& file_name){
        ifstream infile{file_name};
        if (infile.fail()){
            cout << "error when importing file named: '" << file_name << "'\n";
            exit(-1);
        }
        string row;
        int j = 0;
        while (getline(infile, row) && j<MAX_Y){
            for (int i = 0; i < MAX_X; ++i) {
                board[j][i] = convert_char_to_board_cell(row[i]);
            }
            j++;
        }
    }

    /// Standard output for a board position: print line by line separated by "|" for columns and "-" for rows
    friend std::ostream& operator << (std::ostream& stream, const FourInLine& position){
        for (int i = 0; i < 2 * MAX_X+ 1; ++i) {
            stream << '-';
        }
        stream << '\n';

        for (auto row: position.board) {
            stream << '|';
            for (int column = 0; column < MAX_X; ++column) {
                stream << convert_board_cell_to_char(row[column]) << '|';
            }
            stream << '\n';
            for (int i = 0; i < 2 * MAX_X + 1; ++i) {
                stream << '-';
            }
            stream << '\n';
        }

        for (int j = 0; j < MAX_Y; ++j) {

        }
        stream << '\n';
        return stream;
    }

    /// Returns int of row that contains the lowest empty cell.
    /// Returns -1 if entire column is full.
    int highest(int column){
        int row = 6;
        while (row>0){
            row--;
            char cell = board[row][column];
            if (cell == BOARD_CELL::EMPTY) return row;
        }
        return -1;
    }

    /// Returns 1 if move is valid.
    /// Checks if move in range and if column is not full.
    int move_is_valid(int move){
        return !(move < 0 || 7 <= move || highest(move) == -1);
    }

    /// changes board of current instance of class
    void move(int move, int player){
        BOARD_CELL player_cell_type = get_cell_type_for_player(player);
        if (move_is_valid(move)) {
            board[highest(move)][move] = player_cell_type;
        } else {
            cout << "Move is invalid!\n" << "arguments passed:\nmove: " << move << "\nplayer_symbol: " << player_cell_type << '\n';
            exit(-2);
        }
    }

    /// Creates new board and returns it after move specified
    FourInLine board_after_move(int move, int player=-1){
        FourInLine new_position = *this; // create shallow copy of position
        player = player == -1 ? new_position.current_player() : player;
        new_position.move(move, player); // modify new board
        return new_position;
    }

    /// Returns a list of all possible moves of given position
    vector<int> possible_moves(){
        vector<int> moves;
        moves.reserve(7);
        for (int move: DEFAULT_ORDER) {
            if (move_is_valid(move)) {
                moves.emplace_back(move);
            }
        }
        return moves;
    }

    /// Return 1 if current player is maximising player.
    /// Return 0 if current player is minimising player.
    int current_player(){
        int count_cells_empty=0;
        for (auto row: board) {
            for (int i = 0; i < MAX_X; ++i) {
                if (row[i] == BOARD_CELL::EMPTY) count_cells_empty++;
            }
        }
        return !(count_cells_empty&1);
    }

    /// Returns the evaluation score of the position
    int eval_position() {
        int player = current_player();
        for (auto move1: possible_moves()) {
            // check if there is direct win
            FourInLine board_after_move1 = board_after_move(move1, player);

            // technically this is needed for true evaluation but is already checked before in minimax function
            // if (board_after_move1.find4in_line(move1)) return player == 1 ? -infinity : infinity;

            // check how many moves cause the player to lose
            int count_moves_causing_loss = 0;
            for (auto move2: board_after_move1.possible_moves()) {
                if (board_after_move1.find4in_line(move2, !player)) count_moves_causing_loss++;
                return player == 1 ? -count_moves_causing_loss : count_moves_causing_loss;
            }
        }
        return 0;
    }

    /// Checks if game reached a winning position for any of the players
    int game_stops(){
        for (int i = 0; i < MAX_X; ++i) {
            if (find4in_line(i)) {return 1;}
        }
        return 0;
    }

    /// Checks if there are 4 colors in line. returns 1 it true, 0 otherwise.
    /// Extra argument "player" allows to run a simulation that just assumes there was a move made in "last move" position
    int find4in_line(int last_move, int player=-1){
        int highest_element_after_move = highest(last_move);

        // check if last move occurred - if highest block is block 0 then there has been an error but game doesn't stop
        if (highest_element_after_move == MAX_Y-1) { return 0; }

        int row_of_last = highest_element_after_move + 1;

        // if we run this function in simulation mode then we have to get player char else get the char from board
        BOARD_CELL player_cell = player == -1 ? board[row_of_last][last_move] : get_cell_type_for_player(player);

        int i, ile;
        //check row
        ile = 1;
        i = 1;
        while (last_move-i>=0 && board[row_of_last][last_move-i] == player_cell && i < 4) { ile = ++i;}
        i = 1;
        while (last_move+i<MAX_X && board[row_of_last][last_move+i] == player_cell && i < 4 ) {ile++; i++;}
        if (ile > 3) return 1;

        //check column
        i = 1;
        while (row_of_last+i<MAX_Y && board[row_of_last+i][last_move] == player_cell && i < 4) ++i;
        if (i > 3) return 1;

        //check top_diagonal
        ile = 1;
        i = 1;
        while (row_of_last-i>=0 && last_move-i>=0 && board[row_of_last-i][last_move-i] == player_cell && i < 4) { ile = ++i;}
        i = 1;
        while (row_of_last+i<MAX_Y && last_move+i<MAX_X && board[row_of_last+i][last_move+i] == player_cell && i < 4) {ile++; i++;}
        if (ile > 3) return 1;

        //check bottom_diagonal
        ile = 1;
        i = 1;
        while (row_of_last+i<MAX_Y && last_move-i>=0 && board[row_of_last+i][last_move-i] == player_cell && i < 4) { ile = ++i;}
        i = 1;
        while (row_of_last-i>=0 && last_move+i<MAX_X && board[row_of_last-i][last_move+i] == player_cell && i < 4) {ile++; i++;}
        if (ile > 3) return 1;

        // if no case was met - return 0
        return 0;
    }
};

#endif
