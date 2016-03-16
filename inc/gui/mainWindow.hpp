#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <newIngridientWindow.hpp>
#include <newDishWindow.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    NewIngridientWindow *newIngridientWindow {};
    NewDishWindow *newDishWindow {};
};

#endif // MAINWINDOW_H
