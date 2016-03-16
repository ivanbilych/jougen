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
