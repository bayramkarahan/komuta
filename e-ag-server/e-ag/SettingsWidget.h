#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
QWidget* MainWindow::settingsWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*14;
    QWidget * d = new QWidget();
    //d->setFixedSize(this->width(),boy*16);

    d->setWindowTitle("Duyuru Mesaj Penceresi");

    QToolButton *acountButton=new QToolButton();
    acountButton->setFixedSize(e*27,yukseklik);
    acountButton->setAutoRaise(true);
    // duyuruButton->setAutoFillBackground(true);
    acountButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    acountButton->setText("Ağ Profilleri");
    acountButton->setIcon(QIcon(":/icons/session.svg"));
    acountButton->setIconSize(QSize(b*8,b*8));
    acountButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(acountButton, &QToolButton::clicked, [=]() {
        networkProfil();
    });



    QToolButton *macListe1Button=new QToolButton();
    macListe1Button->setFixedSize(e*27,yukseklik);
    macListe1Button->setAutoRaise(true);
    // macListe1Button->setAutoFillBackground(true);
    macListe1Button->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    macListe1Button->setText("İstemci Liste");
    macListe1Button->setIcon(QIcon(":/icons/maclist.svg"));
    macListe1Button->setIconSize(QSize(b*8,yukseklik/2));
    macListe1Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(macListe1Button, &QToolButton::clicked, [=]() {

        HostListWidget()->show();
    });


    QToolButton *webblockButton= new QToolButton;
    webblockButton->setFixedSize(e*27,yukseklik);
    webblockButton->setAutoRaise(true);
    // webblockButton->setAutoFillBackground(true);
    webblockButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    webblockButton->setText("Web Engelleme");
    webblockButton->setIcon(QIcon(":/icons/webblock.svg"));
    webblockButton->setIconSize(QSize(b*8,yukseklik/2));
    webblockButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    connect(webblockButton, &QToolButton::clicked, [=]() {
        webBlockWidget();

    });




    QToolButton *clientUpdateButton= new QToolButton;
    clientUpdateButton->setFixedSize(e*29,yukseklik);
    clientUpdateButton->setAutoRaise(true);
    // clientUpdateButton->setAutoFillBackground(true);
    clientUpdateButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    clientUpdateButton->setText("İstemci Ayarlarını Güncelle");
    clientUpdateButton->setIcon(QIcon(":/icons/clientrefresh.svg"));
    clientUpdateButton->setIconSize(QSize(b*8,yukseklik/2));
    clientUpdateButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(clientUpdateButton, &QToolButton::clicked, [=]() {
        QString kmt="rm "+QDir::homePath()+"/.ssh/known_hosts";
        system(kmt.toStdString().c_str());
        sshCommandAllSlot("systemctl stop e-ag-client.service");
        system("sleep 1");
        sshCommandAllSlot("systemctl start e-ag-client.service");
        system("sleep 1");
        sshCommandAllSlot("systemctl restart e-ag-client.service");
        system("sleep 1");
        sshCommandAllSlot("sed -i 's/#write_enable=YES/write_enable=YES/' /etc/vsftpd.conf");
        system("sleep 1");
        sshCommandAllSlot("systemctl restart vsftpd.service");

    });

    QToolButton *clientShowButton= new QToolButton;
    clientShowButton->setFixedSize(e*27,yukseklik);
    clientShowButton->setAutoRaise(true);
    // clientShowButton->setAutoFillBackground(true);
    clientShowButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    clientShowButton->setText("Gizli Bilgisayarlar");
    clientShowButton->setIcon(QIcon(":/icons/showhost.svg"));
    clientShowButton->setIconSize(QSize(b*8,yukseklik/2));
    clientShowButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(clientShowButton, &QToolButton::clicked, [=]() {
        hideShowPcSlot();
    });

    QToolButton *bilgiButton= new QToolButton;
    bilgiButton->setFixedSize(e*20,yukseklik);
    bilgiButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    bilgiButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    bilgiButton->setText("Hakkında");
    bilgiButton->setIcon(QIcon(":/icons/about.svg"));
    bilgiButton->setIconSize(QSize(b*8,yukseklik/2));
    bilgiButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(bilgiButton, &QToolButton::clicked, [=]() {
        bilgiAlButtonSlot();

    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*20,yukseklik);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText("Yardım");
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik/2));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Ayarlar</h2></center>"
                     "<center><img src=\":/icons/ayar.png\"></center> "

                     "Uygulamanın sorunsuz çalışması için;"

                     "<center><img src=\":/icons/userayar.png\"/></center>"
                     "1-Kontrol edilecek istemcilerin(Uzak Bilgisayar) kullanıcı adı ve parolası aynı olmalıdır."
                     "<br/><br/>2-Uygulamanın kurulu olduğu makine yönetici hesabıyla açılmış olmalı.."
                     "<br/><br/>3-Uygulamadaki Yerel Ağ: bulunduğumuz ağ örn:192.168.1.255 şeklinde girilmeli."
                     "<br/><br/>4-Uygulamadaki Tcp Port: yazılımın kullandığı port boş bırakılırsa 7879 olarak ayarlar."
                     "<br/><br/>5-Bu bilgiler kaydedildikten sonra mutlaka yazılım yeniden başlatılmalı."
                     "<br/><br/>6-Yapılan parola, ip ve port değişikliklerini İstemcilerin algılaması için;"
                     " Ayarlar menüsünden İstemci Ayarlarını Güncelle seçilmelidir.."
                     "<br/><br/>7-İstemcilerin listesini İstemci Listele seçeneği ile yapabilir ve listeyi yazdırabiliriz."
                     "<br/><br/>8-Gizlenmiş istemcileri tekrar listede görünmesi için Gizli İstemcileri Göster seçeneğini kullanabilirsiniz."
                     "<br/><br/>9-İstemcilerde web sitesini kelime bazlı kısıtlamaları için;"
                     " Web Engeleme seçeneğini kullanabilirsiniz."
                     );
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/ayar.pdf");
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
        d1->setWindowTitle("Ayarlar Yardım Penceresi");
        d1->setFixedSize(QSize(boy*190,boy*127));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();


    });

    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    layout->addWidget(acountButton, 0,0,1,1,Qt::AlignCenter);
    //layout->addWidget(clientUpdateButton, 0,1,1,1,Qt::AlignCenter);
    layout->addWidget(macListe1Button, 0,2,1,1,Qt::AlignCenter);
    layout->addWidget(webblockButton, 0,3,1,1,Qt::AlignCenter);
    layout->addWidget(clientShowButton, 0,4,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 0,5,1,1,Qt::AlignCenter);
    layout->addWidget(bilgiButton, 0,6,1,1,Qt::AlignCenter);

    d->setLayout(layout);

    return d;

}

void MainWindow::hideShowPcSlot()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Gizli Bilgisayar Listesi");
    d->setFixedSize(QSize(boy*100,boy*65));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*95,boy*50));
    twlh->setColumnCount(5);
    //twlh->setRowCount(0);

    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem("Seç"));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem("Ip"));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem("Mac"));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem("Adı"));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem("Host"));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*5);
    twlh->setColumnWidth(1, boy*20);
    twlh->setColumnWidth(2,boy*15);
    twlh->setColumnWidth(3,boy*24);
    twlh->setColumnWidth(4,boy*24);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        if (!veri.value("visibleState").toBool())
        {
            twlh->setRowCount(twlh->rowCount()+1);
            QCheckBox *mCheck = new QCheckBox();
            mCheck->setChecked(false);
            twlh->setCellWidget(sr,0,mCheck);
            //qDebug()<<"Kayıtlı Host.";
            twlh->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
            twlh->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
            twlh->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
            twlh->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
            sr++;
        }

    }

    /********************************************************************/
    QToolButton *showPcButton= new QToolButton;
    showPcButton->setFixedSize(QSize(boy*40,boy*10));
    showPcButton->setIconSize(QSize(boy*40,boy*5));
    showPcButton->setStyleSheet("Text-align:center");
    showPcButton->setIcon(QIcon(":/icons/boot.svg"));
    showPcButton->setAutoRaise(true);
    showPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // showPcButton->setFont(f2);
    showPcButton->setText("Seçili Bilgisayarı Göster");

    connect(showPcButton, &QPushButton::clicked, [=]() {
        int numRows = twlh->rowCount();
        bool updateState=false;
        DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
        for ( int i = 0 ; i < numRows ; i++)
        {
            QCheckBox* mBox = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
            if (mBox->isChecked())
            {
                QString _mac = twlh->model()->data(twlh->model()->index(i, 1)).toString().simplified();
                QJsonArray dizi=db->Ara("mac",_mac);
                if(dizi.count()>0)
                {
                    qDebug()<<"Host Görünürlüğü Değiştirilecek."<<_mac;
                    QJsonObject veri=dizi.first().toObject();
                    veri["visibleState"] =true;
                    db->Sil("mac",_mac);
                    db->Ekle(veri);
                    for(int i=0;i<onlinePcList.count();i++)
                    {
                        if(onlinePcList[i]->mac==_mac)
                            onlinePcList[i]->visibleState=true;

                    }
                    updateState=true;
                }
            }
        }
        if(updateState)
        {
            pcListeGuncelleSlotnew("visibleStateUpdate");
            d->close();
        }
    });
    /*********************************************************************/
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(showPcButton);
    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

QWidget* MainWindow::HostListWidget()
{
    int bw,bh;
    bw=en*10;
    bh=boy*10;
    QDialog *wd=new QDialog();
    wd->setWindowTitle("İstemci Listesi");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    wd->setWindowIcon(appIcon);
    wd->setFixedSize(en*95,boy*60);
    wd->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - wd->width())/2;
    int y = (screenGeometry.height() - wd->height()) / 2;
    wd->move(x, y);
    /***************************************************************/
    QTableWidget *twlh=new QTableWidget(wd);

    twlh->setFixedSize(QSize(boy*93,boy*50));
    twlh->setColumnCount(5);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem("Mac"));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem("Ip"));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem("Adı"));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem("Host"));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem("Listele"));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*20);
    twlh->setColumnWidth(1,boy*15);
    twlh->setColumnWidth(2,boy*20);
    twlh->setColumnWidth(3,boy*20);
    twlh->setColumnWidth(4,boy*10);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        //if (!veri.value("visibleState").toBool())
        //{
        twlh->setRowCount(twlh->rowCount()+1);
        //qDebug()<<"Kayıtlı Host.";
        twlh->setItem(sr, 0, new QTableWidgetItem(veri.value("mac").toString()));//ip
        twlh->setItem(sr, 1, new QTableWidgetItem(veri.value("ip").toString()));//mac
        twlh->setItem(sr, 2, new QTableWidgetItem(veri.value("caption").toString()));//caption
        twlh->setItem(sr, 3, new QTableWidgetItem(veri.value("hostname").toString()));//name
        twlh->setItem(sr, 4, new QTableWidgetItem(veri.value("visibleState").toString()));//name
        sr++;
        //}
    }
    /***************************************************************/
    QToolButton *printButton = new QToolButton(wd);
    printButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    printButton->setIcon(QIcon(":icons/print.svg"));
    printButton->setIconSize(QSize(bw,bh/2));
    printButton->setAutoRaise(true);
    printButton->setAutoFillBackground(true);
    printButton->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    printButton->resize(bw,bh);
    printButton->move(wd->width()/2-bw/2,wd->height()-bh);
    printButton->setText("Yazdır");
    //connect(printButton, SIGNAL(clicked()),this, SLOT(printButtonSlot()));
    connect(printButton, &QPushButton::clicked, [=]() {
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount =twlh->model()->rowCount();
        const int columnCount = twlh->model()->columnCount();
        out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(QString("Ağ IP ve Mac Adres Listesi"))
            <<  "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<table border=1 width=600 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead>";
        out << QString("<tr><th colspan=5>%1</th></tr>").arg(QString("Ağ IP ve Mac Adres Listesi"));

        out<<"<tr bgcolor=#f0f0f0>";

        for (int column = 0; column < columnCount; column++)
            if (!twlh->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(twlh->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column =0; column < columnCount; column++) {

                if (!twlh->isColumnHidden(column)) {
                    QString data = twlh->model()->data(twlh->model()->index(row, column)).toString().simplified();
                    QString bilgi=(!data.isEmpty()) ? data : QString("&nbsp;");
                    if(column==0)
                        out << QString("<td bkcolor=0 style='font-size:12px;'>%1-%2</td>").arg(QString::number(row+1),bilgi);
                    else
                        out << QString("<td bkcolor=0 style='font-size:12px;'>%1</td>").arg(bilgi);
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
               "</body>\n"
               "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
        printer.setOutputFileName(QDir::homePath()+"macliste.pdf");
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }

        delete document;


    });

    //qDebug()<<"Mac Listelendi";
    /// mesajSlot("Mac Adresleri Listelendi.");
    return wd;
}

void MainWindow::webBlockWidget()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Web Filtresi");
    d->setFixedSize(QSize(boy*95,boy*50));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*90,boy*35));
    twlh->setColumnCount(5);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem("Seç"));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem("Index"));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem("Engelenen Kelime"));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem(""));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem(""));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*10);
    twlh->setColumnWidth(1, boy*7);
    twlh->setColumnWidth(2,boy*35);
    twlh->setColumnWidth(3,boy*17);
    twlh->setColumnWidth(4,boy*12);

    DatabaseHelper *db=new DatabaseHelper(localDir+"webblockserver.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();

        twlh->setRowCount(twlh->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setFixedWidth(boy*15);
        mCheck->setChecked(false);
        QLineEdit * index = new QLineEdit();
        QLineEdit * word = new QLineEdit();
        QToolButton *saveButton= new QToolButton;
        saveButton->setText("Kelimeyi Kaydet");
        saveButton->setFixedWidth(boy*17);
        connect(saveButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Değişiklikler Kaydedildi.."<<insertButton->toolTip();
            int numRows = twlh->rowCount();
            for ( int i = 0 ; i < numRows ; i++)
            {
                QCheckBox* mBox = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
                QLineEdit * index = static_cast<QLineEdit*> (twlh->cellWidget(i,1));
                QLineEdit * word = static_cast<QLineEdit*> (twlh->cellWidget(i,2));
                if (index->text()==saveButton->toolTip())
                {
                    QJsonArray dizi=db->Ara("index",saveButton->toolTip());
                    if(dizi.count()>0)
                    {
                        qDebug()<<"Kelime Değiştirilecek."<<saveButton->toolTip();
                        QJsonObject veri;
                        if (mBox->isChecked()) veri["selectedWord"] =true;
                        else veri["selectedWord"] =false;
                        veri["index"] = index->text();
                        veri["word"] = word->text();
                        //qDebug()<<"kelime kayıt"<<veri;
                        db->Sil("index",index->text());
                        db->Ekle(veri);
                    }
                }
            }
            d->close();
            webBlockWidget();
        });
        QToolButton *removeButton= new QToolButton;
        removeButton->setText("Profili Sil");
        removeButton->setFixedWidth(boy*12);
        connect(removeButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Profil Silindi.."<<networkRemoveButton->toolTip();
            QJsonArray dizi=db->Ara("networkIndex",removeButton->toolTip());
            qDebug()<<"Web Kelime Silinecek."<<removeButton->toolTip();
            db->Sil("index",index->text());
            d->close();
            webBlockWidget();
        });



        index->setText(veri.value("index").toString());
        index->setReadOnly(true);
        word->setText(veri.value("word").toString());
        saveButton->setToolTip(index->text());
        twlh->setCellWidget(sr,0,mCheck);
        twlh->setCellWidget(sr,1,index);
        twlh->setCellWidget(sr,2,word);
        twlh->setCellWidget(sr,3,saveButton);
        twlh->setCellWidget(sr,4,removeButton);

        //qDebug()<<"Kayıtlı Host.";
        if(veri.value("selectedWord").toBool())
            mCheck->setChecked(true);
        else
            mCheck->setChecked(false);
        sr++;
    }

    /********************************************************************/
    QToolButton *insertWordButton= new QToolButton;
    insertWordButton->setFixedSize(QSize(boy*40,boy*10));
    insertWordButton->setIconSize(QSize(boy*40,boy*5));
    insertWordButton->setStyleSheet("Text-align:center");
    insertWordButton->setIcon(QIcon(":/icons/boot.svg"));
    insertWordButton->setAutoRaise(true);
    insertWordButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // newNetworkButton->setFont(f2);
    insertWordButton->setText("Yeni Profil Ekle");

    connect(insertWordButton, &QPushButton::clicked, [=]() {
        DatabaseHelper *db=new DatabaseHelper(localDir+"webblockserver.json");
        QJsonObject veri;
        veri["index"] =QString::number(db->getIndex("index"));
        if(db->Oku().size()==0) veri["selectedWord"] =true;
        else veri["selectedWord"] =false;
        veri["word"] = "sample";
        db->Ekle(veri);
        d->close();
        webBlockWidget();
    });

    QToolButton *webAyarGuncelleButton= new QToolButton;
    webAyarGuncelleButton->setFixedSize(QSize(en*40,en*10));
    webAyarGuncelleButton->setIconSize(QSize(en*40,en*5));
    webAyarGuncelleButton->setStyleSheet("Text-align:center");
    webAyarGuncelleButton->setIcon(QIcon(":/icons/clientrefresh.svg"));
    webAyarGuncelleButton->setAutoRaise(true);
    webAyarGuncelleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // webAyarGuncelleButton->setFont(f2);
    webAyarGuncelleButton->setText("Açık Pc'lerin Web Filtre Listesini Güncelle");

    connect(webAyarGuncelleButton, &QPushButton::clicked, [=]() {

        for(int i=0;i<onlinePcList.count();i++)
        {
            if((onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                //qDebug()<<"giden pc"<<onlinePcList[i]->ip;
                selectFileCopySlot("webblockserversendfile",onlinePcList[i]->ip, "/usr/share/e-ag/webblockserver.json","webblockserver.json");
                system("sleep 0.1");
             }
        }
        return;
        hostAddressMacButtonSlot();
        for(int k=0;k<ipmaclist.count();k++)
        {
            for(int i=0;i<onlinePcList.count();i++)
            {
                if(onlinePcList[i]->connectState&&
                    (onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                    ipmaclist[k].ip.section(".",0,2)==onlinePcList[i]->ip.section(".",0,2))
                {
                    udpSendData("webblock",QString::number(webblockstate),onlinePcList[i]->ip);

                }
            }
            system("sleep 0.1");
        }

    });
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(insertWordButton);
    hbox->addWidget(webAyarGuncelleButton);

    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

void MainWindow::networkProfil()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Ağ Profil Listesi");
    d->setFixedSize(QSize(boy*170,boy*50));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*165,boy*35));
    twlh->setColumnCount(12);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem("Seçili Ağ"));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem("Ağ No"));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem("Ağ Adı"));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem("Yayın Ip'si"));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem("Port"));
    twlh->setHorizontalHeaderItem(5, new QTableWidgetItem("ftpPort"));
    twlh->setHorizontalHeaderItem(6, new QTableWidgetItem("rootpath"));
    twlh->setHorizontalHeaderItem(7, new QTableWidgetItem("language"));
    twlh->setHorizontalHeaderItem(8, new QTableWidgetItem("Client Ekran Kilidi"));
    twlh->setHorizontalHeaderItem(9, new QTableWidgetItem("Client Web Filtresi"));
    twlh->setHorizontalHeaderItem(10, new QTableWidgetItem(""));
    twlh->setHorizontalHeaderItem(11, new QTableWidgetItem(""));


    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*10);
    twlh->setColumnWidth(1, boy*10);
    twlh->setColumnWidth(2,boy*20);
    twlh->setColumnWidth(3,boy*15);
    twlh->setColumnWidth(4,boy*10);
    twlh->setColumnWidth(5,boy*10);
    twlh->setColumnWidth(6,boy*10);
    twlh->setColumnWidth(7,boy*10);
    twlh->setColumnWidth(8,boy*20);
    twlh->setColumnWidth(9,boy*20);
    twlh->setColumnWidth(10,boy*10);
    twlh->setColumnWidth(11,boy*10);


    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();

        twlh->setRowCount(twlh->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setFixedWidth(boy*15);
        mCheck->setChecked(false);
        QLineEdit * networkIndex = new QLineEdit();
        QLineEdit * networkName = new QLineEdit();
        QLineEdit * serverAddress = new QLineEdit();
        QLineEdit * networkTcpPort = new QLineEdit();
        QLineEdit * ftpPort = new QLineEdit();
        QLineEdit * rootPath= new QLineEdit();
        QLineEdit * language = new QLineEdit();
        QCheckBox * lockScreenState = new QCheckBox();
        QCheckBox * webblockState = new QCheckBox();


        QToolButton *savetButton= new QToolButton;
        savetButton->setText("Kaydet");
        savetButton->setFixedWidth(boy*10);
        connect(savetButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Değişiklikler Kaydedildi.."<<networkInsertButton->toolTip();
            int numRows = twlh->rowCount();
            for ( int i = 0 ; i < numRows ; i++)
            {

                if (networkIndex->text()==savetButton->toolTip())
                {
                    QJsonArray dizi=db->Ara("networkIndex",savetButton->toolTip());
                    if(dizi.count()>0)
                    {
                        QCheckBox* mBox1 = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
                        QLineEdit * networkIndex1 = static_cast<QLineEdit*> (twlh->cellWidget(i,1));
                        QLineEdit * networkName1 = static_cast<QLineEdit*> (twlh->cellWidget(i,2));
                        QLineEdit * serverAddress1 =static_cast<QLineEdit*> (twlh->cellWidget(i,3));
                        QLineEdit * networkTcpPort1 = static_cast<QLineEdit*> (twlh->cellWidget(i,4));
                        QLineEdit * ftpPort1 = static_cast<QLineEdit*> (twlh->cellWidget(i,5));
                        QLineEdit * rootPath1 = static_cast<QLineEdit*> (twlh->cellWidget(i,6));
                        QLineEdit * language1 = static_cast<QLineEdit*> (twlh->cellWidget(i,7));
                        QCheckBox * lockScreenState1 = static_cast<QCheckBox*> (twlh->cellWidget(i,8));
                        QCheckBox * webblockState1 = static_cast<QCheckBox*> (twlh->cellWidget(i,9));

                        qDebug()<<"Ağ Profili Değiştirilecek."<<savetButton->toolTip();
                        QJsonObject veri;
                        if (mBox1->isChecked()) veri["selectedNetworkProfil"] =true;
                        else veri["selectedNetworkProfil"] =false;
                        veri["networkIndex"] = networkIndex1->text();
                        veri["networkName"] = networkName1->text();
                        veri["networkTcpPort"] = networkTcpPort1->text();
                        veri["networkBroadCastAddress"]=networkName1->toolTip();//dikkat
                        veri["serverAddress"]=serverAddress1->text();
                        veri["ftpPort"]=ftpPort1->text();
                        veri["rootPath"]=rootPath1->text();
                        veri["language"]=language1->text();
                        //veri["lockScreenState"]=lockScreenState->text();
                        //veri["webblockState"]=webblockState->text();
                        if (lockScreenState1->isChecked()) veri["lockScreenState"] =true;
                        else veri["lockScreenState"] =false;
                        if (webblockState1->isChecked()) veri["webblockState"] =true;
                        else veri["webblockState"] =false;
                        //qDebug()<<"network kayıt"<<veri;
                        db->Sil("networkIndex",networkIndex1->text());
                        db->Ekle(veri);
                    }
                }
            }
            d->close();
            networkProfil();
            networkProfilLoad();
        });
        QToolButton *networkRemoveButton= new QToolButton;
        networkRemoveButton->setText("Sil");
        networkRemoveButton->setFixedWidth(boy*10);
        connect(networkRemoveButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Profil Silindi.."<<networkRemoveButton->toolTip();
            QJsonArray dizi=db->Ara("networkIndex",networkRemoveButton->toolTip());
            qDebug()<<"Ağ Profili Silinecek."<<networkRemoveButton->toolTip();
            db->Sil("networkIndex",networkIndex->text());
            d->close();
            networkProfil();
            //networkProfilLoad();
        });

        networkIndex->setText(veri.value("networkIndex").toString());
        networkIndex->setReadOnly(true);
        networkName->setText(veri.value("networkName").toString());
        networkName->setToolTip(veri.value("networkBroadCastAddress").toString());
        serverAddress->setText(veri.value("serverAddress").toString());
        networkTcpPort->setText(veri.value("networkTcpPort").toString());
        ftpPort->setText(veri.value("ftpPort").toString());
        rootPath->setText(veri.value("rootPath").toString());
        language->setText(veri.value("language").toString());

        savetButton->setToolTip(networkIndex->text());
        twlh->setCellWidget(sr,0,mCheck);
        twlh->setCellWidget(sr,1,networkIndex);
        twlh->setCellWidget(sr,2,networkName);
        twlh->setCellWidget(sr,3,serverAddress);
        twlh->setCellWidget(sr,4,networkTcpPort);
        twlh->setCellWidget(sr,5,ftpPort);
        twlh->setCellWidget(sr,6,rootPath);
        twlh->setCellWidget(sr,7,language);
        twlh->setCellWidget(sr,8,lockScreenState);
        twlh->setCellWidget(sr,9,webblockState);

        twlh->setCellWidget(sr,10,savetButton);
        twlh->setCellWidget(sr,11,networkRemoveButton);
        if(veri.value("selectedNetworkProfil").toBool()) mCheck->setChecked(true);
        else mCheck->setChecked(false);
        if(veri.value("lockScreenState").toBool()) lockScreenState->setChecked(true);
        else lockScreenState->setChecked(false);
        if(veri.value("webblockState").toBool()) webblockState->setChecked(true);
        else webblockState->setChecked(false);
        //lockScreenState->setText(veri.value("lockScreenState").toString());
        //webblockState->setText(veri.value("webblockState").toString());

        sr++;
    }

    /********************************************************************/
    QToolButton *newNetworkButton= new QToolButton;
    newNetworkButton->setFixedSize(QSize(boy*40,boy*10));
    newNetworkButton->setIconSize(QSize(boy*40,boy*5));
    newNetworkButton->setStyleSheet("Text-align:center");
    newNetworkButton->setIcon(QIcon(":/icons/boot.svg"));
    newNetworkButton->setAutoRaise(true);
    newNetworkButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // newNetworkButton->setFont(f2);
    newNetworkButton->setText("Yeni Profil Ekle");

    connect(newNetworkButton, &QPushButton::clicked, [=]() {
        DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
        //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
        QJsonObject veri;
        veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
        if(db->Oku().size()==0) veri["selectedNetworkProfil"] =true;
        else veri["selectedNetworkProfil"] =false;
        veri["networkName"] = "network";
        veri["networkTcpPort"] = "7879";
        hostAddressMacButtonSlot();
        veri["serverAddress"]=ipmaclist[0].ip;
        veri["networkBroadCastAddress"]=ipmaclist[0].broadcast;
        veri["ftpPort"]="12345";
        veri["rootPath"]="/tmp/";
        veri["language"]="tr_TR";
        veri["lockScreenState"]=false;
        veri["webblockState"]=false;
        db->Ekle(veri);
        d->close();
        networkProfil();
        networkProfilLoad();

    });

    /*********************************************************************/
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(newNetworkButton);

    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

void MainWindow::networkProfilLoad()
{

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    //QJsonArray dizi=db->Oku();
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
    if(dizi.count()>0)
    {
        //qDebug()<<"Kayıtlı Host.";
        QJsonObject veri=dizi.first().toObject();
        //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
        this->networkIndex=veri["networkIndex"].toString();
        this->selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
        this->networkName=veri["networkName"].toString();
        this->networkTcpPort=veri["networkTcpPort"].toString();
        this->networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
        this->serverAddress=veri["serverAddress"].toString();
        this->ftpPort=veri["ftpPort"].toString();
        this->rootPath=veri["rootPath"].toString();
        this->language=veri["language"].toString();
        this->lockScreenState=veri["lockScreenState"].toBool();
        this->webblockState=veri["webblockState"].toBool();

        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            if(ipmaclist[i].broadcast==networkBroadCastAddress)
            {
                if(ipmaclist[i].ip!=serverAddress)
                {
                    qDebug()<<"Server Ip Numarası Güncelleniyor..";
                    QJsonObject veri;
                    veri["networkIndex"] =this->networkIndex;
                    veri["selectedNetworkProfil"] =this->selectedNetworkProfil;
                    veri["networkName"] = this->networkName;
                    veri["networkTcpPort"] = this->networkTcpPort;
                    veri["serverAddress"]=ipmaclist[i].ip;
                    veri["networkBroadCastAddress"]=this->networkBroadCastAddress;
                    veri["ftpPort"]=this->ftpPort;
                    veri["rootPath"]=this->rootPath;
                    veri["language"]=this->language;
                    veri["lockScreenState"]=this->lockScreenState;
                    veri["webblockState"]=this->webblockState;
                    db->Sil("networkIndex",this->networkIndex);
                    db->Ekle(veri);
                }

            }
        }
    }else
    {
        qDebug()<<"Yeni Network Ekleniyor.";

        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
                QJsonObject veri;
                veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
                veri["selectedNetworkProfil"] =true;
                veri["networkName"] = "network";
                veri["networkTcpPort"] = "7879";
                veri["serverAddress"]=ipmaclist[i].ip;
                veri["networkBroadCastAddress"]=ipmaclist[i].broadcast;
                veri["ftpPort"]="12345";
                veri["rootPath"]="/tmp/";
                veri["language"]="tr_TR";
                veri["lockScreenState"]=false;
                veri["webblockState"]=false;
                db->Ekle(veri);
        }
        networkProfilLoad();
    }
}

void MainWindow::bilgiAlButtonSlot()
{

    QTextDocument *doc=new QTextDocument();
    QString yil=QString::number( QDateTime::currentDateTime().date().year());
    doc->setHtml("<center><h2>Program Hakkında</h2></center>"
                 "<center><img src=\":/icons/e-ag.svg\" width=100 height=100 /></center> "
                 "Bu uygulama yerel ağda bilgisayarlara erişim ve yönetmek için yazılmıştır."
                 "<br/> Yapılabilecek Eylemler:"
                 "<br/> Açık olan bilgisayarlara linux komutlarını aynı anda çalıştırabilirsiniz."
                 "<br/> Birden fazla bilgisayara aynı anda dosya kopyalayabilirsiniz.  "
                 "<br/> Bütün bilgisayarlara  ya da tek bilgisayarın ekranına mesaj gönderebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarın ekranını kilitleyebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı kapatabilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı güncellemeler yapabilirsiniz."
                 "<br/> Açık bilgisayara ftp erişimi yapılabilir."
                 "<br/> Açık bilgisayarın ekranına erişim ve kullanma. "
                 "<br/> Video yayını yapabilirsiniz."
                 "<br/> Canlı kamera yayını yapabilirsiniz."
                 "<br/> Açık olan kullanıcı masaüstüne dosya kopyalama ve geri toplayabilirsiniz."
                 "<br/> İstediğiniz bilgisayarları seçip sadece seçili olanlara işlem yapabilirsiniz."
                 "<br/> Uzak bilgisayarın yönetici hesabına script kopyalayıp server üzerinden çalıştırabilirsiniz."
                 "<br/> Server bilgisayarın ekranını yansıtma"
                 "<br/> İki farklı ağ profili ile iki farklı ağ üzerinde çalışılabilmektedir."


                 "<br/><br/>Bu uygulamayı kullanmaktan doğabilecek her türlü hukuki sorumluluğu kullanıcı kabul etmiş sayılır."
                 "<br/><br/> Copyright (C) "+yil+" by Bayram KARAHAN"
                         "<br/>  bayramk@gmail.com"
                         "<br/>  www.bayramkarahan.com.tr"
                         "<br/>  www.bayramkarahan.blogspot.com"

                         "<br/><br/>This program is free software; you can redistribute it and/or modify it under"
                         "the terms of the GNU General Public License as published by the Free Software"
                         "Foundation; either version 3 of the License, or (at your option) any later version."
                         "<br/>"
                         "<br/>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;"
                         "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
                         "See the GNU General Public License for more details."
                         "<br/>"
                         "<br/>You should have received a copy of the GNU General Public License along with"
                         "this program; if not, write to the Free Software Foundation, Inc."
                         ",51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA ."
                 );
    QPrinter pdf;
    pdf.setOutputFileName("/tmp/hakkimda.pdf");
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
    d1->setWindowTitle("Program Hakkında");
    d1->setFixedSize(QSize(boy*120,boy*120));
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d1->setWindowIcon(appIcon);

    d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    d1->setLayout(vbox);
    d1->exec();



}

#endif // SETTINGSWIDGET_H
