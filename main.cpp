#include <QApplication>
#include <window.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window Window;
    Window.show();
    return a.exec();
}
