#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
    QFile file("C:/Users/malouuk/Desktop/projetQt-main/NeonButtons.qss");
                       file.open(QFile::ReadOnly);

                       QString styleSheet { QLatin1String(file.readAll()) };

                       //setup stylesheet
                       a.setStyleSheet(styleSheet);
                       MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                ), QMessageBox::Close);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                ), QMessageBox::Close);



    return a.exec();
}
