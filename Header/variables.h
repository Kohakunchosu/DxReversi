#pragma once

#include "screen.h"
#include "classes.h"
#include "macros.h"

// �����l��WIN,DRAW,LOSE�̒l�Ɣ���Ă͂����Ȃ�
extern int old_result_zun;

extern int zun_handle;

extern int chu_handle;

extern int deepest;

extern int countpattern;

extern int lowest;

extern Screen screen;

extern screen_state ScreenState;

extern float scale_change;

// 1���[�^�[������h�b�g��
extern float DPM;

extern int board_old[64];

extern int play_num_count;

// ���A�N�V�����̂��߂̂���
extern ForReaction for_reaction;

// �Q�[�������X�^�[�g���邩�ǂ���
extern int restart;
