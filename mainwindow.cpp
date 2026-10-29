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

// ================= 数字输入 =================
void MainWindow::onDigitClicked(int digit)   { appendDigit(digit); }
void MainWindow::onPointClicked()           { appendPoint(); }
void MainWindow::onBackspaceClicked()       { backspace(); }
void MainWindow::onClearClicked()           { clearAll(); }
void MainWindow::onOperatorClicked(const QString &op) { applyOperator(op); }
void MainWindow::onEqualClicked()           { calculate(); }

void MainWindow::appendDigit(int digit)
{
    // 错误状态下先复位，再输入新数字
    if (hasError) clearAll();

    // 刚按完等号：新数字作为全新操作数开始输入
    if (justCalculated) {
        currentText = QString::number(digit);
        justCalculated = false;
        waitingSecond = false;
        updateDisplay();
        return;
    }

    // 刚按完运算符：显示屏切换为第二个操作数
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
    if (hasError) clearAll();

    if (justCalculated) {
        currentText = "0.";
        justCalculated = false;
        waitingSecond = false;
        updateDisplay();
        return;
    }
    if (waitingSecond) {
        currentText = "0.";
        waitingSecond = false;
        updateDisplay();
        return;
    }
    // 同一操作数已存在小数点则忽略，防止 1.2.3
    if (!currentText.contains('.'))
        currentText.append('.');
    updateDisplay();
}

void MainWindow::backspace()
{
    if (hasError) { clearAll(); return; }
    // 等待第二个操作数或刚出结果时不允许退格
    if (waitingSecond || justCalculated) return;

    if (currentText.length() <= 1)
        currentText = "0";
    else {
        currentText.chop(1);
        if (currentText.isEmpty() || currentText == "-")
            currentText = "0";
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

// ================= 运算符 =================
void MainWindow::applyOperator(const QString &op)
{
    if (hasError) return;

    // 刚按完等号又按运算符：以上一次结果作为第一个操作数，支持结果基础上连续运算
    if (justCalculated) {
        firstOperand = currentText.toDouble();
        pendingOp = op;
        waitingSecond = true;
        justCalculated = false;
        updateDisplay();
        return;
    }

    // 连续按不同运算符：只替换运算符，不重复计算
    if (waitingSecond) {
        pendingOp = op;
        updateDisplay();
        return;
    }

    // 已有待执行运算符且已输入第二个操作数：先算中间结果，支持链式连续运算
    if (!pendingOp.isEmpty()) {
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

// ================= 等号 =================
void MainWindow::calculate()
{
    if (hasError) return;
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

// ================= 百分号 =================
void MainWindow::onPercentClicked()
{
    if (hasError) return;
    double value = currentText.toDouble() / 100.0;
    currentText = formatNumber(value);
    updateDisplay();
}

// ================= 结果格式化 =================
QString MainWindow::formatNumber(double value)
{
    if (qFuzzyCompare(value, std::round(value)) && qAbs(value) < 1e15)
        return QString::number(value, 'f', 0);
    return QString::number(value, 'g', 12);
}

// ================= 错误处理：锁定状态，直到按清除或数字复位 =================
void MainWindow::showError(const QString &msg)
{
    currentText  = msg;
    pendingOp.clear();
    waitingSecond = false;
    justCalculated = false;
    hasError = true;
    ui->exprLabel->setText("");
    ui->displayLabel->setText(msg);
}

// ================= 刷新显示 =================
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
