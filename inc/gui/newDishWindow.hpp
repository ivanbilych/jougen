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

private:
    Ui::NewDishWindow *ui;
};

#endif // NEWDISHWINDOW_H
