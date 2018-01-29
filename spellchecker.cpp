#include "spellchecker.h"
#include "ui_spellchecker.h"
#include "trie.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <bits/stdc++.h>

using namespace std;

spellchecker::spellchecker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::spellchecker)
{
    ui->setupUi(this);
    get_text();
}

spellchecker::~spellchecker()
{
    delete ui;
}
trie obj;
void spellchecker::get_text()
{

    QFile myFile(":/words_file/words.txt");
    myFile.open(QIODevice::ReadOnly);

    QTextStream textStream(&myFile);
    QString line = textStream.readAll();

    ui->textEdit_2->setPlainText(line);
    QTextCursor textCursor = ui->textEdit_2->textCursor();
    textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

    QStringList _list = line.split("\n");
    QStringList CompletionList;

    for(int i = 0; i < _list.length(); ++i)
    {
        QString temp = _list.at(i);
        CompletionList << temp;
        string word = temp.toStdString();
        root = obj.insert(root, word, 1, 0);
    }
    StringCompleter = new QCompleter(CompletionList, this);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_2->setCompleter(StringCompleter);

     myFile.close();
}

void spellchecker::on_pushButton_2_clicked()
{
    QString word = ui->lineEdit_2->text();

    string searchkey = word.toStdString();
    node *temp = obj.findkey(root, searchkey, 0);

    if(temp != NULL and temp->val == 1)
    {
        ui->textEdit->setFontWeight( 100 );
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->setPlainText("It is in the Dictionary");
        ui->textEdit_2->find(word, QTextDocument::FindWholeWords);
    }
    else
    {
           QStringList sugg_list = obj.suggestions(root, searchkey);
           ui->textEdit->setFontWeight( 100 );
           ui->textEdit->setTextColor( QColor( "red" ) );
           ui->textEdit->setPlainText("It is not in the Dictionary.....Probably spelled incorrectly\n");
           ui->textEdit->setTextColor( QColor("black"));
           ui->textEdit->append("Suggestions are:\n");
           for(int i = 0; i <sugg_list.length(); ++i)
           {
               QString temp = sugg_list.at(i);
               string word = temp.toStdString();
               ui->textEdit->append(temp);
           }
    }

}
