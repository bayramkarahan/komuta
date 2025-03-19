#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Задаём два пункта с текстом локалей в комбобоксе
    ui->comboBox->addItems(QStringList() << "ru" << "en"<<"tr");

    // подключаем к сигналу изменения пункта комбобокса лямбда функцию,
    // в которой будет изменяться перевод приложения
    // Здесь имеется интересный момент. Поскольку QComboBox имеет перегрузку сигнатуры сигнала,
    // то нам необходимо скастовать сигнал к нужной сигнатуре.
    // В данном случае будем использовать название пункта при его изменении
    connect(ui->comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str){
        qtLanguageTranslator.load("QtLanguage_" + str, ".");   // Загружаем перевод
        qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
        qDebug()<<"dil değişti";
    });

    // Сделаем первоначальную инициализацию перевода для окна прилоежния
    qtLanguageTranslator.load(QString("QtLanguage_") + QString("ru"));
    qApp->installTranslator(&qtLanguageTranslator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{

    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);    // переведём окно заново
        qDebug()<<"aaa değişti"<<event->type() ;
    }
}

void MainWindow::on_pushButton_clicked()
{
    qtLanguageTranslator.load("QtLanguage_tr",".");   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
    qDebug()<<"dil değişti";
    ui->retranslateUi(this);    // переведём окно заново
   // qDebug()<<"aaa değişti"<<event->type() ;
}


void MainWindow::on_pushButton_2_clicked()
{
    qtLanguageTranslator.load("QtLanguage_ru", ".");   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
    qDebug()<<"dil değişti";
    ui->retranslateUi(this);    // переведём окно заново
    //qDebug()<<"aaa değişti"<<event->type() ;

}

