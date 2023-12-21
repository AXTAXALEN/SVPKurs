#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация виджетов
    customPlot = new QCustomPlot(this);
    frequencySpinBox = new QDoubleSpinBox(this);
    amplitudeSpinBox = new QDoubleSpinBox(this);
    phaseShiftSpinBox = new QDoubleSpinBox(this);
    clearGraphButton = new QPushButton("Очистить", this);
    saveToFileButton = new QPushButton("Сохранить", this);

    // Установка шага для QDoubleSpinBox
    frequencySpinBox->setSingleStep(0.001);
    amplitudeSpinBox->setSingleStep(0.001);
    phaseShiftSpinBox->setSingleStep(0.001);

    // Подключение сигналов к слотам
    connect(frequencySpinBox, SIGNAL(valueChanged(double)), this, SLOT(updatePlot()));
    connect(amplitudeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updatePlot()));
    connect(phaseShiftSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updatePlot()));
    connect(clearGraphButton, SIGNAL(clicked()), this, SLOT(clearPlot()));
    connect(saveToFileButton, SIGNAL(clicked()), this, SLOT(saveToFile()));

    // Размещение виджетов в интерфейсе
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(customPlot);
    layout->addWidget(frequencySpinBox);
    layout->addWidget(amplitudeSpinBox);
    layout->addWidget(phaseShiftSpinBox);
    layout->addWidget(clearGraphButton);
    layout->addWidget(saveToFileButton);

    // Добавление подписей к виджетам
    frequencySpinBox->setPrefix("Частота: ");
    amplitudeSpinBox->setPrefix("Амплитуда: ");
    phaseShiftSpinBox->setPrefix("Фазовый сдвиг: ");

    // Создание графика и установка макета
    customPlot->addGraph();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlot()
{
    // Реализация построения графика
    int numPoints = 1000;
    QVector<double> x(numPoints), y(numPoints);

    for (int i = 0; i < numPoints; ++i)
    {
        x[i] = i;
        y[i] = amplitudeSpinBox->value() * sin(2 * M_PI * frequencySpinBox->value() * i + phaseShiftSpinBox->value());
    }

    if (customPlot->graphCount() == 0) {
        // Если график с индексом 0 не существует, создаем новый
        customPlot->addGraph();
    }

    customPlot->graph(0)->setData(x, y);

    // Установка диапазона значений по осям
    customPlot->xAxis->setRange(0, numPoints);
    customPlot->yAxis->setRange(-amplitudeSpinBox->value(), amplitudeSpinBox->value());

    customPlot->replot();
}

void MainWindow::clearPlot()
{
    // Очистка графика
    customPlot->clearGraphs();
    customPlot->replot();

    // Сброс значений в спин-боксах к дефолтным
    frequencySpinBox->setValue(0.0);
    amplitudeSpinBox->setValue(0.0);
    phaseShiftSpinBox->setValue(0.0);
}

void MainWindow::saveToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить сигнал"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось сохранить файл."));
        return;
    }

    QTextStream out(&file);

    int numPoints = 1000;
    for (int i = 0; i < numPoints; ++i) {
        out << i << "\t" << amplitudeSpinBox->value() * sin(2 * M_PI * frequencySpinBox->value() * i + phaseShiftSpinBox->value()) << "\n";
    }

    file.close();

    QMessageBox::information(this, tr("Сохранение"), tr("Сигнал успешно сохранен."));
}
