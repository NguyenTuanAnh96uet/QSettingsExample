#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    writeSetting(const QString &key, const QVariant &variant);
private:
    Ui::MainWindow *ui;
private:

private slots:
    void on_pb_getValue();
    void on_pb_setValue();

private:
    QString settingsFileName;

};

#endif // MAINWINDOW_H
