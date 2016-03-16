#include <debug.hpp>

#include <mainWindow.hpp>
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    newIngridientWindow = new NewIngridientWindow();
    newDishWindow = new NewDishWindow();

    PRINT_OBJ("MainWindow created");
}

MainWindow::~MainWindow() {
    delete ui;
    delete newIngridientWindow;
    delete newDishWindow;

    PRINT_OBJ("MainWindow destroyed");
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
