#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>

QString file = "C:/Users/user/Downloads";

void Write(QString File, QString str) {
    QFile mFile(File);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for write";
        return;
    }

    QTextStream out(&mFile);

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

    fileName = QFileDialog::getSaveFileName(this, "匯出通訊錄", ".", "csv(*.csv);;text(*txt)");

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            saveFile += ui->tableWidget->item(i,j)->text() + ",";
        }
        saveFile += "\n";
    }
    Write(file,saveFile);

}

