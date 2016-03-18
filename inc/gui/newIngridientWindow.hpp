#ifndef NEWINGRIDIENTWINDOW_H
#define NEWINGRIDIENTWINDOW_H

#include <QDialog>

#include <item.hpp>
#include <food.hpp>

namespace Ui {
    class NewIngridientWindow;
}

class NewIngridientWindow : public QDialog {
    Q_OBJECT

public:
    explicit NewIngridientWindow(QWidget *parent = 0);
    ~NewIngridientWindow();

signals:
    void itemObjectReady(Item *item);
    void foodObjectReady(Food *food);

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();

private:
    Ui::NewIngridientWindow *ui;
    QStringList measureList {};

    Item* createNewItem(void);
    Food* createNewFood(void);
};

#endif // NEWINGRIDIENTWINDOW_H
