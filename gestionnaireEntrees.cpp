#include "gestionnaireEntrees.hpp"

gestionnaireEntrees::gestionnaireEntrees(SDL_Event *evenement, int joystick)
{
    event = evenement;
    numJoystick = joystick;
    reset();
}


void gestionnaireEntrees::reset()
{
    for( int i=0; i<SDLK_LAST; i++)
    {
        if(touches.length() <= i)
            touches << false;
        else
            touches[i] = false;
    }
    for(int i=0; i < 4; i++)
    {
        if(coordonneesSouris.length() <= i)
            coordonneesSouris << 0;
        else
            coordonneesSouris[i] = 0;
    }

    for( int i=0; i<7; i++)
    {
        if(boutonsSouris.length() <= i)
            boutonsSouris << false;
        else
            boutonsSouris[i] = false;
    }

}

void gestionnaireEntrees::update()
{
    reset();
    while(SDL_PollEvent(event))
    {
        switch(event->type)
        {
        case SDL_KEYDOWN: // On a enfoncé une touche
            touches[event->key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            touches[event->key.keysym.sym] = false;
            break;
        case SDL_MOUSEMOTION:
            coordonneesSouris[0] = event->motion.x;
            coordonneesSouris[1] = event->motion.y;
            coordonneesSouris[2] = event->motion.xrel;
            coordonneesSouris[3] = event->motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
            boutonsSouris[event->button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            boutonsSouris[event->button.button] = false;
            break;
        }
    }
}

void gestionnaireEntrees::waitForAction()
{
    SDL_WaitEvent(event);
    update();
}

bool gestionnaireEntrees::getKeyState(int key)
{
    if(key < SDLK_LAST)
        return touches[key];
    else
        return false;
}
bool gestionnaireEntrees::getMouseButtonState(int btn)
{
    if(btn < 3)
        return boutonsSouris[btn];
    else
        return false;
}

QList<int> gestionnaireEntrees::getMousePosition()
{
    return coordonneesSouris;
}
