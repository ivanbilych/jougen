#include <newDishWindow.hpp>
#include "ui_newDishWindow.h"

NewDishWindow::NewDishWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDishWindow) {

    ui->setupUi(this);
}

NewDishWindow::~NewDishWindow() {
    delete ui;
}
