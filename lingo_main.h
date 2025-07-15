#ifndef LINGO_MAIN_H
#define LINGO_MAIN_H

#include "lingo_common.h"

/*1. 全体制御モジュール*/
int main(int argc, char *argv[]);
bool validate_arguments(int argc, char *argv[]);
bool check_command_format(const char *command);
void display_error_message(void);
int initialize_system(GameData *game_data);
int init_ncurses(void);
int load_word_data(GameData *game_data);
void init_game_variables(GameData *game_data);
void run_main_loop(GameData *game_data);
void manage_screen_transition(GameData *game_data);
void update_game_state(GameData *game_data);
void cleanup_and_exit(GameData *game_data);
void end_ncurses(void);
void free_memory(GameData *game_data);
void reset_game_state(GameData *game_data);


#endif 
