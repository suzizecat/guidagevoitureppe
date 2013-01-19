#ifndef PRINCIPALE_HPP
#define PRINCIPALE_HPP

#include "ui_principale.h"
#include <QStringListModel>

#include "fenexec.hpp"
#include "gestionAffichage.hpp"
#undef main

class Principale : public QMainWindow, private Ui::Principale
{
    Q_OBJECT

public:
    Principale(QMainWindow *parent = 0);


protected:
    QString err;
    bool SdlInitialisee;
    bool presenceJoystick;
 public slots :
    int initSdl();
    int recupInfoJoy(QModelIndex);
    int lanceTest();
};

#endif // PRINCIPALE_HPP
