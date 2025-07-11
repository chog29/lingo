#include "lingo.h"

/*ゲーム画面実行*/
void run_game_screen(GameData *game_data) {
    initialize_game_round(game_data);
    
    while (!check_game_end(game_data)) {
        clear_screen_buffer();
        display_game_interface(game_data);
        
        char input_word[WORD_LENGTH + 1];
        if (handle_word_input(game_data, input_word) == 0) {
            process_guess(game_data, input_word);
        }
    }
}

/*ゲームラウンド初期化*/
void initialize_game_round(GameData *game_data) {
    choose_random_word(game_data);
    reset_attempt_count(game_data);
    prepare_display_hints(game_data);
}

/*ランダム単語選択*/
void choose_random_word(GameData *game_data) {
    int index = rand() % MAX_WORDS;
    strcpy(game_data->answer_word, game_data->word_list[index]);
}

/*試行回数リセット*/
void reset_attempt_count(GameData *game_data) {
    game_data->attempt_count = 0;
}

/*ヒント表示準備*/
void prepare_display_hints(GameData *game_data) {
    game_data->display_word[0] = game_data->answer_word[0];
    for (int i = 1; i < WORD_LENGTH; i++) {
        game_data->display_word[i] = '_';
    }
    game_data->display_word[WORD_LENGTH] = '\0';
}

/*ゲームインターフェース表示*/
void display_game_interface(GameData *game_data) {
    draw_answer_blanks(game_data);
    show_attempt_count(game_data);
    draw_input_prompt();
}

/*解答欄描画*/
void draw_answer_blanks(GameData *game_data) {
    mvprintw(5, 20, "正解単語: ");
    for (int i = 0; i < WORD_LENGTH; i++) {
        mvprintw(5, 30 + i * 2, "%c", game_data->display_word[i]);
    }
}

/*試行回数表示*/
void show_attempt_count(GameData *game_data) {
    mvprintw(7, 20, "試行回数: %d/%d", game_data->attempt_count, MAX_ATTEMPTS);
}

/*入力プロンプト描画*/
void draw_input_prompt(void) {
    mvprintw(10, 10, "5文字の英単語を入力してください: ");
}

/*単語入力処理*/
int handle_word_input(GameData *game_data, char *input_word) {
    set_cursor_position(10, 45);
    get_word_input(input_word);
    
    if (validate_input_format(input_word)) {
        return 0;
    }
    
    mvprintw(12, 10, "無効な入力です。5文字の英単語を入力してください。");
    mvprintw(13, 10, "何かキーを押して続行...");
    getch();
    return -1;
}

/*単語入力取得*/
void get_word_input(char *input_buffer) {
    getstr(input_buffer);
}

/*入力形式検証*/
bool validate_input_format(const char *input) {
    if (strlen(input) != WORD_LENGTH) {
        return false;
    }
    
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!isalpha(input[i])) {
            return false;
        }
    }
    
    return true;
}

/*推測処理*/
void process_guess(GameData *game_data, const char *input_word) {
    char upper_input[WORD_LENGTH + 1];
    convert_to_uppercase(input_word, upper_input);
    
    update_hint_display(game_data, upper_input);
    increment_attempt(game_data);
}

/*正解との比較*/
int compare_with_answer(const char *input, const char *answer) {
    return strcmp(input, answer);
}

/*ヒント表示更新*/
void update_hint_display(GameData *game_data, const char *input_word) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (input_word[i] == game_data->answer_word[i]) {
            game_data->display_word[i] = game_data->answer_word[i];
        }
    }
}

/*試行回数増加*/
void increment_attempt(GameData *game_data) {
    game_data->attempt_count++;
}

/*ゲーム終了チェック*/
bool check_game_end(GameData *game_data) {
    if (check_correct_answer(game_data)) {
        game_data->game_won = true;
        game_data->screen_state = WIN_STATE;
        return true;
    }
    
    if (check_max_attempts(game_data)) {
        game_data->game_won = false;
        game_data->screen_state = LOSE_STATE;
        return true;
    }
    
    return false;
}

/*正解チェック*/
bool check_correct_answer(GameData *game_data) {
    return strcmp(game_data->display_word, game_data->answer_word) == 0;
}

/*最大試行回数チェック*/
bool check_max_attempts(GameData *game_data) {
    return game_data->attempt_count >= MAX_ATTEMPTS;
}

/*結果メッセージ表示*/
void display_result_message(GameData *game_data) {
    clear_screen_buffer();
    
    if (game_data->game_won) {
        mvprintw(10, 15, "おめでとうございます！正解です！");
    } else {
        mvprintw(10, 15, "残念！正解は %s でした", game_data->answer_word);
    }
    
    mvprintw(12, 15, "何かキーを押してメニューに戻る...");
    getch();
}