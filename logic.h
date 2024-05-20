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


    // Thực hiện nước đi và chuyển đổi người chơi tiếp theo
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


    char checkWinner() const {
    // Kiểm tra hàng ngang

    for (int i = 0; i < BOARD_SIZE; i++) {
    // Khởi tạo cờ cho hàng ngang hiện tại
    bool isRowWin = true;
    // So sánh tất cả các ô trong hàng ngang
    for (int j = 1; j < BOARD_SIZE; j++) {
        if (board[i][j] == EMPTY_CELL || board[i][j] != board[i][0]) {
            // Nếu ô không giống hoặc là ô trống, đánh dấu không phải hàng chiến thắng
            isRowWin = false;
            break;
        }
    }
    // Nếu tất cả các ô trong hàng ngang đều giống nhau và không phải là ô trống, in ra giá trị của ô đầu tiên
    if (isRowWin) {
        return board[i][0];

    }
}
   // kiem tra hang doc
    for (int i = 0; i < BOARD_SIZE; i++) {
    // Khởi tạo cờ cho hàng ngang hiện tại
    bool isRowWin = true;
    // So sánh tất cả các ô trong hàng ngang
    for (int j = 1; j < BOARD_SIZE; j++) {
        if (board[i][j] == EMPTY_CELL || board[i][j] != board[0][i]) {

            isRowWin = false;
            break;
        }
    }
    // Nếu tất cả các ô trong hàng ngang đều giống nhau và không phải là ô trống, in ra giá trị của ô đầu tiên
    if (isRowWin) {
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
    // kiemtra duong cheo phu
    bool Win = true;
    for( int i =0; i<BOARD_SIZE; i++)
    {
        if(board[i][BOARD_SIZE-1-i]!=board[0][BOARD_SIZE-1]||board[i][BOARD_SIZE-1-i]== EMPTY_CELL)
        {
            Win = false;
            break;
        }
    }
    if(Win){
        return board[0][BOARD_SIZE-1];

    }
//    // Kiểm tra xem còn ô trống nào không, nếu không thì là hòa
//    for (int i = 0; i < BOARD_SIZE; i++) {
//        for (int j = 0; j < BOARD_SIZE; j++) {
//            if (board[i][j] == EMPTY_CELL) {
//                return EMPTY_CELL; // Chưa kết thúc trò chơi
//            }
//        }
//    }
bool isBoardFull = true;
for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] == EMPTY_CELL) {
            isBoardFull = false;
            break;
        }
    }
    if (!isBoardFull) {
        break;
    }
}
// Nếu không có ô trống nào, trả về 'T' để biểu thị hòa
if (!isBoardFull) {
    return EMPTY_CELL;
}

    return '0'; // Hòa
}

};

#endif

