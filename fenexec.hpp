#ifndef FENEXEC_HPP
#define FENEXEC_HPP

#include "ui_fenexec.h"
#include "gestionnaireEntrees.hpp"
#include <QVariant>

#define AXE_X 0
#define AXE_Y 1
#define D_VAL_X 0
#define D_VAL_Y 1
#define D_DECLENCHE_ENR 2
#define D_CHGTMD 3

class fenExec : public QDialog, private Ui::fenExec
{
    Q_OBJECT

public:
    explicit fenExec(QWidget *parent = 0, int num = 0);

protected:
    int numJoystick;
    bool presenceJoystick;
    void trieEvenements(bool, QList<int> events);
    QList<int> eventsValides;

protected slots:
    int lanceCommande();
};

#endif // FENEXEC_HPP
