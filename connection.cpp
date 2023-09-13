#include "connection.h"
#include "QDebug"
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Project");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("root");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

qDebug() << "Database Error: " << db.lastError().text();



    return  test;
}
