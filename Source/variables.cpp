#include "screen.h"
#include "classes.h"
#include "macros.h"

// �����l��WIN,DRAW,LOSE�̒l�Ɣ���Ă͂����Ȃ�
int old_result_zun = -10;

int zun_handle;

int chu_handle;

int deepest;

int countpattern = 0;

int lowest;

Screen screen;

screen_state ScreenState;

float scale_change = 3.0;

// 1���[�^�[������h�b�g��
float DPM = 2133.0f / scale_change;

int board_old[64] = { WHITE };

int play_num_count = 0;

// ���A�N�V�����̂��߂̂���
ForReaction for_reaction;

// �Q�[�������X�^�[�g���邩�ǂ���
int restart = 0;
