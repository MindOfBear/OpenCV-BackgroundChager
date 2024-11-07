#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_foregroundSelectButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select foreground photo"), "", tr("Images (*.png *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        foregroundPhoto = imread(filePath.toStdString());
        ui->foregroundLabel->setText(filePath);
    }
}

void MainWindow::on_colorSelectButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, tr("Select background color!"));
    if (color.isValid()) {
        selectedColor = color;
    }
}

void MainWindow::on_backgroundSelectButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select background photo"), "", tr("Images (*.png *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        backgroundPhoto = imread(filePath.toStdString());
    }

}

void MainWindow::on_processButton_clicked() {
    Mat outputImage = foregroundPhoto.clone();

    if (ui->backgroundSelectButton->isChecked()) {
        cv::resize(backgroundPhoto, backgroundPhoto, foregroundPhoto.size());
        Mat mask;
        threshold(foregroundPhoto, mask, thresholdValue, 255, cv::THRESH_BINARY);
        backgroundPhoto.copyTo(outputImage, mask);
    }
    else if (ui->colorSelectButton->isChecked()) {
        Mat colorBackground(foregroundPhoto.size(), foregroundPhoto.type(), cv::Scalar(selectedColor.blue(), selectedColor.green(), selectedColor.red()));
        Mat mask;
        threshold(foregroundPhoto, mask, thresholdValue, 255, cv::THRESH_BINARY);
        colorBackground.copyTo(outputImage, mask);
    }
    QImage qImage(outputImage.data, outputImage.cols, outputImage.rows, outputImage.step, QImage::Format_BGR888);

    QSize labelSize = ui->imageLabel->size();
    QImage scaledImage = qImage.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}


void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    thresholdValue = value;
    on_processButton_clicked();
}

