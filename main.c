#include "lingo.h"

/*メイン関数*/
int main(int argc, char *argv[]) {
    GameData game_data;

    setlocale(LC_ALL, "");
    
    /*引数の検証*/
    if (!validate_arguments(argc, argv)) {
        return 1;
    }
    
    /*システム初期化*/
    if (initialize_system(&game_data) != 0) {
        return 1;
    }
    
    /*メインループ実行*/
    run_main_loop(&game_data);
    
    /*終了処理*/
    cleanup_and_exit(&game_data);
    
    return 0;
}

/*コマンドライン引数検証*/
bool validate_arguments(int argc, char *argv[]) {
    if (argc != 2) {
        display_error_message();
        return false;
    }
    
    if (!check_command_format(argv[0])) {
        display_error_message();
        return false;
    }
    
    return true;
}

/*コマンドフォーマットチェック*/
bool check_command_format(const char *command) {
    return strcmp(command, "./lingo") == 0;
}

/*エラーメッセージ表示*/
void display_error_message(void) {
    printf("コマンドが間違っています\n");
}

/*システム初期化*/
int initialize_system(GameData *game_data) {
    /*ncurses初期化*/
    if (init_ncurses() != 0) {
        return -1;
    }
    
    /*単語データ読み込み*/
    if (load_word_data(game_data) != 0) {
        end_ncurses();
        return -1;
    }
    
    /*ゲーム変数初期化*/
    init_game_variables(game_data);
    
    return 0;
}

/*ncurses初期化*/
int init_ncurses(void) {
    if (initscr() == NULL) {
        return -1;
    }
    
    keypad(stdscr, TRUE);
    return 0;
}

/*単語データ読み込み*/
int load_word_data(GameData *game_data) {
    int word_count = load_word_list(game_data->word_list);
    return (word_count > 0) ? 0 : -1;
}

/*ゲーム変数初期化*/
void init_game_variables(GameData *game_data) {
    game_data->attempt_count = 0;
    game_data->current_menu_selection = 0;
    game_data->screen_state = MENU_STATE;
    game_data->hint_count = 1;
    game_data->game_won = false;
    
    /*乱数初期化*/
    srand(time(NULL));
}

/*メインループ実行*/
void run_main_loop(GameData *game_data) {
    while (game_data->screen_state != EXIT_STATE) {
        manage_screen_transition(game_data);
        update_game_state(game_data);
    }
}

/*画面遷移管理*/
void manage_screen_transition(GameData *game_data) {
    switch (game_data->screen_state) {
        case MENU_STATE:
            show_menu_screen(game_data);
            break;
        case GAME_STATE:
            /* ゲーム開始前に状態を確実にリセット */
            if (game_data->attempt_count == 0 && !game_data->game_won) {
                initialize_game_round(game_data);
            }
            run_game_screen(game_data);
            break;
        case HELP_STATE:
            show_help_screen();
            game_data->screen_state = MENU_STATE;
            break;
        case KAKIN_STATE:
            show_kakin_screen(game_data);
            game_data->screen_state = MENU_STATE;
            break;
        case WIN_STATE:
        case LOSE_STATE:
            display_result_message(game_data);
            /* ゲーム終了後に状態をリセット */
            reset_game_state(game_data);
            game_data->screen_state = MENU_STATE;
            break;
        default:
            break;
    }
}

/*ゲーム状態更新*/
void update_game_state(GameData *game_data) {
    refresh();
}

/*終了処理とクリーンアップ*/
void cleanup_and_exit(GameData *game_data) {
    end_ncurses();
    free_memory(game_data);
}

/*ncurses終了*/
void end_ncurses(void) {
    endwin();
}

/*メモリ解放*/
void free_memory(GameData *game_data) {
    /*静的配列のため特に処理なし*/
}

/* ゲーム状態リセット関数を追加 */
void reset_game_state(GameData *game_data) {
    game_data->attempt_count = 0;
    game_data->game_won = false;
    
    /* display_wordを初期状態に戻す */
    for (int i = 0; i < WORD_LENGTH; i++) {
        game_data->display_word[i] = '_';
    }
    game_data->display_word[WORD_LENGTH] = '\0';
}