#include "hidden_pairs.h"

void find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter)
{
    for (int i = 0; i < BOARD_SIZE - 1; i++)
    {
        if (p_cells[i]->num_candidates == 2)
        {
            for (int j = i + 1; j < BOARD_SIZE; j++)
            {
                if (p_cells[j]->num_candidates == 2 &&
                    p_cells[i]->candidates[0] == p_cells[j]->candidates[0] &&
                    p_cells[i]->candidates[1] == p_cells[j]->candidates[1])
                {
                    // Found a hidden pair
                    p_hidden_pairs[*p_counter].p_cells[0] = p_cells[i];
                    p_hidden_pairs[*p_counter].p_cells[1] = p_cells[j];
                    p_hidden_pairs[*p_counter].values[0] = p_cells[i]->candidates[0];
                    p_hidden_pairs[*p_counter].values[1] = p_cells[i]->candidates[1];
                    (*p_counter)++;
                }
            }
        }
    }
}

int hidden_pairs(SudokuBoard *p_board)
{
    HiddenPair hidden_pairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Check hidden pairs in rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &counter);
    }

    // Check hidden pairs in columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &counter);
    }

    // Check hidden pairs in boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &counter);
    }

    // Apply hidden pairs
    for (int i = 0; i < counter; i++)
    {
        Cell *cell1 = hidden_pairs[i].p_cells[0];
        Cell *cell2 = hidden_pairs[i].p_cells[1];

        // Remove other candidates from the cells
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            if (p_board->p_rows[cell1->row_index][k] != cell1 && p_board->p_rows[cell1->row_index][k] != cell2)
            {
                unset_candidate(p_board->p_rows[cell1->row_index][k], hidden_pairs[i].values[0]);
                unset_candidate(p_board->p_rows[cell1->row_index][k], hidden_pairs[i].values[1]);
            }

            if (p_board->p_cols[cell1->col_index][k] != cell1 && p_board->p_cols[cell1->col_index][k] != cell2)
            {
                unset_candidate(p_board->p_cols[cell1->col_index][k], hidden_pairs[i].values[0]);
                unset_candidate(p_board->p_cols[cell1->col_index][k], hidden_pairs[i].values[1]);
            }

            if (p_board->p_boxes[cell1->box_index][k] != cell1 && p_board->p_boxes[cell1->box_index][k] != cell2)
            {
                unset_candidate(p_board->p_boxes[cell1->box_index][k], hidden_pairs[i].values[0]);
                unset_candidate(p_board->p_boxes[cell1->box_index][k], hidden_pairs[i].values[1]);
            }
        }
    }

    return counter;
}
