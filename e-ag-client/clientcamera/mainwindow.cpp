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
#include<QTabWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QRegularExpression>
#include<QTimeEdit>
#include<QDate>
#include<QTimer>
#include<QTime>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QMenu>
#include<QCloseEvent>
#include<QProcess>
#include<QAuthenticator>
#include<QApplication>
#include <stdio.h>
#include <gst/gst.h>
#include <iostream>
#include<gst/gsterror.h>
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
    this->setFixedSize(400,400);
    this->setWindowTitle("Kamera/Video Oynatıcı ");
    /***************************Video**********************************/
    receiverVideo = new QMediaPlayer(this);
    videoWidgetVideo = new QVideoWidget(this);
    receiverVideo->setVideoOutput(videoWidgetVideo);
    receiverVideo->setMedia(QUrl("gst-pipeline: udpsrc port=5000 address=239.0.1.51 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert !  xvimagesink name=qtvideosink"));
    videoWidgetVideo->setStyleSheet("  background-color: rgba(50, 50, 50, 0);");
    videoWidgetVideo->setFixedSize(this->width()*0.8,this->height()*0.8);
    videoWidgetVideo->move(this->width()*0.1,this->height()*0.1);
    videoWidgetVideo->setAspectRatioMode(Qt::IgnoreAspectRatio);
    receiverVideo->play();
    /***************************Audio**********************************/
    receiverAudio = new QMediaPlayer(this);
    receiverAudio->setMedia(QUrl("gst-pipeline: udpsrc port=5001 address=239.0.1.51 ! application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97 ! rtpopusdepay ! opusdec ! autoaudiosink name=qtaudiosink"));
    receiverAudio->play();
}

MainWindow::~MainWindow()
{
  //  delete ui;
}
