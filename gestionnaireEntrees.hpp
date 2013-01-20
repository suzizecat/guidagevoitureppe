#ifndef GESTIONNAIREENTREES_H
#define GESTIONNAIREENTREES_H
#include "SDL/SDL.h"
#include <QList>

class gestionnaireEntrees
{
public:
    gestionnaireEntrees(SDL_Event* evenement, int joystick);
    void reset();
    void update();
    void waitForAction();
    bool getKeyState(int key);
    bool getMouseButtonState(int bouton);
    QList<int> getMousePosition();
private:
    QList<bool> touches; //Etat des touches ( enfoncées /relachées)
    QList<int> coordonneesSouris; // 4 valeurs Coordonnées X,Y + relatives
    QList<bool> boutonsSouris;// 7 différents
    int numJoystick;
    SDL_Event* event;
};

#endif // GESTIONNAIREENTREES_H
