#ifndef NEWDISHWINDOW_H
#define NEWDISHWINDOW_H

#include <QDialog>

namespace Ui {
    class NewDishWindow;
}

class NewDishWindow : public QDialog {
    Q_OBJECT

public:
    explicit NewDishWindow(QWidget *parent = 0);
    ~NewDishWindow();

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();

private:
    Ui::NewDishWindow *ui;
};

#endif // NEWDISHWINDOW_H
