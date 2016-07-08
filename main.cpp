#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    //save values
    QSettings settings("demosettings.ini", QSettings::NativeFormat);
    settings.beginGroup( "Position" );
    settings.setValue( "x", w.x() );
    settings.setValue( "y", w.y() );
    settings.setValue( "width", w.width() );
    settings.setValue( "height", w.height() );
    settings.endGroup();
    settings.sync();
    
    
    //get values
    // settings.beginGroup( "Position" );
    // int x = settings.value( "x", -1 ).toInt();
    // int y = settings.value( "y", -1 ).toInt();
    // int width = settings.value( "width", -1 ).toInt();
    // int height = settings.value( "height", -1 ).toInt();
    // settings.endGroup();
    
    
    
    w.setMinimumSize(400,200);
    w.show();

    return a.exec();
}
