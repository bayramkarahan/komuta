#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTranslator>
#include<QDebug>
#include<QLocale>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QLocale locale;
    QString language = locale.name();
    std::cout << "Sistem dili: " << language.toStdString() << std::endl;

    ui->setupUi(this);
        ui->label->setText(tr("Merhaba Dünya!"));
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){
                QTranslator *translator = new QTranslator(this);
                if (index == 0) { // Türkçe
                    qDebug()<<"türkçe seçildi";
                    translator->load("translations/untitled_tr.qm");
                } else if (index == 1) { // İngilizce
                    qDebug()<<"ingilizce seçildi";
                    translator->load("translations/untitled_en.qm");
                }
                qApp->installTranslator(translator);
                ui->retranslateUi(this);
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}
