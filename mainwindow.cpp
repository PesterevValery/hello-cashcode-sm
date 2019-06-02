#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_BVCtrlr(new CBillValidatorController(this))
{
    ui->setupUi(this);

    QLayout* layout = ui->buttonsVLayout;
    for(int i = 0; i < layout->count(); i++) {
        QPushButton* button = (QPushButton*)layout->itemAt(i)->widget();
        m_BtnGroup->addButton(button, i);
    }
    connect(m_BtnGroup, SIGNAL(buttonClicked(int)), m_BVCtrlr, SLOT(SendCmd(int)));
    connect(m_BtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(ButtonPushed(int)));
}

MainWindow::~MainWindow() { delete ui; }

QString ByteToStr(uchar _byte) {
    char str[3] = "00";
    int num = _byte / 16;
    str[0] = num < 10 ? '0' + num : 'A' + num - 10;
    num = _byte % 16;
    str[1] = num < 10 ? '0' + num : 'A' + num - 10;
    return str;
}

void MainWindow::ButtonPushed(int _id) {
    const CBillValidatorController::CmdT& cmd = m_BVCtrlr->GetCmd(_id);
    QString cmd_str = "-> ";
    for(uchar byte : cmd)
        cmd_str += ByteToStr(byte) + " ";
    ui->listWidget->addItem(cmd_str);
}
