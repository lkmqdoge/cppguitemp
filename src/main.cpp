#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include "SDL3_image/SDL_image.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define TARGET_FPS 60
#define SHOW_FPS

#define PROJECTILE_COUNT 30000
#define PROJECTILE_SPEED 15.0f

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define PROJECTILE_SIZE_X 14
#define PROJECTILE_SIZE_Y 14

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *proj = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer("hello SDL3 with cmake", 800, 600, 0, &window, &renderer) == false)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    proj = IMG_LoadTexture(renderer, "assets/projectile.png");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
        if (event->key.key == SDLK_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }
    default:
        break;
    }

    return SDL_APP_CONTINUE;
}


/*
    MAIN LOOP THING
*/
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer, 0, 78, 127, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    SDL_FRect r {0, 0, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y};
    SDL_RenderTexture(renderer, proj, NULL, &r);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/*
    SDL will clean up the window/renderer for us
*/
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(proj);
}