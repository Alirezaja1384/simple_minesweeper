#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "etc.h"
#include "logics.h"
#include "constants.h"
#include "visuals.h"
#include "controls.h"
#include "utils.h"

void render_register_form(GameState *state_ptr)
{
    printf("Enter your name: ");
    state_ptr->username = get_valid_string();
    state_ptr->step = MENU_PAGE;
}

void render_menu(GameState *state_ptr)
{
    printf("Hello %s!\n\n", state_ptr->username);

    puts("Menu:");
    puts(" 1 - Change your name");
    puts(" 2 - Play");

    char answer;
    do
    {
        printf("\n* Choose the action: ");
        answer = getchar();
    } while (answer != '1' && answer != '2');

    if (answer == '1')
        state_ptr->step = EDIT_PROFILE_PAGE;
    else
        start_game(state_ptr);
}

void render_edit_profile(GameState *state_ptr)
{
    printf("Your current name: %s\n", state_ptr->username);
    printf("Enter your new name: ");
    state_ptr->username = get_valid_string();
    state_ptr->step = MENU_PAGE;
}

void render_game(GameState *state_ptr)
{
    render_game_header(state_ptr);

    printf("  ");
    for (int i = 0; i < 3 * state_ptr->size; i++)
        printf("-");

    printf(NL);

    for (int j = 0; j < state_ptr->size; j++)
    {
        printf(" |");
        for (int i = 0; i < state_ptr->size; i++)
            draw_cell(state_ptr, i, j);

        printf("|" NL);
    }

    printf("  ");
    for (int i = 0; i < 3 * state_ptr->size; i++)
        printf("-");

    printf(NL);

    switch (state_ptr->step)
    {
    case GAME_PAGE_PLAYING:
        wait_for_game_action(state_ptr);
        break;

    case GAME_PAGE_LOST:
        game_lose_footer(state_ptr);
        break;

    case GAME_PAGE_WON:
        game_won_footer(state_ptr);
        break;

    default:
        break;
    }
}

void render_game_header(GameState *state_ptr)
{
    switch (state_ptr->step)
    {
    case GAME_PAGE_PLAYING:
        printf(FG_BLUE "Good luck %s!\n" RESET, state_ptr->username);
        break;
    case GAME_PAGE_WON:
        printf(FG_GREEN "Well done %s!\n" RESET, state_ptr->username);
        break;
    case GAME_PAGE_LOST:
        printf(FG_YELLOW "Maybe next time %s!\n" RESET, state_ptr->username);
        break;
    }

    printf("Wins: %d | Loses: %d | Total: %d" NL, state_ptr->stats.wins, state_ptr->stats.losses, state_ptr->stats.wins + state_ptr->stats.losses);
    printf("Remaining flags: %d | Remaining sweeps: %d" NL, state_ptr->remaining_flags, state_ptr->remaining_sweeps);
}

void draw_cell(GameState *state_ptr, int i, int j)
{
    char *cell_fg = "";
    char *cell_bg = "";
    char cell_content[50];

    if (state_ptr->step == GAME_PAGE_PLAYING && state_ptr->current_position[0] == i && state_ptr->current_position[1] == j)
        cell_bg = SELECT;

    if (state_ptr->show_all || state_ptr->swept[i][j])
    {
        if (state_ptr->mines[i][j])
            strcpy(cell_content, BOMB);
        else
        {
            int count = count_neighbor_mines(state_ptr, i, j);
            cell_fg = get_num_color(count);
            sprintf(cell_content, "%d", count);
        }
    }
    else if (state_ptr->flags[i][j])
        strcpy(cell_content, FLAG);
    else
        strcpy(cell_content, PLACEHOLDER);

    printf("%s%s %s %s", cell_fg, cell_bg, cell_content, RESET);
}

void game_lose_footer(GameState *state_ptr)
{
    puts(FG_RED "YOU LOSE ..." RESET);
    sleep(2);
    reload_or_exit_footer(state_ptr);
}

void game_won_footer(GameState *state_ptr)
{
    puts(FG_GREEN "YOU WON ..." RESET);
    sleep(2);
    reload_or_exit_footer(state_ptr);
}

void reload_or_exit_footer(GameState *state_ptr)
{
    char answer;
    do
    {
        puts("Press \"R\" to reload or \"Q\" to quit ...");
        answer = tolower(getchar());
    } while (answer != 'r' && answer != 'q');

    switch (answer)
    {
    case 'r':
        start_game(state_ptr);
        break;

    case 'q':
        exit(0);
        break;
    }
}

char *get_num_color(int num)
{
    char *color_codes[] = {FG_GRAY, FG_BLUE, FG_RED, FG_GREEN, FG_PURPLE};
    return (num >= 0 && num <= 4) ? color_codes[num] : "";
}