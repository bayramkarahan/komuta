/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef MYPC_H
#define MYPC_H

#include <QWidget>
#include<QLabel>
#include<QToolButton>
#include<QPushButton>
#include <QTimer>
#include<QCheckBox>
#include<QWidgetAction>
#include<QObject>
#include<QDesktopWidget>
#include<QScreen>
#include<pcdata.h>
#include<QDesktopServices>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<Database.h>
#include <QCoreApplication>

class MyPc: public QWidget
{
    Q_OBJECT
public:
    explicit MyPc(const QString _mac, QString _ip, QWidget *parent = nullptr);
    ~MyPc();
    enum { Type =  20 };

        int type()
        {
            // Enable the use of qgraphicsitem_cast with this item.
            return Type;
        }
        bool iconState=false;
        bool iconControlState=false;
        bool pcState;
        bool sshState;
        bool vncState;
        bool ftpState;
        bool connectState;
        bool kilitState=false;
        bool kilitControlState=false;
        bool transparanKilitState=false;
        bool transparanKilitControlState=false;
        int tcpConnectCounter=0;
        QString font="12";
        QString mac;
        QString ip;
        QString user;
        QString hostname;
        QString caption;
        bool visibleState=true;

        QString vncport=0;
        bool select;
        bool multiSelect;

protected:
void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
void pcClickSignal(QString mac);
void pcRightClickSignal();
void pcListeSignal();
void pcHideSignal(QString _mac);
void pcListeStateSignal();
void pcTcpPortControlSignal(QString mac,QString ip);
void pcSshPortControlSignal(QString mac,QString ip);
void pcVncPortControlSignal(QString mac,QString ip);
void pcFtpPortControlSignal(QString mac,QString ip);
void pcKilitStateControlSignal(QString mac,QString ip,bool _kilitstate);
void pcKilitTransparanStateControlSignal(QString mac,QString ip,bool _transparankilitstate);
void pcIconStateControlSignal(QString mac,QString ip,bool _iconstate);
void pcMenuSignal(QString mac,QString ip,QString _slot);

public slots:
void setSize(int _w, int _h, QString _font);
//void setCaption(QString cap);
//void setDisplay(QString _dis);
void setUser(QString _os);
void setHostname(QString _hostname);
//void setAcount(QString username, QString password);
void setKilitControlState(bool state);
void setKilitTransparanControlState(bool state);
void setIconControlState(bool state);

void setConnectState(bool state);
void setPcState(bool state);
void setSshState(bool state);
void setVncState(bool state);
void setFtpState(bool state);
void slotMouseClick();
void slotMouseDoubleClick();
void slotSelectPc();
void slotUnselectPc();
void slothidePc();
private slots:
//void pcselectMenu();
QString  getIpPortStatus(QString ip_,QString port);
void slotPcAyar();

private:


bool refreshContinueState=false;
    QTimer *timerPortControl;
    QTimer *timerPortControlOnline;
    QString localDir;


   // QString mac;

    qreal w;
    qreal h;

    QToolButton *btnayar;
    QLabel *hostnameLabel;
    QLabel *pcstateLabel;
    QLabel *sshstateLabel;
    QLabel *vncstateLabel;
    QLabel *connectstateLabel;
    QLabel *ftpstateLabel;
    QLabel *selectLabel;
    QLabel *userstateLabel;
    QLabel *iconstateLabel;

    QMediaPlayer *receiver;
    QVideoWidget *videoWidget;

};

#endif // MYPC_H
