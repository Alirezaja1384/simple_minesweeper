#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "etc.h"
#include "utils.h"
#include "sync.h"
#include "constants.h"
#include "logics.h"

void initiate(GameState *state_ptr, int size)
{
    srand(time(NULL));

    state_ptr->stats.losses = 0;
    state_ptr->stats.wins = 0;

    state_ptr->show_all = false;
    state_ptr->size = size;
    state_ptr->mines = NULL;
    state_ptr->flags = NULL;
    state_ptr->swept = NULL;
    state_ptr->step = REGISTER_PAGE;
};

void start_game(GameState *state_ptr)
{
    int size = state_ptr->size;

    state_ptr->total_mines = size * size * ((float)5 / 32);
    state_ptr->total_flags = state_ptr->total_mines;
    state_ptr->current_position[0] = 0;
    state_ptr->current_position[1] = 0;

    state_ptr->show_all = false;
    state_ptr->step = GAME_PAGE_PLAYING;

    free(state_ptr->mines);
    free(state_ptr->flags);
    free(state_ptr->swept);

    state_ptr->mines = create_bool_matrix(size);
    state_ptr->flags = create_bool_matrix(size);
    state_ptr->swept = create_bool_matrix(size);

    place_mines(state_ptr);
    sync(state_ptr);
}

// TODO: Implement!
void place_mines(GameState *state_ptr)
{
    int size = state_ptr->size;
    bool **mines = state_ptr->mines;

    int remaining = state_ptr->total_mines - sum_bool_matrix(mines, size);
    if (MAX_MINES_PER_COLUMN > size || remaining > size * MAX_MINES_PER_COLUMN)
    {
        puts("Invalid mines configuration!");
        exit(2);
    }

    while (remaining > 0)
    {
        int rand_i = rand() % size, rand_j = rand() % size;
        int column_bombs = count_active_cells(mines, rand_i, rand_i, 0, size - 1);

        if (column_bombs <= MAX_MINES_PER_COLUMN && !mines[rand_i][rand_j])
        {
            mines[rand_i][rand_j] = true;
            remaining--;
        }
    }
}

int count_neighbor_mines(GameState *state_ptr, int i, int j)
{
    int i_start = i == 0 ? 0 : i - 1, i_end = i == state_ptr->size - 1 ? i : i + 1;
    int j_start = j == 0 ? 0 : j - 1, j_end = j == state_ptr->size - 1 ? j : j + 1;

    return count_active_cells(state_ptr->mines, i_start, i_end, j_start, j_end);
}

void toggle_flag(GameState *state_ptr, int i, int j)
{
    if (state_ptr->swept[i][j])
        return;

    if (state_ptr->flags[i][j])
        state_ptr->flags[i][j] = false;
    else if (state_ptr->remaining_flags > 0)
        state_ptr->flags[i][j] = true;

    sync(state_ptr);
}

void sweep(GameState *state_ptr, int i, int j)
{
    if (state_ptr->swept[i][j])
        return;

    state_ptr->swept[i][j] = true;
    sync(state_ptr);

    int i_start = i == 0 ? 0 : i - 1, i_end = i == state_ptr->size - 1 ? i : i + 1;
    int j_start = j == 0 ? 0 : j - 1, j_end = j == state_ptr->size - 1 ? j : j + 1;

    if (count_neighbor_mines(state_ptr, i, j) == 0)
    {
        for (int jj = j_start; jj <= j_end; jj++)
            for (int ii = i_start; ii <= i_end; ii++)
                sweep(state_ptr, ii, jj);
    }
}
