#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private slots:
    void onAddNew();
};