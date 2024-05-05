#include <iostream>
#include <SDL.h>

#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;





//void logErrorAndExit(const char* msg, const char* error)
//{
//    // ghi thong tin vao
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//
//}
//
//SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
//{
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//        logErrorAndExit("SDL_Init", SDL_GetError());
//
//    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    //full screen
//    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
//    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
//    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
//        logErrorAndExit( "SDL_image error:", IMG_GetError());
//
//    return window;
//}
////nap anh tu file explorer
//SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
//{
//	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
//                     "Loading %s", filename);
//
//	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
//	if (texture == NULL) {
//        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
//                       "Load texture %s", IMG_GetError());
//      }
//
//	return texture;
//}
//
//SDL_Renderer* createRenderer(SDL_Window* window)
//{
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
//                                              SDL_RENDERER_PRESENTVSYNC);
//    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
//    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
//
//    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
//
//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//    return renderer;
//}
//void renderTexture(SDL_Texture *texture, int x, int y,
//                   SDL_Renderer* renderer)
//{
//	SDL_Rect dest;
//	dest.x = x;
//	dest.y = y;
//	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
//
//	SDL_RenderCopy(renderer, texture, NULL, &dest);
//}
//
//
//void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
//{
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

//void drawSomething(SDL_Window* window, SDL_Renderer* renderer) {
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
//    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
//    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
//    SDL_Rect filled_rect;
//    filled_rect.x = SCREEN_WIDTH - 400;
//    filled_rect.y = SCREEN_HEIGHT - 150;
//    filled_rect.w = 320;
//    filled_rect.h = 100;
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
//    SDL_RenderFillRect(renderer, &filled_rect);
//}
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("bikiniBottom.jpg");
    graphics.prepareScene(background);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_Texture* spongeBob = graphics.loadTexture("Spongebob.png");
    graphics.renderTexture(spongeBob, 200, 200);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_DestroyTexture( spongeBob );
    spongeBob = NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    graphics.quit();
    return 0;
}
