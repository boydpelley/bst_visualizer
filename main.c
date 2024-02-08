#include <stdio.h>
#include "SDL2/SDL.h"
#include "binary_search_tree.h"
#include "ascii_digits.h"

void render_digit(SDL_Renderer* renderer, short digit[], int x, int y) {
    for (int i = 0; i < DIGIT_HEIGHT; ++i) {
        for (int j = 0; j < DIGIT_WIDTH; ++j) {
            if (digit[i * DIGIT_WIDTH + j] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
                SDL_Rect rect = {x + j, y + i, 1, 1};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void render_tree(SDL_Renderer *renderer, node *root, int x, int y, int spacing)
{
    if (root != NULL)
    {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        SDL_Rect rect = {x, y, 30, 30};
        SDL_RenderFillRect(renderer, &rect);

        render_tree(renderer, root->left, x - spacing, y + 50, spacing / 2);
        render_tree(renderer, root->right, x + spacing, y + 50, spacing / 2);
    }
}

void render_screen(SDL_Renderer *renderer, node * root)
{
    // Render a white screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    render_tree(renderer, root, 300, 50, 50);

    SDL_RenderPresent(renderer);
}


short get_user_input()
{
    SDL_Event event;
    short user_input = 0;
    int waiting_for_input = 1;

    while (waiting_for_input)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            waiting_for_input = 0;
                            break;
                        default:
                            if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                            {
                                user_input = user_input * 10 + (event.key.keysym.sym - SDLK_0);
                            }
                            break;
                    }
                break;
            }
        }
    }

    return user_input;
}

short process_events(SDL_Window *window, node **root)
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
                    case SDLK_r:
                    {
                        short key = rand() % 100 + 1;
                        *root = insert(*root, key);
                        break;
                    }
                    case SDLK_i:
                    {
                        short key = get_user_input();
                        *root = insert(*root, key);
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

    node * root = NULL;

    short done = 0;
    while (!done)
    {
        done = process_events(window, &root);

        render_screen(renderer, root);
    }

    return 0;
}
