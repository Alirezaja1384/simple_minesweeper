#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "constants.h"
#include "utils.h"
#include "etc.h"
#include "sync.h"
#include "logics.h"
#include "controls.h"
#include "visuals.h"

GameState state;

int main(int argc, char **argv)
{
    int size = argc > 1 ? atoi(argv[1]) : 8;

    initiate(&state, size);
    start_bad_things();

    while (1)
    {
        clear_screen();
        switch (state.step)
        {
        case REGISTER_PAGE:
            render_register_form(&state);
            break;

        case MENU_PAGE:
            render_menu(&state);
            break;

        case EDIT_PROFILE_PAGE:
            render_edit_profile(&state);
            break;

        case GAME_PAGE_PLAYING:
        case GAME_PAGE_WON:
        case GAME_PAGE_LOST:
            render_game(&state);
            break;

        default:
            puts("Invalid step!");
            exit(255);
            break;
        }
    }

    end_bad_things();
    return 0;
}
