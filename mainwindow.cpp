#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

#include <QSettings>
#include <QApplication>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settingsFileName ="demosettings.ini";
    //QApplication::applicationDirPath().left(1) + "demosettings.ini";
    qDebug()<< QApplication::applicationDirPath().left(1)<<"\n\n"<<settingsFileName;

    QSettings settings(settingsFileName, QSettings::NativeFormat);
    QStringList keys=settings.allKeys();
    qDebug()<<keys;

    connect(ui->pb_getVal, SIGNAL(clicked()),this, SLOT (on_pb_getValue()));
    connect(ui->pb_setVal, SIGNAL(clicked()),this, SLOT (on_pb_setValue()));
}

void MainWindow::on_pb_getValue()
{
    qDebug()<<"on_pb_getValue()";
    QString key=ui->le_getKey->text();
    QString val;

    QSettings settings(settingsFileName, QSettings::NativeFormat);
    val=settings.value(key,"default val").toString();
    ui->le_getVal->setText(val);

}

void MainWindow::on_pb_setValue()
{

    qDebug()<<"on_pb_setValue()";
    QString key=ui->le_setKey->text();
    QString val=ui->le_setVal->text();

    QSettings settings(settingsFileName, QSettings::NativeFormat);
    settings.setValue(key, val);
}
void MainWindow::writeSetting(const QString &key, const QVariant &variant)
{
    QSettings settings(settingsFileName, QSettings::NativeFormat);
    settings.setValue(key, variant);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::saveWndInfo(QWidget *w)
{  
    QSettings settings(settingsFileName, QSettings::NativeFormat);
    settings.beginGroup(w->windowTitle());
    {
        settings.setValue( "x", w->x() );
        settings.setValue( "y", w->y() );
        settings.setValue( "width", w->width() );
        settings.setValue( "height", w->height() );
    }
    settings.endGroup();
}

void  MainWindow::readWndInfo(QWidget *w,QString &errText)
{
    QSettings settings(settingsFileName, QSettings::NativeFormat);
    settings.beginGroup(w->windowTitle());
    {
        bool b=false;
        bool rez=true;
        int x = settings.value( "x", -1 ).toInt(b);
        rez&=b;
        int y = settings.value( "y", -1 ).toInt(b);
        rez&=b;
        int width = settings.value( "width", -1 ).toInt(b);
        rez&=b;
        int height = settings.value( "height", -1 ).toInt(b);
        rez&=b;
        if(!rez){
            errText="Ошибка в данных для текущего положения окна"+w->windowTitle()+
                    "в файле "+settingsFileName+".";
        }
        else{
            if( x > 0 && y > 0 && width > 0 && height > 0 ) {
                w->setGeometry( x, y, width, height );
            } 
        }
    }
    settings.endGroup();
}
