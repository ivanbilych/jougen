#include <debug.hpp>

#include <aboutWindow.hpp>
#include "ui_aboutWindow.h"

AboutWindow::AboutWindow(QDialog *parent) :
    QDialog { parent },
    ui { new Ui::AboutWindow } {

    ui->setupUi(this);

    PRINT_OBJ("AboutWindow created");
}

AboutWindow::~AboutWindow() {
    delete ui;

    PRINT_OBJ("AboutWindow destroyed");
}

void AboutWindow::on_pushButton_clicked() {
    this->close();
}
