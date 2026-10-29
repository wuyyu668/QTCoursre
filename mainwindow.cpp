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

    // ================= 界面样式表（QSS） =================
    // 深色背景；上方表达式栏灰色小字；主显示屏白色大字；
    // 数字键深灰、清除类中灰、运算符与等号橙色高亮。
    this->setStyleSheet(
        "QMainWindow { background-color: #1e1e2e; }"
        "QLabel#exprLabel { color: #9a9ab0; font-size: 16px; "
        "qproperty-alignment: AlignRight|AlignVCenter; padding-right: 14px; }"
        "QLabel#displayLabel { color: #ffffff; font-size: 42px; font-weight: bold; "
        "qproperty-alignment: AlignRight|AlignVCenter; padding-right: 14px; }"
        "QPushButton { font-size: 20px; border: none; border-radius: 12px; min-height: 58px; "
        "color: #ffffff; background-color: #2c2c3e; }"
        "QPushButton:hover { background-color: #3d3d52; }"
        "QPushButton:pressed { background-color: #50506a; }"
        "QPushButton#btnClear, QPushButton#btnBackspace, QPushButton#btnPercent { "
        "background-color: #555566; }"
        "QPushButton#btnPlus, QPushButton#btnMinus, QPushButton#btnMultiply, "
        "QPushButton#btnDivide, QPushButton#btnEqual { background-color: #ff9f0a; font-size: 24px; }"
    );

    // ================= 鼠标信号与槽连接 =================
    // 数字键：用 lambda 把按钮对应的数字传给同一个处理函数，避免为 10 个数字各写一个槽函数
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

    connect(ui->btnPlus,    &QPushButton::clicked, this, [this]() { onOperatorClicked("+"); });
    connect(ui->btnMinus,   &QPushButton::clicked, this, [this]() { onOperatorClicked("-"); });
    connect(ui->btnMultiply,&QPushButton::clicked, this, [this]() { onOperatorClicked("×"); });
    connect(ui->btnDivide,  &QPushButton::clicked, this, [this]() { onOperatorClicked("÷"); });

    connect(ui->btnEqual,   &QPushButton::clicked, this, &MainWindow::onEqualClicked);

    clearAll();  // 初始化显示为 0
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================= 数字输入 =================
void MainWindow::onDigitClicked(int digit)
{
    appendDigit(digit);
}

void MainWindow::appendDigit(int digit)
{
    // 错误状态下先复位，再输入新数字
    if (hasError) clearAll();

    // 刚按完等号：新数字作为一个全新操作数开始输入
    if (justCalculated) {
        currentText = QString::number(digit);
        justCalculated = false;
        waitingSecond = false;
        updateDisplay();
        return;
    }

    // 刚按完运算符：显示屏切换为第二个操作数的输入
    if (waitingSecond) {
        currentText = QString::number(digit);
        waitingSecond = false;
        updateDisplay();
        return;
    }

    // 当前为 0 时直接替换，避免出现 000、012 这样的前导零
    if (currentText == "0")
        currentText = QString::number(digit);
    else
        currentText.append(QString::number(digit));

    updateDisplay();
}

// ================= 小数点 =================
void MainWindow::onPointClicked()
{
    appendPoint();
}

void MainWindow::appendPoint()
{
    if (hasError) clearAll();

    // 刚出结果或刚按完运算符：新操作数以 0. 开头
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

    // 关键判断：当前操作数中已经存在小数点就忽略，防止输入 1.2.3
    if (!currentText.contains('.'))
        currentText.append('.');

    updateDisplay();
}

// ================= 退格 =================
void MainWindow::onBackspaceClicked()
{
    backspace();
}

void MainWindow::backspace()
{
    if (hasError) { clearAll(); return; }
    // 等待第二个操作数或刚出结果时，退格不产生作用
    if (waitingSecond || justCalculated) return;

    if (currentText.length() <= 1) {
        currentText = "0";
    } else {
        currentText.chop(1);
        if (currentText.isEmpty() || currentText == "-")
            currentText = "0";
    }
    updateDisplay();
}

// ================= 清除 =================
void MainWindow::onClearClicked()
{
    clearAll();
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
void MainWindow::onOperatorClicked(const QString &op)
{
    applyOperator(op);
}

void MainWindow::applyOperator(const QString &op)
{
    if (hasError) return;

    // 刚按完等号又按运算符：以上一次结果作为第一个操作数，实现结果基础上的连续运算
    if (justCalculated) {
        firstOperand = currentText.toDouble();
        pendingOp = op;
        waitingSecond = true;
        justCalculated = false;
        updateDisplay();
        return;
    }

    // 连续按不同运算符：只替换待执行运算符，不重复计算
    if (waitingSecond) {
        pendingOp = op;
        updateDisplay();
        return;
    }

    // 已有待执行运算符且已输入第二个操作数：先算出中间结果，支持 1+2+3 链式连续运算
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
void MainWindow::onEqualClicked()
{
    calculate();
}

void MainWindow::calculate()
{
    if (hasError) return;
    if (pendingOp.isEmpty()) return;  // 没有运算符，等号不做处理

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
        if (b == 0.0) { ok = false; return 0.0; }  // 除数为 0，置错误标志
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
    // 整数直接按整数显示；非整数用 g 格式去掉多余尾零，最多保留 12 位有效数字
    if (qFuzzyCompare(value, std::round(value)) && qAbs(value) < 1e15)
        return QString::number(value, 'f', 0);
    return QString::number(value, 'g', 12);
}

// ================= 错误处理 =================
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

// ================= 键盘事件 =================
// 键盘按下后映射到对应的统一处理函数，与鼠标点击走完全相同的一套逻辑
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0: case Qt::Key_1: case Qt::Key_2: case Qt::Key_3:
    case Qt::Key_4: case Qt::Key_5: case Qt::Key_6: case Qt::Key_7:
    case Qt::Key_8: case Qt::Key_9:
        onDigitClicked(event->key() - Qt::Key_0);
        event->accept();
        return;
    case Qt::Key_Period:
    case Qt::Key_Comma:
        onPointClicked();
        event->accept();
        return;
    case Qt::Key_Plus:
        onOperatorClicked("+");
        event->accept();
        return;
    case Qt::Key_Minus:
        onOperatorClicked("-");
        event->accept();
        return;
    case Qt::Key_Asterisk:
        onOperatorClicked("×");
        event->accept();
        return;
    case Qt::Key_Slash:
        onOperatorClicked("÷");
        event->accept();
        return;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal:
        onEqualClicked();
        event->accept();
        return;
    case Qt::Key_Backspace:
        onBackspaceClicked();
        event->accept();
        return;
    case Qt::Key_Escape:
    case Qt::Key_Delete:
        onClearClicked();
        event->accept();
        return;
    default:
        // 其他按键交给父类默认处理
        QMainWindow::keyPressEvent(event);
        return;
    }
}
