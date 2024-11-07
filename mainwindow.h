#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>
#include <QDir>
#include <QRadioButton>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
#include <QColorDialog>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Mat foregroundPhoto;
    Mat backgroundPhoto;
    cv::Mat outputImage;
    QColor selectedColor;
    int thresholdValue = 230;

private slots:

    void on_foregroundSelectButton_clicked();

    void on_colorSelectButton_clicked();

    void on_backgroundSelectButton_clicked();

    void on_processButton_clicked();

    void on_thresholdSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
