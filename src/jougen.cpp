#include <debug.hpp>

#include <QApplication>
#include <mainWindow.hpp>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
