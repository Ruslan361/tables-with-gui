#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "orderedmaplist.h"
#include "orderedmapvector.h"
#include "unorderedmaplist.h"
#include "unorderedmapvector.h"
#include "hashtable.h"
#include "ttable.h"
#include "AVLTree.h"
#include "polynom.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




struct Tables
{
    QStringList names = {"Ordered map on vector",
        "Unordered map on vector",
        "Ordered map on list",
        "Unordered map on list",
        "Hash table",
        "AVL Tree"
    };
    unsigned int mode;
    TContainer<int, Polynom<int>>** container;
    Tables()
    {
        mode = 0;
        int count = names.count();
        container = new TContainer<int, Polynom<int>>*[count];
        container[0] = new TOrderedMapVector<int, Polynom<int>>;
        container[1] = new TUnorderedMapVector<int, Polynom<int>>;
        container[2] = new TOrderedMapList<int, Polynom<int>>;
        container[3] = new TUnorderedMapList<int, Polynom<int>>;
        container[4] = new THashTable<int, Polynom<int>>;
        container[5] = new AVLTree<int, Polynom<int>>;
    }
    void Add(int table_id, int key, const Polynom<int>& value)
    {
        container[table_id]->Add(key, value);
    }
    void Remove(int table_id, int key)
    {
        container[table_id]->Remove(key);
    }
    TSingleLinkedList<int> GetKeys(int table_id)
    {
        return container[table_id]->GetKeys();
    }
    TSingleLinkedList<Polynom<int>> GetValues(int table_id, int key)
    {
        return container[table_id]->GetValues(key);
    }
    bool Search(int table_id, int id, Polynom<int>& result)
    {
        return container[table_id]->Search(id, result);
    }
    //Iterator<TPair<int, Polynom<int>>> begin(int table_id)
    //{
     //   return container[table_id]->begin();
    //}
    ~Tables()
    {
        for (int var = 0; var < names.count(); ++var) {
            delete container[var];
        }
        delete[] container;
    }
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Tables tables;

    void RefreshTable(int index);

private slots:
    void on_AddBtn_clicked();

    void on_SelectTableComboBox_currentIndexChanged(int index);

    void on_RemBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
