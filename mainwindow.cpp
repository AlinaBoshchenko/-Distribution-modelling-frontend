#include "mainwindow.h"
#include "dialog.h"
#include "intro.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

/* If Format was chosen - draw a line */
void MainWindow::on_actionModel_triggered() {
    auto width = this->ui->renderarea->getLineWidth();
    auto color = this->ui->renderarea->getRectColor();
    auto modelDialog = new Dialog(width, color, this);
    double chi_tmp = 0;
    auto exp_freq = std::vector<double>(0, 0); // histograms


    if (modelDialog->exec() == QDialog::Accepted) {
        modelDialog->activateModel(chi_tmp, exp_freq);

        ui->renderarea->getMenu() = Menu::Model;
        ui->renderarea->getSampleSize() = modelDialog->getSampleSize();
        ui->renderarea->getRectColor() = modelDialog->getRectColor();
        ui->renderarea->getChi() = modelDialog->getChi();

        ModelType temp  =modelDialog->getModelType();
        if (temp == ModelType::Bern)
            ui->renderarea->getModelType() = ModellingType::Bern;
        else if (temp == ModelType::Inv)
            ui->renderarea->getModelType() = ModellingType::Inv;

//        ui->renderarea->getChi() = modelDialog->activateModel(chi_tmp, 0, exp_freq);
        ui->renderarea->getP() =    modelDialog->getP();
        ui->renderarea->getExpFreq() =  exp_freq;



    }
}

/* If Color was chosen - draw a rectangle */
void MainWindow::on_actionPval_triggered() {
    auto col = ui->renderarea->getRectColor();
    auto color = QColorDialog::getColor(col, this, "Select color", QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        ui->renderarea->getRectColor() = color;
        ui->renderarea->getMenu() = Menu::Pval;
    }
}


void MainWindow::on_actionHi_triggered() {

      auto dialog = new Intro(this);

      dialog->show();
      dialog->raise();
      dialog->activateWindow();
}

void MainWindow::on_actionExit_triggered(){
    QApplication::exit();
}

MainWindow::~MainWindow() {
    delete ui;
}
