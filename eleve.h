#ifndef ELEVE_H
#define ELEVE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Eleve
{
public:
    Eleve();
    Eleve(int a, QString n, QString p, QDate dn,int e);

    QSqlQueryModel *afficher();
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int idE);

    void setId(int a);
    void set_en(int a);
    void setNom(const QString &n);
    void setPrenom(const QString &p);
    void setDateNaissance(const QDate &dn);

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateNaissance() const;
               QSqlQueryModel *tri_prenom();
               QSqlQueryModel *tri_id();
               QSqlQueryModel *tri_nom();
               QSqlQueryModel *displayClause(QString cls);
               void notification_ajouteleve();
               void notification_suppeleve();
               void notification_modifeleve();
               void notification_pdf();


private:
    int id;
    QString nom;
    QString prenom;
    QDate dateNaissance;
    int id_en;
};

#endif // MATERIEL_H
