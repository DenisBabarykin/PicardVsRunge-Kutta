#include "MainForm.h"
#include "ui_MainForm.h"
#include <QMessageBox>
#include <cmath>
#include "Picard.h"
#include "Timer.h"
#include "Runge-Kutta.h"
#include "CalcFunc.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    upperBound = step = 0;

    // set upper bound of input data to 20000
    initialConditionsValidator = new QDoubleValidator(0, 20000, 30, this);
    initialConditionsValidator->setLocale(QLocale::c());
    ui->ledtUpperBound->setValidator(initialConditionsValidator);
    ui->ledtStep->setValidator(initialConditionsValidator);

    QTableWidgetItem *protoitem = new QTableWidgetItem();
    protoitem->setTextAlignment(Qt::AlignRight);
    ui->tblwdgSolutions->setItemPrototype(protoitem);
    //ui->tblwdgTime->setItemPrototype(protoitem);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::Validate()
{
    int pos = 0;
    QString strUpperBound = ui->ledtUpperBound->text();
    QString strStep = ui->ledtStep->text();

    if (initialConditionsValidator->validate(strUpperBound, pos) != QValidator::Acceptable ||
            initialConditionsValidator->validate(strStep, pos) != QValidator::Acceptable ||
            ui->ledtUpperBound->text().toDouble() <= 0 ||
            ui->ledtStep->text().toDouble() <= 0)
        QMessageBox::warning(this, "Error", "Incorrect initial conditions");
}

void MainForm::SetTabsItemsAlignement(int curRow, int curCol)
{
    ui->tblwdgSolutions->item(curRow, curCol)->setTextAlignment(Qt::AlignRight);
    ui->tblwdgTime->item(curRow, curCol)->setTextAlignment(Qt::AlignRight);
}

void MainForm::PrepareTables()
{
    ui->tblwdgSolutions->clearContents();
    ui->tblwdgTime->clearContents();
    int nRows = ceil(upperBound / step) + 1;
    ui->tblwdgSolutions->setRowCount(nRows);
    ui->tblwdgTime->setRowCount(nRows);
}

void MainForm::PicardFill(int curRow, long double x)
{
    ns_timer::Timer timer(true);
    long double picardFirst = PicardFirstIteration(x);
    ui->tblwdgTime->setItem(curRow, 1, new QTableWidgetItem(QString::number(timer.stopGet())));
    ui->tblwdgSolutions->setItem(curRow, 1, new QTableWidgetItem(QString::number((double) picardFirst)));
    SetTabsItemsAlignement(curRow, 1);

    timer.start(true);
    long double picardSecondPartial = PartialPicardSecondIteration(x);
    long double picardSecond = picardFirst * picardSecondPartial;
    ui->tblwdgTime->setItem(curRow, 2, new QTableWidgetItem(QString::number(timer.stopGet())));
    ui->tblwdgSolutions->setItem(curRow, 2, new QTableWidgetItem(QString::number((double) picardSecond)));
    SetTabsItemsAlignement(curRow, 2);

    timer.start(true);
    long double picardThirdPartial = PartialPicardThirdIteration(x);
    long double picardThird = picardFirst * (picardSecondPartial + picardThirdPartial);
    ui->tblwdgTime->setItem(curRow, 3, new QTableWidgetItem(QString::number(timer.stopGet())));
    ui->tblwdgSolutions->setItem(curRow, 3, new QTableWidgetItem(QString::number((double) picardThird)));
    SetTabsItemsAlignement(curRow, 3);
}

void MainForm::ExplicitFill(int curRow, long double x)
{
    static long double explRunge;
    ns_timer::Timer timer(true);
    if (x == 0)
        explRunge = 0;
    else
        explRunge = ExplicitRungeKutta(step, x - step, explRunge, func);
    ui->tblwdgTime->setItem(curRow, 4, new QTableWidgetItem(QString::number(timer.stopGet())));
    ui->tblwdgSolutions->setItem(curRow, 4, new QTableWidgetItem(QString::number((double) explRunge)));
    SetTabsItemsAlignement(curRow, 4);
}

void MainForm::ImplicitFill(int curRow, long double x)
{
    static long double impl;
    ns_timer::Timer timer(true);
    if (x == 0)
        impl = 0;
    else
        impl = Implicit(step, x, impl, func);
    ui->tblwdgTime->setItem(curRow, 5, new QTableWidgetItem(QString::number(timer.stopGet())));
    ui->tblwdgSolutions->setItem(curRow, 5, new QTableWidgetItem(QString::number((double) impl)));
    SetTabsItemsAlignement(curRow, 5);
}

void MainForm::XFill(int curRow, long double x)
{
    ui->tblwdgSolutions->setItem(curRow, 0, new QTableWidgetItem(QString::number((double) x)));
    ui->tblwdgTime->setItem(curRow, 0, new QTableWidgetItem(QString::number((double) x)));
    SetTabsItemsAlignement(curRow, 0);
}

void MainForm::on_btnSolve_clicked()
{
    Validate();
    upperBound = ui->ledtUpperBound->text().toDouble();
    step = ui->ledtStep->text().toDouble();
    PrepareTables();

    long double x;
    int curRow;
    for (x = 0, curRow = 0; x <= upperBound; x += step, ++curRow)
    {
        XFill(curRow, x);
        PicardFill(curRow, x);
        ExplicitFill(curRow, x);
        ImplicitFill(curRow, x);
    }
}
