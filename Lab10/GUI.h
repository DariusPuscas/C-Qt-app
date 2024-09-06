#pragma once
#include "ServiceDiscipline.h"
#include "RepoLab.h"
#include "RepoDiscipline.h"
#include "FileRepoDiscipline.h"
#include "RepoContract.h"
#include "Validator.h"

#include "ListModel.h"

#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>

#include <QList>

#include <QPainter>

///

class Contract: public QWidget,public Observable, public Observer{
    friend class ServiceDiscipline;
    friend class GUI;
    friend class ContractReadOnlyGUI;
private:
    ServiceDiscipline& srv;
    //buttons
    QPushButton* refreshL=new QPushButton{"&REFRESH LIST"};
    QPushButton* add_contract=new QPushButton{"&ADD TO CONTRACT"};
    QPushButton* empty_contract=new QPushButton{"&EMPTY CONTRACT"};
    QPushButton* generate_contract=new QPushButton{"&Generate CONTRACT"};
    QPushButton* export_contract=new QPushButton{"&EXPORT TO CONTRACT"};
    QPushButton* exit_contract=new QPushButton{"&EXIT"};
    //text fields
    QLineEdit* txtContractName=new QLineEdit;
   // QLineEdit* txtContractTeacher=new QLineEdit;
    QLineEdit* txtContractNumber=new QLineEdit;
    QLineEdit* txtContractFile=new QLineEdit;
    //list
    QListView*  lst_view = new QListView;
    ListModel* model = new ListModel{srv.getall_contract()};
    QListWidget* contract_list=new QListWidget;

    void ui_addContract() ;
public:
    explicit Contract(ServiceDiscipline &srv): srv(srv){
       // addObserver(this);
    };
    void innit_contract();
    void connectSignalContract();
    void reloadList(const vector<Disciplina> &list);
    void update() override{
        reloadList(srv.getall_contract());

    }

};
class ContractReadOnlyGUI: public QWidget,public Observer{
    friend class Contract;
    Contract* contr;
    QListWidget* lista_obj;

public:
    explicit ContractReadOnlyGUI(Contract *c): contr(c){
        contr->srv.addObserver(this);
      //  contr->addObserver(this);
    }
    void innitContract()
    {
        lista_obj=new QListWidget();
        QHBoxLayout* main=new QHBoxLayout;
        main->addWidget(lista_obj);
        this->setLayout(main);
    }
    void update() override{
        this->repaint();
    }
    void reload()
    {
        lista_obj->clear();
        for(const auto &s: contr->srv.getall_contract())
        {
            lista_obj->addItem(QString::fromStdString(s.get_denumire()+","+std::to_string(s.get_nr_ore())+","+s.get_tip()+","+s.get_cadru_didactic()));
        }
    }
    void paintEvent(QPaintEvent* e) override{
        QPainter p(this);
        p.drawImage(0,0,QImage("book.png"));
        srand(time(0));
        int x = -20;
        for (const auto &elem : contr->srv.getall_contract())
        {
            x += 40;
            int forma = rand()%4;
            int inaltime = rand()%130;
            int start_y = rand()%60;
            QColor color;

            int color_num = rand() %5;
            switch (color_num)
            {
                case 0:
                    color = Qt::red;
                    break;
                case 1:
                    color = Qt::green;
                    break;
                case 2:
                    color = Qt::black;
                    break;
                case 3:
                    color = Qt::blue;
                    break;
                case 4:
                    color = Qt::lightGray;
                    break;
                default:
                    break;
            }

            switch (forma)
            {
                case 0: // dreptunghi
                    p.drawRect(x, start_y, 20, inaltime);
                    break;
                case 1: // elipsa
                    p.drawEllipse(x, start_y, 20, inaltime);
                    break;
                case 2: // dreptunghi colorat
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
                default: // dreptunghi colorat
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
            }}}
    ~ContractReadOnlyGUI()
    {
        contr->srv.removeObserver(this);
    }

};



///

class GUI: public QWidget,public Observable{
private:
    ServiceDiscipline& serv;
    Contract* contract;
  //  QWidget* contract=new QWidget;
    QTableWidget* table_main=new QTableWidget;
  //  QListWidget* contract_list=new QListWidget;
    /** BUTTONS MAIN
     */
    QPushButton* undo=new QPushButton{"&UNDO"};
    QPushButton* add=new QPushButton{"&ADD"};
    QPushButton* del=new QPushButton{"&STERGE"};
    QPushButton* modify=new QPushButton{"&MODIFICA"};
  //  QPushButton* open_contract=new QPushButton{"&OPEN CONTRACT"};
    QRadioButton* sort_name=new QRadioButton{"&Name"};
    QRadioButton* sort_hours=new QRadioButton{"&Hours"};
    QRadioButton* sort_teacher=new QRadioButton{"&Teacher"};
    QPushButton* filter_hours=new QPushButton{"&HOURS"};
    QPushButton* filter_teacher=new QPushButton{"&TEACHER"};
    QLineEdit* txtfilter=new QLineEdit;
    QPushButton* exit=new QPushButton{"&EXIT"};
    QPushButton* load=new QPushButton{"&LOAD"};

    QPushButton*  add_cos = new QPushButton{"ADD contract"};
    QPushButton*  empty = new QPushButton{"Goleste contract"};
    QPushButton* generare = new QPushButton{"Genereaza contract"};
    QPushButton* exp = new QPushButton{"Export"};


    //CONTRACT BUTTON
 //   QPushButton* add_contract=new QPushButton{"&ADD TO CONTRACT"};
 //   QPushButton* empty_contract=new QPushButton{"&EMPTY CONTRACT"};
 //   QPushButton* generate_contract=new QPushButton{"&Generate CONTRACT"};
 //   QPushButton* export_contract=new QPushButton{"&EXPORT TO CONTRACT"};
 //   QPushButton* exit_contract=new QPushButton{"&EXIT"};
    QPushButton* open_contract=new QPushButton{"&OPEN CONTRACT"};
    QPushButton* open_roc=new QPushButton{"Open read only contract"};


    /**FORM LAYOUT*/
    QLineEdit* txtSubject=new QLineEdit;
    QLineEdit* txtHours=new QLineEdit;
    QLineEdit* txtType=new QLineEdit;
    QLineEdit* txtTeacher=new QLineEdit;
    /*
     * Contract
     */
 //   QLineEdit* txtContractName=new QLineEdit;
 //   QLineEdit* txtContractTeacher=new QLineEdit;
 //   QLineEdit* txtContractNumber=new QLineEdit;
  //  QLineEdit* txtContractFile=new QLineEdit;
//    void loadList(const vector<Disciplina> &subject);


    void loadTable(const vector<Disciplina> &subject);
 //   void contractgui();
    void connectSignalSlots();
    // void initiateTable();

    void initgui();

    void ui_add();
    void ui_delete();
    void ui_modify();
    void ui_filter_h();
    void ui_filter_t();
    void ui_sort_n();
  //  void ui_addContract();


public:
    GUI(ServiceDiscipline& service): serv{service}{
        initgui();
        //contractgui();
        contract = new Contract(serv);
        contract->innit_contract();
        contract->connectSignalContract();
        //addObserver(contract);
        loadTable(service.getall());
        connectSignalSlots();
    };




};



