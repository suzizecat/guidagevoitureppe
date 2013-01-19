#include <QtGui/QApplication>
#include "principale.hpp"

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QTextCodec>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    qDebug() << "Mise en place de la traduction et de l'encodage ...";
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //Pour activer l'encodage UTF-8 sur les boites de dialogue
    qDebug() << "Langue : " << locale ;


    Principale w;
    w.show();
    
    return app.exec();
}
