#include "QApplication"

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    #if QT_VERSION_MAJOR == 5
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QApplication a(argc, argv);

    auto *w = new DbNodes::Widgets::MainWindow();
    w->show();

    return QApplication::exec();
}
