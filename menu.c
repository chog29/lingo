#include "lingo.h"

/*メニュー画面表示*/
void show_menu_screen(GameData *game_data) {
    clear_screen_buffer();
    display_menu_items(game_data);
    
    int key = handle_menu_input(game_data);
    if (key != -1) {
        process_menu_selection(game_data, key);
    }
}

/*メニュー項目表示*/
void display_menu_items(GameData *game_data) {
    draw_title();
    draw_menu_options();
    highlight_current_option(game_data);
}

/*タイトル描画*/
void draw_title(void) {
    mvprintw(2, 25, "LINGO GAME");
    mvprintw(3, 25, "==========");
}

/*メニュー選択肢描画*/
void draw_menu_options(void) {
    mvprintw(6, 28, "START");
    mvprintw(8, 28, "HELP");
    mvprintw(10, 28, "EXIT");
    mvprintw(12, 28, "KAKIN");
}

/*現在選択項目ハイライト*/
void highlight_current_option(GameData *game_data) {
    int y_pos = 6 + (game_data->current_menu_selection * 2);
    mvprintw(y_pos, 26, ">");
    mvprintw(y_pos, 34, "<");
}

/*メニュー入力処理*/
int handle_menu_input(GameData *game_data) {
    int key = get_key_input();
    
    if (validate_menu_key(key)) {
        return key;
    }
    
    return -1;
}

/*キー入力取得*/
int get_key_input(void) {
    return getch();
}

/*メニュー有効キー検証*/
bool validate_menu_key(int key) {
    return (key == KEY_UP || key == KEY_DOWN || key == '\n' || key == KEY_ENTER);
}

/*メニュー選択処理*/
void process_menu_selection(GameData *game_data, int key) {
    if (key == KEY_UP || key == KEY_DOWN) {
        move_cursor_up_down(game_data, key);
    } else if (key == '\n' || key == KEY_ENTER) {
        execute_selected_option(game_data);
    }
}

/*カーソル上下移動*/
void move_cursor_up_down(GameData *game_data, int key) {
    if (key == KEY_UP) {
        game_data->current_menu_selection--;
        if (game_data->current_menu_selection < 0) {
            game_data->current_menu_selection = MENU_ITEMS - 1;
        }
    } else if (key == KEY_DOWN) {
        game_data->current_menu_selection++;
        if (game_data->current_menu_selection >= MENU_ITEMS) {
            game_data->current_menu_selection = 0;
        }
    }
}

/*選択項目実行*/
void execute_selected_option(GameData *game_data) {
    switch (game_data->current_menu_selection) {
        case 0:  /*START*/
            set_next_screen(game_data, GAME_STATE);
            break;
        case 1:  /*HELP*/
            set_next_screen(game_data, HELP_STATE);
            break;
        case 2:  /*EXIT*/
            set_next_screen(game_data, EXIT_STATE);
            break;
        case 3:  /*KAKIN*/
            set_next_screen(game_data, KAKIN_STATE);
            break;
    }
}

/*次画面設定*/
void set_next_screen(GameData *game_data, ScreenState next_state) {
    game_data->screen_state = next_state;
}