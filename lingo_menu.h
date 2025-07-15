#ifndef LINGO_MENU_H
#define LINGO_MENU_H

#include "lingo_common.h"

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

#endif
