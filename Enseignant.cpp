#include "Enseignant.h"
#include <QSystemTrayIcon>

Enseignant::Enseignant()
{

}

Enseignant::Enseignant(int id, QString nom, QString prenom, QString gendre, QDate dateNaissance, float salaire)
{
    m_id = id;
    m_nom = nom;
    m_prenom = prenom;
    m_dateNaissance = dateNaissance;
    m_salaire = salaire;
    m_gendre = gendre;
}

void Enseignant::setNom(const QString &nom)
{
    m_nom = nom;
}

void Enseignant::setPrenom(const QString &prenom)
{
    m_prenom = prenom;
}
void Enseignant::setGendre(const QString &gendre)
{
    m_gendre = gendre;
}
void Enseignant::setSalaire(int s)
{
    m_salaire = s;
}

QSqlQueryModel *Enseignant::afficher_enseignant()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignants");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire($)"));

    return model;
}

bool Enseignant::ajouter_enseignant()
{
    QSqlQuery query;
    QString res = QString::number(m_id);
    query.prepare("INSERT INTO Enseignants(id, nom, prenom, date_naissance, gendre, salaire) VALUES (:id, :nom, :prenom, :dateNaissance, :gendre, :salaire)");
    query.bindValue(":id", res);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":dateNaissance", m_dateNaissance);
    query.bindValue(":gendre", m_gendre);
    query.bindValue(":salaire", m_salaire);

    return query.exec();
}

bool Enseignant::supprimer_enseignant(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM Enseignants WHERE id = :id");
    query.bindValue(":id", res);

    return query.exec();
}

bool Enseignant::modifier_enseignant(int idEN)
{
    QSqlQuery query;
    QString res = QString::number(idEN);

    query.prepare("UPDATE Enseignants SET nom=:nom, prenom=:prenom, date_naissance=:dateNaissance, gendre=:gendre, salaire=:salaire WHERE id=:idEN");
    query.bindValue(":idEN", res);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":dateNaissance", m_dateNaissance);
    query.bindValue(":gendre", m_gendre);
    query.bindValue(":salaire", m_salaire);

    return query.exec();
}

QSqlQueryModel *Enseignant::tri_id_enseignant()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignants ORDER BY id ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire($)"));

    return model;
}

QSqlQueryModel *Enseignant::tri_nom_enseignant()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignants ORDER BY nom ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire($)"));


    return model;
}

QSqlQueryModel *Enseignant::tri_salaire_enseignant()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignants ORDER BY salaire ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire($)"));

    return model;
}

QSqlQueryModel *Enseignant::displayClause_enseignant(QString cls)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignants " + cls);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire($)"));

    return model;
}

void Enseignant::notification_ajoutenseignant()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des enseignants", "Nouvel enseignant ajouté", QSystemTrayIcon::Information, 15000);
}

void Enseignant::notification_suppenseignant()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des enseignants", "Enseignant supprimé", QSystemTrayIcon::Information, 15000);
}

void Enseignant::notification_modifenseignant()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des enseignants", "Enseignant modifié", QSystemTrayIcon::Information, 15000);
}

void Enseignant::notification_pdfenseignant()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des enseignants", "PDF généré", QSystemTrayIcon::Information, 15000);
}
