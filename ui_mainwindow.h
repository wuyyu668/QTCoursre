/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actSetStudentList;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitterMain;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *btnDelCurRow;
    QPushButton *btnInsertRow;
    QPushButton *btnAppendRow;
    QCheckBox *chkBoxHeaderH;
    QCheckBox *chkBoxTabEditable;
    QPushButton *btnReadToEdit;
    QCheckBox *chkBoxRowColor;
    QRadioButton *rBtnSelectItem;
    QCheckBox *chkBoxHeaderV;
    QRadioButton *rBtnSelectRow;
    QPushButton *btnIniData;
    QSpinBox *spinRowCount;
    QPushButton *btnSetHeader;
    QPushButton *btnSetRows;
    QPushButton *btnAutoHeght;
    QPushButton *btnAutoWidth;
    QSplitter *splitter;
    QTableWidget *tableInfo;
    QPlainTextEdit *textEdit;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(791, 486);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        actSetStudentList = new QAction(MainWindow);
        actSetStudentList->setObjectName("actSetStudentList");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        splitterMain = new QSplitter(centralWidget);
        splitterMain->setObjectName("splitterMain");
        splitterMain->setOrientation(Qt::Orientation::Horizontal);
        groupBox = new QGroupBox(splitterMain);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        btnDelCurRow = new QPushButton(groupBox);
        btnDelCurRow->setObjectName("btnDelCurRow");

        gridLayout->addWidget(btnDelCurRow, 4, 0, 1, 2);

        btnInsertRow = new QPushButton(groupBox);
        btnInsertRow->setObjectName("btnInsertRow");

        gridLayout->addWidget(btnInsertRow, 3, 0, 1, 1);

        btnAppendRow = new QPushButton(groupBox);
        btnAppendRow->setObjectName("btnAppendRow");

        gridLayout->addWidget(btnAppendRow, 3, 1, 1, 1);

        chkBoxHeaderH = new QCheckBox(groupBox);
        chkBoxHeaderH->setObjectName("chkBoxHeaderH");
        chkBoxHeaderH->setChecked(true);

        gridLayout->addWidget(chkBoxHeaderH, 8, 0, 1, 1);

        chkBoxTabEditable = new QCheckBox(groupBox);
        chkBoxTabEditable->setObjectName("chkBoxTabEditable");
        chkBoxTabEditable->setChecked(true);

        gridLayout->addWidget(chkBoxTabEditable, 7, 0, 1, 1);

        btnReadToEdit = new QPushButton(groupBox);
        btnReadToEdit->setObjectName("btnReadToEdit");
        btnReadToEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(btnReadToEdit, 6, 0, 1, 2);

        chkBoxRowColor = new QCheckBox(groupBox);
        chkBoxRowColor->setObjectName("chkBoxRowColor");
        chkBoxRowColor->setChecked(true);

        gridLayout->addWidget(chkBoxRowColor, 7, 1, 1, 1);

        rBtnSelectItem = new QRadioButton(groupBox);
        rBtnSelectItem->setObjectName("rBtnSelectItem");
        rBtnSelectItem->setChecked(true);

        gridLayout->addWidget(rBtnSelectItem, 9, 1, 1, 1);

        chkBoxHeaderV = new QCheckBox(groupBox);
        chkBoxHeaderV->setObjectName("chkBoxHeaderV");
        chkBoxHeaderV->setChecked(true);

        gridLayout->addWidget(chkBoxHeaderV, 8, 1, 1, 1);

        rBtnSelectRow = new QRadioButton(groupBox);
        rBtnSelectRow->setObjectName("rBtnSelectRow");
        rBtnSelectRow->setChecked(false);

        gridLayout->addWidget(rBtnSelectRow, 9, 0, 1, 1);

        btnIniData = new QPushButton(groupBox);
        btnIniData->setObjectName("btnIniData");
        btnIniData->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(btnIniData, 2, 0, 1, 2);

        spinRowCount = new QSpinBox(groupBox);
        spinRowCount->setObjectName("spinRowCount");
        spinRowCount->setMinimum(2);
        spinRowCount->setValue(10);

        gridLayout->addWidget(spinRowCount, 1, 1, 1, 1);

        btnSetHeader = new QPushButton(groupBox);
        btnSetHeader->setObjectName("btnSetHeader");
        btnSetHeader->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(btnSetHeader, 0, 0, 1, 2);

        btnSetRows = new QPushButton(groupBox);
        btnSetRows->setObjectName("btnSetRows");
        btnSetRows->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(btnSetRows, 1, 0, 1, 1);

        btnAutoHeght = new QPushButton(groupBox);
        btnAutoHeght->setObjectName("btnAutoHeght");

        gridLayout->addWidget(btnAutoHeght, 5, 0, 1, 1);

        btnAutoWidth = new QPushButton(groupBox);
        btnAutoWidth->setObjectName("btnAutoWidth");

        gridLayout->addWidget(btnAutoWidth, 5, 1, 1, 1);

        splitterMain->addWidget(groupBox);
        splitter = new QSplitter(splitterMain);
        splitter->setObjectName("splitter");
        splitter->setFrameShadow(QFrame::Shadow::Plain);
        splitter->setLineWidth(2);
        splitter->setOrientation(Qt::Orientation::Vertical);
        tableInfo = new QTableWidget(splitter);
        if (tableInfo->columnCount() < 5)
            tableInfo->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableInfo->rowCount() < 6)
            tableInfo->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableInfo->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableInfo->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableInfo->setItem(0, 4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableInfo->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableInfo->setItem(2, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableInfo->setItem(5, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableInfo->setItem(5, 4, __qtablewidgetitem9);
        tableInfo->setObjectName("tableInfo");
        tableInfo->setAlternatingRowColors(true);
        tableInfo->setShowGrid(true);
        tableInfo->setGridStyle(Qt::PenStyle::SolidLine);
        tableInfo->setRowCount(6);
        tableInfo->setColumnCount(5);
        splitter->addWidget(tableInfo);
        tableInfo->horizontalHeader()->setVisible(true);
        tableInfo->horizontalHeader()->setDefaultSectionSize(80);
        tableInfo->verticalHeader()->setVisible(true);
        tableInfo->verticalHeader()->setDefaultSectionSize(27);
        textEdit = new QPlainTextEdit(splitter);
        textEdit->setObjectName("textEdit");
        splitter->addWidget(textEdit);
        splitterMain->addWidget(splitter);

        verticalLayout->addWidget(splitterMain);

        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        toolBar->addAction(actSetStudentList);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTableWidget\347\232\204\344\275\277\347\224\250", nullptr));
        actSetStudentList->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\255\246\347\224\237\345\220\215\345\215\225", nullptr));
#if QT_CONFIG(tooltip)
        actSetStudentList->setToolTip(QCoreApplication::translate("MainWindow", "\347\202\271\345\207\273\345\220\216\351\207\215\346\226\260\350\256\276\347\275\256\345\217\263\344\276\247\345\255\246\347\224\237\345\220\215\345\215\225\350\241\250\346\240\274", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QString());
        btnDelCurRow->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", nullptr));
        btnInsertRow->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\214", nullptr));
        btnAppendRow->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", nullptr));
        chkBoxHeaderH->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\260\264\345\271\263\350\241\250\345\244\264", nullptr));
        chkBoxTabEditable->setText(QCoreApplication::translate("MainWindow", "\350\241\250\346\240\274\345\217\257\347\274\226\350\276\221", nullptr));
        btnReadToEdit->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\350\241\250\346\240\274\345\206\205\345\256\271\345\210\260\346\226\207\346\234\254", nullptr));
        chkBoxRowColor->setText(QCoreApplication::translate("MainWindow", "\351\227\264\351\232\224\350\241\214\345\272\225\350\211\262", nullptr));
        rBtnSelectItem->setText(QCoreApplication::translate("MainWindow", "\345\215\225\345\205\203\346\240\274\351\200\211\346\213\251", nullptr));
        chkBoxHeaderV->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\236\202\347\233\264\350\241\250\345\244\264", nullptr));
        rBtnSelectRow->setText(QCoreApplication::translate("MainWindow", "\350\241\214\351\200\211\346\213\251", nullptr));
        btnIniData->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\350\241\250\346\240\274\346\225\260\346\215\256", nullptr));
        btnSetHeader->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\260\264\345\271\263\350\241\250\345\244\264", nullptr));
        btnSetRows->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\350\241\214\346\225\260", nullptr));
        btnAutoHeght->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\350\241\214\351\253\230", nullptr));
        btnAutoWidth->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\345\210\227\345\256\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\210\2271", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\345\210\2272", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\345\210\2273", nullptr));

        const bool __sortingEnabled = tableInfo->isSortingEnabled();
        tableInfo->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableInfo->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "0\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableInfo->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "0\350\241\214\357\274\2141\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableInfo->item(0, 4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "0\350\241\214\357\274\2144\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableInfo->item(1, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "1\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableInfo->item(2, 0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "2\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableInfo->item(5, 0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "5\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableInfo->item(5, 4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "5\350\241\214\357\274\2144\345\210\227", nullptr));
        tableInfo->setSortingEnabled(__sortingEnabled);

        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
