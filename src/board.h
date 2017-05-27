/* Natalie Menato
   Numero USP: 10295051
   07/05/2017
   Submissao para Trabalho Parte 2  */

#ifndef BOARD_H
#define BOARD_H


#define ROW_SIZE 3
#define COLUMN_SIZE 4

#include "main.h"

//struct to store the game board
typedef struct {
    int elements[ROW_SIZE][COLUMN_SIZE];
} t_board;

// Prints the board that was passed to the function to the screen.
void print_board(t_board);

// Clears all positions of the board
int clear_board(t_board *);

//check if it is possible to play at desired position
int valid_board_move(int [], t_board);

//updates the board with the latest move
void update_board(int [], t_board *);

//return TRUE if more possible moves, FALSE if there are no more possible moves
int remaining_moves(t_board);

//return TRUE if last move caused player to win game, FALSE otherwise
int won_game(t_board, int []);

//check if a user has won in a column, return TRUE if yes, otherwise FALSE
int check_column(t_board, int);

//check if a user has won in a row, return TRUE if yes, otherwise FALSE
int check_row(t_board, int);

//check if user won in diagonal, return TRUE if yes, otherwise FALSE
int check_diagonal(t_board, int []);

//verify if the decreasing diaganal has three in a row
int dec_diag(t_board, int []);

int dec_diag(t_board, int [2]);

#endif
