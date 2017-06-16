/** @file input.c
 *  @brief Contains functions related to user input
 *
 *  This file contains the functions related to user input, including getting
 *  the next move and validating it.
 *
 *  @author Natalie Menato (10295051)
 */

#include "ai.h"

/*
 * Finds all of the possible legal moves, given the current board
 */
t_possible_moves possible_moves(t_board board) {
    int i, j;
    t_move move;
    t_possible_moves poss_moves;
    poss_moves.num_moves = 0;

    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COLUMN_SIZE; j++) {
            move.row = i;
            move.column = j;
            if (valid_board_move(move, board) == TRUE) {
                poss_moves.possible_moves[poss_moves.num_moves] = move;
                poss_moves.num_moves++;
            }
        }
    }
    return poss_moves;
}

/*
 * Scores a potential move based on the current board, to help computer decide
 * its next move
 */
int score_move(t_board board, t_move move) {
    int i;
    t_possible_moves player_moves;
    //score each of the possible moves
    make_move(move, &board);
    if (won_game(board, move)) {
        return 1;
    }
    //get possible moves still available after move is made
    player_moves = possible_moves(board);
    for (i = 0; i < player_moves.num_moves; i++) {
        t_move player_move = player_moves.possible_moves[i];
        make_move(player_move, &board);
        if (won_game(board, player_move)) {
            return -1;
        }
        undo_move(player_move, &board);
    }
    undo_move(move, &board);
    return 0;
}

/*
 * Computer picks its move, based on the best possible score
 */
t_move computer_move(t_board board) {
    int i;
    t_move comp_move;
    t_possible_moves poss_moves = possible_moves(board);
    //the indexes of all moves with the max score
    int ind_best_scores[poss_moves.num_moves];

    //int ind_best_score = 0;
    //max scores starts with score of first possible move
    int best_score = score_move(board, poss_moves.possible_moves[0]);
    //start with one move of same score
    int num_best_scores = 1;
    //store the index of the best score so far
    ind_best_scores[0] = 0;
    //evaluate each possible computer move and determine the highest score, save scores to score array
    for (i = 1; i < poss_moves.num_moves; i++) {
        int score = score_move(board, poss_moves.possible_moves[i]);
        //if it is higher than precious best score, it is the new best score, and it is the only high score so far
        if (score > best_score) {
            best_score = score;
            ind_best_scores[0] = i;
            num_best_scores = 1;
        }
            //if it is equal to the best score, add the index to the list and increment number of best scores
        else if (score == best_score) {
            ind_best_scores[num_best_scores] = i;
            num_best_scores++;
        }
    }
    //pick one of the indexes of the best moves at random
    int index = rand() % num_best_scores;
    index = ind_best_scores[index];

    comp_move = poss_moves.possible_moves[index];
    return comp_move;
}

/*
 * Computer makes a random valid move
 */
void random_move(t_move *move, t_board board) {
// Saves a valid, random move to move
    move->row = rand() % ROW_SIZE;
    move->column = rand() % COLUMN_SIZE;
    while (valid_board_move(*move, board) == FALSE) {
        move->row = rand() % ROW_SIZE;
        move->column = rand() % COLUMN_SIZE;
    }
    return;
}