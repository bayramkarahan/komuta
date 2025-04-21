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
#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QLockFile>
#include <QDir>
#include<pcdata.h>
#include "scdimgserver.h"
#include <QSettings>
#include <QApplication>
#include <QPushButton>
//! [0]
#include <QTranslator>
#define  echo QTextStream(stderr) <<

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //return a.exec();
    QLocale locale;
    QString systemlanguage = locale.name();
    //qDebug()<<"Sistem dili:"<<systemlanguage;


/*
    QTranslator *translator = new QTranslator();
    translator->load("translations/"+language+".qm");
    qApp->installTranslator(translator);
*/

    MainWindow *w=new MainWindow();
    w->networkProfilLoad();
    int ftpPort=0;
    QString rootPath="";

    for (const NetProfil &item : w->NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
        ftpPort=item.ftpPort.toInt();
        rootPath=item.rootPath;
    }
qDebug()<<"rootpath: "<<rootPath;
    SCDImgServer srv(0,ftpPort,rootPath);

    if (srv.start())
    {

        w->show();
        return a.exec();
    }

    return 0;
}
