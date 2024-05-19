#ifndef _LOGIC__H
#define _LOGIC__H
#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

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
        if (row >= 0 && row < BOARD_SIZE &&
            column >= 0 && column < BOARD_SIZE)
        {
            board[row][column] = nextMove;
            if(nextMove==O_CELL)
            {
                nextMove = X_CELL;
            }
            else nextMove = O_CELL;
        }
    char winner = checkWinner();
    if (winner != EMPTY_CELL) {
        return -1; // Trò chơi đã kết thúc
    }
    else if(winner == '0')
    {
        return 0;
    }

        return 1;
    }

    char checkWinner() const {
    // Kiểm tra hàng ngang
    char kt;
    for (int i = 0; i < BOARD_SIZE; i++)
    {

        for( int j = 0 ; j< BOARD_SIZE; j++)
        {
            if(board[i][0]==board[j][0]&&board[i][0]!=EMPTY_CELL)
            {
                kt = board[i][0];
                continue;
            }
            else
            {
                kt =board[i][0];
                break;
            }
        }
        if(kt == board[i][0])return board[i][0];
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {

        for( int j = 0 ; j< BOARD_SIZE; j++)
        {
            if(board[0][i]==board[0][j]&&board[0][j]!=EMPTY_CELL)
            {
                kt = board[0][j];
                continue;
            }
            else
            {
                kt = board[0][i];
                break;
            }
        }
        if(kt == board[0][i]) return board[0][i];
    }
    // Kiểm tra đường chéo chính
    for( int i =0; i< BOARD_SIZE; i++)
    {
        if(board[0][0]!=EMPTY_CELL&&board[0][0]==board[i][i])
        {
            kt = board[0][0];
        }
        else
        {
                kt = board[i][i];
                break;
        }
        if(kt == board[0][0]) return board[0][0];
    }
    // Kiểm tra đường chéo phụ
    for( int i =0; i< BOARD_SIZE; i++)
    {
        if(board[0][BOARD_SIZE-1]!=EMPTY_CELL&&board[0][BOARD_SIZE-1]==board[i][BOARD_SIZE-1-i])
        {
            kt = board[0][BOARD_SIZE-1];
        }
        else
        {
                kt = board[i][BOARD_SIZE-1-i];
                break;
        }
        if(kt == board[0][BOARD_SIZE-1]) return board[0][BOARD_SIZE-1];
    }

    // Kiểm tra xem còn ô trống nào không, nếu không thì là hòa
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                return EMPTY_CELL; // Chưa kết thúc trò chơi
            }
        }
    }

    return '0'; // Hòa
}

};

#endif

