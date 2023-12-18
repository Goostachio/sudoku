#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl
{
    Cell *p_cells[2];
    int values[2];
} HiddenPair;

// Find hidden pairs in a row, column, or box
void find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter);

// Find hidden pairs in a board, return the number of hidden pairs found
int hidden_pairs(SudokuBoard *p_board);