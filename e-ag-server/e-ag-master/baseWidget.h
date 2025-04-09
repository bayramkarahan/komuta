#ifndef BASEWIDGET_H
#define BASEWIDGET_H


QWidget* MainWindow::baseWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*10;
    QWidget * d = new QWidget();
    // d->setFixedSize(e*180,b*23);
    // d->setStyleSheet("background-color: #ffdced;font-size:"+QString::number(font.toInt()-2)+"px;");



    QToolButton *vncConnectPcButton = new QToolButton();
    vncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncConnectPcButton->setIcon(QIcon(":icons/vnc.svg"));
    vncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    vncConnectPcButton->setAutoRaise(true);
    // vncConnectPcButton->setAutoFillBackground(true);
    vncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    vncConnectPcButton->setText("VNC");
    connect(vncConnectPcButton, &QToolButton::clicked, [=]() {
        slotVnc(_display);
    });

    QToolButton *novncConnectPcButton = new QToolButton();
    novncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    novncConnectPcButton->setIcon(QIcon(":icons/novnc.svg"));
    novncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    novncConnectPcButton->setAutoRaise(true);
    // vncConnectPcButton->setAutoFillBackground(true);
    novncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    novncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    novncConnectPcButton->setText("noVNC");
    connect(novncConnectPcButton, &QToolButton::clicked, [=]() {
        QString kmt26="env MOZ_USE_XINPUT2=1 /usr/lib/firefox/firefox "+pcIp->text()+":6085/vnc.html";
        system(kmt26.toStdString().c_str());

        // QDesktopServices::openUrl(QUrl("192.168.1.101:6085"));
    });
    /* QToolButton *xrdpConnectPcButton = new QToolButton();
    xrdpConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    xrdpConnectPcButton->setIcon(QIcon(":icons/rdp.svg"));
    xrdpConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    xrdpConnectPcButton->setAutoRaise(true);
   // xrdpConnectPcButton->setAutoFillBackground(true);
    xrdpConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    xrdpConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    xrdpConnectPcButton->setText("RDP");
    connect(xrdpConnectPcButton, &QToolButton::clicked, [=]() {
        slotRdp();
    });
*/
    QToolButton *terminalPcButton = new QToolButton();
    terminalPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    terminalPcButton->setIcon(QIcon(":icons/ssh.svg"));
    terminalPcButton->setIconSize(QSize(yukseklik,boy*8));
    terminalPcButton->setAutoRaise(true);
    //  terminalPcButton->setAutoFillBackground(true);
    terminalPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    terminalPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    terminalPcButton->setText(tr("Terminal"));
    connect(terminalPcButton, &QToolButton::clicked, [=]() {
        slotTerminal();
    });

    QToolButton *selectPcButton = new QToolButton();
    selectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    selectPcButton->setIconSize(QSize(yukseklik,boy*8));
    selectPcButton->setIcon(QIcon(":icons/select.svg"));
    selectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    selectPcButton->setAutoRaise(true);
    // selectPcButton->setAutoFillBackground(true);
    selectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    selectPcButton->setText(tr("Pc Seç"));
    connect(selectPcButton, &QToolButton::clicked, [=]() {
        selectSlot();

    });


    QToolButton *ftpPc=new QToolButton();
    ftpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ftpPc->setIcon(QIcon(":/icons/ftp.svg"));
    ftpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ftpPc->setIconSize(QSize(yukseklik,boy*8));

    ftpPc->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    ftpPc->setAutoRaise(true);
    // ftpPc->setAutoFillBackground(true);
    ftpPc->setText("FTP");
    connect(ftpPc, &QToolButton::clicked, [=]() {
        QString _remoteuser=getActiveUserName();
        bool ok;
        _remoteuser = QInputDialog::getText(0, "İstemci Parolası",
                                                    " İstemcideki Kullanıcının Adını Giriniz :", QLineEdit::Normal,
                                                    _remoteuser, &ok);
        QString _remotepasswd = QInputDialog::getText(0, "İstemci Parolası",
                                                      _remoteuser+" Kullanıcının Parolasını Giriniz :", QLineEdit::Normal,
                                                      "", &ok);
        //QString komut="sshlogin "+remoteUserName+" "+remotePassword;
        if(_remoteuser!=""&&_remotepasswd!="")
        {
            system("cp /usr/share/e-ag/filezilla.xml ~/.config/filezilla/");
            textBrowser_receivedMessages->clear();
            QStringList arguments;
            QString  komut;
            komut.append("nohup filezilla ").append(_remoteuser+":").append(_remotepasswd).append("@"+pcIp->text()+" &");
            // qDebug()<<komut;
            arguments << "-c" << komut;
            QProcess process;
            process.start("/bin/bash",arguments);
            process.waitForFinished(-1); // will wait forever until finished
        }
    });

    QToolButton *wolButton=new QToolButton();
    wolButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    wolButton->setIcon(QIcon(":/icons/wol.svg"));
    wolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    wolButton->setIconSize(QSize(yukseklik,boy*8));

    wolButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    wolButton->setAutoRaise(true);
    // ftpPc->setAutoFillBackground(true);
    wolButton->setText("Pc Aç");
    connect(wolButton, &QToolButton::clicked, [=]() {
        wolWidget();
    });


    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(yukseklik*0.9, yukseklik*1.5);
    helpButton->setIconSize(QSize(yukseklik,boy*8));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setAutoRaise(true);

    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {

        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Temel İşlemler</h2></center>"
                     "<center><img src=\":/icons/temelislem.png\" /></center> "
                     "1-Ağ üzerinde açık istemcileri listelemek için Yenile seçeneği kullanılmalıdır."
                     "<br/><br/>2-Birden fazla istemciyi seçmek için çift tıklama/sol tuşa basarak alan seçimi yapılabilir."
                     "Seçili olmayan istemcileri seçmek için Pc Seç seçeneği kullanılır."
                     "<br/><br/>3-İstemcinin canlı ekranı Vnc seçeneği ile erişilebilir."
                     "<br/><br/>4-İstemcinin kullanıcıdan bağımsız ekranına Rdp seçeneği ile erişilebilir."
                     "<br/><br/>5-İstemcinin ssh üzerinden konsoluna bağlanmak için Terminal seçeneği kullanılabilir."
                     "<br/><br/>6-İstemcinin dosyalarına dosya yöneticisi ile erişmek için Ftp seçeneği kullanılabilir."
                     "<br/><br/>7-İstemcinin uzaktan başlatmak için Pc Aç seçeneği kullanılabilir."
                     "Pc Aç seçeneği için; İstemcinin BIOS seçeneklerinden Wake On Lan seçeneği aktif edilmeli. "
                     "<br/><br/>8-İstemci simgelerinin altındaki P V S F X işaretleri servisleri ifade eder."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "Simgeler yeşilse servis çalışıyor. Kırmızı ise servis çalışmıyordur."
                     "<br/>P=İstemci, yeşil=istemci açık/kırmızı=istemci kapalı"
                     "<br/>V=Vnc servisi, yeşil=açık/kırmızı=kapalı"
                     "<br/>S=Ssh servisi, yeşil=açık/kırmızı=kapalı"
                     "<br/>F=Ftp servisi, yeşil=açık/kırmızı=kapalı"
                     "<br/>X=x11 ekranı, yeşil=kullanıcı login olmuş/kırmızı=kullanıcı login olmamış"
                     );
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/temelislem.pdf");
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
        d1->setWindowTitle("Temel İşlemler Yardım Penceresi");
        d1->setFixedSize(QSize(boy*150,boy*120));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();

    });
    /******************************************************/
    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setHorizontalSpacing(0);
    // layout->addWidget(hostListePcButton, 0,0,3,1);
    //layout->addWidget(selectPcButton, 0,1,3,1);

    layout->addWidget(vncConnectPcButton, 0,2,3,1);
    layout->addWidget(novncConnectPcButton, 0,5,3,1);

    //  layout->addWidget(xrdpConnectPcButton, 0,6,3,1);

    layout->addWidget(terminalPcButton, 0,7,3,1);
    layout->addWidget(ftpPc, 0,8,3,1);
    layout->addWidget(wolButton, 0,9,3,1);

    layout->addWidget(kilitWidget(), 0,10,3,1);
    layout->addWidget(kilittransparanWidget(), 0,12,3,1);
    layout->addWidget(ekranWidget(), 0,13,3,1);
    layout->addWidget(poweroffrebootWidget(), 0,20,3,1);
    layout->addWidget(volumeWidget(), 0,23,3,1);

    layout->addWidget(logoutWidget(), 0,25,3,1);
    //  layout->addWidget(languageWidget(), 0,28,3,1);

    layout->addWidget(helpButton, 0,30,3,1);
    d->setLayout(layout);
    return d;
}


#endif // BASEWIDGET_H
