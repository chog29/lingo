#include "lingo.h"

int load_word_list(char word_list[][WORD_LENGTH + 1]){
    FILE *fp = open_answer_file();
    if (fp == NULL) {
        return -1;
    }
    int word_count;
    word_count = read_words_to_array(fp, word_list);
    close_file(fp);
    return word_count;
}

FILE* open_answer_file(void){
    return fopen(ANSWER_FILE, "r");
}

int read_words_to_array(FILE *fp, char word_list[][WORD_LENGTH + 1]){
    char buffer[100];
    int count = 0;
    while(fgets(buffer, sizeof(buffer), fp) != NULL && count < MAX_WORDS){
        buffer[strcspn(buffer, "\n")] = '\0';
        if(strlen(buffer) == WORD_LENGTH){
            strcpy(word_list[count], buffer);
            count++;
        }
    }
    /*printf("Loaded %d words from file.\n", count);*/
    return count;
}

void close_file(FILE *fp){
    if(fp != NULL){
        fclose(fp);
    }
}

void manage_game_state(GameData *game_data){
    init_attempt_counter(game_data);
    select_answer_word(game_data);
    setup_display_word(game_data);
}

void init_attempt_counter(GameData *game_data){
    game_data->attempt_count = 0;
}

void select_answer_word(GameData *game_data){
    int index;
    index = rand() % MAX_WORDS;
    strcpy(game_data->answer_word, game_data->word_list[index]);
}

void setup_display_word(GameData *game_data){
    game_data->display_word[0] = game_data->answer_word[0];
    for(int i = 1; i < WORD_LENGTH; i++){
        game_data->display_word[i] = '_';
    }
    game_data->display_word[WORD_LENGTH] = '\0';
}