#ifndef SCREENVIEWWIDGET_H
#define SCREENVIEWWIDGET_H
QWidget* MainWindow::ekranWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Ekran Yansıtma Seçenekleri"));
    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/
    QToolButton *screenImagePc=new QToolButton();
    screenImagePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    screenImagePc->setIcon(QIcon(":/icons/monitor.svg"));
    screenImagePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    screenImagePc->setFixedSize(yukseklik*1.4,boy*7);
    screenImagePc->setAutoRaise(true);
    // screenImagePc->setAutoFillBackground(true);
    screenImagePc->setText(tr("Ekran İzle"));
    // screenImagePc->setMenu(sessionMenu());
    // screenImagePc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(screenImagePc, &QToolButton::clicked, [=]() {
        slotEkranIzle();
    });

    QToolButton* screenImagePcStop = new QToolButton(0);
    screenImagePcStop->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    screenImagePcStop->setIcon(QIcon(":/icons/monitorstop.svg"));
    screenImagePcStop->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    screenImagePcStop->setFixedSize(yukseklik*1.4,boy*7);
    screenImagePcStop->setAutoRaise(true);
    // screenImagePcStop->setAutoFillBackground(true);
    screenImagePcStop->setText(tr("İzleme Durdur"));
    // screenImagePcStop->setMenu(sessionMenu());
    //screenImagePcStop->setPopupMode(QToolButton::MenuButtonPopup);

    connect(screenImagePcStop, &QToolButton::clicked, [=]() {
        slotEkranIzleDurdur();
    });

    QToolButton *ekranMenuButton= new QToolButton();
    // ekranMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    ekranMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ekranMenuButton->setFixedSize(e*5,b*2);
    ekranMenuButton->setAutoRaise(true);
    //ekranMenuButton->setAutoFillBackground(true);
    ekranMenuButton->setText("");
    ekranMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranMenuButton->setMenu(ekranImageMenu());
    ekranMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(ekranMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(screenImagePc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(screenImagePcStop, 5,0,1,1,Qt::AlignCenter);
    //layout->addWidget(ekranMenuButton, 6,0,1,1,Qt::AlignRight);
    return sor;
}
void MainWindow::slotEkranIzle()
{
   for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            onlinePcList[i]->setIconControlState(true);
        }
    }
    udpSendData("x11command","x11command","serverscreen");
    mesajSlot(tr("Seçili Ekran İzlemeler Başlatıldı."));
}
void MainWindow::slotEkranIzleDurdur()
{   
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            onlinePcList[i]->setIconControlState(false);
        }
    }
    udpSendData("x11command","x11command","pkill serverscreen");
    mesajSlot(tr("Seçili Ekran İzlemeler Durduruldu."));
}
void MainWindow::slotEkranIzleAll()
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState)
        {
            onlinePcList[i]->setIconControlState(true);
          }
    }
    mesajSlot(tr("Tüm Ekran İzlemeler Başlatıldı."));

}
void MainWindow::slotEkranIzleAllDurdur()
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState)
        {
            onlinePcList[i]->setIconControlState(false);
         }
    }
    mesajSlot(tr("Tüm Ekran İzlemeler Durduruldu."));

}

#endif // SCREENVIEWWIDGET_H
