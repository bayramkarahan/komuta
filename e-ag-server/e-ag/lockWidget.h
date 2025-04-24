#ifndef LOCKWIDGET_H
#define LOCKWIDGET_H

QWidget* MainWindow::kilittransparanWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Ekran Yansıtma Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/

    QToolButton *transparanUnlockPc=new QToolButton();
    transparanUnlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanUnlockPc->setIcon(QIcon(":/icons/transparanunlock.svg"));
    transparanUnlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanUnlockPc->setFixedSize(yukseklik*1.4,boy*7);
    transparanUnlockPc->setAutoRaise(true);
    // transparanUnlockPc->setAutoFillBackground(true);
    transparanUnlockPc->setText(tr("Şeffaf Kilit Aç"));
    //transparanUnlockPc->setMenu(sessionMenu());
    //transparanUnlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(transparanUnlockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilitAc();
    });

    /**************************************************/
    QToolButton *transparanLockPc=new QToolButton();
    transparanLockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanLockPc->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanLockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanLockPc->setFixedSize(yukseklik*1.4,boy*7);
    transparanLockPc->setAutoRaise(true);
    // transparanLockPc->setAutoFillBackground(true);
    transparanLockPc->setText(tr("Şeffaf Kilitle"));
    //transparanLockPc->setMenu(sessionMenu());
    //transparanLockPc->setPopupMode(QToolButton::MenuButtonPopup);
    connect(transparanLockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilit();
    });

    QToolButton *transparanKilitMenuButton= new QToolButton();
    // transparanKilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanKilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    transparanKilitMenuButton->setFixedSize(e*5,b*2);
    transparanKilitMenuButton->setAutoRaise(true);
    //transparanKilitMenuButton->setAutoFillBackground(true);
    transparanKilitMenuButton->setText("");
    transparanKilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitMenuButton->setMenu(transparanKilitMenu());
    transparanKilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(transparanKilitMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(transparanLockPc, 4,1,1,1,Qt::AlignCenter);
    layout->addWidget(transparanUnlockPc, 5,1,1,1,Qt::AlignCenter);
    //layout->addWidget(transparanKilitMenuButton, 6,1,1,1,Qt::AlignRight);
    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

QWidget* MainWindow::kilitWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Kilit Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);
    //sor->setStyleSheet("background-color: #dceded;font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/
    QToolButton *lockPc=new QToolButton();
    lockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    lockPc->setIcon(QIcon(":/icons/lock.svg"));
    lockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    lockPc->setFixedSize(yukseklik*1.4,b*7);
    lockPc->setAutoRaise(true);
    // lockPc->setAutoFillBackground(true);
    lockPc->setText(tr("Kilitle"));

    // lockPc->setMenu(kilitMenu());
    // lockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(lockPc, &QToolButton::clicked, [=]() {
        auto start = std::chrono::high_resolution_clock::now();

       /***********************************/
        udpSendData("x11command","kilitstatetrue","");
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
            {
                onlinePcList[i]->setKilitControlState(true);
            }
        }

        /***************************************/
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Bir başka uzun süren işlem " << duration.count() << " milisaniye sürdü." << std::endl;
        mesajSlot(tr("Seçili Hostlarda Ekran Kilitlendi."));
    });
    /**************************************************/
    QToolButton *unlockPc=new QToolButton();
    unlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    unlockPc->setIcon(QIcon(":/icons/unlock.svg"));
    unlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    unlockPc->setFixedSize(yukseklik*1.4,b*7);
    unlockPc->setAutoRaise(true);
    //unlockPc->setAutoFillBackground(true);
    unlockPc->setText(tr("Kilit Aç"));
    //  unlockPc->setMenu(kilitMenu());
    //unlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(unlockPc, &QToolButton::clicked, [=]() {
        slotKilitAc();
    });


    QToolButton *kilitMenuButton= new QToolButton();
    // kilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    kilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    kilitMenuButton->setFixedSize(e*5,b*2);
    kilitMenuButton->setAutoRaise(true);
    //kilitMenuButton->setAutoFillBackground(true);
    kilitMenuButton->setText("");
    kilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitMenuButton->setMenu(kilitMenu());
    kilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(kilitMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });


    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(lockPc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(unlockPc, 5,0,1,1,Qt::AlignCenter);
    //layout->addWidget(kilitMenuButton, 6,0,1,1,Qt::AlignRight);
    /// layout->addWidget(kilitAllButton, 7,0,1,1);
    /// layout->addWidget(kilitAcAllButton, 8,0,1,1);
    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

void MainWindow::slotKilit(){
    //system("sleep 1");
    udpSendData("x11command","kilitstatetrue","");
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
           // udpSendData("x11command","kilitstatetrue",onlinePcList[i]->ip);
            onlinePcList[i]->setKilitControlState(true);
        }
    }
    mesajSlot(tr("Seçili Hostlarda Ekran Kilitlendi."));

}
void MainWindow::slotTransparanKilit()
{
    //system("sleep 1");
 udpSendData("x11command","transparankilitstatetrue","");
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            onlinePcList[i]->setKilitTransparanControlState(true);
           // udpSendData("x11command","transparankilitstatetrue",onlinePcList[i]->ip);
        }
    }
    mesajSlot(tr("Seçili Hostlar Şeffaf Kilitlendi."));

}
void MainWindow::slotKilitAc(){
    //system("sleep 1");
     udpSendData("x11command","kilitstatefalse","");
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            onlinePcList[i]->setKilitControlState(false);
            //udpSendData("x11command","kilitstatefalse",onlinePcList[i]->ip);
        }
    }
    mesajSlot(tr("Seçili Hostlarda Kilit Açıldı."));

}
void MainWindow::slotTransparanKilitAc(){
    //system("sleep 1");
    udpSendData("x11command","transparankilitstatefalse","");
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            onlinePcList[i]->setKilitTransparanControlState(false);
            //udpSendData("x11command","transparankilitstatefalse",onlinePcList[i]->ip);
        }
    }
    mesajSlot(tr("Seçili Hostlarda Şeffaf Kilit Açıldı."));

}

QMenu *MainWindow::kilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
    /*************************************/

    QPushButton *kilitAllButton= new QPushButton;
    kilitAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    kilitAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));

    kilitAllButton->setText(tr(" Tümünü Kilitle"));
    kilitAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitAllButton->setFlat(true);
    kilitAllButton->setIcon(QIcon(":icons/lock.svg"));

    connect(kilitAllButton, &QPushButton::clicked, [=]() {
        menu->close();
    });




    QPushButton *kilitAcAllButton= new QPushButton;
    kilitAcAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    kilitAcAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    kilitAcAllButton->setText(tr(" Tüm Kilitleri Aç"));
    kilitAcAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitAcAllButton->setFlat(true);
    kilitAcAllButton->setIcon(QIcon(":icons/unlock.svg"));

    connect(kilitAcAllButton, &QPushButton::clicked, [=]() {
        menu->close();
    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(kilitAllButton, 5,0,1,1);
    layout->addWidget(kilitAcAllButton, 6,0,1,1);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
    //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
    return menu;




}

QMenu *MainWindow::transparanKilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
    /*************************************/
    QPushButton *transparanKilitAllButton= new QPushButton;
    transparanKilitAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    transparanKilitAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    transparanKilitAllButton->setText(tr(" Tümünü Kilitle"));
    transparanKilitAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitAllButton->setFlat(true);
    transparanKilitAllButton->setIcon(QIcon(":icons/transparanlock.svg"));

    connect(transparanKilitAllButton, &QPushButton::clicked, [=]() {
        menu->close();
    });



    QPushButton *transparankilitAcAllButton= new QPushButton;
    transparankilitAcAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    transparankilitAcAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    transparankilitAcAllButton->setText(tr(" Tüm Kilitleri Aç"));
    transparankilitAcAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    transparankilitAcAllButton->setFlat(true);
    transparankilitAcAllButton->setIcon(QIcon(":icons/transparanunlock.svg"));

    connect(transparankilitAcAllButton, &QPushButton::clicked, [=]() {
        menu->close();

    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    // layout->addWidget(kilitButton, 2,0,1,2);
    // layout->addWidget(kilitAllButton, 3,0,1,2);
    // layout->addWidget(logoutButton, 4,0,1,2);
    layout->addWidget(transparanKilitAllButton, 5,0,1,1);
    layout->addWidget(transparankilitAcAllButton, 6,0,1,1);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
    return menu;

}

#endif // LOCKWIDGET_H
