#ifndef LINGO_GAME_H
#define LINGO_GAME_H

#include "lingo_common.h"

/*4. ゲームプレイ制御モジュール*/
void run_game_screen(GameData *game_data);
void initialize_game_round(GameData *game_data);
void choose_random_word(GameData *game_data);
void reset_attempt_count(GameData *game_data);
void prepare_display_hints(GameData *game_data);
void display_game_interface(GameData *game_data);
void draw_answer_blanks(GameData *game_data);
void show_attempt_count(GameData *game_data);
void draw_input_prompt(void);
int handle_word_input(GameData *game_data, char *input_word);
void get_word_input(char *input_buffer);
bool validate_input_format(const char *input);
void process_guess(GameData *game_data, const char *input_word);
int compare_with_answer(const char *input, const char *answer);
void update_hint_display(GameData *game_data, const char *input_word);
void increment_attempt(GameData *game_data);
bool check_game_end(GameData *game_data);
bool check_correct_answer(GameData *game_data);
bool check_max_attempts(GameData *game_data);
void display_result_message(GameData *game_data);

#endif
