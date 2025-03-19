#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    // Метод получения событий в главном окне приложения
    // В нём будет производиться проверка события смены перевода приложения
    void changeEvent(QEvent * event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator qtLanguageTranslator;   // Выделяем перевод в отдельном поле, иначе ничего работать не будет
};

#endif // MAINWINDOW_H
