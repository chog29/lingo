#ifndef LINGO_H
#define LINGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>

/*定数定義*/
#define MAX_WORDS 30
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 5
#define MENU_ITEMS 4
#define ANSWER_FILE "answer.txt"

/*画面状態の列挙型*/
typedef enum {
    MENU_STATE,
    GAME_STATE,
    HELP_STATE,
    KAKIN_STATE,
    EXIT_STATE,
    WIN_STATE,
    LOSE_STATE
} ScreenState;

/*ゲームデータ構造体*/
typedef struct {
    char word_list[MAX_WORDS][WORD_LENGTH + 1];
    char answer_word[WORD_LENGTH + 1];
    char display_word[WORD_LENGTH + 1];
    int attempt_count;
    int current_menu_selection;
    ScreenState screen_state;
    int hint_count;
    bool game_won;
} GameData;

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

/*2. データ管理モジュール*/
int load_word_list(char word_list[][WORD_LENGTH + 1]);
FILE* open_answer_file(void);
int read_words_to_array(FILE *fp, char word_list[][WORD_LENGTH + 1]);
void close_file(FILE *fp);
void manage_game_state(GameData *game_data);
void init_attempt_counter(GameData *game_data);
void select_answer_word(GameData *game_data);
void setup_display_word(GameData *game_data);

/*3. メニュー画面制御モジュール*/
void show_menu_screen(GameData *game_data);
void display_menu_items(GameData *game_data);
void draw_title(void);
void draw_menu_options(void);
void highlight_current_option(GameData *game_data);
int handle_menu_input(GameData *game_data);
int get_key_input(void);
bool validate_menu_key(int key);
void process_menu_selection(GameData *game_data, int key);
void move_cursor_up_down(GameData *game_data, int key);
void execute_selected_option(GameData *game_data);
void set_next_screen(GameData *game_data, ScreenState next_state);

/*4. ゲーム画面制御モジュール*/
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

/*6. 補助機能モジュール*/
void show_help_screen(void);
void display_game_rules(void);
void wait_for_return_key(void);
void show_kakin_screen(GameData *game_data);
void display_kakin_interface(void);
bool simulate_payment_process(void);
void add_hint_characters(GameData *game_data);
void screen_control_utils(void);
void clear_screen_buffer(void);
void refresh_display(void);
void set_cursor_position(int y, int x);

#endif /*LINGO_H*/