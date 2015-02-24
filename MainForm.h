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
private slots:
    void on_btnSolve_clicked();

private:
    Ui::MainForm *ui;
    double upperBound;
    double step;
    QDoubleValidator *initialConditionsValidator;
};

#endif // MAINFORM_H
