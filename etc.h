#ifndef ms_etc
#define ms_etc

#include <stdbool.h>
#include "constants.h"

struct game_stats
{
    int wins;
    int losses;
};

struct game_state
{
    int size;
    char *username;

    bool show_all;

    enum step step;
    struct game_stats stats;

    int total_mines;

    int total_flags;
    int remaining_flags;

    int remaining_sweeps;
    int current_position[2];

    bool **mines;
    bool **flags;
    bool **swept;
};

typedef struct game_state GameState;

#endif