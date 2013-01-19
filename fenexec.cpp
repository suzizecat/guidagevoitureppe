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
        SDL_EnableKeyRepeat(10,100);
        presenceJoystick = false;
    }
    else
    {
        qDebug() << "Déclaration du Joystick\n\tNumero : " << numJoystick
                 <<"\n\tNombre d'axes : " << SDL_JoystickNumAxes(joystick);
        presenceJoystick = true;
    }



    qDebug() << "Déclaration des listes";
    QList<QVariant> donnees;
    donnees << 0 << 0 << false << false;
    QList<QList<QVariant> > donneesFinales;

    qDebug() << "Activation des evenements lies aux joysticks";
    SDL_JoystickEventState(SDL_ENABLE);

    qDebug() << "Desactivation des évenements non utilisés";
    trieEvenements(true, eventsValides);

    qDebug() << "Affichage de la surface SDL";
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    qDebug() << "Debut de la boucle";
    while (continuer)
    {
        if(! presenceJoystick)
        {
            qDebug() << "Réinit valeurs" << donnees[0].toString() <<" " << donnees[1].toString() <<" " << donnees[2].toInt() <<" " << donnees[3].toInt();
        if(donnees[D_VAL_X] != 0)
            donnees[D_VAL_X] = 0;

        if(donnees[D_VAL_Y] != 0)
            donnees[D_VAL_Y] = 0;
        }
        qDebug() << "Attente d'un evenement";
        do
        {

            SDL_WaitEvent(&event);
        }while(event.type == SDL_JOYAXISMOTION && (event.jaxis.value < ZNMORTE && event.jaxis.value > -ZNMORTE));
        qDebug() << "Evenement !";
        switch(event.type)
        {
        case SDL_QUIT:
            qDebug() << "\tIcone quitter";
            continuer = false;
            break;
        case SDL_KEYDOWN:
            qDebug() << "\tTouche clavier";
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = false;
                break;
            case SDLK_RETURN:
                donnees[D_DECLENCHE_ENR] = ! donnees[D_DECLENCHE_ENR].toBool();
                break;
            case SDLK_SPACE:
                donnees[D_CHGTMD] = ! donnees[D_CHGTMD].toBool();
                break;
                if(! presenceJoystick)
                {
            case SDLK_RIGHT:
                        donnees[D_VAL_X]= JOY_VALMAX;
                        break;
                    case SDLK_LEFT:
                        donnees[D_VAL_X]= -JOY_VALMAX;
                        break;
                    case SDLK_UP:
                        donnees[D_VAL_Y]= JOY_VALMAX;
                        break;
                    case SDLK_DOWN:
                        donnees[D_VAL_Y]= - JOY_VALMAX;
                        break;
                }
            default:
                break;
            }
            break;
        case SDL_JOYAXISMOTION:
            if(event.jaxis.axis == AXE_X)  // Si déplacement horizontal
            {
                qDebug() << "\tAXE_X";
                donnees[D_VAL_X] = event.jaxis.value;
            }
            if(event.jaxis.axis == AXE_Y )
            {
                qDebug() << "\tAXE_Y";
                donnees[D_VAL_Y] = event.jaxis.value;
            }
            break;

        }
        qDebug() << event.type << donnees[0].toString() <<" " << donnees[1].toString() <<" " << donnees[2].toInt() <<" " << donnees[3].toInt();




    }
    info->setText("Appuyez sur le boutton Go !");
    if(presenceJoystick)
    {
        SDL_JoystickClose(joystick);
    }

    SDL_Quit();
}

void fenExec::trieEvenements(bool activer, QList<int> listeDonnees)
{
    qDebug() << "Selection des evenements a exploiter" ;
    qDebug() << "\t"<< listeDonnees.count() << " elements passes / 14";
    if(activer)
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
        for(int i = 0; i < listeDonnees.count(); i ++ )
        {
            SDL_EventState(listeDonnees[i], SDL_ENABLE );
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
        for(int i = 0; i < listeDonnees.count(); i ++ )
        {
            SDL_EventState(listeDonnees[i], SDL_IGNORE );
        }
    }


}
