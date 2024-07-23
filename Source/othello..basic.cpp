#include "funcs.h"

void Othello::Basic::ChangeBoard(int board[64], int color, int location)
{
    // 8方向の移動ベクトルを定義
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 指定された位置に石を置く
    board[location] = color;

    // 8方向に対してひっくり返す処理を行う
    for (int dir = 0; dir < 8; ++dir)
    {
        int x = location % 8;
        int y = location / 8;
        x += dx[dir];
        y += dy[dir];

        // ひっくり返す対象の石が相手の色である限りひっくり返し続ける
        while (x >= 0 && x < 8 && y >= 0 && y < 8 && board[y * 8 + x] == -color)
        {
            x += dx[dir];
            y += dy[dir];
        }

        // ひっくり返す処理
        if (x >= 0 && x < 8 && y >= 0 && y < 8 && board[y * 8 + x] == color)
        {
            x = location % 8;
            y = location / 8;
            x += dx[dir];
            y += dy[dir];

            while (x >= 0 && x < 8 && y >= 0 && y < 8 && board[y * 8 + x] == -color)
            {
                board[y * 8 + x] = color;
                x += dx[dir];
                y += dy[dir];
            }
        }
    }
}

int Othello::Basic::ExchangeXY(int x, int y)
{
    int f;
    f = 63 - (8 - x) - 8 * (y - 1);
    return f;
}

int Othello::Basic::CountColor(int *board, int color)
{
    int b = 0, w = 0;
    for (int i = 0; i < 64; i++)
    {
        if (board[i] == -1)
        {
            b++;
        }
        if (board[i] == 1)
        {
            w++;
        }
    }
    if (color == -1)
    {
        return b;
    }
    if (color == 1)
    {
        return w;
    }
    return -1; // エラー時
}

int Othello::Basic::PutAble(int *board, int color, int location)
{
    // 置くことができれば1を返し、置くことができなければ0を返す。
    int ac[64];
    for (int i = 0; i < 64; i++)
    {
        ac[i] = board[i];
    }
    if (ac[location] != 0)
    {
        return 0;
    }

    ac[location] = color;

    int co0 = Othello::Basic::CountColor(ac, color);
    Othello::Basic::ChangeBoard(ac, color, location);
    int co = Othello::Basic::CountColor(ac, color);
    if (co > co0)
    {
        return 1;
    }
    else
    {

        return 0;
    }
}

int Othello::Basic::PutAbleAll(int board[], int color)
{
    // 盤面の全てにおいて、特定の色でおける場所があるかを判定。
    // おける場所がなければ0を返す。
    for (int i = 0; i < 64; i++)
    {
        if (Othello::Basic::PutAble(board, color, i) == 1)
        {
            return 1;
        }
    }
    return 0;
}

void Othello::Basic::BoardCpy(int *board1, int *board2)
{
    for (int i = 0; i < 64; i++)
    {
        board1[i] = board2[i];
    }
    return;
}

void Othello::Basic::InitBoard(int *board)
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }
    board[35] = -1, board[28] = -1, board[36] = 1, board[27] = 1;
    return;
}

int Othello::Basic::IsEnd(int board[])
{
    // if game end, return 1, else return 0.
    for (int i = 0; i < 64; i++)
    {
        if (Othello::Basic::PutAble(board, -1, i) == 1)
        {
            return 0;
        }
        if (Othello::Basic::PutAble(board, 1, i) == 1)
        {
            return 0;
        }
    }
    return 1;
}

int Othello::Basic::BoardCmp(int board1[64], int board2[64])
{
    // 要素番号６３までが他のオセロ配列と等しいかどうかを判定する関数。
    // 等しければ１を返し、そうでなければ０を返す。

    for (int i = 0; i < 64; i++)
    {
        if (board1[i] != board2[i])
        {
            return 0;
        }
    }
    return 1;
}
