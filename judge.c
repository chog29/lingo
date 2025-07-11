#include "lingo.h"

/*単語一致判定のメイン関数*/
int judge_word_match(const char *input, const char *answer, char *display) {
    char clean_input[WORD_LENGTH + 1];
    bool match_results[WORD_LENGTH];
    
    /*入力の妥当性チェックと清浄化*/
    if (!validate_word_input(input, clean_input)) {
        return -1;
    }
    
    /*文字比較処理*/
    compare_characters(clean_input, answer, match_results);
    
    /*ヒント表示更新*/
    update_display_hints(clean_input, answer, display, match_results);
    
    /*ゲーム状態判定*/
    return determine_game_status(match_results, 0);
}

/*入力された単語の妥当性チェック*/
bool validate_word_input(const char *input, char *clean_input) {
    /*文字数チェック*/
    if (!check_word_length(input)) {
        return false;
    }
    
    /*英字チェック*/
    if (!validate_alphabetic(input)) {
        return false;
    }
    
    /*大文字変換*/
    convert_to_uppercase(input, clean_input);
    
    return true;
}

/*単語が5文字かチェック*/
bool check_word_length(const char *word) {
    return strlen(word) == WORD_LENGTH;
}

/*全て英字で構成されているかチェック*/
bool validate_alphabetic(const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (!isalpha(word[i])) {
            return false;
        }
    }
    return true;
}

/*文字列を大文字に変換*/
void convert_to_uppercase(const char *input, char *output) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        output[i] = toupper(input[i]);
    }
    output[WORD_LENGTH] = '\0';
}

/*入力単語と正解単語を文字ごとに比較*/
void compare_characters(const char *input, const char *answer, bool *match_results) {
    loop_character_positions(input, answer, match_results);
}

/*文字位置をループして比較処理*/
void loop_character_positions(const char *input, const char *answer, bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        bool is_match = match_position_check(input[i], answer[i]);
        store_match_results(match_results, i, is_match);
    }
}

/*指定位置の文字が一致するかチェック*/
bool match_position_check(char input_char, char answer_char) {
    return input_char == answer_char;
}

/*一致結果を配列に格納*/
void store_match_results(bool *match_results, int position, bool is_match) {
    match_results[position] = is_match;
}

/*表示用のヒントを更新*/
void update_display_hints(const char *input, const char *answer, char *display, bool *match_results) {
    update_correct_positions(display, answer, match_results);
    keep_blanks_for_wrong(display, match_results);
}

/*正解位置の文字を表示単語に反映*/
void update_correct_positions(char *display, const char *answer, bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (match_results[i]) {
            display[i] = answer[i];
        }
    }
}

/*不正解位置を空白のまま保持*/
void keep_blanks_for_wrong(char *display, bool *match_results) {
    int i;
    for (i = 0; i < WORD_LENGTH; i++) {
        if (!match_results[i]) {
            /* 正解でない位置は既存の値を保持（通常は'_'） */
            /* 特に何もしない - 既存の値を保持 */
        }
    }
}

/*ゲームの状態を判定*/
int determine_game_status(bool *match_results, int attempt_count) {
    bool is_perfect_match = check_perfect_match(match_results);
    return set_win_lose_status(is_perfect_match, attempt_count);
}

/*全ての文字が一致しているかチェック*/
bool check_perfect_match(bool *match_results) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!match_results[i]) {
            return false;
        }
    }
    return true;
}

/*試行回数を更新*/
void update_attempt_counter(int *attempt_count) {
    (*attempt_count)++;
}

/*勝敗状態を設定*/
int set_win_lose_status(bool is_perfect_match, int attempt_count) {
    if (is_perfect_match) {
        return 1;  /*勝利*/
    }
    
    if (attempt_count >= MAX_ATTEMPTS) {
        return -1;  /*敗北*/
    }
    
    return 0;  /*継続*/
}