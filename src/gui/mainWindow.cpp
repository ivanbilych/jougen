#include <mainWindow.hpp>
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    newIngridientWindow = new NewIngridientWindow();
    newDishWindow = new NewDishWindow();
}

MainWindow::~MainWindow() {
    delete ui;
    delete newIngridientWindow;
    delete newDishWindow;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    newIngridientWindow->close();
    newDishWindow->close();
}

void MainWindow::on_pushButton_1_clicked() {
    newIngridientWindow->show();
}

void MainWindow::on_pushButton_3_clicked() {
    newDishWindow->show();
}
