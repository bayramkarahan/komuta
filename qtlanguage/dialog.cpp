#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->labelTranslate->setText(trUtf8("This is a test text for"
                                       "With support multilanguage in Qt applications. \n"
                                       "Eat more of these soft French rolls, so drink some tea."));
}

Dialog::~Dialog()
{
    delete ui;
}
