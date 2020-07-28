#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

}


void MainWindow::ShowMessage(QString title, QString body)
{
    QMessageBox msgBox( "", body,  QMessageBox::Information, 0, 0, 0, nullptr, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    msgBox.QDialog::setWindowTitle(title);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
}
