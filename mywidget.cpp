#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>


void Write(QString File, QString str) {
    QFile mFile(File);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out.setEncoding(QStringConverter::System);

    out << str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList ColTitle;
    ColTitle << "學號" << "班級" << "姓名" << "電話";
    ui->tableWidget->setHorizontalHeaderLabels(ColTitle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inCol1, *inCol2, *inCol3, *inCol4;
    inCol1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inCol2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inCol3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inCol4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, inCol1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, inCol2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, inCol3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, inCol4);

}


void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveFile="";

    fileName = QFileDialog::getSaveFileName(this, "匯出通訊錄", ".", "csv(*.csv);;text(*.txt)");

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            saveFile += ui->tableWidget->item(i,j)->text() + (j != ui->tableWidget->columnCount()? "," : "");
        }
        saveFile += "\n";
    }
    Write(fileName,saveFile);

}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入通訊錄", "", "CSV Files (*.csv);;Text Files (*.txt)");

    // 沒東西
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    // 開啟檔案
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }

    QTextStream in(&file);

    // 清除舊資料
    ui->tableWidget->setRowCount(0);

    // 一行一行讀取
    while (!in.atEnd()) {
        QString line = in.readLine();

        // 跳過空白行
        if (line.trimmed().isEmpty()) {
            continue;
        }

        // 使用逗號分割
        QStringList data = line.split(',');

        // 確認有4個欄位
        if (data.size() != 4) {
            continue;
        }

        int row = ui->tableWidget->rowCount();

        // 新增一列
        ui->tableWidget->insertRow(row);

        // 將資料放入表格
        for (int col = 0; col < 4; col++) {
            ui->tableWidget->setItem(
                row,
                col,
                new QTableWidgetItem(data[col])
                );
        }
    }

    file.close();

}

