#include "gestionAffichage.hpp"

void info(QWidget *parent, QString contenu)
{
    QMessageBox::information(parent,"Système de pilotage de voiture pour PPE 2013",contenu);
}
void info(QWidget *parent,QString titre ,QString contenu)
{
    QMessageBox::information(parent,titre,contenu);
}

void avertissement(QWidget *parent, QString contenu)
{
    QMessageBox::warning(parent,"Système de pilotage de voiture pour PPE 2013",contenu);
}
void avertissement(QWidget *parent,QString titre ,QString contenu)
{
    QMessageBox::warning(parent,titre,contenu);
}

void alerte(QWidget *parent, QString contenu)
{
    QMessageBox::critical(parent,"Système de pilotage de voiture pour PPE 2013",contenu);
}
void alerte(QWidget *parent,QString titre ,QString contenu)
{
    QMessageBox::critical(parent,titre,contenu);
}

bool ouiNon(QWidget *parent, QString contenu)
{
   int i = QMessageBox::question(parent,"Système de pilotage de voiture pour PPE 2013",contenu,QMessageBox::Yes|QMessageBox::No);

   if (i==QMessageBox::Yes)
       return true;
   else
       return false;

}
bool ouiNon(QWidget *parent,QString titre ,QString contenu)
{
   int i = QMessageBox::question(parent,titre,contenu,QMessageBox::Yes|QMessageBox::No);

   if (i==QMessageBox::Yes)
       return true;
   else
       return false;
}

QString intVersStr(int nombre)
{
    return QVariant(nombre).toString();
}

void changeTitreFen(QWidget *parent, QString titre,bool titreComplet)
{
    if( ! titreComplet)
        parent->setWindowTitle(titre);
    else
        parent->setWindowTitle(QString("Système de pilotage de voiture pour PPE 2013 "+titre));
}
