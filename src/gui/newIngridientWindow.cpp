#include <debug.hpp>

#include <newIngridientWindow.hpp>
#include "ui_newIngridientWindow.h"

NewIngridientWindow::NewIngridientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewIngridientWindow) {

    ui->setupUi(this);

    PRINT_OBJ("NewIngridientWindow created");
}

NewIngridientWindow::~NewIngridientWindow() {
    delete ui;

    PRINT_OBJ("NewIngridientWindow destroyed");
}

void NewIngridientWindow::on_buttonBox_1_accepted() {
    this->hide();
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();
}
