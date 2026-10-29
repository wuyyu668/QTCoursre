#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 数字键：用 lambda 把按钮对应的数字传给同一个槽函数
    QPushButton *digitButtons[10] = {
        ui->btn0, ui->btn1, ui->btn2, ui->btn3, ui->btn4,
        ui->btn5, ui->btn6, ui->btn7, ui->btn8, ui->btn9
    };
    for (int i = 0; i < 10; ++i) {
        connect(digitButtons[i], &QPushButton::clicked, this,
                [this, i]() { onDigitClicked(i); });
    }

    connect(ui->btnPoint,     &QPushButton::clicked, this, &MainWindow::onPointClicked);
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    connect(ui->btnClear,     &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnPercent,   &QPushButton::clicked, this, &MainWindow::onPercentClicked);

    connect(ui->btnPlus,     &QPushButton::clicked, this, [this]() { onOperatorClicked("+"); });
    connect(ui->btnMinus,    &QPushButton::clicked, this, [this]() { onOperatorClicked("-"); });
    connect(ui->btnMultiply, &QPushButton::clicked, this, [this]() { onOperatorClicked("×"); });
    connect(ui->btnDivide,   &QPushButton::clicked, this, [this]() { onOperatorClicked("÷"); });

    connect(ui->btnEqual,    &QPushButton::clicked, this, &MainWindow::onEqualClicked);

    clearAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================= 槽函数（第一阶段：仅完成界面框架与信号连接） =================
void MainWindow::onDigitClicked(int digit)   { appendDigit(digit); }
void MainWindow::onPointClicked()            { appendPoint(); }
void MainWindow::onBackspaceClicked()        { backspace(); }
void MainWindow::onClearClicked()           { clearAll(); }
void MainWindow::onOperatorClicked(const QString &op) { applyOperator(op); }
void MainWindow::onEqualClicked()           { calculate(); }
void MainWindow::onPercentClicked()         {}

void MainWindow::appendDigit(int digit)
{
    currentText = QString::number(digit);
    updateDisplay();
}

void MainWindow::appendPoint()   {}
void MainWindow::backspace()     {}

void MainWindow::clearAll()
{
    currentText  = "0";
    firstOperand = 0.0;
    pendingOp.clear();
    waitingSecond = false;
    justCalculated = false;
    hasError = false;
    updateDisplay();
}

void MainWindow::applyOperator(const QString &op)
{
    pendingOp = op;
    waitingSecond = true;
    updateDisplay();
}

void MainWindow::calculate() {}

double MainWindow::perform(double a, double b, const QString &op, bool &ok)
{
    ok = true;
    Q_UNUSED(a); Q_UNUSED(b); Q_UNUSED(op);
    return 0.0;
}

QString MainWindow::formatNumber(double value)
{
    return QString::number(value);
}

void MainWindow::showError(const QString &msg)
{
    currentText = msg;
    updateDisplay();
}

void MainWindow::updateDisplay()
{
    ui->displayLabel->setText(currentText);
    ui->exprLabel->setText(pendingOp);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
}
