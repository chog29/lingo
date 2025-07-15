#ifndef LINGO_COMMON_H
#define LINGO_COMMON_H

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

#endif