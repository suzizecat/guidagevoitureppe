#include "principale.hpp"

Principale::Principale(QMainWindow *parent) : QMainWindow(parent)
{
    setupUi(this);
    SdlInitialisee = 0;
    liste_carac_joysticks->setSelectionMode(QAbstractItemView::NoSelection);
    initSdl();
}
int Principale::initSdl()
{
    presenceJoystick = false;
    liste_joysticks->setModel(new QStringListModel());
    liste_carac_joysticks->setModel(new QStringListModel());
    if (SDL_Init(SDL_INIT_JOYSTICK) == -1) // Démarrage de la SDL. Si erreur :
    {
        err = "Erreur d'initialisation de la SDL : " + QString(SDL_GetError()); // Écriture de l'erreur
        SdlInitialisee = 0;

        return 1; // On quitte le programme
    }



    QStringList nomsJoy;

    int i = 0;

    while(i < SDL_NumJoysticks() )
    {
        nomsJoy << QVariant(i+1).toString() + " : " + SDL_JoystickName(i);
        i++;
    }
     nomsJoy << "Clavier (sans joystick)";

    QStringListModel * ModelListJoystick = new QStringListModel(nomsJoy);
    liste_joysticks->setModel(ModelListJoystick);
    SDL_Quit();
    SdlInitialisee = 1;



    return 0;
}
int Principale::recupInfoJoy(QModelIndex numJoy)
{
    if (SDL_Init(SDL_INIT_JOYSTICK)  == -1)// Démarrage de la SDL. Si erreur :
    {
        err = "Erreur d'initialisation de la SDL : " + QString(SDL_GetError()); // Écriture de l'erreur
        SdlInitialisee = 0;

        return 1; // On quitte le programme
    }

    if ( ! SdlInitialisee)
    {
        err = "La SDL n'est pas initialisée"; // Écriture de l'erreur
        return 2;
    }
    QStringList caracJoy;
    SDL_Joystick * joy;
    joy = SDL_JoystickOpen(numJoy.row());

    if(SDL_JoystickName(numJoy.row()) != "")
    {
        caracJoy << "Joystick sélectionné : " <<  SDL_JoystickName(numJoy.row()) << "\n\n"
            << "Votre joystick dispose de : " << "\t" + QVariant(SDL_JoystickNumAxes(joy)).toString() + " axe(s)"
             << "\t" + QVariant(SDL_JoystickNumButtons(joy)).toString() + " bouton(s)"
             << "\t" + QVariant(SDL_JoystickNumHats(joy)).toString() + " chapeau(x)"
             << "\t" + QVariant(SDL_JoystickNumBalls(joy)).toString() + " trackball(s)" ;
    }
    if(SDL_JoystickNumAxes(joy) < 2 && QString(SDL_JoystickName(numJoy.row())).contains("[A-Za-z0-9]"))
    {
        alerte(this,"Attention : Pour fonctionner, le logiciel nécessite un joystick avec au moins deux axes...\nCe joystick en possède " + QVariant(SDL_JoystickNumAxes(joy)).toString() +" il ne sera donc pas utilisé.\n Utilisez les touches directionnelles de votre clavier à la place.");
    }
    QStringListModel * ModelDetailJoystick = new QStringListModel(caracJoy);
    liste_carac_joysticks->setModel(ModelDetailJoystick);
    SDL_JoystickClose(joy);

    SDL_Quit();
    presenceJoystick = true;


}

int Principale::lanceTest()
{
    fenExec fen(this,liste_joysticks->currentIndex().row());
    fen.exec();


}
