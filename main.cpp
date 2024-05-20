#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include <SDL_mixer.h>
//#include "intro.h"
using namespace std;
void  processClick(int x, int y, Tictactoe& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
     int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}
void handleEvent()
{
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

    }
}
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    graphics.renderIntro();
    handleEvent();

    Tictactoe game;
    game.init();
    graphics.renderBackground(game);
    graphics.render(game);
    Mix_Music *gMusic = graphics.loadMusic("Point.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("sound.mp3");

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
                    graphics.play(gJump);
                    if (game.checkWinner() != EMPTY_CELL)
                    {
                        processClick(x, y, game);
                        graphics.render(game);
                        if (game.checkWinner() == '0') {
                            cout << "Hoa";

                        } else {
                            cout << "Win";

                        }

                        quit = true;
                    }
                    else
                    {
                        processClick(x, y, game);
                        graphics.render(game);
                    }

                    break;
            }

        }
        SDL_Delay(100);

    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);


    graphics.quit();
    return 0;
}
