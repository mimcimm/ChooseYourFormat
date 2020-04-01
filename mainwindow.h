#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QtCore>
#include <QtXml>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readJSON();
    void writeJSON();
    void readXML();
    void writeXML();
    void readINI();
    void writeINI();
    void listElements(QDomElement root, QString tagname, QString attribute);
private slots:
    void readIt();
    void writeIt();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
