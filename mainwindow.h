#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_But1_clicked();

    void on_But3_clicked();

    void on_But4_clicked();

    void on_But5_clicked();

    void on_But6_clicked();

    void on_But7_clicked();

    void on_But8_clicked();

    void on_But9_clicked();

    void on_But10_clicked();

    void on_But11_clicked();

    void on_But12_clicked();

    void on_But13_clicked();

    void on_But14_clicked();

    void on_But15_clicked();

    void on_But16_clicked();

    void on_But17_clicked();

    void on_But18_clicked();

    void on_But19_clicked();

    void on_But20_clicked();

    void on_But21_clicked();

    void on_But22_clicked();

    void on_But23_clicked();

    void on_But2_clicked();

    void on_But25_clicked();

    void on_But24_clicked();

    void on_Start_clicked();

    void winner();

    void handleButton(int i,int j);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
