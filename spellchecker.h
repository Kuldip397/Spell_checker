#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QCompleter>
#include <QDirModel>

using namespace  std;

struct node
{
    int val;
    node *links[256];
};

namespace Ui {
class spellchecker;
}

class spellchecker : public QMainWindow
{
    Q_OBJECT

public:
    explicit spellchecker(QWidget *parent = 0);
    ~spellchecker();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::spellchecker *ui;
    node *root = NULL;
    void get_text();
    QCompleter *StringCompleter;
};

#endif // SPELLCHECKER_H
