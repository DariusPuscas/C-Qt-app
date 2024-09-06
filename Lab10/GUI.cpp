#include "GUI.h"

void GUI::initgui() {
    //main layout
    this->setWindowTitle("Subjects App");

    QHBoxLayout* lymain=new QHBoxLayout;
    setLayout(lymain);

    QVBoxLayout* left_layout=new QVBoxLayout;
    lymain->addLayout(left_layout,9);

    left_layout->addWidget(new QLabel{"Table"});
    table_main->resizeColumnsToContents();
    left_layout->addWidget(table_main);
    left_layout->addWidget(undo);
    left_layout->addWidget(open_contract);

    /**
     * RIGHT LAYOUT
     */

    QVBoxLayout* right_layout=new QVBoxLayout;
    lymain->addLayout(right_layout,20);
    //operations
    QFormLayout* data_layout=new QFormLayout;
    right_layout->addLayout(data_layout);
    data_layout->addRow(new QLabel{"NAME:"},txtSubject);
    data_layout->addRow(new QLabel{"HOURS:"},txtHours);
    data_layout->addRow(new QLabel{"TYPE:"},txtType);
    data_layout->addRow(new QLabel{"TEACHER:"},txtTeacher);
    QHBoxLayout* actions=new QHBoxLayout;
    right_layout->addLayout(actions);
    actions->addWidget(add);
    actions->addWidget(modify);
    actions->addWidget(del);

    QVBoxLayout* sflayer=new QVBoxLayout;
    right_layout->addLayout(sflayer);
    sflayer->addWidget(new QLabel{"SORT TYPE"});
    sflayer->addWidget(sort_name);
    sflayer->addWidget(sort_hours);
    sflayer->addWidget(sort_teacher);
    sflayer->addWidget(new QLabel{"FILTER"});
    QHBoxLayout* filterlayer=new QHBoxLayout;
    right_layout->addLayout(filterlayer);
    filterlayer->addWidget(filter_hours);
    filterlayer->addWidget(filter_teacher);
    right_layout->addWidget(txtfilter);
    left_layout->addWidget(load);
    right_layout->addWidget(exit);
    right_layout->addWidget(open_roc);
    //loadTable(service.getAll());

    right_layout->addWidget(add_cos);
    right_layout->addWidget(empty);
    right_layout->addWidget(generare);
    right_layout->addWidget(exp);


//
//
//    lst->addItem(new QListWidgetItem{"item 2"});
//    lymain->addWidget(lst);
}
void Contract::innit_contract() {
    srv.addObserver(this);
  //  addObserver(this);
    //second layout for uh School Contract
   setWindowTitle("Set Contract");
   // QPalette second_pal=QPalette();
  //  second_pal.setColor(QPalette::Window,"#092b2b");
   // QFont font2("Comic Sans",12);
   // contract->setPalette(second_pal);
   // contract->setFont(font2);
    QHBoxLayout* lysecond=new QHBoxLayout;
    setLayout(lysecond);
    QVBoxLayout* l_lay=new QVBoxLayout;
    lysecond->addLayout(l_lay);
    l_lay->addWidget(new QLabel{"CONTRACT"});
    l_lay->addWidget(refreshL);
    l_lay->addWidget(empty_contract);
    QFormLayout* l_form=new QFormLayout;
    l_lay->addLayout(l_form);
    l_form->addRow(new QLabel{"Name:"},txtContractName);
  //  l_form->addRow(new QLabel{"Teacher:"},txtContractTeacher);
    l_lay->addWidget(add_contract);
    l_lay->addWidget(new QLabel{"GENERATE"});
    QFormLayout* gen_layout=new QFormLayout;
    l_lay->addLayout(gen_layout);
    gen_layout->addRow(new QLabel{"How many:"},txtContractNumber);
    l_lay->addWidget(generate_contract);
    l_lay->addWidget(new QLabel{"Export"});
    QFormLayout* export_layout=new QFormLayout;
    l_lay->addLayout(export_layout);
    export_layout->addRow(new QLabel{"FILE:"},txtContractFile);
    l_lay->addWidget(export_contract);
    QVBoxLayout* r_layout=new QVBoxLayout;
    lysecond->addLayout(r_layout);

    lst_view->setUniformItemSizes(true);
    lst_view->setModel(model);
    r_layout->addWidget(lst_view);

    //r_layout->addWidget(contract_list);
    r_layout->addWidget(exit_contract);
    //contract->show();

}
void GUI::loadTable(const vector<Disciplina> &subject) {
    this->table_main->clearContents();
    this->table_main->setColumnCount(5);
    this->table_main->setRowCount(subject.size()+1);
    int line_nr=0;
    table_main->setItem(line_nr,0,new QTableWidgetItem("NR"));
    table_main->setItem(line_nr,1,new QTableWidgetItem("NAME"));
    table_main->setItem(line_nr,2,new QTableWidgetItem("HOURS"));
    table_main->setItem(line_nr,3,new QTableWidgetItem("TEACHER"));
    table_main->setItem(line_nr,4,new QTableWidgetItem("TYPE"));
    line_nr++;
    for(const auto& Subject:subject)
    {
        table_main->setItem(line_nr,0,new QTableWidgetItem(QString::number(line_nr)));
        table_main->setItem(line_nr,1,new QTableWidgetItem(QString::fromStdString(Subject.get_denumire())));
        table_main->setItem(line_nr,2,new QTableWidgetItem(QString::number(Subject.get_nr_ore())));
        table_main->setItem(line_nr,3,new QTableWidgetItem(QString::fromStdString(Subject.get_cadru_didactic())));
        table_main->setItem(line_nr,4,new QTableWidgetItem(QString::fromStdString(Subject.get_tip())));
        line_nr++;
    }


}

void GUI::ui_add() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    string type=txtType->text().toStdString();
    string hours=txtHours->text().toStdString();
    qDebug()<<name<<teacher;
    int h;
    try {
        h= stoi(hours);
    }
    catch(std::invalid_argument& mes)
    {
        QMessageBox::warning(this,"WARNING","INVALID DATA");
        return;
    }

        serv.add(name,h,type,teacher);

    loadTable(serv.getall());

}
void GUI::ui_delete() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    qDebug()<<name<<teacher;

        serv.sterge(name,teacher);

    loadTable(serv.getall());
}
void GUI::ui_modify() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    string type=txtType->text().toStdString();
    string hours=txtHours->text().toStdString();
    qDebug()<<name<<teacher;
    int h;
    try {
        h= stoi(hours);
    }
    catch(std::invalid_argument& mes)
    {
        QMessageBox::warning(this,"WARNING","INVALID DATA");
        return;
    }
        Disciplina d;

        serv.modifica(d,d);

    loadTable(serv.getall());
}
void GUI::ui_filter_h(){
    string h=txtfilter->text().toStdString();
    int hours;
    try
    {
        hours=stoi(h);
    }
    catch (std::invalid_argument &mes)
    {
        QMessageBox::warning(nullptr,"!","INVALID INPUT");
    }
    vector<Disciplina> sbj=serv.filtrare_ore(hours);

    loadTable(sbj);
}
void GUI::ui_filter_t(){
    string teacher=txtfilter->text().toStdString();
    qDebug()<<teacher;
    vector<Disciplina> sbj=serv.filtrare_cd(teacher);

    loadTable(sbj);
}
void GUI::ui_sort_n() {
    vector<Disciplina> s=serv.sort_denumire();
    loadTable(s);
}
/*void Contract::loadList(const vector<Disciplina> &subject) {
    contract_list->clear();
    for(const auto& s:subject)
    {
        contract_list->addItem(QString::fromStdString(s.get_denumire()+","+std::to_string(s.get_nr_ore())+","+s.get_tip()+","+s.get_cadru_didactic()));
    }
}
*/
void Contract::reloadList(const vector<Disciplina> &subject) {
    model->setDiscipline(subject);
    /*contract_list->clear();
    for(const auto& s:subject)
    {   //QListWidgetItem* it=new QListWidgetItem()
        contract_list->addItem(QString::fromStdString(s.get_denumire()+","+std::to_string(s.get_nr_ore())+","+s.get_tip()+","+s.get_cadru_didactic()));
    }*/
}

void Contract::ui_addContract() {
    string name=txtContractName->text().toStdString();
 //   string teacher=txtContractTeacher->text().toStdString();
    auto found=srv.filtrare_denumire(name);
    if(found.empty())
    {
        QMessageBox::warning(nullptr,"1","SUBJECT: UNFOUND");
        return;
    }
    if(found.size()==1)
    {try
        {
            srv.add_to_contract(found[0].get_denumire());
        }
        catch(RepoException &m)
        {
            QMessageBox::warning(nullptr,"!",QString::fromStdString(m.get_mesaj()));
            return;
        }
       }
  /*  else
    {
        if(!teacher.empty())
        {
            try
            {
                serv.add_to_contract(name,teacher,found);
            }

            catch(RepoException &m)
            {
                QMessageBox::warning(nullptr,"!",QString::fromStdString(m.get_mesaj()));
                return;
            }

        }
        else
        {
            QMessageBox::warning(nullptr,"!","You have to provide something in the teacher field!");
        }
    }*/
    reloadList(srv.getall_contract());
    notify();
}

void Contract::connectSignalContract() {
    this->reloadList(srv.getall_contract());
    QObject::connect(exit_contract, &QPushButton::clicked, [&]() {
       notify();
       close();
    });
    QObject::connect(refreshL,&QPushButton::clicked,[&](){
        reloadList(srv.getall_contract());
    });
    QObject::connect(empty_contract, &QPushButton::clicked, [&]() {
        srv.emptyContract();
        reloadList(srv.getall_contract());
        notify();
    });
    QObject::connect(generate_contract, &QPushButton::clicked, [&]() {
        string n = txtContractNumber->text().toStdString();
        int nr;
        try {
            nr = stoi(n);
        }
        catch (std::invalid_argument &m) {
            QMessageBox::warning(nullptr, "!", "INVALID ARGUMENT");
        }
        srv.generateContract(nr);
        reloadList(srv.getall_contract());
        notify();
    });
    QObject::connect(add_contract, &QPushButton::clicked, this, &Contract::ui_addContract);
    QObject::connect(export_contract, &QPushButton::clicked, [&]() {
        string file = txtContractFile->text().toStdString();
        srv.export_contract(file);
    });


}

void GUI::connectSignalSlots() {
    /**GUI*/
    //exit
    QObject::connect(exit, &QPushButton::clicked, [&]() {
        this->close();
        contract->close();
        QMessageBox::information(nullptr, "!", "Closing app");
    });
    QObject::connect(add, &QPushButton::clicked, this, &GUI::ui_add);
    QObject::connect(del, &QPushButton::clicked, this, &GUI::ui_delete);
    QObject::connect(modify, &QPushButton::clicked, this, &GUI::ui_modify);
    QObject::connect(filter_teacher, &QPushButton::clicked, this, &GUI::ui_filter_t);
    QObject::connect(filter_hours, &QPushButton::clicked, this, &GUI::ui_filter_h);
    QObject::connect(load, &QPushButton::clicked, [&]() {
        this->loadTable(serv.getall());
    });
    QObject::connect(sort_name, &QRadioButton::toggled, this, &GUI::ui_sort_n);
    QObject::connect(sort_teacher, &QRadioButton::toggled, [&]() {

        loadTable(serv.sort_cd_tip());
    });
    QObject::connect(sort_hours, &QRadioButton::toggled, [&]() {

        loadTable(serv.sort_nr_ore());
    });
    QObject::connect(undo, &QPushButton::clicked, [&]() {
        try {
            serv.Undo();
        }
        catch (RepoException &mes) {
            QMessageBox::warning(nullptr, "!", QString::fromStdString(mes.get_mesaj()));
        }
        loadTable(serv.getall());
    });
    QObject::connect(open_contract, &QPushButton::clicked, [&]() {
        //contract->show();
        Contract*  contract_n = new Contract(serv);
        contract_n->innit_contract();
        contract_n->connectSignalContract();
        contract_n->show();
       // contract_n->addObserver( contract_n);
    });
    QObject::connect(open_roc, &QPushButton::clicked, [&]() {
        ContractReadOnlyGUI* contractRO = new  ContractReadOnlyGUI(contract);
        contractRO->show();

    });


    QObject::connect(add_cos,&QPushButton::clicked,[&](){\
        string name=txtSubject->text().toStdString();
       // string teacher=txtTeacher->text().toStdString();
        serv.add_to_contract(name);


    });
    QObject::connect(empty,&QPushButton::clicked,[this](){
        serv.emptyContract();
    });

    QObject::connect(generare,&QPushButton::clicked,[this](){
        int nr = txtHours->text().toInt();
        serv.generateContract(nr);
    });
    QObject::connect(exp,&QPushButton::clicked,[this](){
        serv.export_contract(R"(D:\OOP\Lab10\Discipline_Contract.html)");
    });


}