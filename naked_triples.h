#pragma once

#include "sudoku.h"

// Function to find and print Naked Triples in a group of cells
void find_and_print_naked_triples_in_group(Cell **group, int group_size);

// Function to check if three cells form Naked Triples
bool are_naked_triples(Cell *cell1, Cell *cell2, Cell *cell3);

void find_and_print_naked_triples(SudokuBoard *p_board);

void print_candidates(Cell *cell);