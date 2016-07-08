#include "mainwindow.h"
#include <QApplication>
#include <QDataStream>
truct MyStruct
{
    QString name;
    qint32 key;
};

Q_DECLARE_METATYPE(MyStruct)
Q_DECLARE_METATYPE(QList<MyStruct>)

QDataStream& operator<<(QDataStream& ostream, const MyStruct& ms)
{
    ostream << ms.name << ms.key;
    return ostream;
}

QDataStream& operator>>(QDataStream& istream, MyStruct& ms)
{
    istream >> ms.name >> ms.key
    return istream;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    //--------------------------------save values-----------------------------------------
    QSettings settings("demosettings.ini", QSettings::NativeFormat);
    //1) add standart type
    settings.beginGroup( "Position" );
    settings.setValue( "x", w.x() );
    settings.setValue( "y", w.y() );
    settings.setValue( "width", w.width() );
    settings.setValue( "height", w.height() );
    settings.endGroup();
    
    //2) add my own type
    qRegisterMetaTypeStreamOperators<MyStruct>("MyStruct");
    qRegisterMetaTypeStreamOperators<QList<MyStruct> >("QList<MyStruct>");

    QList<MyStruct> msList;
    MyStruct ms = {"MyStruct name", 123};
    msList << ms;
    //settings.setValue("ListMyStruct", qVariantFromValue(msList));
    QVariant variant;
    variant.setValue(QVariant::fromValue<QList<MyStruct> >(msList));
    settings.setValue("ListMyStruct", variant);
   
    settings.sync();
    
    //--------------------------------get values-----------------------------------------
    // settings.beginGroup( "Position" );
    // int x = settings.value( "x", -1 ).toInt();
    // int y = settings.value( "y", -1 ).toInt();
    // int width = settings.value( "width", -1 ).toInt();
    // int height = settings.value( "height", -1 ).toInt();
    // settings.endGroup();
    // if( x > 0 && y > 0 && width > 0 && height > 0 ) {
    //     w.setGeometry( x, y, width, height );
    // }
    
    //msList = settings.value("Shared/RecentSRS").value<SRSDefinition>();
    
    
    w.setMinimumSize(400,200);
    w.show();

    return a.exec();
}
