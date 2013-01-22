#include "gestionnaireEntrees.hpp"

gestionnaireEntrees::gestionnaireEntrees(SDL_Event *evenement, int joystick)
{
    qDebug() << "\tAdresse reçue :" << evenement;
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

    for( int i=0; i<4; i++)
    {
        if(axesJoystick.length() <= i)
            axesJoystick << 0;
        else
            axesJoystick[i] = 0;
    }
    quit = false;

}

void gestionnaireEntrees::update()
{



    type = event->type;
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
        case SDL_JOYAXISMOTION:
            axesJoystick[event->jaxis.axis] = event->jaxis.value;
            break;
        case SDL_QUIT:
            quit = true;
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

bool gestionnaireEntrees::getQuit()
{
    return quit;
}

int gestionnaireEntrees::getJoyValue(int axe)
{
    return axesJoystick[axe];
}

int gestionnaireEntrees::getLastType()
{
    return type;
}

void gestionnaireEntrees::setKeyState(int key, bool state)
{
    touches[key] = state;
}

void gestionnaireEntrees::setEvents(QList<int> events, bool etat)
{
    qDebug() << "Selection des evenements a exploiter" ;
    qDebug() << "\t"<< events.count() << " elements passes / 14";
    if(etat)
    {
        qDebug() << "\tDesactivation de tous les evenements";
        SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
        SDL_EventState(SDL_QUIT, SDL_IGNORE);
        SDL_EventState(SDL_VIDEORESIZE, SDL_IGNORE);
        SDL_EventState(SDL_VIDEOEXPOSE, SDL_IGNORE);
        SDL_EventState(SDL_USEREVENT, SDL_IGNORE);
        SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
        SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
        SDL_EventState(SDL_KEYUP, SDL_IGNORE);
        SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
        SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
        SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
        SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);

        qDebug() << "\tActivation des elements selectionnes";
        for(int i = 0; i < events.count(); i ++ )
        {
            qDebug() << "\tActivation de l'event " << events[i];
            SDL_EventState(events[i], SDL_ENABLE );
        }
    }
    else
    {
        qDebug() << "\tActivation de tous les evenements";
        SDL_EventState(SDL_MOUSEBUTTONDOWN,SDL_ENABLE);
        SDL_EventState(SDL_MOUSEMOTION,SDL_ENABLE);
        SDL_EventState(SDL_QUIT,SDL_ENABLE);
        SDL_EventState(SDL_VIDEORESIZE,SDL_ENABLE);
        SDL_EventState(SDL_VIDEOEXPOSE,SDL_ENABLE);
        SDL_EventState(SDL_USEREVENT,SDL_ENABLE);
        SDL_EventState(SDL_ACTIVEEVENT,SDL_ENABLE);
        SDL_EventState(SDL_KEYDOWN,SDL_ENABLE);
        SDL_EventState(SDL_KEYUP,SDL_ENABLE);
        SDL_EventState(SDL_JOYAXISMOTION,SDL_ENABLE);
        SDL_EventState(SDL_JOYHATMOTION,SDL_ENABLE);
        SDL_EventState(SDL_JOYBUTTONDOWN,SDL_ENABLE);
        SDL_EventState(SDL_JOYBUTTONUP,SDL_ENABLE);

        qDebug() << "\tDesactivation des elements selectionnes";
        for(int i = 0; i < events.count(); i ++ )
        {
            SDL_EventState(events[i], SDL_IGNORE );
        }
    }


}
