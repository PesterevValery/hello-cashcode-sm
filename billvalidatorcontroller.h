#ifndef BILLVALIDATORCONTROLLER_H
#define BILLVALIDATORCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>

#include <vector>

class CBillValidatorController : public QObject {
    Q_OBJECT
public:
    enum CMD {
        CMD_Ack = 0,
        CMD_Reset,
        CMD_GetStatus,
        CMD_Poll,
        CMD_Identification,
        CMD_GetBillTable,
        CMD_Stack,
        CMD_Return,
        CMD_Hold,
        CMD_ExtractBarcodeData,
        CMD_RequestStatistic,
        CMD_EnableBillTypes,
        CMD_DisableBillTypes
    };

    using CmdT = std::vector<char>;
    using CmdListT = std::vector<CmdT>;

    explicit CBillValidatorController(QObject *parent = nullptr);

    bool OpenSerialPort(QString _port_name);
    void CloseSerialPort();

    const CmdT& GetCmd(int _index) const;
    const CmdT& GetCmd(CMD _name) const;

public slots:
    void SendCmd(int _index) const;

private:
    qint64 SendCmd(const CmdT& _cmd) const;

    QSerialPort* m_Serial = nullptr;

    static const CmdListT m_CmdList;
};

#endif // BILLVALIDATORCONTROLLER_H
