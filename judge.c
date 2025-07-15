#include "lingo.h"

int judge_word_match(const char *input, const char *answer, char *display) {
    char clean_input[WORD_LENGTH + 1];
    bool match_results[WORD_LENGTH];
    if (!validate_word_input(input, clean_input)) {
        return -1;
    }
    compare_characters(clean_input, answer, match_results);
    update_display_hints(clean_input, answer, display, match_results);
    return determine_game_status(match_results, 0);
}

bool validate_word_input(const char *input, char *clean_input) {
    if (!check_word_length(input)) {
        return false;
    }
    if (!validate_alphabetic(input)) {
        return false;
    }
    convert_to_uppercase(input, clean_input);
    return true;
}

bool check_word_length(const char *word) {
    return strlen(word) == WORD_LENGTH;
}

bool validate_alphabetic(const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (!isalpha(word[i])) {
            return false;
        }
    }
    return true;
}

void convert_to_uppercase(const char *input, char *output) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        output[i] = toupper(input[i]);
    }
    output[WORD_LENGTH] = '\0';
}

void compare_characters(const char *input, const char *answer, bool *match_results) {
    loop_character_positions(input, answer, match_results);
}

void loop_character_positions(const char *input, const char *answer, bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        bool is_match = match_position_check(input[i], answer[i]);
        store_match_results(match_results, i, is_match);
    }
}

bool match_position_check(char input_char, char answer_char) {
    return input_char == answer_char;
}

void store_match_results(bool *match_results, int position, bool is_match) {
    match_results[position] = is_match;
}

void update_display_hints(const char *input, const char *answer, char *display, bool *match_results) {
    update_correct_positions(display, answer, match_results);
    keep_blanks_for_wrong(display, match_results);
}

void update_correct_positions(char *display, const char *answer, bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (match_results[i]) {
            display[i] = answer[i];
        }
    }
}

void keep_blanks_for_wrong(char *display, bool *match_results) {
    int i;
    for (i = 0; i < WORD_LENGTH; i++) {
        if (!match_results[i]) {
        }
    }
}

int determine_game_status(bool *match_results, int attempt_count) {
    bool is_perfect_match = check_perfect_match(match_results);
    return set_win_lose_status(is_perfect_match, attempt_count);
}

bool check_perfect_match(bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!match_results[i]) {
            return false;
        }
    }
    return true;
}

void update_attempt_counter(int *attempt_count) {
    (*attempt_count)++;
}

int set_win_lose_status(bool is_perfect_match, int attempt_count) {
    if (is_perfect_match) {
        return 1; 
    }
    if (attempt_count >= MAX_ATTEMPTS) {
        return -1;
    }
    return 0; 
}