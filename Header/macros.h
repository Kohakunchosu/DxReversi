#pragma once

// ずんだもん音声
#define ZUN_YOUKOSO 0
#define ZUN_WIN 1
#define ZUN_LOSE 2
#define ZUN_DRAW 3
#define ZUN_CONER 4
#define ZUN_AFTER_LOSE_0 5
#define ZUN_AFTER_LOSE_1 6
#define ZUN_AFTER_WIN 7
#define ZUN_AFTER_DRAW 8
// ai vs ai
#define _3_START_ZUN1 9
#define _3_END_ZUN1 10
#define _3_END_ZUN2 11
#define _3_END_ZUN3 12
// player vs player
#define _2_START_ZUN1 13
#define _2_END_ZUN1 14
#define _2_END_ZUN2 15
#define _2_END_ZUN3 16

// 中国うさぎ音声
// ai vs ai
#define _3_START_CHU1 0
#define _3_END_CHU1 1
#define _3_END_CHU2 2
#define _3_END_CHU3 3
#define _3_REACTION_CHU1 5
// player vs player
#define _2_START_CHU1 4

// ゲーム結果
#define DRAW 0
#define WIN 1
#define LOSE 2

// 石の色について
#define BLACK -1
#define WHITE 1

// 効果音種類
#define PUT_SOUND 0
#define MOVE_SOUND 1

// ゲームプレイタイプ
#define AI_VS_PLAYER 0
#define PLAYER_VS_PLAYER 1
#define AI_VS_AI 2