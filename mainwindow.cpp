#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QtMath>
#include <cmath>

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

// ================= 数字 / 小数点 / 退格 / 清除 =================
void MainWindow::onDigitClicked(int digit)   { appendDigit(digit); }
void MainWindow::onPointClicked()           { appendPoint(); }
void MainWindow::onBackspaceClicked()       { backspace(); }
void MainWindow::onClearClicked()           { clearAll(); }
void MainWindow::onOperatorClicked(const QString &op) { applyOperator(op); }
void MainWindow::onEqualClicked()           { calculate(); }

void MainWindow::appendDigit(int digit)
{
    if (waitingSecond) {
        currentText = QString::number(digit);
        waitingSecond = false;
        updateDisplay();
        return;
    }
    if (currentText == "0")
        currentText = QString::number(digit);
    else
        currentText.append(QString::number(digit));
    updateDisplay();
}

void MainWindow::appendPoint()
{
    if (waitingSecond) {
        currentText = "0.";
        waitingSecond = false;
        updateDisplay();
        return;
    }
    if (!currentText.contains('.'))
        currentText.append('.');
    updateDisplay();
}

void MainWindow::backspace()
{
    if (waitingSecond) return;
    if (currentText.length() <= 1)
        currentText = "0";
    else {
        currentText.chop(1);
        if (currentText.isEmpty()) currentText = "0";
    }
    updateDisplay();
}

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

// ================= 运算符：双操作数状态管理与链式连续运算 =================
void MainWindow::applyOperator(const QString &op)
{
    // 已有待执行运算符且已输入第二个操作数：先算出中间结果（1+2+3 链式计算）
    if (!pendingOp.isEmpty() && !waitingSecond) {
        double second = currentText.toDouble();
        bool ok = true;
        double result = perform(firstOperand, second, pendingOp, ok);
        if (!ok) { showError("除数不能为0"); return; }
        firstOperand = result;
        currentText = formatNumber(result);
    } else {
        firstOperand = currentText.toDouble();
    }

    pendingOp = op;
    waitingSecond = true;
    updateDisplay();
}

// ================= 等号计算 =================
void MainWindow::onPercentClicked()
{
    double value = currentText.toDouble() / 100.0;
    currentText = formatNumber(value);
    updateDisplay();
}

void MainWindow::calculate()
{
    if (pendingOp.isEmpty()) return;

    double second = currentText.toDouble();
    bool ok = true;
    double result = perform(firstOperand, second, pendingOp, ok);
    if (!ok) { showError("除数不能为0"); return; }

    currentText = formatNumber(result);
    pendingOp.clear();
    waitingSecond = true;
    justCalculated = true;
    updateDisplay();
}

// ================= 四则运算核心 =================
double MainWindow::perform(double a, double b, const QString &op, bool &ok)
{
    ok = true;
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "×") return a * b;
    if (op == "÷") {
        if (b == 0.0) { ok = false; return 0.0; }
        return a / b;
    }
    return a;
}

// ================= 结果格式化 =================
QString MainWindow::formatNumber(double value)
{
    if (qFuzzyCompare(value, std::round(value)) && qAbs(value) < 1e15)
        return QString::number(value, 'f', 0);
    return QString::number(value, 'g', 12);
}

void MainWindow::showError(const QString &msg)
{
    currentText = msg;
    updateDisplay();
}

void MainWindow::updateDisplay()
{
    ui->displayLabel->setText(currentText);
    if (pendingOp.isEmpty())
        ui->exprLabel->setText("");
    else
        ui->exprLabel->setText(formatNumber(firstOperand) + " " + pendingOp);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
}
