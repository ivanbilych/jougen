#ifndef NEWDISHWINDOW_H
#define NEWDISHWINDOW_H

#include <dish.hpp>
#include <food.hpp>
#include <item.hpp>

#include <QDialog>
#include <QStringListModel>

namespace Ui {
    class NewDishWindow;
}

class NewDishWindow : public QDialog {
    Q_OBJECT

public:
    explicit NewDishWindow(QWidget *parent = 0);
    explicit NewDishWindow(Dish *dish, QWidget *parent = 0);
    ~NewDishWindow();

signals:
    void itemObjectReady(Dish *dish);

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();

public slots:
    void fillItemList(std::list<Item *> *itemsList);

private:
    Ui::NewDishWindow *ui;
    QStringList *foodStringList {};
    QStringListModel *itemListModel {};
    Dish *dish {};
    std::list<Item *> *avaliableItemsList;
    std::list<Food *> dishFoodList;
    bool editMode {false};

    Dish* createNewDish(void);
    void applyStats(Dish* dish);
};

#endif // NEWDISHWINDOW_H
