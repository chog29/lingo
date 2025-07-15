#include "lingo.h"

void run_game_screen(GameData *game_data){
    char input_word[WORD_LENGTH + 1];
    initialize_game_round(game_data);
    while(!check_game_end(game_data)){
        clear_screen_buffer();
        display_game_interface(game_data);
        if(handle_word_input(game_data, input_word) == 0){
            process_guess(game_data, input_word);
        }
    }
}

void initialize_game_round(GameData *game_data){
    choose_random_word(game_data);
    reset_attempt_count(game_data);
    prepare_display_hints(game_data);

    game_data->game_won = false;
    game_data->screen_state = GAME_STATE;
}

void choose_random_word(GameData *game_data){
    int index;

    index = rand() % MAX_WORDS;
    strcpy(game_data->answer_word, game_data->word_list[index]);

    /*mvprintw(0,0,"debug word: %s", game_data->answre_word)*/
}

void reset_attempt_count(GameData *game_data){
    game_data->attempt_count = 0;
}

void prepare_display_hints(GameData *game_data){
    int i;

    for(i = 0; i < WORD_LENGTH; i++){
        game_data->display_word[i] = '_';
    }
    game_data->display_word[WORD_LENGTH] = '\0';
    game_data->display_word[0] = game_data->answer_word[0];
    if(game_data->hint_count > 1){
        for(i = 1; i < game_data->hint_count && i < WORD_LENGTH; i++){
            game_data->display_word[i] = game_data->answer_word[i];
        }
    }
}

void display_game_interface(GameData *game_data){
    draw_answer_blanks(game_data);
    show_attempt_count(game_data);
    draw_input_prompt();
}

void draw_answer_blanks(GameData *game_data){
    int i;

    mvprintw(5, 20, "正解単語: ");
    for(i = 0; i < WORD_LENGTH; i++){
        mvprintw(5, 30 + i * 2, "%c", game_data->display_word[i]);
    }
}

void show_attempt_count(GameData *game_data){
    mvprintw(7, 20, "試行回数: %d/%d", game_data->attempt_count, MAX_ATTEMPTS);
}

void draw_input_prompt(void){
    mvprintw(10, 10, "5文字の英単語を入力してください: ");
}

int handle_word_input(GameData *game_data, char *input_word){
    set_cursor_position(10,45);
    get_word_input(input_word);
    if(validate_input_format(input_word)){
        return 0;
    }
    mvprintw(12, 10, "無効な入力です。5文字の英単語を入力してください。");
    mvprintw(13, 10, "何かキーを押して続行...");

    getch();
    return -1;
}

void get_word_input(char *input_buffer){
    getstr(input_buffer);
}

bool validate_input_format(const char *input){
    int i;

    if(strlen(input) != WORD_LENGTH){
        return false;
    }

    for(i = 0; i < WORD_LENGTH; i++){
        if(!isalpha(input[i])){
            return false;
        }
    }
    return true;
}

void process_guess(GameData *game_data, const char *input_word){
    char upper_input[WORD_LENGTH + 1];

    convert_to_uppercase(input_word, upper_input);
    if(strcmp(upper_input, game_data->answer_word) == 0){
        strcpy(game_data->display_word, game_data->answer_word);
        game_data->game_won = true;
        game_data->screen_state = WIN_STATE;
    }else{
        update_hint_display(game_data, upper_input);
    }
    increment_attempt(game_data);
}

int compare_with_answer(const char *input, const char *answer){
    return strcmp(input,answer);
}

void update_hint_display(GameData *game_data, const char *input_word){
    int i;

    for(i = 0; i < WORD_LENGTH; i++){
        if(input_word[i] == game_data->answer_word[i]){
            game_data->display_word[i] = game_data->answer_word[i];
        }
    }
}

void increment_attempt(GameData *game_data){
    game_data->attempt_count++;
}

bool check_game_end(GameData *game_data){
    if(game_data->game_won){
        return true;
    }
    if(check_max_attempts(game_data)){
        game_data->game_won = false;
        game_data->screen_state = LOSE_STATE;
        return true;
    }
    return false;
}

bool check_correct_answer(GameData *game_data){
    return strcmp(game_data->display_word, game_data->answer_word) == 0;
}

bool check_max_attempts(GameData *game_data){
    return game_data->attempt_count >= MAX_ATTEMPTS;
}

void display_result_message(GameData *game_data){
    clear_screen_buffer();

    if(game_data->game_won){
        mvprintw(10, 15, "おめでとうございます！正解です！");
    } else {
        mvprintw(10, 15, "残念！正解は %s でした", game_data->answer_word);
    }
    mvprintw(12, 15, "何かキーを押してメニューに戻る...");
    getch();
}