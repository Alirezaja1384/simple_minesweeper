#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "etc.h"
#include "utils.h"
#include "controls.h"
#include "logics.h"

void start_bad_things(void)
{
    /* use system call to make terminal send all keystrokes directly to stdin */
    system("stty -icanon min 1");
}

void end_bad_things(void)
{
    /* use system call to set terminal behaviour to more normal behaviour */
    system("stty cooked");
}

bool wait_for_game_action(GameState *state_ptr)
{
    int i = state_ptr->current_position[0], j = state_ptr->current_position[1];

    char c = tolower(rt_getchar());
    switch (c)
    {
    // [Arrow keys => Move]
    // if the first value is esc
    case '\033':
        rt_getchar();                          // skip the [
        handle_arrow(state_ptr, rt_getchar()); // Handle arrow keys (A, B, C, D)
        break;

    // [Space => Flag]
    case ' ':
        toggle_flag(state_ptr, i, j);
        break;

    // [Enter => sweep]
    case '\n':
        sweep(state_ptr, i, j);
        break;

    // [d => Debug]
    case 'd':
        state_ptr->show_all = !state_ptr->show_all;
        break;

    // [r => Reload]
    case 'r':
        start_game(state_ptr);
        break;

    // [q => Quit]
    case 'q':
        exit(0);
    }

    return true;
}

void handle_arrow(GameState *state_ptr, char c)
{
    int move[2] = {0, 0};
    switch (c)
    {

    case 'A':
        // code for arrow up
        move[0] = 0;
        move[1] = -1;
        break;
    case 'B':
        // code for arrow down
        move[0] = 0;
        move[1] = 1;
        break;
    case 'C':
        // code for arrow right
        move[0] = 1;
        move[1] = 0;
        break;
    case 'D':
        // code for arrow left
        move[0] = -1;
        move[1] = 0;
        break;
    default:
        break;
    }

    move_position(state_ptr, move[0], move[1]);
}

void move_position(GameState *state_ptr, int i, int j)
{
    int next_i = state_ptr->current_position[0] + i;
    int next_j = state_ptr->current_position[1] + j;

    if (next_i >= 0 && next_i < state_ptr->size && next_j >= 0 && next_j < state_ptr->size)
    {
        state_ptr->current_position[0] += i;
        state_ptr->current_position[1] += j;
    }
}
