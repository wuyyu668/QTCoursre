#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // 重写键盘事件：键盘输入统一转发到与鼠标相同的处理函数，保证两套输入逻辑一致
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onDigitClicked(int digit);              // 数字键 0~9（鼠标点击）
    void onPointClicked();                       // 小数点（鼠标点击）
    void onBackspaceClicked();                   // 退格（鼠标点击）
    void onClearClicked();                       // 清除 AC（鼠标点击）
    void onOperatorClicked(const QString &op);   // 四则运算符（鼠标点击）
    void onEqualClicked();                       // 等号（鼠标点击）
    void onPercentClicked();                     // 百分号（鼠标点击）

private:
    Ui::MainWindow *ui;

    // ================= 计算器内部状态 =================
    QString currentText;          // 显示屏上当前的数字字符串
    double firstOperand = 0.0;   // 第一个操作数
    QString pendingOp;            // 待执行的运算符（+ - × ÷）
    bool waitingSecond = false;   // 是否正在等待输入第二个操作数
    bool justCalculated = false;  // 上一次操作是否刚按过等号
    bool hasError = false;        // 是否处于错误状态（如除数为 0）

    // ---------- 统一的输入处理函数：鼠标槽函数与键盘事件都调用它们 ----------
    void appendDigit(int digit);              // 追加一个数字
    void appendPoint();                       // 追加小数点
    void backspace();                         // 删除最后一位
    void clearAll();                          // 复位全部状态
    void applyOperator(const QString &op);    // 记录/切换运算符，必要时先做链式计算
    void calculate();                         // 按等号完成一次计算
    double perform(double a, double b, const QString &op, bool &ok); // 真正执行四则运算
    QString formatNumber(double value);       // 结果格式化：整数不带小数点，非整数去掉尾零
    void showError(const QString &msg);      // 显示错误信息并锁定输入
    void updateDisplay();                     // 刷新主显示屏与上方表达式栏
};

#endif // MAINWINDOW_H
