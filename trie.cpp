#include "ui_spellchecker.h"
#include "trie.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <bits/stdc++.h>

trie::trie()
{

}
node *trie::findkey(node *Node, string word, int ind)
{
    if(Node == NULL) return Node;

    if(ind == word.length()) return Node;

    return findkey(Node->links[word[ind]], word, ind+1);
}
node *trie::insert(node *Node, string word, int val, int ind)
{
    if(Node == NULL)
    {
        Node = new node();
    }

    if(ind == word.length())
    {
        Node->val = 1;
        return Node;
    }
    char ch = word[ind];
    Node->links[ch] = insert(Node->links[ch], word, val, ind+1);

    return Node;
}
node *trie::util(node *Node, string word, string &commonprefix, int ind)
{
    if(Node->links[word[ind]] == NULL)
        return Node;
    if(ind == word.length())
        return Node;
    commonprefix+=word[ind];
    return util(Node->links[word[ind]], word, commonprefix, ind+1);


}
node *trie::getcommonprefix(node *Node, string word, string &commonprefix)
{
    return util(Node, word, commonprefix, 0);
}
void trie::collect(node *Node, string commonprefix, deque<string> &sugg)
{
    if(Node == NULL)
    {
        return;
    }
    if(Node->val == 1)
    {
        sugg.push_back(commonprefix);
    }
    for(int i = 0; i < 256; ++i)
    {
            collect(Node->links[i], commonprefix+(char) i, sugg);
    }

}
QStringList trie::suggestions(node *root, string word)
{
    string commonprefix = "";
    node *Node = getcommonprefix(root, word, commonprefix);
    deque<string> sugg;
    collect(Node, commonprefix, sugg);
    QStringList sugg_list;
    while(!sugg.empty())
    {
        string temp = sugg.front();
        QString qstr = QString::fromStdString(temp);
        sugg_list << qstr;
        sugg.pop_front();
    }
    return sugg_list;
}
