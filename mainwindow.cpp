#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QByteArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_json_file_with_inputs_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "D:/Projects/january2022_test", tr("Image Files (*.json)"));

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open input file.");
        return;
    }
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));

    auto jsonObject = doc.object();

    auto inputs = jsonObject["inputs"];

    qDebug() << "Is array?" << inputs.isArray();
    qDebug() << "values" << inputs.isArray();

    auto array = inputs.toArray();

    QStringList _values;
    for (const auto& val : array)
    {
        if (val.isDouble())
        {
//            qDebug() << val.toDouble();
            _values.append(QString::number(val.toDouble()));
        }
    }
    //    qDebug() << _values;

    std::sort(_values.begin(), _values.end(),
              [](const QString& val1, const QString& val2) {return val1.toDouble() < val2.toDouble();});

    for (const auto& val : _values)
    {
        qDebug() << val;
    }
}

