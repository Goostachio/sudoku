#pragma once

#include "sudoku.h"

typedef struct HiddenTriple_impl
{
    Cell *p_cells[3];
    int values[3];
} HiddenTriple;

// Find hidden triples in a row, column, or box
void find_hidden_triples(Cell **p_cells, HiddenTriple *p_hidden_triples, int *p_counter);

// Find hidden triples in a board, return the number of hidden triples found
int hidden_triples(SudokuBoard *p_board);
