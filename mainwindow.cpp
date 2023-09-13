#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtCharts>
#include <QPieSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int idEleve = ui->lineEdit_id_ray->text().toInt();
    int idEnseignant = ui->lineEdit_id_ray_el_en->text().toInt();
    QString nomEleve = ui->lineEdit_nom_ray->text();
    QString prenomEleve = ui->lineEdit_Prenom_ray->text();
    QDate dateNaissance = ui->dateEdit_naissance->date();

    Eleve eleve(idEleve, nomEleve, prenomEleve, dateNaissance,idEnseignant);

    if (!nomEleve.isEmpty() && !prenomEleve.isEmpty())
    {
        bool ajoutReussi = eleve.ajouter();
        if (ajoutReussi)
        {
            QMessageBox::information(this, "Ajout réussi", "L'élève a été ajouté avec succès.");
            eleve.notification_ajouteleve();
            ui->tableView_ray->setModel(eleve.afficher());
        }
        else
        {
            QMessageBox::critical(this, "Erreur d'ajout", "Une erreur est survenue lors de l'ajout de l'élève.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le nom et le prénom de l'élève.");
    }
}

void MainWindow::on_pushButton_afficher_ray_clicked()
{
    Eleve eleve;
    ui->tableView_ray->setModel(eleve.afficher());
}

void MainWindow::on_pushButton_supp_ray_clicked()
{
    int idDel = ui->tableView_ray->model()->data(ui->tableView_ray->model()->index(ui->tableView_ray->currentIndex().row(), 0)).toInt();
    Eleve eleve;
    bool test = eleve.supprimer(idDel);
    if (test)
    {
        QMessageBox::information(this, "Suppression réussie", "L'élève a été supprimé avec succès.");
        eleve.notification_suppeleve();
    }
    else
    {
        QMessageBox::critical(this, "Erreur de suppression", "Une erreur est survenue lors de la suppression de l'élève.");
    }
    ui->tableView_ray->setModel(eleve.afficher());
}

void MainWindow::on_pushButton_modif_ray_clicked()
{
    int idUp = ui->tableView_ray->model()->data(ui->tableView_ray->model()->index(ui->tableView_ray->currentIndex().row(), 0)).toInt();
    QString nomEleve = ui->lineEdit_nom_ray->text();
    QString prenomEleve = ui->lineEdit_Prenom_ray->text();
    QDate dateNaissance = ui->dateEdit_naissance->date();
     int idEnseignant = ui->lineEdit_id_ray_el_en->text().toInt();

    Eleve eleve(idUp, nomEleve, prenomEleve, dateNaissance,idEnseignant);

    if (!nomEleve.isEmpty() || !prenomEleve.isEmpty())
    {
        if (nomEleve.isEmpty()) {
            // Si le nom est vide, récupérer le nom actuel de l'élève
            QString ancienNom = ui->tableView_ray->model()->data(ui->tableView_ray->model()->index(ui->tableView_ray->currentIndex().row(), 1)).toString();
            eleve.setNom(ancienNom);
        }

        if (prenomEleve.isEmpty()) {
            // Si le prénom est vide, récupérer le prénom actuel de l'élève
            QString ancienPrenom = ui->tableView_ray->model()->data(ui->tableView_ray->model()->index(ui->tableView_ray->currentIndex().row(), 2)).toString();
            eleve.setPrenom(ancienPrenom);
        }

        bool test = eleve.modifier(idUp);
        if (test)
        {
            QMessageBox::information(this, "Modification réussie", "Les informations de l'élève ont été modifiées avec succès.");
            eleve.notification_modifeleve();
            ui->tableView_ray->setModel(eleve.afficher());
        }
        else
        {
            QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification de l'élève.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le nom ou le prénom de l'élève.");
    }
}


void MainWindow::on_lineEdit_rech_id_ray_textChanged()
{
    Eleve eleve;
    if (ui->lineEdit_rech_id_ray->text() != "")
    {
        QString a = ui->lineEdit_rech_id_ray->text();
        ui->tableView_ray->setModel(eleve.displayClause("WHERE (id LIKE '%" + a + "%') "));
    }
    else
    {
        ui->tableView_ray->setModel(eleve.afficher());
    }
}

void MainWindow::on_lineEdit_rech_nom_ray_textChanged()
{
    Eleve eleve;
    if (ui->lineEdit_rech_nom_ray->text() != "")
    {
        QString a = ui->lineEdit_rech_nom_ray->text();
        ui->tableView_ray->setModel(eleve.displayClause("WHERE (nom LIKE '%" + a + "%') "));
    }
    else
    {
        ui->tableView_ray->setModel(eleve.afficher());
    }
}
void MainWindow::on_lineEdit_rech_prenom_ray_textChanged()
{
    Eleve eleve;
    if (ui->lineEdit_rech_prenom_ray->text() != "")
    {
        QString a = ui->lineEdit_rech_prenom_ray->text();
        ui->tableView_ray->setModel(eleve.displayClause("WHERE (prenom LIKE '%" + a + "%') "));
    }
    else
    {
        ui->tableView_ray->setModel(eleve.afficher());
    }
}

void MainWindow::on_pushButton_triID_ray_clicked()
{
    Eleve eleve;
    ui->tableView_ray->setModel(eleve.tri_id());
}

void MainWindow::on_pushButton_trinom_ray_clicked()
{
    Eleve eleve;
    ui->tableView_ray->setModel(eleve.tri_nom());
}

void MainWindow::on_pushButton_triprenom_ray_clicked()
{
    Eleve eleve;
    ui->tableView_ray->setModel(eleve.tri_prenom());
}

void MainWindow::on_pushButton_pdf_ray_clicked()
{
    Eleve eleve;
    QPdfWriter pdf("Eleves.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(3300, 1200, "Liste Des élèves");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(1500, 200, 7300, 2600);
    painter.drawRect(0, 3000, 9600, 500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(1000, 3300, "ID");
    painter.drawText(2000, 3300, "NOM");
    painter.drawText(3000, 3300, "PRENOM");
    painter.drawText(4000, 3300, "DATE DE NAISSANCE");
    painter.drawText(6000, 3300, "Id_Enseignant");

    QSqlQuery query;
            query.prepare("select * from eleves");
            query.exec();
            while (query.next())
            {
                painter.drawText(1000,i,query.value(0).toString());
                painter.drawText(2000,i,query.value(1).toString());
                painter.drawText(3000,i,query.value(2).toString());
                painter.drawText(4000,i,query.value(3).toString());
                painter.drawText(6000,i,query.value(4).toString());




                i = i +500;
            }


    eleve.notification_pdf();

    int reponse = QMessageBox::question(this, "Générer PDF", "PDF enregistré. Voulez-vous l'afficher ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("Eleves.pdf"));
    }

    painter.end();
}

void MainWindow::on_pushButton_stat_ray_clicked()
{
    Eleve eleve;
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT date_naissance FROM eleves");

    QVector<int> ageCounts(6);

    QDate currentDate = QDate::currentDate();
    int currentYear = currentDate.year();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QDate dob = model->data(model->index(row, 0), Qt::DisplayRole).toDate();
        int age = currentYear - dob.year();
        if (age >= 0 && age <= 5)
            ageCounts[0]++;
        else if (age >= 6 && age <= 10)
            ageCounts[1]++;
        else if (age >= 11 && age <= 15)
            ageCounts[2]++;
        else if (age >= 16 && age <= 20)
            ageCounts[3]++;
        else if (age >= 21 && age <= 25)
            ageCounts[4]++;
        else
            ageCounts[5]++;
    }

    QPieSeries *series = new QPieSeries();
    series->append("0-5 ans (" + QString::number(ageCounts[0]) + ")", ageCounts[0]);
    series->append("6-10 ans (" + QString::number(ageCounts[1]) + ")", ageCounts[1]);
    series->append("11-15 ans (" + QString::number(ageCounts[2]) + ")", ageCounts[2]);
    series->append("16-20 ans (" + QString::number(ageCounts[3]) + ")", ageCounts[3]);
    series->append("21-25 ans (" + QString::number(ageCounts[4]) + ")", ageCounts[4]);
    series->append(">25 ans (" + QString::number(ageCounts[5]) + ")", ageCounts[5]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des âges des élèves");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();


}

void MainWindow::on_pushButton_2_clicked()
{
    int idEnseignant = ui->lineEdit_id_ray_2->text().toInt();
    QString nomEnseignant = ui->lineEdit_nom_ray_2->text();
    QString prenomEnseignant = ui->lineEdit_Prenom_ray_2->text();
    QDate dateNaissance = ui->dateEdit_naissance_2->date();
    int salaireEnseignant = ui->lineEdit_Salaire_ray->text().toInt();

    QString gendreEnseignant = ui->comboBox_gendre_ray_2->currentText();

    Enseignant enseignant(idEnseignant, nomEnseignant, prenomEnseignant, gendreEnseignant, dateNaissance, salaireEnseignant);

    if (!nomEnseignant.isEmpty() && !prenomEnseignant.isEmpty())
    {
        bool ajoutReussi = enseignant.ajouter_enseignant();
        if (ajoutReussi)
        {
            QMessageBox::information(this, "Ajout réussi", "L'enseignant a été ajouté avec succès.");
            enseignant.notification_ajoutenseignant();
            ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
        }
        else
        {
            QMessageBox::critical(this, "Erreur d'ajout", "Une erreur est survenue lors de l'ajout de l'enseignant.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le nom et le prénom de l'enseignant.");
    }
}


void MainWindow::on_pushButton_afficher_ray_2_clicked()
{
    Enseignant enseignant; // Create an instance of the Enseignant class
        ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
}

void MainWindow::on_pushButton_supp_ray_2_clicked()
{
    int idDel = ui->tableView_ray_2->model()->data(ui->tableView_ray_2->model()->index(ui->tableView_ray_2->currentIndex().row(), 0)).toInt();
        Enseignant enseignant;
        bool test = enseignant.supprimer_enseignant(idDel);
        if (test)
        {
            QMessageBox::information(this, "Suppression réussie", "L'enseignant a été supprimé avec succès.");
            enseignant.notification_suppenseignant();
        }
        else
        {
            QMessageBox::critical(this, "Erreur de suppression", "Une erreur est survenue lors de la suppression de l'enseignant.");
        }
        ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
}

void MainWindow::on_pushButton_modif_ray_2_clicked()
{
    int idUp = ui->tableView_ray_2->model()->data(ui->tableView_ray_2->model()->index(ui->tableView_ray_2->currentIndex().row(), 0)).toInt();
        QString nomEnseignant = ui->lineEdit_nom_ray_2->text();
        QString prenomEnseignant = ui->lineEdit_Prenom_ray_2->text();
        QDate dateNaissance = ui->dateEdit_naissance_2->date();
        float salaireEnseignant = ui->lineEdit_Salaire_ray->text().toFloat();
        QString gendreEnseignant = ui->comboBox_gendre_ray_2->currentText();
        Enseignant enseignant(idUp, nomEnseignant, prenomEnseignant,gendreEnseignant, dateNaissance, salaireEnseignant);

        if (!nomEnseignant.isEmpty() || !prenomEnseignant.isEmpty())
        {
            if (nomEnseignant.isEmpty()) {
                // Si le nom est vide, récupérer le nom actuel de l'enseignant
                QString ancienNom = ui->tableView_ray_2->model()->data(ui->tableView_ray_2->model()->index(ui->tableView_ray_2->currentIndex().row(), 1)).toString();
                enseignant.setNom(ancienNom);
            }

            if (prenomEnseignant.isEmpty()) {
                // Si le prénom est vide, récupérer le prénom actuel de l'enseignant
                QString ancienPrenom = ui->tableView_ray_2->model()->data(ui->tableView_ray_2->model()->index(ui->tableView_ray_2->currentIndex().row(), 2)).toString();
                enseignant.setPrenom(ancienPrenom);
            }

            bool test = enseignant.modifier_enseignant(idUp);
            if (test)
            {
                QMessageBox::information(this, "Modification réussie", "Les informations de l'enseignant ont été modifiées avec succès.");
                enseignant.notification_modifenseignant();
                ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
            }
            else
            {
                QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification de l'enseignant.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le nom ou le prénom de l'enseignant.");
        }
    }



void MainWindow::on_lineEdit_rech_id_ray_2_textChanged()
{
    Enseignant enseignant;
        if (ui->lineEdit_rech_id_ray_2->text() != "")
        {
            QString a = ui->lineEdit_rech_id_ray_2->text();
            ui->tableView_ray_2->setModel(enseignant.displayClause_enseignant("WHERE (id LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
        }
}

void MainWindow::on_lineEdit_rech_nom_ray_2_textChanged()
{
    Enseignant enseignant;
        if (ui->lineEdit_rech_nom_ray_2->text() != "")
        {
            QString a = ui->lineEdit_rech_nom_ray_2->text();
            ui->tableView_ray_2->setModel(enseignant.displayClause_enseignant("WHERE (nom LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
        }
}

void MainWindow::on_lineEdit_rech_prenom_ray_2_textChanged()
{
    Enseignant enseignant;
        if (ui->lineEdit_rech_prenom_ray_2->text() != "")
        {
            QString a = ui->lineEdit_rech_prenom_ray_2->text();
            ui->tableView_ray_2->setModel(enseignant.displayClause_enseignant("WHERE (prenom LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView_ray_2->setModel(enseignant.afficher_enseignant());
        }
}

void MainWindow::on_pushButton_triID_ray_2_clicked()
{
    Enseignant enseignant;
    ui->tableView_ray_2->setModel(enseignant.tri_id_enseignant());
}

void MainWindow::on_pushButton_trinom_ray_2_clicked()
{
    Enseignant enseignant;
    ui->tableView_ray_2->setModel(enseignant.tri_nom_enseignant());
}

void MainWindow::on_pushButton_trisalaire_ray_2_clicked()
{
    Enseignant enseignant;
    ui->tableView_ray_2->setModel(enseignant.tri_salaire_enseignant());
}

void MainWindow::on_pushButton_pdf_ray_2_clicked()
{
    Enseignant enseignant;
    QPdfWriter pdf("Enseignant.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(2200, 1800, "Liste Des Enseignants ");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(1000, 200, 7300, 2600);
    painter.drawRect(0, 3000, 9600, 500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(1500, 3300, "ID");
    painter.drawText(2500, 3300, "NOM");
    painter.drawText(3500, 3300, "PRENOM");
    painter.drawText(4500, 3300, "DOB");
    painter.drawText(5500, 3300, "SALAIRE");
    painter.drawText(6500, 3300, "GENDRE");


    QSqlQuery query;
            query.prepare("select * from enseignants");
            query.exec();
            while (query.next())
            {
                painter.drawText(1500,i,query.value(0).toString());
                painter.drawText(2500,i,query.value(1).toString());
                painter.drawText(3500,i,query.value(2).toString());
                painter.drawText(4500,i,query.value(3).toString());
                painter.drawText(5500,i,query.value(4).toString());
                painter.drawText(6500,i,query.value(5).toString());




                i = i +500;
            }

    enseignant.notification_pdfenseignant();

    int reponse = QMessageBox::question(this, "Générer PDF", "PDF enregistré. Voulez-vous l'afficher ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("Enseignant.pdf"));
    }

    painter.end();
}

void MainWindow::on_pushButton_stat_ray_4_clicked()
{
    Enseignant enseignant;

    QSqlQueryModel *model = enseignant.afficher_enseignant();

    int maleCount = 0;
    int femaleCount = 0;
    int otherCount = 0;

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QString gender = model->data(model->index(row, 5), Qt::DisplayRole).toString();

        if (gender == "Masculin")
            maleCount++;
        else if (gender == "Feminin")
            femaleCount++;
        else
            otherCount++;
    }

    QPieSeries *series = new QPieSeries();
    series->append("Masculin (" + QString::number(maleCount) + ")", maleCount);
    series->append("Feminin (" + QString::number(femaleCount) + ")", femaleCount);
    series->append("Other (" + QString::number(otherCount) + ")", otherCount);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des enseignants par genre");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();


}

void MainWindow::on_tableView_ray_doubleClicked(const QModelIndex &index)
{
    int id=ui->tableView_ray->model()->data(ui->tableView_ray->model()->index(ui->tableView_ray->currentIndex().row(),0)).toInt();
       QString res = QString::number(id);
       ui->lineEdit_id_ray->setText(res);

       ui->lineEdit_nom_ray->clear();
       ui->lineEdit_Prenom_ray->clear();
       ui->lineEdit_id_ray_el_en->clear();


}

void MainWindow::on_tableView_ray_2_doubleClicked(const QModelIndex &index)
{
    int id=ui->tableView_ray_2->model()->data(ui->tableView_ray_2->model()->index(ui->tableView_ray_2->currentIndex().row(),0)).toInt();
       QString res = QString::number(id);
       ui->lineEdit_id_ray_2->setText(res);

       ui->lineEdit_nom_ray_2->clear();
       ui->lineEdit_Prenom_ray_2->clear();
       ui->lineEdit_Salaire_ray->clear();
}
