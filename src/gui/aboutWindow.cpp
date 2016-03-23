#include <debug.hpp>
#include <versionInfo.hpp>

#include <aboutWindow.hpp>
#include "ui_aboutWindow.h"

AboutWindow::AboutWindow(QDialog *parent) :
    QDialog { parent },
    ui { new Ui::AboutWindow } {

    ui->setupUi(this);

    ui->label_2->setText(QString::fromStdString(programVersion));
    ui->label_4->setText(QString::fromStdString(buildCommit));
    ui->label_6->setText(QString::fromStdString(buildTimestamp));
    ui->label_8->setText(QString::fromStdString(projectURL));

    PRINT_OBJ("AboutWindow created");
}

AboutWindow::~AboutWindow() {
    delete ui;

    PRINT_OBJ("AboutWindow destroyed");
}

void AboutWindow::on_pushButton_clicked() {
    this->close();
}
