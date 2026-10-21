#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>


void Write(QString File, QString str) {
    QFile mFile(File);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "開不了";
        return;
    }

    QTextStream out(&mFile);
    out.setEncoding(QStringConverter::System); //使用當前系統編碼

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
    ColTitle << "學號" << "班級" << "姓名" << "電話"; //行標題設置
    ui->tableWidget->setHorizontalHeaderLabels(ColTitle); //水平標頭文字設置
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
    ui->tableWidget->insertRow(ui->tableWidget->rowCount()); //新增一列(insertRow(row(index))

    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, inCol1); //因為每次都是取Row當前數量，所以每次都得-1
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, inCol2); //setItem(row(index),col(index),QString value)
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, inCol3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, inCol4);

    //rowCount取得當前列數

}


void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveFile="";

    fileName = QFileDialog::getSaveFileName(this, "匯出通訊錄", ".", "csv(*.csv);;text(*.txt)");

    if (fileName.isEmpty()) {
        qDebug() << "空的" ;
        return;
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {

            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            if (item != nullptr) {
                saveFile += item->text();
            }

            if (j != ui->tableWidget->columnCount() - 1) {
                saveFile += ",";
            }
        }
        saveFile += "\n";
    }
    Write(fileName,saveFile);

}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入通訊錄", "", "csv(*.csv);;text(*.txt)");
    if (fileName.isEmpty()) {
        qDebug() << "空的" ;
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "開不了";
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::System);


    // 清除舊資料
    ui->tableWidget->setRowCount(0);

    // 一行一行讀取
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed().isEmpty()) {
            continue;
        }

        QStringList data = line.split(',');

        // 確認有4個欄位
        if (data.size() != 4) {
            continue;
        }

        int row = ui->tableWidget->rowCount();


        ui->tableWidget->insertRow(row);

        // 將資料放入表格
        for (int col = 0; col < 4; col++) {
            ui->tableWidget->setItem(row,col,new QTableWidgetItem(data[col]));
        }
    }

    file.close();

}

