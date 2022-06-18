#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_draw_clicked() //функция для кнопки "Построить график"
{
    xVector.clear();
    yVector.clear();
    QString warning_XB = "", warning_XE = "", warning_A = "", warning_B = "", warning_C = "", warning_S = "", warning_u = "";

         ui->widget->clearGraphs();
        // проверка ввода параметров
        if (ui->input_xBegin->text().toDouble() == 0 && ui->input_xBegin->text() != "0" )
            warning_XB = "Начальное значение X должно быть числом. ";
        if (ui->input_xEnd->text().toDouble() == 0 && ui->input_xEnd->text() != "0")
            warning_XE = "Конечное значение X должно быть числом. ";
        if (ui->inputA->text().toDouble() == 0 && ui->inputA->text() != "0")
            warning_A = "'a' должно быть числом. ";
        if (ui->inputB->text().toDouble() == 0 && ui->inputB->text() != "0" )
            warning_B = "'b' должно быть числом. ";
        if (ui->inputC->text().toDouble() == 0 && ui->inputC->text() != "0" || ui->inputC->text().toDouble() > 1 || ui->inputC->text().toDouble() < 0)
            warning_C = "'z' должно быть числом от 0 до 1 ";
        double s2 = ui->input_xEnd->text().toDouble();
        double s1 = ui->input_xBegin->text().toDouble();
        double st = ui->input_step->text().toDouble();
        if ((s1 + st) > s2 )
           warning_u = "Плохой шаг или неправильно заданы значения X.  ";
        if ((ui->input_step->text().toDouble() == false) || (ui->input_step->text().toDouble() <= 0))
            warning_S = "Шаг должен быть положительным. ";

        // если всё введено корректно, то строим график
        if (warning_XB == "" && warning_XE == "" && warning_A == "" && warning_B == "" && warning_C == "" && warning_S == "" && warning_u == "")
        {
            // заносим все введенные данные в переменные
            xBegin = ui->input_xBegin->text().toDouble();
            xEnd = ui->input_xEnd->text().toDouble();
            step = ui->input_step->text().toDouble();
            a = ui->inputA->text().toDouble();
            b = ui->inputB->text().toDouble();
            c = ui->inputC->text().toDouble();
            double func = a*tan(pow(xBegin, 2)) + b*cos(pow(xBegin, 2)) + c;
            yBegin = func;
            yEnd = func;

            //устанавливаем начальное значение итератора цикла
            double i = xBegin;

            //организуем цикл заполнения векторов и параллельного поиска min и max функции
            while (i <= xEnd)
            {
            //заполняем вектора
            xVector.push_back(i);
            double f = a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c;
            if (f < -100) {
                yVector.push_back(-100);
            } else if (f > 100) {
                yVector.push_back(100);
            } else {
                yVector.push_back(a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c);
            }

            //ищем min и max функции
            if (a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c < yBegin) yBegin = a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c;
            if (a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c > yEnd) yEnd = a*tan(pow(i, 2)) + b*cos(pow(i, 2)) + c;

            //меняем значение итератора
            i += step;
            }
            if (yBegin < -100) {
                yBegin = -100;
            }
            if (yEnd > 100) {
                yEnd = 100;
            }
            ui->widget->addGraph(); //Добавляем один график в widget
            ui->widget->xAxis->setRange(xBegin, xEnd); //устанавливаем диапазон для оси Х
            ui->widget->yAxis->setRange(yBegin - 2, yEnd + 2); //устанавливаем диапазон для оси Y
            ui->widget->graph(0)->addData(xVector, yVector); //заносим данные из векторов на график
            ui->widget->replot(); //И перерисуем график на нашем widget

            // масштабирование графика
            ui->widget->setInteraction(QCP::iRangeZoom, true);
            ui->widget->setInteraction(QCP::iRangeDrag, true);
       }

        // сообщение об ошибке
        else
        {
            QMessageBox::warning(this, "Ошибка при вводе параметров", "При вводе информации у вас допущены ошибки: "
            + warning_XB + warning_XE + warning_A + warning_B +warning_C + warning_S + warning_u + "Исправьте ошибки.");
        }


}

void MainWindow::on_clear_clicked() //функция для кнопки "Удалить"
{
  ui->input_xBegin->clear();
  ui->input_xEnd->clear();
  ui->input_step->clear();
  ui->inputA->clear();
  ui->inputB->clear();
  ui->inputC->clear();
  ui->widget->clearGraphs();
  ui->widget->replot();

}
