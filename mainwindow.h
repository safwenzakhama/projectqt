#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "eleve.h"
#include "Enseignant.h"

#include<QtPrintSupport/QPrinter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_afficher_ray_clicked();

    void on_pushButton_supp_ray_clicked();

    void on_pushButton_modif_ray_clicked();

    void on_lineEdit_rech_id_ray_textChanged();

    void on_lineEdit_rech_nom_ray_textChanged();

    void on_lineEdit_rech_prenom_ray_textChanged();

    void on_pushButton_triID_ray_clicked();

    void on_pushButton_trinom_ray_clicked();

    void on_pushButton_triprenom_ray_clicked();

    void on_pushButton_pdf_ray_clicked();

    void on_pushButton_stat_ray_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_afficher_ray_2_clicked();

    void on_pushButton_supp_ray_2_clicked();

    void on_pushButton_modif_ray_2_clicked();

    void on_lineEdit_rech_id_ray_2_textChanged();

    void on_lineEdit_rech_nom_ray_2_textChanged();


    void on_lineEdit_rech_prenom_ray_2_textChanged();

    void on_pushButton_triID_ray_2_clicked();

    void on_pushButton_trinom_ray_2_clicked();

    void on_pushButton_trisalaire_ray_2_clicked();

    void on_pushButton_pdf_ray_2_clicked();

    void on_pushButton_stat_ray_4_clicked();

    void on_tableView_ray_doubleClicked(const QModelIndex &index);

    void on_tableView_ray_2_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Eleve ptmp;
    QLabel *dateLabel;
};

#endif // MAINWINDOW_H
