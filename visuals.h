#ifndef ms_visuals
#define ms_visuals

#include "etc.h"

void render_register_form(GameState *state_ptr);

void render_menu(GameState *state_ptr);

void render_edit_profile(GameState *state_ptr);

void render_game(GameState *state_ptr);
void render_game_header(GameState *state_ptr);
void draw_cell(GameState *state_ptr, int i, int j);

void game_lose_footer(GameState *state_ptr);
void game_won_footer(GameState *state_ptr);
void reload_or_exit_footer(GameState *state_ptr);

char *get_num_color(int num);

#endif
