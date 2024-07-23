#include "screen.h"
#include "classes.h"
#include "macros.h"

// 初期値はWIN,DRAW,LOSEの値と被ってはいけない
int old_result_zun = -10;

int zun_handle;

int chu_handle;

int deepest;

int countpattern = 0;

int lowest;

Screen screen;

screen_state ScreenState;

float scale_change = 3.0;

// 1メーターあたりドット数
float DPM = 2133.0f / scale_change;

int board_old[64] = { WHITE };

int play_num_count = 0;

// リアクションのためのもの
ForReaction for_reaction;

// ゲームをリスタートするかどうか
int restart = 0;
