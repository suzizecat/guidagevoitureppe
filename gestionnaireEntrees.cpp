#include "gestionnaireEntrees.h"

gestionnaireEntrees::gestionnaireEntrees()
{
    reset();
}


void gestionnaireEntrees::reset()
{
    for( int i=0; i<SDLK_LAST; i++)
    {
        touches[i] = false;
    }
    for(i=0; i < coordonneesSouris.length(); i++)
    {
        coordonneesSouris[i] = 0;
    }
}

void gestionnaireEntrees::update()
{
    SDL_Event *event;
    while(SDL_PollEvent(&event))
    {
        switch(event->type)
        {
        case SDL_KEYDOWN: // On a enfoncé une touche
            touches[event->key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            touches[event->key.keysym.sym] = false;
            break;

        }
    }
}

bool gestionnaireEntrees::getKeyState(int key)
{
    if(key < SDLK_LAST)
        return touches[key];
    else
        return false;
}
