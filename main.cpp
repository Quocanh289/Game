#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include <SDL_mixer.h>
//#include "intro.h"
using namespace std;
int processClick(int x, int y, Tictactoe& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
     int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    return game.move(clickedRow, clickedCol);
}
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    graphics.renderIntro();

    SDL_Event e;
    bool introDone = false;

    while (!introDone) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
            {
                introDone = true;
            } else if (e.type == SDL_KEYDOWN || e.type == SDL_FINGERDOWN)
            {
                introDone = true;
            }
        }
        SDL_Delay(100);
    }

    Tictactoe game;
    game.init();
    graphics.renderBackground(game);
    graphics.render(game);

    int x, y;
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0)
            {
             switch (event.type)
             {
                case SDL_QUIT:
                    quit = true; // Thoát khỏi trò chơi
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    // Xử lý click chuột và kiểm tra kết thúc trò chơi
                    if (processClick(x, y, game) == -1)
                    {
                        graphics.render(game);
                        graphics.renderIntro();
                        quit = true;
                    }
                    else if(processClick(x,y,game)==1)
                    {
                        graphics.render(game);
                        // Kiểm tra kết thúc trò chơi sau mỗi nước đi
                            cout << "Player " << game.checkWinner() << " wins!" << endl;

                    }
                    else if(processClick(x,y,game)==0)
                    {
                        graphics.render(game);
                        quit = true;
                    }
              }
                    break;
            }

        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}
