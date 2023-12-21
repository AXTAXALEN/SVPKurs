#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePlot();
    void clearPlot();
    void saveToFile();

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QDoubleSpinBox *frequencySpinBox;
    QDoubleSpinBox *amplitudeSpinBox;
    QDoubleSpinBox *phaseShiftSpinBox;
    QPushButton *clearGraphButton;
    QPushButton *saveToFileButton;
};
#endif // MAINWINDOW_H
