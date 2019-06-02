#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

#include "billvalidatorcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void ButtonPushed(int _id);
private:
    Ui::MainWindow *ui;

    QButtonGroup* m_BtnGroup = new QButtonGroup(this);
    CBillValidatorController* m_BVCtrlr = nullptr;
};

#endif // MAINWINDOW_H
