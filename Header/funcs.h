#pragma once

#include <list>
#include <Box2D/Box2D.h>

// プレイヤーのインプットを受け取る関数
namespace PlayerInput
{
    // プレイヤーがクリックしたマス目の座標を取得 (x,yともに0-8)
    int ClickLocation(int *x, int *y);

    // プレイヤーから合法的なゲーム選択を得る
    int GetChoice(int board[], char color);

    // ゲームの最中、プレイヤーの入力に応じて何かしらの必要な処理をする
    void ProcessInput();

    // ProcessInputを呼び出しながら一定時間待つ
    void WaitTimer(int time);

    // ProcessInputを呼び出しながらキー入力を待つ
    void WaitKey();

    // restart 変数の値が１の時に終了する
    void WaitKeyWithRestart();

    // プレイタイプを選択させる。戻り値はプレイタイプ
    int ChosePlayType();
};

namespace SomePlayType
{
    void PlayerVsPlayer();

    void PlayerVsAI();

    void AIVsAI();
};

// 何かしらのサウンドを再生する関数
namespace Sound
{
    namespace Effect
    {
        // エフェクトの再生をする
        int Play(int play_type);
    }

    namespace Zunda
    {
        // ずんだもんを待つ
        int Wait();

        // 2プレイ目以降、ゲーム開始時にずんだもんに何かしゃべらせるためのもの
        int Start();

        // ずんだもんの再生
        void Play(int play_type);
    };

    namespace Usagi
    {
        // うさぎを待つ
        void Wait();

        // うさぎの再生
        void Play(int play_type);
    };

    // ゲーム終了時に出力する音声もろもろ
    namespace End
    {
        // ai vs player のとき
        void EndVoice1(int board[]);

        // player vs player のとき
        void EndVoice2(int board[]);

        // ai vs ai のとき
        void EndVoice3(int board[]);
    };

    namespace Start
    {
        void StartVoice1();

        void StartVoice2();

        void StartVoice3();
    };

    // ずんだもんやら中国うさぎのリアクション。
    // 石を置いた直後に呼び出し、しゃべり終わるまで関数の終了を待つ必要はない。
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

// 仮想の画面に何かを表示する関数
namespace DispV
{
    // RateDpで使われる関数で、仮想画面上にでっかい数字を表示するためのもの。戻り値はハンドル。
    std::list<int> DispNum(int num, char color, int locate);

    // 何対何かというのを仮想画面に表示する。戻り値はハンドル。
    std::list<int> DispRate(int board[], int reset);

    // 仮想画面上に石を置く。戻り値はハンドル。
    int PutStone(int x, int y, char color);

    int PutPoint(int x, int y, int color);

    // ai vs player モードにおいて
    int PrintBoard1(int board[], int reset, int before_turn);

    // player vs player モードにおいて
    void PrintBoard2(int board[], int reset, int before_turn);

    void PrintBoard3(int board[], int reset, int before_turn);
};

// 現実の画面に何かを表示する関数
namespace DispR
{
    // 盤面の状態を実際の画面上に表示する
    int PrintBoard(int board[], int reset, int before_turn);

    // スタート画面を表示する
    int Start();

    // ボタンが押された状態のスタート画面を表示する
    int StartPressed();
};

// いくつかの場面において初期化を行う関数
namespace Init
{
    //  ずんだもん vs 人 ゲーム開始時の初期化をする
    int Game1(int board_new[]);

    int Game2(int board_new[]);

    int Game3(int board_new[]);

    // プログラムが実行されてすぐに必要な初期化を行う
    int Program();
};

// オセロゲームそのものにかかわるような様々な関数
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

// 汎用的な機能を持った関数
namespace Utility
{
    namespace Arr
    {
        int Max(int *a, int yo);

        int MaxIndex(int *a, int yo);

        // 最大値となる要素が複数ある場合、それらの要素のうち一つの要素の番号をランダムに返す
        int MaxIndexRand(int arr[], int num);

        int Min(int *a, int yo);

        float Ave(int arr[], int n);

        int Sum(int arr[], int n);
    };

    int RandBetween(int minimum, int maximum);

    float RandBetweenF(float min, float max);

}

// 物理演算に関連する関数
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
