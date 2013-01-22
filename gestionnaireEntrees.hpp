#ifndef GESTIONNAIREENTREES_H
#define GESTIONNAIREENTREES_H
#include "SDL/SDL.h"
#include <QList>
#include <QDebug>
class gestionnaireEntrees
{
public:
    gestionnaireEntrees(SDL_Event* evenement, int joystick);
    void reset();
    void update();

    bool getQuit();
    bool getKeyState(int key);
    bool getMouseButtonState(int bouton);
    int getJoyValue(int axe);
    int getLastType();
    QList<int> getMousePosition();

    void setKeyState(int key, bool state);

    void setEvents(QList<int> events, bool etat);
private:
    QList<bool> touches; //Etat des touches ( enfoncées /relachées)
    QList<int> coordonneesSouris; // 4 valeurs Coordonnées X,Y + relatives
    QList<bool> boutonsSouris;// 7 différents
    QList<int> axesJoystick;
    bool quit; // Action SDL_QUIT ...
    int numJoystick;
    int type;
    int typeDerniereTouche;
    SDL_Event* event;
};

#endif // GESTIONNAIREENTREES_H
