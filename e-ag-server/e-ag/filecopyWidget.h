#ifndef FILECOPYWIDGET_H
#define FILECOPYWIDGET_H

QWidget*  MainWindow::fileWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7.5;
    QWidget * d = new QWidget();
    d->setWindowTitle("ssh Dosya Kopyalama Penceresi");
    QLineEdit *le = new QLineEdit();
    le->setFixedSize(e*75,boy*15);
    le->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    // le->setFont(ff);
    /*QLineEdit * ple = new QLineEdit();
    ple->setFixedSize(e*61,boy*7);
    ple->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");
*/
    QLabel *commandFileLabel=new QLabel("Dosya");
    commandFileLabel->setFixedSize(e*7,yukseklik);
    commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
/*
    QLabel *pathLabel=new QLabel("Hedef Konum\n/home/user/\n/tmp/");
    pathLabel->setFixedSize(e*12,yukseklik);
    pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
*/


    fileSelectButton=new QToolButton();
    fileSelectButton->setFixedSize(e*13,yukseklik*2);
    fileSelectButton->setAutoRaise(true);
    //fileSelectButton->setAutoFillBackground(true);
    fileSelectButton->setText("Dosya\nSeç");
    fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
    fileSelectButton->setIconSize(QSize(b*6,yukseklik*0.9));
    fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileSelectButton, &QToolButton::clicked, [=]() {
        //pcClickSlot(pcMac->text());
        QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),QDir::homePath(), tr("Files (*)"));
        le->setText(fileName);

        QFileInfo fi(le->text());

        mesajSlot("Dosya Seçildi.");
    });


    fileCopyButton=new QToolButton();
    fileCopyButton->setFixedSize(e*13,yukseklik*2);
    fileCopyButton->setAutoRaise(true);
    fileCopyButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyButton->setText("Pc'lere\nKopyala");
    fileCopyButton->setIcon(QIcon(":/icons/selectcopyfile.svg"));
    fileCopyButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        //QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");

        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                selectFileCopySlot("homesendfile",onlinePcList[i]->ip, pth.fromPercentEncoding(name1.toUtf8()),ad+"."+uzanti);

                /*sshSelectFileCopySlot( pth.fromPercentEncoding(name1.toUtf8()),"/tmp/"+ad+"."+uzanti);
                         sshCommandSlot("cp /tmp/"+ad+"."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
                         sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/"+ad+"."+uzanti,btnlist[i]->ip);
                         sshCommandSlot("chown "+btnlist[i]->user+":"+btnlist[i]->user+" /home/"+btnlist[i]->user+"/Masaüstü/"+ad+"."+uzanti,btnlist[i]->ip);
*/
            }
        }

        // mesajSlot("Dosya Masaüstlerine Gönderildi.");

        //         sshSelectFileCopySlot(pth.fromPercentEncoding(name.toUtf8()),ple->text());
        mesajSlot("Dosya Seçili Pc'ye Kopyalandı.");
    });

    fileCopyInstallButton=new QToolButton();
    fileCopyInstallButton->setFixedSize(e*13,yukseklik*2);
    fileCopyInstallButton->setAutoRaise(true);
    fileCopyInstallButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyInstallButton->setText("Paketi\nKur");
    fileCopyInstallButton->setIcon(QIcon(":/icons/install.svg"));
    fileCopyInstallButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyInstallButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyInstallButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        //qDebug()<<"dosya adı:"<<name<<ad<<uzanti;
        //QString path=QFileInfo(le->text()).canonicalPath();
        // path=le->text().replace("+","\\ ");
        //qDebug()<<"dosya adı:"<<name1;
        QString dosya=QString("cat >/tmp/debeagscript << EOF"
                                "\n#!/bin/bash"
                                "\nset -x"
                                "\napt --fix-broken install -y"
                                "\napt install -f -y"
                                "\napt autoremove -y"
                                "\napt update"
                                "\ndpkg -i --force-all /tmp/%1"
                                "\napt install -f -y"
                                "\nEOF").arg(name);

        system(dosya.toStdString().c_str());
        /*****************************************************************************/
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                selectFileCopySlot("realdebsendfile",onlinePcList[i]->ip,pth.fromPercentEncoding(name1.toUtf8()),name);
                //system("sleep 0.1");
                selectFileCopySlot("debscriptsendfile",onlinePcList[i]->ip, "/tmp/debeagscript","debeagscript");
            }
        }

        /*sshSelectFileCopySlot("/tmp/eaginstall","");
             sshSelectPcCommandSlot("chmod 755 eaginstall");
             sshSelectPcCommandSlot("bash eaginstall");*/
        mesajSlot("Dosya Seçili Pc'ye Kopyalandı ve Kuruldu.");
    });

    fileCopyInstallScriptButton=new QToolButton();
    fileCopyInstallScriptButton->setFixedSize(e*13,yukseklik*2);
    fileCopyInstallScriptButton->setAutoRaise(true);
    fileCopyInstallScriptButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyInstallScriptButton->setText("Scripti\nÇalıştır");
    fileCopyInstallScriptButton->setIcon(QIcon(":/icons/bash.svg"));
    fileCopyInstallScriptButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyInstallScriptButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyInstallScriptButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        //qDebug()<<"dosya adı:"<<name<<ad<<uzanti;
        //QString path=QFileInfo(le->text()).canonicalPath();
        // path=le->text().replace("+","\\ ");
        //qDebug()<<"dosya adı:"<<name1;
        //qDebug()<<pth.fromPercentEncoding(name1.toUtf8());
        //qDebug()<<ple->text();
        //qDebug()<<name;
        QString dosya=QString("cat >/tmp/eagscript << EOF"
                                "\n#!/bin/bash"
                                "\nset -x"
                                "\napt --fix-broken install -y"
                                "\napt install -f -y"
                                "\napt autoremove -y"
                                "\napt update"
                                "\nbash /tmp/%1"
                                "\napt install -f -y"
                                "\nEOF").arg(name);

        system(dosya.toStdString().c_str());
        /*****************************************************************************/
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                selectFileCopySlot("realscriptsendfile",onlinePcList[i]->ip,pth.fromPercentEncoding(name1.toUtf8()),name);
                //system("sleep 0.1");
                selectFileCopySlot("scriptsendfile",onlinePcList[i]->ip, "/tmp/eagscript","eagscript");
            }
        }
        /*sshSelectFileCopySlot("/tmp/eaginstall","");
             sshSelectPcCommandSlot("chmod 755 eaginstall");
             sshSelectPcCommandSlot("bash eaginstall");*/
        mesajSlot("Script Dosya Seçili Pc'ye Kopyalandı ve Kuruldu.");
    });


    QToolButton *fileCopyDesktopNotGetSendButton=new QToolButton();
    fileCopyDesktopNotGetSendButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopNotGetSendButton->setAutoRaise(true);
    fileCopyDesktopNotGetSendButton->setText("Masaüstüne\nGönder");
    fileCopyDesktopNotGetSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopNotGetSendButton->setIcon(QIcon(":/icons/senddesktopfile.svg"));
    fileCopyDesktopNotGetSendButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopNotGetSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopNotGetSendButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");

        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                selectFileCopySlot("desktopsendfile",onlinePcList[i]->ip, pth.fromPercentEncoding(name1.toUtf8()),ad+"."+uzanti);

                /*sshSelectFileCopySlot( pth.fromPercentEncoding(name1.toUtf8()),"/tmp/"+ad+"."+uzanti);
                         sshCommandSlot("cp /tmp/"+ad+"."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
                         sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/"+ad+"."+uzanti,btnlist[i]->ip);
                         sshCommandSlot("chown "+btnlist[i]->user+":"+btnlist[i]->user+" /home/"+btnlist[i]->user+"/Masaüstü/"+ad+"."+uzanti,btnlist[i]->ip);
*/
            }
        }

        mesajSlot("Dosya Masaüstlerine Gönderildi.");
    });

    QToolButton *fileCopyDesktopSendButton=new QToolButton();
    fileCopyDesktopSendButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopSendButton->setAutoRaise(true);
    fileCopyDesktopSendButton->setText("Çalışma\n Dağıt");
    fileCopyDesktopSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopSendButton->setIcon(QIcon(":/icons/senddesktopquiz.svg"));
    fileCopyDesktopSendButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopSendButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        // QString ad = fi.baseName();
        // qDebug()<<"dosya adı:"<<name<<ad<<uzanti;
        //QString path=QFileInfo(le->text()).canonicalPath();
        // path=le->text().replace("+","\\ ");
        //qDebug()<<"dosya adı:"<<path;
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                selectFileCopySlot("desktopsendworkfile",onlinePcList[i]->ip,pth.fromPercentEncoding(name1.toUtf8()),"e-ag-server."+uzanti);

                /*sshSelectFileCopySlot(pth.fromPercentEncoding(name1.toUtf8()),"/tmp/e-ag-server."+uzanti);
                     sshCommandSlot("mv /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server.* /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server.old",btnlist[i]->ip);
                     sshCommandSlot("cp /tmp/e-ag-server."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
                     sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server."+uzanti,btnlist[i]->ip);
                     sshCommandSlot("chown "+btnlist[i]->user+":"+btnlist[i]->user+" /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server."+uzanti,btnlist[i]->ip);
                    */
            }
        }

        mesajSlot("Dosya Masaüstlerine Gönderildi.");
    });

    QToolButton *fileCopyDesktopGetButton=new QToolButton();
    fileCopyDesktopGetButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopGetButton->setAutoRaise(true);
    //fileCopyDesktopGetButton->setAutoFillBackground(true);
    fileCopyDesktopGetButton->setText("Çalışma\n Topla");
    fileCopyDesktopGetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopGetButton->setIcon(QIcon(":/icons/getdesktopquiz.svg"));
    fileCopyDesktopGetButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopGetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopGetButton, &QToolButton::clicked, [=]() {
        /*for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState)
            {
                udpSendData("x11command","dosyatopla",onlinePcList[i]->ip);


            }
        }*/
        udpSendData("dosyatopla","","");


        mesajSlot("Dosya Masaüstlerinden Alındı.");
    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*13,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText("Yardım");
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik*0.9));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Dosya Kopyalama</h2></center>"
                     "<center><img src=\":/icons/dosyakopyalama.png\" /></center> "
                     "1-Kopyalama işlemi ssh servisi ile yapmaktadır."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "2-İstemci simgelerinin altındaki S işareti ssh servisini ifade eder."
                     "<br/><br/>3-S işareti yeşilse ssh çalışıyor. Kırmızı ise ssh çalışmıyordur."
                     "<br/><br/>4-Sorunsuz kopyalama yapmak için istemcilerde ssh servisinin çalışıyor olması gerekmektedir."
                     "<br/><br/>5-ssh servisinin çalışıp çalışmadığını manuel test etmek için Temel İşlemler bölümünden \"Servis Sorgula\" seçeneğini kullanabilirsiniz."
                     "<br/><br/>6-Klasör içeriğinin tamamını kopyalamak için dosya ismi yerine * konulması gerekir;"
                     "<br/> Örneğin: /home/user/* şeklinde klasör içeriğini kopyalar."
                     "<br/><br/>7-İstemcide açık kullanıcı masaüstüne dosya kopyalama için Masaüstlerine Dağıt seçeneğini kullanabilirsiniz."
                     "<br/><br/>8-İstemcide açık kullanıcı masaüstüne çalışma dosyası göndermek için Çalışmaları Dağıt seçeneğini kullanabilirsiniz."
                     "<br/><br/>9-İstemcide açık kullanıcı masaüstündeki çalışma dosyasını Sunucuya toplamak için Çalışmaları Topla seçeneğini kullanabilirsiniz."
                     "<br/><br/>10-Dosyalar Uzak Kullanıcı ev dizinine kopyalanacaktır."
                     "<br/><br/>10-Dosyalar Uzak Kullanıcı ev dizini dışında başka yere kopyalacaksa \"Hedef Konum\" bölünüde belirtilmelidir."
                     "<br/>Örneğin: /tmp/"
                     "<br/>11-Birden fazla istemciye kopyalama için istemci simgelerine çift tıklayıp seçilerek kopyalanabilir."
                     "<br/>12-Seçili Pc'lere Paket kur seçeneği ile deb uzantılı paketi istemciye kururulumu yapılır."
                     );
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/dosyakopyalama.pdf");
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
        d1->setWindowTitle("Dosya Kopyalama Yardım Penceresi");
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
    //vbox->addWidget(pathLabel,2,1,1,1);
    //vbox->addWidget(ple,2,2,1,1);
    vbox->addWidget(commandFileLabel,1,1,1,1);
    vbox->addWidget(le,1,2,1,1);
    vbox->addWidget(fileSelectButton,1,3,2,1);
    vbox->addWidget(fileCopyInstallButton,1,4,2,1);
    vbox->addWidget(fileCopyInstallScriptButton,1,5,2,1);
    vbox->addWidget(fileCopyButton,1,6,2,1);
    //vbox->addWidget(fileCopyAllButton,1,7,2,1);

    vbox->addWidget(fileCopyDesktopNotGetSendButton,1,8,2,1);

    vbox->addWidget(fileCopyDesktopSendButton,1,9,2,1);
    vbox->addWidget(fileCopyDesktopGetButton,1,10,2,1);


    vbox->addWidget(helpButton,1,11,2,1);

    d->setLayout(vbox);
    return d;
}

void MainWindow::selectFileCopySlot(QString _mesajtype,QString _ip,QString _sourcePath,QString _targetPath)
{
    //int Port     = 12345;
    // QString host = "localhost";

    //SCDImgClient imgc(host,Port,10000); // declare the client obj
    // connect your client desidered events...

    /* imgc.connect(&imgc, &SCDImgClient::notifyConnected,  onConnect);
    imgc.connect(&imgc, &SCDImgClient::notifyDisconnect, onDisconnect);
    imgc.connect(&imgc, &SCDImgClient::notifyError,      onError);
    imgc.connect(&imgc, &SCDImgClient::finished,         onFinished);
    imgc.connect(&imgc, &SCDImgClient::fileReceived,     onFileReceived);
    imgc.connect(&imgc, &SCDImgClient::fileSaving,       onFileSaving);
*/
    // qDebug()<<"kopyalanacak dosya: "<<_sourcePath<<_targetPath;
    //   qDebug()<<"kopyalanacak dosya: "<<_sourcePath<<_targetPath;
    // SCDImgClient imgc("192.168.23.240",12345,10000); // declare the client obj
    // int result=imgc.sendFile(_sourcePath,_targetPath);  // send a file to img server (PUT => upload)
    // qDebug()<<"koplayalama sonucu: "<<result;
    /// for(int i=0;i<onlinePcList.count();i++)
    //{
    // if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
    // {
    //SCDImgClient imgc(onlinePcList[i]->ip,12345,10000); // declare the client obj
    //int result=imgc.sendFile(_sourcePath,_targetPath);  // send a file to img server (PUT => upload)
    qDebug()<<"kopyalanacak dosya: "<<_sourcePath<<_targetPath<<_ip;
    QString komut="/usr/bin/scd-client "+_ip+" 12345 PUT "+_sourcePath+" /"+_targetPath;
    mesajSlot(komut);
    // system(komut.toStdString().c_str());
    QStringList arguments;
    arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished
    udpSendData(_mesajtype,_targetPath,"");
    // }
    //}
    mesajSlot("Dosya Seçili Pc'lere Kopyalandı");
}
void MainWindow::sshFileCopyAllSlot(QString _sourcePath,QString _targetPath)
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        {
            QString komut="nohup sshpass -p "+remotePassword+" scp -o StrictHostKeyChecking=no "+_sourcePath+" "+
                            remoteUserName+"@"+onlinePcList[i]->ip+":"+_targetPath+" &";
            mesajSlot(komut);
            QStringList arguments;
            arguments << "-c" << komut;
            QProcess process;
            process.start("/bin/bash",arguments);
            process.waitForFinished(-1); // will wait forever until finished
        }
    }
    mesajSlot("Komut Ağ'da Çalıştırıldı");
    mesajSlot("Dosya Ağ'da Bütün Pc'lere Kopyalandı");
}
void MainWindow::sshSelectFileCopySlot(QString _sourcePath,QString _targetPath)
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            {
                QString komut="nohup sshpass -p "+remotePassword+" scp -o StrictHostKeyChecking=no "+_sourcePath+" "+
                                remoteUserName+"@"+onlinePcList[i]->ip+":"+_targetPath+" &";
                mesajSlot(komut);
                QStringList arguments;
                arguments << "-c" << komut;
                QProcess process;
                process.start("/bin/bash",arguments);
                process.waitForFinished(-1); // will wait forever until finished
            }
        }
    }
    mesajSlot("Dosya Seçili Pc'lere Kopyalandı");
}

#endif // FILECOPYWIDGET_H
