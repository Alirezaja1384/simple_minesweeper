#include <stdbool.h>
#include "etc.h"
#include "utils.h"
#include "sync.h"

void sync(GameState *state_ptr)
{
    fix_swept_flags(state_ptr);
    sync_remaining_flags(state_ptr);
    sync_remaining_sweeps(state_ptr);
    lose_if_mine_swept(state_ptr);
    win_if_all_swept(state_ptr);
}

void fix_swept_flags(GameState *state_ptr)
{
    for (int j = 0; j < state_ptr->size; j++)
        for (int i = 0; i < state_ptr->size; i++)
            if (state_ptr->swept[i][j])
                state_ptr->flags[i][j] = false;
}

void sync_remaining_flags(GameState *state_ptr)
{
    state_ptr->remaining_flags = state_ptr->total_flags - sum_bool_matrix(state_ptr->flags, state_ptr->size);
}

void sync_remaining_sweeps(GameState *state_ptr)
{
    state_ptr->remaining_sweeps = state_ptr->size * state_ptr->size - state_ptr->total_mines - sum_bool_matrix(state_ptr->swept, state_ptr->size);
}

void lose_if_mine_swept(GameState *state_ptr)
{
    if (state_ptr->step == GAME_PAGE_PLAYING)
    {
        for (int i = 0; i < state_ptr->size; i++)
            for (int j = 0; j < state_ptr->size; j++)
                if (state_ptr->mines[i][j] && state_ptr->swept[i][j])
                {
                    state_ptr->step = GAME_PAGE_LOST;
                    state_ptr->show_all = true;
                    state_ptr->stats.losses++;
                    return;
                }
    }
}

void win_if_all_swept(GameState *state_ptr)
{
    if (state_ptr->step == GAME_PAGE_PLAYING && state_ptr->remaining_sweeps == 0)
    {
        state_ptr->step = GAME_PAGE_WON;
        state_ptr->show_all = true;
        state_ptr->stats.wins++;
    }
}
