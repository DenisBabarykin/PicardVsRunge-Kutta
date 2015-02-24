#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QDoubleValidator>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void Validate();
    void SetTabsItemsAlignement(int curRow, int curCol);
    void PrepareTables();
    void XFill(int curRow, long double x);
    void PicardFill(int curRow, long double x);
    void ExplicitFill(int curRow, long double x);
    void ImplicitFill(int curRow, long double x);
private slots:
    void on_btnSolve_clicked();

private:
    Ui::MainForm *ui;
    long double upperBound;
    long double step;
    QDoubleValidator *initialConditionsValidator;
};

#endif // MAINFORM_H
