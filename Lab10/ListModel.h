#include <QAbstractListModel>
#include <string>
#include <vector>

#include "Disciplina.h"

using namespace std;
/*
class ListModel : public QAbstractListModel {
    vector<Disciplina> discipline;
public:
    ListModel(const vector<Disciplina>& discipline) : discipline{ discipline } {}

    int rowCount(const QModelIndex &parent) const override {
        return discipline.size();
    }

    int columnCount(const QModelIndex&parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || index.row() +1 >= discipline.size())
            return QVariant();

        if (role == Qt::DisplayRole) {
            Disciplina d = discipline.at(index.row() + 1);
            if (index.column() == 0)
                return QString::fromStdString(d.get_denumire());
            if (index.column() == 1)
                return QString::fromStdString(d.get_tip());
            if (index.column() == 2)
                return QString::number(d.get_nr_ore());
            if (index.column() == 3)
                return QString::fromStdString(d.get_cadru_didactic());
        }

        return QVariant();
    }

    void setDiscipline(const vector<Disciplina>& discipline) {
        this->discipline = discipline;
        auto topLeft = createIndex(0, 0);
        int x = discipline.size();
        auto bottomRight = createIndex(x, 4);
        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();

      }
};
 */
class ListModel:public QAbstractListModel{
    vector<Disciplina> discipline;
public:
    ListModel(const vector<Disciplina>& discipline): discipline{discipline}{}


    int rowCount(const QModelIndex &parent=QModelIndex()) const override{
        return discipline.size();
    }

    QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override{
        if(role==Qt::DisplayRole){
            auto d=discipline[index.row()].get_denumire()+','+discipline[index.row()].get_cadru_didactic()+','+discipline[index.row()].get_tip();
            return QString::fromStdString(d+','+to_string(discipline[index.row()].get_nr_ore()));
        }
        return QVariant{};
    }

    void setDiscipline(const vector<Disciplina>& discipline){
        this->discipline=discipline;
        auto topIndex= createIndex(0,0);
        auto botIndex= createIndex(rowCount(),0);
        emit dataChanged(topIndex,botIndex);
        emit layoutChanged();
    }
};