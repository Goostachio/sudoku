#include "hidden_triples.h"

void find_hidden_triples(Cell **p_cells, HiddenTriple *p_hidden_triples, int *p_counter)
{
    for (int i = 0; i < BOARD_SIZE - 2; i++)
    {
        if (p_cells[i]->num_candidates == 3)
        {
            for (int j = i + 1; j < BOARD_SIZE - 1; j++)
            {
                if (p_cells[j]->num_candidates == 3)
                {
                    for (int k = j + 1; k < BOARD_SIZE; k++)
                    {
                        if (p_cells[k]->num_candidates == 3 &&
                            (p_cells[i]->candidates[0] == p_cells[j]->candidates[0] ||
                             p_cells[i]->candidates[0] == p_cells[k]->candidates[0] ||
                             p_cells[j]->candidates[0] == p_cells[k]->candidates[0]) &&
                            (p_cells[i]->candidates[1] == p_cells[j]->candidates[1] ||
                             p_cells[i]->candidates[1] == p_cells[k]->candidates[1] ||
                             p_cells[j]->candidates[1] == p_cells[k]->candidates[1]) &&
                            (p_cells[i]->candidates[2] == p_cells[j]->candidates[2] ||
                             p_cells[i]->candidates[2] == p_cells[k]->candidates[2] ||
                             p_cells[j]->candidates[2] == p_cells[k]->candidates[2]))
                        {
                            // Found a hidden triple
                            p_hidden_triples[*p_counter].p_cells[0] = p_cells[i];
                            p_hidden_triples[*p_counter].p_cells[1] = p_cells[j];
                            p_hidden_triples[*p_counter].p_cells[2] = p_cells[k];
                            p_hidden_triples[*p_counter].values[0] = p_cells[i]->candidates[0];
                            p_hidden_triples[*p_counter].values[1] = p_cells[i]->candidates[1];
                            p_hidden_triples[*p_counter].values[2] = p_cells[i]->candidates[2];
                            (*p_counter)++;
                        }
                    }
                }
            }
        }
    }
}

int hidden_triples(SudokuBoard *p_board)
{
    HiddenTriple hidden_triples[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Check hidden triples in rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples(p_board->p_rows[i], hidden_triples, &counter);
    }

    // Check hidden triples in columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples(p_board->p_cols[i], hidden_triples, &counter);
    }

    // Check hidden triples in boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples(p_board->p_boxes[i], hidden_triples, &counter);
    }

    // Apply hidden triples
    for (int i = 0; i < counter; i++)
    {
        Cell *cell1 = hidden_triples[i].p_cells[0];
        Cell *cell2 = hidden_triples[i].p_cells[1];
        Cell *cell3 = hidden_triples[i].p_cells[2];

        // Remove other candidates from the cells
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            if (p_board->p_rows[cell1->row_index][k] != cell1 && p_board->p_rows[cell1->row_index][k] != cell2 && p_board->p_rows[cell1->row_index][k] != cell3)
            {
                unset_candidate(p_board->p_rows[cell1->row_index][k], hidden_triples[i].values[0]);
                unset_candidate(p_board->p_rows[cell1->row_index][k], hidden_triples[i].values[1]);
                unset_candidate(p_board->p_rows[cell1->row_index][k], hidden_triples[i].values[2]);
            }

            if (p_board->p_cols[cell1->col_index][k] != cell1 && p_board->p_cols[cell1->col_index][k] != cell2 && p_board->p_cols[cell1->col_index][k] != cell3)
            {
                unset_candidate(p_board->p_cols[cell1->col_index][k], hidden_triples[i].values[0]);
                unset_candidate(p_board->p_cols[cell1->col_index][k], hidden_triples[i].values[1]);
                unset_candidate(p_board->p_cols[cell1->col_index][k], hidden_triples[i].values[2]);
            }

            if (p_board->p_boxes[cell1->box_index][k] != cell1 && p_board->p_boxes[cell1->box_index][k] != cell2 && p_board->p_boxes[cell1->box_index][k] != cell3)
            {
                unset_candidate(p_board->p_boxes[cell1->box_index][k], hidden_triples[i].values[0]);
                unset_candidate(p_board->p_boxes[cell1->box_index][k], hidden_triples[i].values[1]);
                unset_candidate(p_board->p_boxes[cell1->box_index][k], hidden_triples[i].values[2]);
            }
        }
    }

    return counter;
}