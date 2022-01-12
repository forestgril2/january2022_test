#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QByteArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QStringListModel"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
#ifndef NDEBUG
    median_test();
#endif
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

//    qDebug() << "Is array?" << inputs.isArray();
//    qDebug() << "values" << inputs.isArray();

    auto array = inputs.toArray();

    QStringList _values;
    QStringList _incorrectValues;
    for (const auto& val : array)
    {
        if (val.isDouble() &&
            val.toDouble() > -70 &&
            val.toDouble() < 2.28E9)
        {
//            qDebug() << val.toDouble();
            _values.append(QString::number(val.toDouble()));
        }
        else
        {
            qDebug() << val;
            _incorrectValues.append(QString::number(val.toDouble()));
        }
    }

    qDebug() << _incorrectValues;

    std::sort(_values.begin(), _values.end(),
              [](const QString& val1, const QString& val2) {return val1.toDouble() < val2.toDouble();});

    QStringListModel* stringListModel = new QStringListModel(_values);
    ui->listView->setModel(stringListModel);

    QStringListModel* stringListModel2 = new QStringListModel(_incorrectValues);
    ui->listView_2->setModel(stringListModel2);


    std::vector<double> sortedValues;
    sortedValues.reserve(_values.size());
    for (const auto& val : _values)
    {
        sortedValues.push_back(val.toDouble());
    }

    qDebug() << " ### " << median(sortedValues);
}

double MainWindow::median(std::vector<double> sortedValues)
{
    if (sortedValues.size() == 0)
        return 0;

    size_t n = sortedValues.size() / 2;
    if (sortedValues.size() % 2 == 0)
        return (sortedValues[n] + sortedValues[n-1])/2;
    else
        return sortedValues[n];
}

bool MainWindow::median_test()
{
    std::vector<double> t1;
    assert(qFuzzyIsNull(median(t1)));

    std::vector<double> t2{0};
    assert(median(t2) == 0.0);

    std::vector<double> t3{0,1.0};
    assert(qFuzzyCompare(median(t3), 0.5));

    assert(qFuzzyCompare(median(std::vector<double>{0, 1.0, 2.0}), 1.0));

    return true;
}

