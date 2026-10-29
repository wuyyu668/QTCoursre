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

// ================= 数字输入 =================
void MainWindow::onDigitClicked(int digit)   { appendDigit(digit); }
void MainWindow::onPointClicked()           { appendPoint(); }
void MainWindow::onBackspaceClicked()       { backspace(); }
void MainWindow::onClearClicked()           { clearAll(); }
void MainWindow::onOperatorClicked(const QString &op) { applyOperator(op); }
void MainWindow::onEqualClicked()           { calculate(); }
void MainWindow::onPercentClicked()         {}

void MainWindow::appendDigit(int digit)
{
    if (hasError) clearAll();

    // 刚按完运算符：切换为第二个操作数输入
    if (waitingSecond) {
        currentText = QString::number(digit);
        waitingSecond = false;
        updateDisplay();
        return;
    }

    // 当前为 0 时直接替换，避免前导零
    if (currentText == "0")
        currentText = QString::number(digit);
    else
        currentText.append(QString::number(digit));

    updateDisplay();
}

void MainWindow::appendPoint()
{
    if (hasError) clearAll();
    if (waitingSecond) {
        currentText = "0.";
        waitingSecond = false;
        updateDisplay();
        return;
    }
    // 同一操作数只允许一个小数点
    if (!currentText.contains('.'))
        currentText.append('.');
    updateDisplay();
}

void MainWindow::backspace()
{
    if (hasError) { clearAll(); return; }
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

// ================= 运算符与计算（第二阶段占位，后续提交实现） =================
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
