#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <iostream>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    readFromFile("input.txt");
}

void MainWindow::writeToFile(QString writeLine, QString fileName)
{
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::Append | QIODevice::Text)){
        qDebug() << "Cannot write to file.";
    }
    outFile.write(qPrintable(writeLine + "\n"));
    outFile.close();
}

void MainWindow::readFromFile(QString fileName) {
    char buf[1024];
    QString qsTemp;
    QFile inputFile(fileName);
    ui->label_5->setText("Reading palindromes from file: " + fileName + " and writing them to file output.txt");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open file" ;
    }
    while (!inputFile.atEnd()) {
        inputFile.readLine(buf, 1024);
        qsTemp = buf;
        qsTemp = qsTemp.trimmed();
        if (isPalindrome(qsTemp))  qsTemp =  "yes, it is a palindrome: " + qsTemp;
        else  qsTemp = "this is not a palindrome: " + qsTemp;
        ui->plainTextEdit->appendPlainText(qsTemp);
        writeToFile(qsTemp, "output.txt");
    }
}

void MainWindow::on_pushButton_Sort_clicked()
{
    sortList("input.txt");
}

void MainWindow::sortList(QString fileName){
    int p = 0;
    char phrase[1024];
    QString proverbs[1024];
    int proverbNumber[1024] = {0};
    int countLetters [1024] = {0};
    QFile inputFile(fileName);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open file " + fileName;
    }
    while (!inputFile.atEnd()) {
        int count = 0;

        for (int i = 0; i < 1024; i++){
            if (phrase[i] == '\n') break;
            count = i;
            countLetters[p] = i;
        }
        inputFile.readLine(phrase, 1024);
        for (int j = 0; j < 1024; j++){
            proverbs [p] = phrase;
            proverbNumber[p] = p;
        }
        if (count == 0) continue;
        qDebug() << "Number of letters in proverb No" << proverbNumber[p] << " is " << count + 1;
        p++;
    }
    countLetters[0] = 0;
    int max = *std::max_element(std::begin(countLetters), std::end(countLetters));
    qDebug() << "The longest proverbs are: ";
    int longestLines = 5;
    for (int j = max; j > 0; j--){
        bool yes = false;
        for (int i = 0; i < 1024; i++){
            if (countLetters[i] == max){
                yes = true;
                qDebug() << "Proverb of" << countLetters[i] << "letters long is No" << proverbNumber[i];
            }
        }
        max--;
        if (yes == true){longestLines--; qDebug();}
        if (longestLines <= 0) break;
    }
    writeToFile(proverbs[p], "output.txt");
}

bool MainWindow::isPalindrome(QString line)
{
       int j = line.size() - 1;
       for (int i = 0; i < line.size(); i++){
           if (line[i] == line[j]){
               j--;
               return true;
           } else return false;
       }
}
