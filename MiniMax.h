#ifndef MINIMAX_ALGORITHM
#define MINIMAX_ALGORITHM


#include "FourInLine.h"

#ifndef infinity
#define infinity INT_MAX
#endif


int MiniMax(FourInLine position, int depth, int maximising_player=1, int alfa=-infinity, int beta=infinity){
    if (position.game_stops()) {return maximising_player ? -infinity : infinity;}
    if (depth == 0) return position.eval_position();

    vector<int> moves = position.possible_moves();
    if (maximising_player){
        int maxEval = -infinity;

        // for all children of position create new position and evaluate it
        for (auto move: moves) {
            FourInLine new_position = position.board_after_move(move, maximising_player);
            int eval = MiniMax(new_position, depth - 1, !maximising_player, alfa, beta);
            maxEval = eval > maxEval ? eval : maxEval;
            alfa = eval > alfa ? eval : alfa;
            if (beta <= alfa) break;
        }
        return maxEval;
    } else {
        int minEval = infinity;

        // for all children of position create new position and evaluate it
        for (auto move: moves) {
            FourInLine new_position = position.board_after_move(move, maximising_player);
            int eval = MiniMax(new_position, depth - 1, !maximising_player, alfa, beta);
            minEval = eval < minEval ? eval : minEval;
            beta = eval < alfa ? eval : beta;
            if (beta <= alfa) break;
        }
        return minEval;
    }
}

#endif // MINIMAX_ALGORITHM