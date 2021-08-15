#include "QApplication"
#include "QDebug"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    #if QT_VERSION_MAJOR == 5
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QApplication a(argc, argv);

    auto *w = new DbNodes::Widgets::MainWindow();
    w->show();

    return QApplication::exec();
}
