// tao san cac texture, window, render(chi can goi ham de no thuc hien la dc)
#include "logic.h"
struct Graphics {
    // trong struc
    SDL_Renderer *renderer;
    SDL_Window *window;
    // tao texture san cho vao 1 ham rieng
    SDL_Texture*cellEmpty, *cellX, *cellO;
    SDL_Texture* intro, *background;

    void init()
    {
        initSDL();
        cellEmpty = loadTexture("cell_empty.png");
        cellX = loadTexture("cell_x.png");
        cellO= loadTexture("cell_o.png");

    }

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
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
     void render(const Tictactoe& game) {

        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                    case X_CELL: renderTexture(cellX, x, y); break;
                    case O_CELL: renderTexture(cellO, x, y); break;
                };
            };

        presentScene();

    }
//    void handleEvents() {
//        SDL_Event e;
//	while (SDL_PollEvent(&e))
//	{
//		if (e.type == SDL_QUIT)
//		{
//			return  EXIT ;
//		}
//		else if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN))
//		{
//			return Gamestates:: TITLE;
//		}
//	}
    void renderBackground(Tictactoe game)
    {
        background = loadTexture("background.jpg");
        prepareScene(background);
        presentScene();
    }
    void renderIntro()
    {
        intro = loadTexture("title screen.png");
        prepareScene(intro);
        presentScene();
    }



    void quit()
    {
        SDL_DestroyTexture(cellEmpty);
        cellEmpty = nullptr;
        SDL_DestroyTexture(cellX);
        cellX = nullptr;
        SDL_DestroyTexture(cellO);
        cellO = nullptr;

        IMG_Quit();


        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
