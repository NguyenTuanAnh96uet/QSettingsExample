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

