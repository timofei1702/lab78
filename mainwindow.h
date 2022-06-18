#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_draw_clicked(); //функция для кнопки "Построить график"

    void on_clear_clicked(); //функция для кнопки "Удалить"

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, yBegin, yEnd, step, a, b, c;
    QVector<double> xVector, yVector;
};
#endif // MAINWINDOW_H
