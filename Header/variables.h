#pragma once

#include "screen.h"
#include "classes.h"
#include "macros.h"

// 初期値はWIN,DRAW,LOSEの値と被ってはいけない
extern int old_result_zun;

extern int zun_handle;

extern int chu_handle;

extern int deepest;

extern int countpattern;

extern int lowest;

extern Screen screen;

extern screen_state ScreenState;

extern float scale_change;

// 1メーターあたりドット数
extern float DPM;

extern int board_old[64];

extern int play_num_count;

// リアクションのためのもの
extern ForReaction for_reaction;

// ゲームをリスタートするかどうか
extern int restart;
