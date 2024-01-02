#ifndef ms_constants
#define ms_constants

#define SELECT "\x1B[30m\x1B[47m"

#define FG_GRAY "\e[0;90m"
#define FG_RED "\e[0;31m"
#define FG_GREEN "\e[0;32m"
#define FG_BLUE "\e[0;34m"
#define FG_PURPLE "\e[0;35m"
#define FG_YELLOW "\e[0;93m"

#define RESET "\x1B[0m"
#define NL "\n"

#define FLAG "♠"
#define BOMB "Ơ"
#define PLACEHOLDER "-"

#define MAX_MINES_PER_COLUMN 3

enum step
{
    REGISTER_PAGE,
    MENU_PAGE,
    EDIT_PROFILE_PAGE,
    GAME_PAGE_PLAYING,
    GAME_PAGE_LOST,
    GAME_PAGE_WON
};

#endif