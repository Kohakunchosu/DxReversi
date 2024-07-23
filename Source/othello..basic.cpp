#include "funcs.h"

void Othello::Basic::ChangeBoard(int board[64], int color, int location)
{
    // 8�����̈ړ��x�N�g�����`
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    // �w�肳�ꂽ�ʒu�ɐ΂�u��
    board[location] = color;

    // 8�����ɑ΂��ĂЂ�����Ԃ��������s��
    for (int dir = 0; dir < 8; ++dir)
    {
        int x = location % 8;
        int y = location / 8;
        x += dx[dir];
        y += dy[dir];

        // �Ђ�����Ԃ��Ώۂ̐΂�����̐F�ł������Ђ�����Ԃ�������
        while (x >= 0 && x < 8 && y >= 0 && y < 8 && board[y * 8 + x] == -color)
        {
            x += dx[dir];
            y += dy[dir];
        }

        // �Ђ�����Ԃ�����
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
    return -1; // �G���[��
}

int Othello::Basic::PutAble(int *board, int color, int location)
{
    // �u�����Ƃ��ł����1��Ԃ��A�u�����Ƃ��ł��Ȃ����0��Ԃ��B
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
    // �Ֆʂ̑S�Ăɂ����āA����̐F�ł�����ꏊ�����邩�𔻒�B
    // ������ꏊ���Ȃ����0��Ԃ��B
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
    // �v�f�ԍ��U�R�܂ł����̃I�Z���z��Ɠ��������ǂ����𔻒肷��֐��B
    // ��������΂P��Ԃ��A�����łȂ���΂O��Ԃ��B

    for (int i = 0; i < 64; i++)
    {
        if (board1[i] != board2[i])
        {
            return 0;
        }
    }
    return 1;
}
