#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->getButton,SIGNAL(clicked()),this,SLOT(readIt()));
    connect(ui->setButton,SIGNAL(clicked()),this,SLOT(writeIt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readIt()
{
    if(ui->comboBox->currentText() == ".json")
        readJSON();
    else if(ui->comboBox->currentText() == ".xml")
        readXML();
    else
        readINI();
}

void MainWindow::writeIt()
{
    if(ui->comboBox->currentText() == ".json")
        writeJSON();
    else if(ui->comboBox->currentText() == ".xml")
        writeXML();
    else
        writeINI();
}

void MainWindow::readJSON()
{
      QString val, printJSONData;
      QFile file("C:/Users/a.kurtvuran/Documents/jsonFile.json");
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
         qDebug() <<"file not opened"<<endl;
      val = file.readAll();
      file.close();
      qDebug() << val;
      QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
      QJsonObject sett2 = d.object();
      QJsonValue value = sett2.value(QString("name"));
      printJSONData.append("name: " + value.toString());
      ui->outLabel->setText(printJSONData);
}

void MainWindow::writeJSON()
{
     QFile file("C:/Users/a.kurtvuran/Documents/jsonFile.json");
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
         qDebug() <<"file not opened"<<endl;
     QTextStream stream(&file);
     QJsonObject obj;
     obj[ui->nameEdit->text()] = ui->valueEdit->text();//(1)

     stream << QJsonDocument(obj).toJson(QJsonDocument::Compact);
     file.close();
     qDebug() << "JSON Wrote";
}

void MainWindow::readXML()
{
    QDomDocument document;
    QFile file("C:/Users/a.kurtvuran/Documents/MyXML.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return;
    } else {
        if(!document.setContent(&file)) {
            qDebug() << "Failed to load document";
            return;
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();
    listElements(root,"Object", "name");
    qDebug() << "\r\nMore Advanced\r\n";
   // QDomNodeList books = root.elementsByTagName("Book");
    qDebug() << "Finished";
}

void MainWindow::writeXML()
{
    QDomDocument document;
    QDomElement root = document.createElement("Objects");
    document.appendChild(root);
    for(int i = 0; i < 10; i++){
        QDomElement domElement = document.createElement("Object");
        domElement.setAttribute( ui->nameEdit->text(), ui->valueEdit->text() + QString::number(i));
        root.appendChild(domElement);
    }

    QFile file("C:/Users/a.kurtvuran/Documents/MyXML.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writting";
        return ;
    } else {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Finished";
    }
}

void MainWindow::readINI() {
    QSettings settings { "C:/Users/a.kurtvuran/Documents/MySettings.ini", QSettings::IniFormat };
    //const auto highScores = settings.value("highScores");
     qDebug() << "dosyadan okundu" << settings.value("name").toString();
     ui->outLabel->setText(settings.value("name").toString());
}

void MainWindow::writeINI()  {
    QSettings settings {  "C:/Users/a.kurtvuran/Documents/MySettings.ini", QSettings::IniFormat };
    //const auto highScores = settings.value("highScores");
    settings.setValue(ui->nameEdit->text(), ui->valueEdit->text());
    qDebug() << "Dosyaya yazıldı";
}

void MainWindow::listElements(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);
    qDebug() << "Total items = " << items.count();
    QString printXMLData;

    for(int i = 0; i < items.count(); i++) {
       QDomNode itemnode = items.at(i);
       if(itemnode.isElement()) {
           QDomElement itemele = itemnode.toElement();
           qDebug() << itemele.attribute(attribute);
           printXMLData.append(itemele.attribute(attribute) + "\n");
       }
    }
    ui->outLabel->setText(printXMLData);
}

