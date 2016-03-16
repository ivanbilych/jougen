#include <newIngridientWindow.hpp>
#include "ui_newIngridientWindow.h"

NewIngridientWindow::NewIngridientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewIngridientWindow) {

    ui->setupUi(this);
}

NewIngridientWindow::~NewIngridientWindow() {
    delete ui;
}

void NewIngridientWindow::on_buttonBox_1_accepted() {
    this->hide();
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();
}
