#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Enseignant
{
public:
    Enseignant();
    Enseignant(int id, QString nom, QString prenom, QString gendre, QDate dateNaissance, float salaire);
    QSqlQueryModel *afficher_enseignant();
    bool ajouter_enseignant();
    bool supprimer_enseignant(int id);
    bool modifier_enseignant(int idEN);

    void setId(int id);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setDateNaissance(const QDate &dateNaissance);
    void setSalaire(int salaire);
    void setGendre(const QString &gendre);

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateNaissance() const;
    int getSalaire() const;
    QString getGendre() const;
    QSqlQueryModel *tri_salaire_enseignant();
    QSqlQueryModel *tri_id_enseignant();
    QSqlQueryModel *tri_nom_enseignant();
    QSqlQueryModel *displayClause_enseignant(QString cls);

    void notification_ajoutenseignant();
    void notification_suppenseignant();
    void notification_modifenseignant();
    void notification_pdfenseignant();

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    QDate m_dateNaissance;
    int m_salaire;
    QString m_gendre;
};

#endif // ENSEIGNANT_H
