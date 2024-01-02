#ifndef ms_logics
#define ms_logics

#include "etc.h"

void place_mines(GameState *state_ptr);
int count_neighbor_mines(GameState *state_ptr, int i, int j);

void toggle_flag(GameState *state_ptr, int i, int j);
void sweep(GameState *state_ptr, int i, int j);

void initiate(GameState *state_ptr, int size);
void start_game(GameState *state_ptr);

#endif