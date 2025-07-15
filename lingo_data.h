#ifndef LINGO_DATA_H
#define LINGO_DATA_H

#include "lingo_common.h"

/*2. データ管理モジュール*/
int load_word_list(char word_list[][WORD_LENGTH + 1]);
FILE* open_answer_file(void);
int read_words_to_array(FILE *fp, char word_list[][WORD_LENGTH + 1]);
void close_file(FILE *fp);
void manage_game_state(GameData *game_data);
void init_attempt_counter(GameData *game_data);
void select_answer_word(GameData *game_data);
void setup_display_word(GameData *game_data);

#endif 