#pragma once

#include <stdbool.h>

#define BOARD_SIZE 9

struct Cell_impl
{
    int row_index;
    int col_index;
    int box_index;
    int num_candidates;
    int candidates[BOARD_SIZE];
    int value; // solved or 0
    bool fixed;
};

typedef struct Cell_impl Cell;

struct SudokuBoard_impl
{
    int solved_counter;
    Cell **data; // 9x9 cell board

    Cell **p_rows[BOARD_SIZE];  // rows pointers
    Cell **p_cols[BOARD_SIZE];  // cols pointers
    Cell **p_boxes[BOARD_SIZE]; // boxes pointers
    Cell *solved_cells[BOARD_SIZE *
                       BOARD_SIZE]; // solved cell pointers (maximum)
};

typedef struct SudokuBoard_impl SudokuBoard;

void init_sudoku(SudokuBoard *p_board);
void load_sudoku(SudokuBoard *p_board, char *input_text);
bool apply_constraint(Cell **p_cells, int value);
bool is_in_list(Cell **p_array, int size, Cell *p);
void print_candidate_num(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);

void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
void free_sudoku(SudokuBoard *p_board);
bool is_candidate(Cell *cell, int value);
bool is_solved(SudokuBoard *p_board);

/*
    while (board->solved_counter < BOARD_SIZE * BOARD_SIZE)
    {
        solved_counter = check_solved_cells(board, &p_solved_cells);
        printf("check_solved_cells %d\n", solved_counter);
        if (show_possible(board, p_solved_cells, solved_counter))
        {
            printf("show_possible -> Yes\n");
            continue;
        }
        //hidden singles
        solved_counter = hidden_singles(board);
        if (solved_counter)
        {
            printf("hidden_singles %d\n", solved_counter);
            continue;
        }
        // Hidden Pairs
        solved_counter = hidden_pairs(board);
        if (solved_counter) {
            printf("hidden_pairs %d\n", solved_counter);
            continue;
        }

        // Hidden Triples
        solved_counter = hidden_triples(board);
        if (solved_counter) {
            printf("hidden_triples %d\n", solved_counter);
            continue;
        }

        // Naked Pairs
        solved_counter = naked_pairs(board);
        if (solved_counter) {
            printf("naked_pairs %d\n", solved_counter);
            continue;
        }

        // Naked Triples
        solved_counter = naked_triples(board);
        if (solved_counter) {
            printf("naked_triples %d\n", solved_counter);
            continue;
        }

    }
*/