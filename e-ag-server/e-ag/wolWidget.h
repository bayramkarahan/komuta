#ifndef WOLWIDGET_H
#define WOLWIDGET_H

void MainWindow::wolWidget()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Kapalı Host Listesi");
    d->setFixedSize(QSize(boy*100,boy*100));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);

    /***********************************************************************/
    QTableWidget *twl=new QTableWidget;

    twl->setFixedSize(QSize(boy*95,boy*75));
    twl->setColumnCount(4);
    //twl->setRowCount(0);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Seç"));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem("Ip"));
    twl->setHorizontalHeaderItem(2, new QTableWidgetItem("Mac"));
    twl->setHorizontalHeaderItem(3, new QTableWidgetItem("Adı"));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twl->setRowCount(0);
    twl->setColumnWidth(0, boy*5);
    twl->setColumnWidth(1, boy*25);
    twl->setColumnWidth(2,boy*30);
    twl->setColumnWidth(3,boy*30);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        twl->setRowCount(twl->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setChecked(false);
        twl->setCellWidget(sr,0,mCheck);
        //qDebug()<<"Kayıtlı Host.";
        twl->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
        twl->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
        twl->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
        //twl->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
        sr++;
    }

    /********************************************************************/
    QToolButton *powerOnButton= new QToolButton;
    powerOnButton->setFixedSize(QSize(boy*40,boy*10));
    powerOnButton->setIconSize(QSize(boy*40,boy*5));
    powerOnButton->setStyleSheet("Text-align:center");
    powerOnButton->setIcon(QIcon(":/icons/boot.svg"));
    powerOnButton->setAutoRaise(true);
    powerOnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // powerOnButton->setFont(f2);
    powerOnButton->setText("Seçili Pc'leri Aç");

    connect(powerOnButton, &QPushButton::clicked, [=]() {
        int numRows = twl->rowCount();
        for ( int i = 0 ; i < numRows ; i++)
        {
            QCheckBox* mBox = static_cast<QCheckBox*> (twl->cellWidget(i,0));
            if (mBox->isChecked())
            {
                QString  _mac= twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
                QString  _ip= twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
                QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
                // qDebug()<<i<<mBox->isChecked()<<_ip<<_mac<<ad;
                slotWakeOnLan(_ip,_mac);
            }
        }
    });
    /*********************************************************************/
    /********************************************************************/
    QToolButton *powerOnButtonAll= new QToolButton;
    powerOnButtonAll->setFixedSize(QSize(boy*40,boy*10));
    powerOnButtonAll->setIconSize(QSize(boy*40,boy*5));
    powerOnButtonAll->setStyleSheet("Text-align:center");
    powerOnButtonAll->setIcon(QIcon(":/icons/boot.svg"));
    powerOnButtonAll->setAutoRaise(true);
    powerOnButtonAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //powerOnButtonAll->setFont(f2);
    powerOnButtonAll->setText("Tüm Pc'leri Aç");

    connect(powerOnButtonAll, &QPushButton::clicked, [=]() {
        int numRows = twl->rowCount();
        for ( int i = 0 ; i < numRows ; i++)
        {
            QString  _mac= twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
            QString  _ip= twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
            //QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
            //qDebug()<<_ip<<_mac;
            slotWakeOnLan(_ip,_mac);
        }
    });
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twl);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(powerOnButton);
    hbox->addWidget(powerOnButtonAll);
    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

void MainWindow::slotWakeOnLan(QString _ip,QString _mac)
{

    _mac=_mac.toUpper();
    QHostAddress FakeAddress;
    qDebug()<<"mac adresi:"<<_mac<<_ip;
    hostAddressMacButtonSlot();
    for(int k=0;k<interfaceList.count();k++)
    {
        if(interfaceList[k].ip.section(".",0,2)==_ip.section(".",0,2))
        {
            char MACAddr [6];
            char MagicPacket [102]; // Magic package for remote boot

            int j = sscanf (_mac.toLatin1().data(), "%2x-%2x-%2x-%2x-%2x-%2x",
                           & MACAddr [0], & MACAddr [1], & MACAddr [2], & MACAddr [3], & MACAddr [4], & MACAddr [5]);

            // Set to hexadecimal before the magicpacket array 6 characters ff
            memset (MagicPacket, 0xff, 6);
            int packetsize = 6; // the beginning of the initial value is 6, do not wrong. I is because the effect of the initial value of the written as 0, it is too effortless.
            // Build MagicPacket.
            for (int z = 0; z <16; z++)
            {
                memcpy (MagicPacket + packetsize, MACAddr, 6);
                packetsize += 6;
            }

            FakeAddress.setAddress (interfaceList[k].broadcast);
            QString kmt29="wakeonlan "+_mac;
            system(kmt29.toStdString().c_str());
            qDebug()<<kmt29;
        }
    }
    mesajSlot("Seçili Hostlar Uzaktan  Başlatıl.");

}

#endif // WOLWIDGET_H
