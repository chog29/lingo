#include "lingo.h"

/*ヘルプ画面表示*/
void show_help_screen(void) {
    clear_screen_buffer();
    display_game_rules();
    wait_for_return_key();
}

/*ゲームルール表示*/
void display_game_rules(void) {
    mvprintw(2, 10, "=== LINGO GAME ヘルプ ===");
    mvprintw(4, 5, "【ゲームの目的】");
    mvprintw(5, 5, "隠された5文字の英単語を当てるゲームです。");
    mvprintw(7, 5, "【ルール】");
    mvprintw(8, 5, "1. 最初の1文字がヒントとして表示されます");
    mvprintw(9, 5, "2. 5文字の英単語を入力してください");
    mvprintw(10, 5, "3. 正しい位置にある文字は次回以降も表示されます");
    mvprintw(11, 5, "4. 5回以内に正解を当ててください");
    mvprintw(13, 5, "【操作方法】");
    mvprintw(14, 5, "↑↓キー: メニュー選択");
    mvprintw(15, 5, "Enterキー: 決定");
    mvprintw(16, 5, "英字入力: 単語入力");
    mvprintw(18, 5, "【勝利条件】");
    mvprintw(19, 5, "5回以内に正解の英単語を当てること");
    mvprintw(21, 5, "【課金機能】");
    mvprintw(22, 5, "課金することで追加のヒント文字を表示できます");
}

/*メニューに戻るキー入力待機*/
void wait_for_return_key(void) {
    mvprintw(24, 10, "メニューに戻るには何かキーを押してください...");
    refresh();
    getch();
}

/*課金画面表示*/
void show_kakin_screen(GameData *game_data) {
    clear_screen_buffer();
    display_kakin_interface();
    
    if (simulate_payment_process()) {
        add_hint_characters(game_data);
    }
    
    mvprintw(15, 10, "何かキーを押してメニューに戻る...");
    refresh();
    getch();
}

/*課金インターフェース表示*/
void display_kakin_interface(void) {
    mvprintw(3, 15, "=== 課金===");
    mvprintw(5, 10, "追加のヒント文字を購入できます");
    mvprintw(7, 10, "価格: ¥100,000");
    mvprintw(8, 10, "効果: 正解単語の2文字目も表示されます");
    mvprintw(12, 10, "課金しますか？ (y/n): ");
}

/*支払い処理シミュレート*/
bool simulate_payment_process(void) {
    int input = getch();
    
    if (input == 'y' || input == 'Y') {
        mvprintw(13, 10, "課金処理中...");
        refresh();
        
        /*演出のための待機*/
        for (int i = 0; i < 1000000000; i++) {
            /*何もしない（待機処理）*/
        }
        
        mvprintw(14, 10, "課金が完了しました！");
        refresh();
        return true;
    }
    
    mvprintw(13, 10, "課金をキャンセルしました");
    refresh();
    return false;
}

/*ヒント文字数追加*/
void add_hint_characters(GameData *game_data) {
    game_data->hint_count++;
    
    /*2文字目も表示するように設定*/
    if (strlen(game_data->answer_word) >= 2) {
        game_data->display_word[1] = game_data->answer_word[1];
    }
    
    mvprintw(16, 10, "ヒントが追加されました！");
    mvprintw(17, 10, "2文字目も表示されるようになります");
}

/*画面制御ユーティリティ*/
void screen_control_utils(void) {
    clear_screen_buffer();
    refresh_display();
}

/*画面バッファクリア*/
void clear_screen_buffer(void) {
    clear();
}

/*画面表示更新*/
void refresh_display(void) {
    refresh();
}

/*カーソル位置設定*/
void set_cursor_position(int y, int x) {
    move(y, x);
}
