#ifndef ms_controls
#define ms_controls

#include "etc.h"

void start_bad_things(void);
void end_bad_things(void);

bool wait_for_game_action(GameState *state_ptr);
void handle_arrow(GameState *state_ptr, char c);
void move_position(GameState *state_ptr, int i, int j);

#endif