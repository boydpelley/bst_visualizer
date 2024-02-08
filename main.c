#include <stdio.h>
#include "SDL2/SDL.h"
#include "binary_search_tree.h"

void render_tree(SDL_Renderer *renderer, node *root, int x, int y, int spacing)
{
    if (root != NULL)
    {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        SDL_Rect rect = {x, y, x + 30, y + 30};
        SDL_RenderFillRect(renderer, &rect);

        render_tree(renderer, root->left, x - spacing, y + 50, spacing / 2);
        render_tree(renderer, root->right, x + spacing, y + 50, spacing / 2);
    }
}

void render_screen(SDL_Renderer *renderer)
{
    // Render a white screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

short process_events(SDL_Window *window)
{
    SDL_Event event;

    short done = 0;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if (window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = 1;
                        break;
                    }
                }
            }
                break;
            case SDL_QUIT:
            {
                done = 1;
            }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                break;
        }
    }
    return done;
}

int main(int argc, char * argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Paint Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    short done = 0;
    while (!done)
    {
        done = process_events(window);

        render_screen(renderer);
    }

    return 0;
}
