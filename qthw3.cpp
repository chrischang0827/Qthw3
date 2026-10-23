#include "qthw3.h"
#include "ui_qthw3.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStringConverter>

Qthw3::Qthw3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Qthw3)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList ColTitle;

    ColTitle << "學號" << "班級" << "姓名" << "電話";

    ui->tableWidget->setHorizontalHeaderLabels(ColTitle);
}

Qthw3::~Qthw3()
{
    delete ui;
}

void Qthw3::on_pushButton_clicked()
{

    QString studentID = ui->lineEdit->text();
    QString studentClass = ui->lineEdit_2->text();
    QString studentName = ui->lineEdit_3->text();
    QString studentPhone = ui->lineEdit_4->text();

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(studentID));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(studentClass));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(studentName));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(studentPhone));

}




void Qthw3::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "匯出 TXT 檔案",
        "students.txt",
        "文字檔 (*.txt)"
        );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".txt", Qt::CaseInsensitive))
        fileName += ".txt";

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "錯誤", "無法開啟檔案");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString saveFile = "";

        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);

            if (item != nullptr)
                saveFile += item->text();

            if (j < ui->tableWidget->columnCount() - 1)
                saveFile += ",";
        }

        out << saveFile << "\n";
    }

    file.close();

    QMessageBox::information(this, "成功", "TXT 匯出成功！");
}





void Qthw3::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "選擇 CSV 檔案",
        "",
        "CSV 檔案 (*.csv)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "錯誤", "無法開啟檔案");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    // 清除原本的資料，保留表格標題
    ui->tableWidget->setRowCount(0);

    bool firstLine = true;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.trimmed().isEmpty())
            continue;

        QStringList data = line.split(",");

        // 如果第一行是標題，就略過
        if (firstLine)
        {
            firstLine = false;

            if (!data.isEmpty() && data[0].trimmed() == "學號")
                continue;
        }

        if (data.size() != 4)
            continue;

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < 4; col++)
        {
            ui->tableWidget->setItem(
                row,
                col,
                new QTableWidgetItem(data[col])
                );
        }
    }

    file.close();

    QMessageBox::information(
        this,
        "完成",
        "CSV 資料匯入成功！"
        );
}

