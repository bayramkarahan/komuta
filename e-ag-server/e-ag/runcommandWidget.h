#ifndef RUNCOMMANDWIDGET_H
#define RUNCOMMANDWIDGET_H

QWidget* MainWindow::commandWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7.5;
    QWidget * d = new QWidget();
    d->setWindowTitle("ssh Komut Çalıştırma Penceresi");
    commandFileL = new QLineEdit();
    commandFileL->setFixedSize(e*100,boy*15);
    commandFileL->setStyleSheet("font-size:"+QString::number(font.toInt()+5)+"px;");

    //commandFileL->setFont(ff);
    QLabel *commandFileLabel=new QLabel("Komut");
    commandFileLabel->setFixedSize(e*12,yukseklik);

    commandExampleButton=new QToolButton();
    commandExampleButton->setFixedSize(e*15,yukseklik*2);
    commandExampleButton->setAutoRaise(true);
    //commandExampleButton->setAutoFillBackground(true);
    commandExampleButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    commandExampleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    commandExampleButton->setText("Hazır\nKomutlar");
    commandExampleButton->setIcon(QIcon(":icons/command.svg"));
    commandExampleButton->setIconSize(QSize(b*6,yukseklik*0.9));

    commandExampleButton->setMenu(commandExampleMenu());
    commandExampleButton->setPopupMode(QToolButton::InstantPopup);
    // connect(commandExecuteButton, SIGNAL(clicked()),this, SLOT(commandExecuteSlot()));
    connect(commandExampleButton, &QToolButton::clicked, [=]() {

            //  sshButtonSlot();
            //  QMenu *commandExampleMenus=commandExampleMenu();
            //  commandExampleMenus->exec(mapToGlobal(commandExampleButton->pos() + QPoint(0,b*13)));
    });

    commandExecuteButton=new QToolButton();
    commandExecuteButton->setFixedSize(e*24,yukseklik*2);
    commandExecuteButton->setAutoRaise(true);
    // commandExecuteButton->setAutoFillBackground(true);
    commandExecuteButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    commandExecuteButton->setIcon(QIcon(":/icons/network.svg"));
    commandExecuteButton->setIconSize(QSize(b*8,yukseklik*0.9));
    commandExecuteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    commandExecuteButton->setText("Terminalde\nÇalıştır");
    connect(commandExecuteButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
        udpSendData("consolecommand","consolecommand",commandFileL->text());
    });





    QToolButton *x11CommandButton=new QToolButton();
    x11CommandButton->setFixedSize(e*24,yukseklik*2);
    x11CommandButton->setAutoRaise(true);
    //x11CommandButton->setAutoFillBackground(true);
    x11CommandButton->setText("Masaüstlerinde\n Çalıştır");
    x11CommandButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    x11CommandButton->setIcon(QIcon(":/icons/user.svg"));
    x11CommandButton->setIconSize(QSize(b*8,yukseklik*0.9));
    x11CommandButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(x11CommandButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
        udpSendData("x11command","x11command",commandFileL->text());
    });





    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*12,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText("Yardım");
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik*0.9));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Komut Çalıştırma</h2></center>"
                     "<center><img src=\":/icons/sshcommand.png\" /></center> "
                     "<br/>1-Komutlar ssh servisi ile çalıştırılmaktadır."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/>2-İstemci simgelerinin altındaki S işareti ssh servisini ifade eder."
                     "<br/><br/>3-S işareti yeşilse ssh çalışıyor. Kırmızı ise ssh çalışmıyordur."
                     "<br/><br/>4-Sorunsuz komut çalıştırmak için istemcilerde ssh servisinin çalışıyor olması gerekmektedir."
                     "<br/><br/>5-ssh servisinin çalışıp çalışmadığını manuel test etmek için Temel İşlemler bölümünden \"Servis Sorgula\" seçeneğini kullanabilirsiniz."
                     "<br/><br/>6-Komutlar Uzak Kullanıcı hesabı üzerinden çalıştırılmaktadır."
                     "<br/><br/>7-Uzak Kullanıcı Ayarlar bölümünden Uzak/Yerel Hesaplar seçeneğinden ayarlanmaktadır."
                     "<br/><br/>8-İstemcide Uzak Kullanıcı hesabında işlemler olduğu için dikkatli olmak gerekmektedir."
                     "<br/>Örneğin, \"rm cp mv mkdir rmdir vb.\" komutlar Uzak Kullanıcı ev dizini üzerinde yapılır."
                     "<br/><br/>9-Birden fazla istemcide komut çalıştırmak için istemci simgelerine çift tıklayıp seçilerek çalıştırılabilir."
                     "<br/><br/>10-İstemcilerde script dosyası çalıştırmak için;"
                     "<br/>Örneğin: install.sh dosyasını bash install.sh şeklinde yazıp istemcilerde çalıştırabiliriz."
                     );
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/sshcommand.pdf");
        pdf.setOutputFormat(QPrinter::PdfFormat);
        doc->print(&pdf);

        QTextEdit *document = new QTextEdit();
        document->setReadOnly(true);
        //  document->show();
        document->setDocument(doc);
        QVBoxLayout * vbox = new QVBoxLayout();
        QHBoxLayout * hbox1= new QHBoxLayout();

        // hbox1->addWidget(commandFileLabel);
        hbox1->addWidget(document);

        vbox->addLayout(hbox1);
        QDialog * d1 = new QDialog();
        d1->setWindowTitle("Komut Çalıştırma Yardım Penceresi");
        d1->setFixedSize(QSize(boy*150,boy*120));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();
    });


    QGridLayout * vbox = new QGridLayout();
    vbox->setContentsMargins(0, 0, 0,0);
    vbox->setVerticalSpacing(0);

    vbox->addWidget(commandFileLabel,1,1,2,1);
    vbox->addWidget(commandExampleButton,1,2,2,1);

    vbox->addWidget(commandFileL,1,3,2,1);

    vbox->addWidget(commandExecuteButton,1,4,2,1);
    //vbox->addWidget(commandExecuteAllButton,1,5,2,1);

    vbox->addWidget(x11CommandButton,1,6,2,1);
    //vbox->addWidget(x11CommandAllButton,1,7,2,1);

    vbox->addWidget(helpButton,1,8,2,1);


    d->setLayout(vbox);

    return d;

}

void MainWindow::slotCommand(QString _kmt)
{
    udpSendData("x11command",_kmt,"");
    /*for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            udpSendData("x11komut",_kmt,onlinePcList[i]->ip);
        }
    }*/
    mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");

}

void MainWindow::slotPcCommandSelect(QString _kmt){
    udpSendData("x11command",_kmt,"");
    /*for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->select||onlinePcList[i]->multiSelect)
        {
            udpSendData("x11komut",_kmt,onlinePcList[i]->ip);

        }
    }*/
    mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");

}
void MainWindow::slotPcCommandAll(QString _kmt){

    udpSendData("x11command",_kmt,"");


    /*for(int i=0;i<onlinePcList.count();i++)
    {

        udpSendData("x11komut",_kmt,onlinePcList[i]->ip);


    }*/
    mesajSlot("Komut Tüm Hostlarda Çalıştırıldı.");

}

#endif // RUNCOMMANDWIDGET_H
