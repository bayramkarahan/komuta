#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QScreen>
#include <QIcon>

class MyDialog : public QDialog {
public:
    MyDialog(QString baslik, QString mesaj,
             QString evet, QString hayir, QString tamam,
             int _w, int _h,
             QWidget *parent = nullptr)
        : QDialog(parent)
    {
        // Bellekten otomatik silinmesi için:
        setAttribute(Qt::WA_DeleteOnClose);

        // Pencere başlığı ve ikon
        setWindowTitle(baslik);
        setWindowIcon(QIcon(":/icons/lock.png"));
        setFixedSize(_w, _h);

        // Mesaj label'ı
        QLabel *lmesaj = new QLabel(this);
        lmesaj->setText(mesaj);
        lmesaj->setWordWrap(true);
        lmesaj->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        // Scroll alanı içine mesajı koy
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidget(lmesaj);
        scrollArea->setWidgetResizable(true);

        QSize screenSize = qApp->screens()[0]->size();
        scrollArea->setFixedSize(screenSize.width() * 0.8, screenSize.height() * 0.7);

        // Butonlar
        QPushButton *okButton = new QPushButton(tr("Tamam"));
        connect(okButton, &QPushButton::clicked, this, &MyDialog::accept);

        QPushButton *cancelButton = new QPushButton(tr("Vazgeç"));
        connect(cancelButton, &QPushButton::clicked, this, &MyDialog::reject);

        QPushButton *yesButton = new QPushButton(tr("Evet"));
        connect(yesButton, &QPushButton::clicked, this, &MyDialog::accept);

        // Ana layout
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(scrollArea, 0, 0, 1, 3);

        int buttonCol = 0;
        if (evet == "evet")
            layout->addWidget(yesButton, 1, buttonCol++, 1, 1);
        if (tamam == "tamam")
            layout->addWidget(okButton, 1, buttonCol++, 1, 1);
        if (hayir == "hayir")
            layout->addWidget(cancelButton, 1, buttonCol++, 1, 1);

        setLayout(layout);

        // Ekranın ortasına taşı
        move(screenSize.width() / 2 - width() / 2,
             screenSize.height() / 2 - height() / 2);
    }
};

#endif // MYDIALOG_H
