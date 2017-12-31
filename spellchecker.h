#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QMainWindow>
#include <bits/stdc++.h>
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
    node *insert(node *Node, string word, int val, int ind);
    node *findkey(node *Node, string word, int ind);
    QStringList suggestions(node *root, string word);
    node *getcommonprefix(node *Node, string word, string &commonprefix);
    node *util(node *Node, string word, string &commonprefix, int ind);
    void collect(node *Node, string commonprefix, deque<string> &sugg);
};

#endif // SPELLCHECKER_H
