#ifndef ms_sync
#define ms_sync

#include "etc.h"

void sync(GameState *state_ptr);
void fix_swept_flags(GameState *state_ptr);
void sync_remaining_flags(GameState *state_ptr);
void sync_remaining_sweeps(GameState *state_ptr);
void lose_if_mine_swept(GameState *state_ptr);
void win_if_all_swept(GameState *state_ptr);
void disable_debug_while_playing(GameState *state_ptr);

#endif