#ifndef LINGO_HELP_H
#define LINGO_HELP_H

#include "lingo_common.h"

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

#endif
