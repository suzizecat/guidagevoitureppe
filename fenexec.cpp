#include "fenexec.hpp"
#define ZNMORTE 1
#define JOY_VALMAX 32768
fenExec::fenExec(QWidget *parent, int num) :
    QDialog(parent)
{
    setupUi(this);
    numJoystick = num;
    connect(lancerTransmition,SIGNAL(clicked()),this,SLOT(lanceCommande()));
}
int fenExec::lanceCommande()
{
    qDebug() << "Déclaration des variables";
    SDL_Event event;
    qDebug() << "Génération du gestionnaire d'entrées:\n\tAdresse event: "<< &event;
    gestionnaireEntrees listeEvents(&event,numJoystick);
    bool continuer = true;
    bool enregistrer = false;
    SDL_Joystick* joystick;
    eventsValides << SDL_KEYDOWN << SDL_QUIT << SDL_JOYAXISMOTION; ;

    info->setText("Test en cours");
    qDebug() << "Debut transmition\n" << "Initialisation SDL";
    if(SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) < 0 )
    {
        return EXIT_FAILURE;
    }

    joystick = SDL_JoystickOpen(numJoystick);
    if(SDL_JoystickNumAxes(joystick) < 2)
    {
        qDebug() << "Pas assez d'axe sur le joystick, passage en mode clavier !\n"
                 << "\tNom :" << SDL_JoystickName(numJoystick) << "\n"
                 << "\tNbre d'axes :" << SDL_JoystickNumAxes(joystick);
        qDebug() << "Activation de la répétition automatique\n\tDélai : 10\n\tIntervale : 100";
        //  SDL_EnableKeyRepeat(10,100);
        presenceJoystick = false;
    }
    else
    {
        qDebug() << "Déclaration du Joystick\n\tNumero : " << numJoystick
                 <<"\n\tNombre d'axes : " << SDL_JoystickNumAxes(joystick);
        presenceJoystick = true;
    }

    qDebug() << "Event SourisMotion" << SDL_MOUSEMOTION;

    qDebug() << "Déclaration des listes";
    QList<QVariant> donnees;
    donnees << 0 << 0 << false << false;
    QList<QList<QVariant> > donneesFinales;

    qDebug() << "Activation des evenements lies aux joysticks";
    SDL_JoystickEventState(SDL_ENABLE);

    qDebug() << "Desactivation des évenements non utilisés";
    //trieEvenements(true, eventsValides);
    //listeEvents.setEvents(eventsValides,true);

    qDebug() << "Affichage de la surface SDL";
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    qDebug() << "Debut de la boucle";


    while (continuer)
    {
        SDL_Delay(100);
        listeEvents.update();
        if(listeEvents.getLastType() < 20)
        {
            if(listeEvents.getQuit() || listeEvents.getKeyState(SDLK_ESCAPE))
            {
                qDebug() << "\tFin de la session de test";
                continuer = false;

            }
            if(listeEvents.getKeyState(SDLK_RETURN))
            {
                donnees[D_DECLENCHE_ENR] = ! donnees[D_DECLENCHE_ENR].toBool();
                listeEvents.setKeyState(SDLK_RETURN,false);
            }
            if(listeEvents.getKeyState(SDLK_SPACE))
            {
                donnees[D_CHGTMD] = ! donnees[D_CHGTMD].toBool();
                listeEvents.setKeyState(SDLK_SPACE,false);
            }
            if(! presenceJoystick)
            {
                if(listeEvents.getKeyState(SDLK_UP))
                    donnees[D_VAL_Y]= JOY_VALMAX;
                if(listeEvents.getKeyState(SDLK_DOWN))
                    donnees[D_VAL_Y]= - JOY_VALMAX;
                if(listeEvents.getKeyState(SDLK_LEFT))
                    donnees[D_VAL_X]= -JOY_VALMAX;
                if(listeEvents.getKeyState(SDLK_RIGHT))
                    donnees[D_VAL_X]= JOY_VALMAX;

                if(listeEvents.getKeyState(SDLK_LEFT) == listeEvents.getKeyState(SDLK_RIGHT))
                    donnees[D_VAL_X] = 0;
                if(listeEvents.getKeyState(SDLK_DOWN) == listeEvents.getKeyState(SDLK_UP))
                    donnees[D_VAL_Y] = 0;

            }
            else
             {
                donnees[D_VAL_X] = listeEvents.getJoyValue(D_VAL_X);
                donnees[D_VAL_Y] = -listeEvents.getJoyValue(D_VAL_Y);
            }

            qDebug() << event.type <<"\t"<< donnees[0].toInt() <<"\t" << donnees[1].toInt() << "\t" << donnees[2].toInt() <<"\t" << donnees[3].toInt();

        }



    }
    info->setText("Appuyez sur le boutton Go !");
    if(presenceJoystick)
    {
        SDL_JoystickClose(joystick);
    }

    SDL_Quit();
}

void fenExec::trieEvenements(bool etat, QList<int> events)
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
