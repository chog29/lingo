#ifndef LINGO_JUDGE_H
#define LINGO_JUDGE_H

#include "lingo_common.h"

/*5. 単語判定処理モジュール*/
int judge_word_match(const char *input, const char *answer, char *display);
bool validate_word_input(const char *input, char *clean_input);
bool check_word_length(const char *word);
bool validate_alphabetic(const char *word);
void convert_to_uppercase(const char *input, char *output);
void compare_characters(const char *input, const char *answer, bool *match_results);
void loop_character_positions(const char *input, const char *answer, bool *match_results);
bool match_position_check(char input_char, char answer_char);
void store_match_results(bool *match_results, int position, bool is_match);
void update_display_hints(const char *input, const char *answer, char *display, bool *match_results);
void update_correct_positions(char *display, const char *answer, bool *match_results);
void keep_blanks_for_wrong(char *display, bool *match_results);
int determine_game_status(bool *match_results, int attempt_count);
bool check_perfect_match(bool *match_results);
void update_attempt_counter(int *attempt_count);
int set_win_lose_status(bool is_perfect_match, int attempt_count);

#endif 