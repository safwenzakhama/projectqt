#include "eleve.h"
#include <QSystemTrayIcon>

Eleve::Eleve()
{

}

Eleve::Eleve(int a, QString n, QString p, QDate dn,int e)
{
    id = a;
    nom = n;
    prenom = p;
    dateNaissance = dn;
    id_en=e;
}
void Eleve::setNom(const QString &n)
{
    nom = n;
}

void Eleve::setPrenom(const QString &p)
{
    prenom = p;
}
void Eleve::set_en(int a)
{
    id_en = a;
}

QSqlQueryModel *Eleve::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Eleves");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_enseignant"));

    return model;
}

bool Eleve::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString res2 = QString::number(id_en);
    query.prepare("INSERT INTO Eleves(id, nom, prenom, date_naissance,id_enseignant) VALUES (:id, :nom, :prenom, :dateNaissance,:id_e)");
    query.bindValue(":id", res);
    query.bindValue(":id_e", res2);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", dateNaissance);

    return query.exec();
}

bool Eleve::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM Eleves WHERE id = :id");
    query.bindValue(":id", res);

    return query.exec();
}

bool Eleve::modifier(int idE)
{
    QSqlQuery query;
    QString res = QString::number(idE);
    QString res2 = QString::number(id_en);

    query.prepare("UPDATE Eleves SET nom=:nom, prenom=:prenom, date_naissance=:dateNaissance,id_enseignant=:id_e WHERE id=:idE");
    query.bindValue(":idE", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":id_e", res2);

    return query.exec();
}



QSqlQueryModel * Eleve::tri_prenom()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM eleves ORDER BY prenom ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_enseignant"));

    return model;
}


QSqlQueryModel * Eleve::tri_id()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM eleves ORDER BY id ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_enseignant"));

    return model;
}



QSqlQueryModel * Eleve::tri_nom()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM eleves ORDER BY nom ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_enseignant"));

    return model;
}




QSqlQueryModel *Eleve::displayClause(QString cls)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM eleves " + cls);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_enseignant"));

    return model;
}


void Eleve::notification_ajouteleve()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des eleves ","Nouveau eleve ajouté ",QSystemTrayIcon::Information,15000);
}


void Eleve::notification_suppeleve()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des eleves ","eleve supprime ",QSystemTrayIcon::Information,15000);
}

void Eleve::notification_modifeleve()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des eleves ","eleve modifie ",QSystemTrayIcon::Information,15000);
}


void Eleve::notification_pdf()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des eleves ","pdf generee ",QSystemTrayIcon::Information,15000);
}
