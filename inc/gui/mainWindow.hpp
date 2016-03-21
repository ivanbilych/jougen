#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include <newIngridientWindow.hpp>
#include <newDishWindow.hpp>
#include <itemsForm.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    enum InfoType {
        ITEM,
        FOOD,
        DISH,
        NONE
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_listView_1_clicked(const QModelIndex &index);
    void on_listView_2_clicked(const QModelIndex &index);
    void on_listView_1_entered(const QModelIndex &index);
    void on_listView_2_entered(const QModelIndex &index);

public slots:
    void addNewItemObject(Item *item);
    void addNewFoodObject(Food *food);

private:
    Ui::MainWindow *ui;
    InfoType infoWindowType {NONE};
    QStringList *itemStringList {};
    QStringList *dishStringList {};
    QStringListModel *itemListModel {};
    QStringListModel *dishListModel {};
    ItemForm *itemForm {};

    void displayListViewInfoItem(const QModelIndex &index);
    void displayListViewInfoDish(const QModelIndex &index);
};

#endif // MAINWINDOW_H
