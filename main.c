#include "lingo.h"

int main(int argc, char *argv[]) {
    GameData game_data;

    setlocale(LC_ALL, "");
    if (!validate_arguments(argc, argv)) {
        return 1;
    }
    if (initialize_system(&game_data) != 0) {
        return 1;
    }
    run_main_loop(&game_data);
    cleanup_and_exit(&game_data);

    return 0;
}

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

bool check_command_format(const char *command) {
    return strcmp(command, "./lingo") == 0;
}

void display_error_message(void) {
    printf("コマンドが間違っています\n");
}

int initialize_system(GameData *game_data) {
    if (init_ncurses() != 0) {
        return -1;
    }
    if (load_word_data(game_data) != 0) {
        end_ncurses();
        return -1;
    }
    init_game_variables(game_data);
    return 0;
}

int init_ncurses(void) {
    if (initscr() == NULL) {
        return -1;
    }
    keypad(stdscr, TRUE);
    return 0;
}

int load_word_data(GameData *game_data) {
    int word_count = load_word_list(game_data->word_list);
    return (word_count > 0) ? 0 : -1;
}

void init_game_variables(GameData *game_data) {
    game_data->attempt_count = 0;
    game_data->current_menu_selection = 0;
    game_data->screen_state = MENU_STATE;
    game_data->hint_count = 1;
    game_data->game_won = false;
    srand(time(NULL));
}

void run_main_loop(GameData *game_data) {
    while (game_data->screen_state != EXIT_STATE) {
        manage_screen_transition(game_data);
        update_game_state(game_data);
    }
}

void manage_screen_transition(GameData *game_data) {
    switch (game_data->screen_state) {
        case MENU_STATE:
            show_menu_screen(game_data);
            break;
        case GAME_STATE:
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

void update_game_state(GameData *game_data) {
    refresh();
}

void cleanup_and_exit(GameData *game_data) {
    end_ncurses();
    free_memory(game_data);
}

void end_ncurses(void) {
    endwin();
}

void free_memory(GameData *game_data) {
    /*静的配列のため特に処理なし*/
}

void reset_game_state(GameData *game_data) {
    game_data->attempt_count = 0;
    game_data->game_won = false;
    /* display_wordを初期状態に戻す */
    for (int i = 0; i < WORD_LENGTH; i++) {
        game_data->display_word[i] = '_';
    }
    game_data->display_word[WORD_LENGTH] = '\0';
}