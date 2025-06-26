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
#include<QCheckBox>
#include<QProcess>
#include<QProgressDialog>
#include<QToolButton>

#ifndef AYAR_H
#define AYAR_H

QWidget *MainWindow::ayar()
{

    QWidget *ayarPage=new QWidget();
     QFont f2( "Arial", font.toInt()-2, QFont::Normal);
    /*******************************************************/

    QToolButton *webblockWidgetButton= new QToolButton;
    webblockWidgetButton->setFixedSize(QSize(boy*30,boy*10));
    webblockWidgetButton->setIconSize(QSize(boy*5,boy*5));
    webblockWidgetButton->setStyleSheet("Text-align:center");
    webblockWidgetButton->setIcon(QIcon(":/icons/webblock.svg"));
    //webblockWidgetButton->setAutoRaise(true);
    webblockWidgetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    webblockWidgetButton->setFont(f2);
    webblockWidgetButton->setText("Web Block Filtresi");

    connect(webblockWidgetButton, &QPushButton::clicked, [=]() {
        webBlockWidget();
    });
    QToolButton *networkProfilWidgetButton= new QToolButton;
    networkProfilWidgetButton->setFixedSize(QSize(boy*30,boy*10));
    networkProfilWidgetButton->setIconSize(QSize(boy*5,boy*5));
    networkProfilWidgetButton->setStyleSheet("Text-align:center");
    networkProfilWidgetButton->setIcon(QIcon(":/icons/session.svg"));
    //networkProfilWidgetButton->setAutoRaise(true);
    networkProfilWidgetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    networkProfilWidgetButton->setFont(f2);
    networkProfilWidgetButton->setText("Ağ Profili");

    connect(networkProfilWidgetButton, &QPushButton::clicked, [=]() {
        networkProfil();
    });

    auto layout = new QGridLayout(ayarPage);
    layout->setContentsMargins(0, 0, 0,0);

    layout->addWidget(networkProfilWidgetButton, 7,0,1,1);
    layout->addWidget(webblockWidgetButton, 8,0,1,1);



    return ayarPage;
}


#endif // AYAR_H
