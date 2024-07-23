#pragma once

#include <list>
#include <Box2D/Box2D.h>

// �v���C���[�̃C���v�b�g���󂯎��֐�
namespace PlayerInput
{
    // �v���C���[���N���b�N�����}�X�ڂ̍��W���擾 (x,y�Ƃ���0-8)
    int ClickLocation(int *x, int *y);

    // �v���C���[���獇�@�I�ȃQ�[���I���𓾂�
    int GetChoice(int board[], char color);

    // �Q�[���̍Œ��A�v���C���[�̓��͂ɉ����ĉ�������̕K�v�ȏ���������
    void ProcessInput();

    // ProcessInput���Ăяo���Ȃ����莞�ԑ҂�
    void WaitTimer(int time);

    // ProcessInput���Ăяo���Ȃ���L�[���͂�҂�
    void WaitKey();

    // restart �ϐ��̒l���P�̎��ɏI������
    void WaitKeyWithRestart();

    // �v���C�^�C�v��I��������B�߂�l�̓v���C�^�C�v
    int ChosePlayType();
};

namespace SomePlayType
{
    void PlayerVsPlayer();

    void PlayerVsAI();

    void AIVsAI();
};

// ��������̃T�E���h���Đ�����֐�
namespace Sound
{
    namespace Effect
    {
        // �G�t�F�N�g�̍Đ�������
        int Play(int play_type);
    }

    namespace Zunda
    {
        // ���񂾂����҂�
        int Wait();

        // 2�v���C�ڈȍ~�A�Q�[���J�n���ɂ��񂾂���ɉ�������ׂ点�邽�߂̂���
        int Start();

        // ���񂾂���̍Đ�
        void Play(int play_type);
    };

    namespace Usagi
    {
        // ��������҂�
        void Wait();

        // �������̍Đ�
        void Play(int play_type);
    };

    // �Q�[���I�����ɏo�͂��鉹���������
    namespace End
    {
        // ai vs player �̂Ƃ�
        void EndVoice1(int board[]);

        // player vs player �̂Ƃ�
        void EndVoice2(int board[]);

        // ai vs ai �̂Ƃ�
        void EndVoice3(int board[]);
    };

    namespace Start
    {
        void StartVoice1();

        void StartVoice2();

        void StartVoice3();
    };

    // ���񂾂����璆���������̃��A�N�V�����B
    // �΂�u��������ɌĂяo���A����ׂ�I���܂Ŋ֐��̏I����҂K�v�͂Ȃ��B
    namespace Reaction
    {
        // ai vs player
        void Voice1();

        // player vs player
        void Voice2();

        // ai vs ai
        void Voice3();
    }
};

// ���z�̉�ʂɉ�����\������֐�
namespace DispV
{
    // RateDp�Ŏg����֐��ŁA���z��ʏ�ɂł�����������\�����邽�߂̂��́B�߂�l�̓n���h���B
    std::list<int> DispNum(int num, char color, int locate);

    // ���Ή����Ƃ����̂����z��ʂɕ\������B�߂�l�̓n���h���B
    std::list<int> DispRate(int board[], int reset);

    // ���z��ʏ�ɐ΂�u���B�߂�l�̓n���h���B
    int PutStone(int x, int y, char color);

    int PutPoint(int x, int y, int color);

    // ai vs player ���[�h�ɂ�����
    int PrintBoard1(int board[], int reset, int before_turn);

    // player vs player ���[�h�ɂ�����
    void PrintBoard2(int board[], int reset, int before_turn);

    void PrintBoard3(int board[], int reset, int before_turn);
};

// �����̉�ʂɉ�����\������֐�
namespace DispR
{
    // �Ֆʂ̏�Ԃ����ۂ̉�ʏ�ɕ\������
    int PrintBoard(int board[], int reset, int before_turn);

    // �X�^�[�g��ʂ�\������
    int Start();

    // �{�^���������ꂽ��Ԃ̃X�^�[�g��ʂ�\������
    int StartPressed();
};

// �������̏�ʂɂ����ď��������s���֐�
namespace Init
{
    //  ���񂾂��� vs �l �Q�[���J�n���̏�����������
    int Game1(int board_new[]);

    int Game2(int board_new[]);

    int Game3(int board_new[]);

    // �v���O���������s����Ă����ɕK�v�ȏ��������s��
    int Program();
};

// �I�Z���Q�[�����̂��̂ɂ������悤�ȗl�X�Ȋ֐�
namespace Othello
{
    namespace Basic
    {
        void ChangeBoard(int board[64], int color, int position);

        int ExchangeXY(int x, int y);

        int CountColor(int *board, int color);

        int PutAble(int *board, int color, int position);

        int PutAbleAll(int board[], int color);

        void BoardCpy(int *board1, int *board2);

        void InitBoard(int *board);

        int IsEnd(int board[]);

        int BoardCmp(int board1[64], int board2[64]);
    };

    namespace AI
    {
        namespace Chose
        {
            int Strong(int board[], char bw, int *count, int total);

            int Weak(int board[], char color);

            int Rand(int board[], int color);

            int Most(int board[], int color);
        }

        int ExpandNode(int turn, int board[], int boardex[][64]);

        int MinMaxConer(int board[], int turn, int depth);

        int MinMaxMost(int board[], int turn, int depth);

        int AlphaBetaMost(int board[], int turn, int depth, int alpha, int beta);

        int AlphaBetaConer(int board[], int turn, int depth, int alpha, int beta);

        void EvalueCpy(int board[]);

        int EvalueCalcMost(int board[]);

        int EvalueCalcConer(int board[]);
    };
};

// �ėp�I�ȋ@�\���������֐�
namespace Utility
{
    namespace Arr
    {
        int Max(int *a, int yo);

        int MaxIndex(int *a, int yo);

        // �ő�l�ƂȂ�v�f����������ꍇ�A�����̗v�f�̂�����̗v�f�̔ԍ��������_���ɕԂ�
        int MaxIndexRand(int arr[], int num);

        int Min(int *a, int yo);

        float Ave(int arr[], int n);

        int Sum(int arr[], int n);
    };

    int RandBetween(int minimum, int maximum);

    float RandBetweenF(float min, float max);

}

// �������Z�Ɋ֘A����֐�
namespace Physics
{
    b2Body *CreateStaticBox(float xl, float yl, float xp, float yp, b2World *world);

    b2Body *CreateCircle(float r, float x, float y, b2World *world);

    int ExX(float x);

    int ExY(float y);
};

namespace Animation
{
    void StoneDrop1(int board_new[], int board_old[], int time);

    void StoneDrop2(int board_old[], int time);
};
