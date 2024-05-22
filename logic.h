#ifndef _LOGIC__H
#define _LOGIC__H
#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'O'
#define X_CELL 'X'

struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
        }

    }
    int move(int row, int column)
{
    // Di va nuoc tiep theo
    if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE)
        {
            board[row][column] = nextMove;
            if (nextMove == O_CELL)
            {
                nextMove = X_CELL;
            }
            else
            {
                nextMove = O_CELL;
            }
        }
}


    char checkWinner() const
{
    // kiem tra hang ngang
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        bool isRowWin = true;
        for (int j = 1; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL || board[i][j] != board[i][0])
            {
                isRowWin = false;
                break;
            }
        }
        if (isRowWin)
        {
            return board[i][0];
        }
    }
   // kiem tra hang doc
    for (int i = 1; i < BOARD_SIZE; i++)
    {
        bool isColWin = true;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[j][i] == EMPTY_CELL || board[j][i] != board[0][i])
            {
                isColWin = false;
                break;
            }
        }
        if (isColWin)
        {
            return board[0][i];
        }
    }
    // kiem tra duong cheo chinh
    bool isWin = true;
    for( int i =0; i<BOARD_SIZE; i++)
    {
        if(board[i][i]!=board[0][0]||board[i][i]== EMPTY_CELL)
        {
            isWin = false;
            break;
        }
    }
    if(isWin){
       return board[0][0];

    }
    // kiem tra duong cheo phu
    bool Win = true;
    for( int i =0; i<BOARD_SIZE; i++)
    {
        if(board[i][BOARD_SIZE-1-i]!=board[0][BOARD_SIZE-1]||board[i][BOARD_SIZE-1-i]== EMPTY_CELL)
        {
            Win = false;
            break;
        }
    }
    if(Win)
        {
            return board[0][BOARD_SIZE-1];
        }
    // kiem tra bang con trong hay khong

    bool isBoardFull = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                isBoardFull = false;
                break;
            }
        }
        if (!isBoardFull)
        {
            break;
        }
    }
    if (!isBoardFull)
    {
        return EMPTY_CELL;
    }

    return '0'; // Hòa
    }

    };

#endif

