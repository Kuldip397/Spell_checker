#ifndef TRIE_H
#define TRIE_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include "spellchecker.h"

using namespace std;

class trie
{
public:
    trie();
    node *insert(node *Node, string word, int val, int ind);
    node *findkey(node *Node, string word, int ind);
    QStringList suggestions(node *root, string word);
private:
    node *getcommonprefix(node *Node, string word, string &commonprefix);
    node *util(node *Node, string word, string &commonprefix, int ind);
    void collect(node *Node, string commonprefix, deque<string> &sugg);
};

#endif // TRIE_H
