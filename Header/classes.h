#pragma once

typedef struct screen_state
{
    int board[64];
    int RateNum[2][4];
} screen_state;

class Setting
{
public:
    int screen;
    int init;
    int end;
    int play_type;
};

// ���A�N�V�����̂��߂ɕK�v�Ȓ��O�ɋN���������Ƃ��L�^
class ForReaction
{
public:
    int position = -1;

    // ���O�����ЂƂO
    int position_old = -1;

    int color;
    int zun_said;
    int chu_said;
};
