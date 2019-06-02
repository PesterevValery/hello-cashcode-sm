#include "billvalidatorcontroller.h"

const CBillValidatorController::CmdListT CBillValidatorController::m_CmdList = {
    { '\x02', '\x03', '\x06', '\x00', '\xC2', '\x82' }, // CMD_Ack
    { '\x02', '\x03', '\x06', '\x30', '\x41', '\xB3' }, // CMD_Reset
    { '\x02', '\x03', '\x06', '\x31', '\xC8', '\xA2' }, // CMD_GetStatus
    { '\x02', '\x03', '\x06', '\x33', '\xDA', '\x81' }, // CMD_Poll
    { '\x02', '\x03', '\x06', '\x37', '\xFE', '\xC7' }, // CMD_Identification
    { '\x02', '\x03', '\x06', '\x41', '\x4F', '\xD1' }, // CMD_GetBillTable
    { '\x02', '\x03', '\x06', '\x35', '\xEC', '\xE4' }, // CMD_Stack
    { '\x02', '\x03', '\x06', '\x36', '\x77', '\xD6' }, // CMD_Return
    { '\x02', '\x03', '\x06', '\x38', '\x09', '\x3F' }, // CMD_Hold
    { '\x02', '\x03', '\x06', '\x3A', '\x1B', '\x1C' }, // CMD_ExtractBarcodeData
    { '\x02', '\x03', '\x06', '\x60', '\xC4', '\xE1' }, // CMD_RequestStatistic
    { '\x02', '\x03', '\x0C', '\x34', '\xFF', '\xFF',
      '\xFF', '\x00', '\x00', '\x00', '\xB5', '\xC1' }, // CMD_EnableBillTypes
    { '\x02', '\x03', '\x0C', '\x34', '\x00', '\x00',
      '\x00', '\x00', '\x00', '\x00', '\x17', '\x0C' }  // CMD_DisableBillTypes
};


CBillValidatorController::CBillValidatorController(QObject *parent) :
    QObject(parent), m_Serial(new QSerialPort(this))
{ }

bool CBillValidatorController::OpenSerialPort(QString _port_name) {
    m_Serial->setPortName(_port_name);
    m_Serial->setBaudRate(9600);
    m_Serial->setDataBits(QSerialPort::Data8);
    m_Serial->setParity(QSerialPort::NoParity);
    m_Serial->setStopBits(QSerialPort::OneStop);
    m_Serial->setFlowControl(QSerialPort::NoFlowControl);

    const int tries_count = 3; // 30;
    const int sleep_time = 100;
    m_Serial->open(QIODevice::ReadWrite);
    for(int i = 0; i < tries_count && !m_Serial->isOpen(); i++) {
        thread()->msleep(sleep_time);
        m_Serial->open(QIODevice::ReadWrite);
    }
    return m_Serial->isOpen();
}

void CBillValidatorController::CloseSerialPort() {
    if (m_Serial->isOpen())
        m_Serial->close();
}


const CBillValidatorController::CmdT& CBillValidatorController::GetCmd(int _index) const {
    return m_CmdList[_index];
}
const CBillValidatorController::CmdT& CBillValidatorController::GetCmd(CBillValidatorController::CMD _name) const {
    return GetCmd((int)_name); // m_CmdList[(int)_name];
}

void CBillValidatorController::SendCmd(int _index) const {
    SendCmd(GetCmd(_index));
}

qint64 CBillValidatorController::SendCmd(const CmdT& _cmd) const {
    return m_Serial->write(_cmd.data(), _cmd.size());
}
