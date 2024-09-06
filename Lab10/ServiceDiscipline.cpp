#include "ServiceDiscipline.h"
#include <cassert>


const vector<Disciplina> &ServiceDiscipline::getall_contract() {
    return contract.get_contract();
}

int ServiceDiscipline::get_contractsize() {
    return (int)contract.get_contract().size();
}

void ServiceDiscipline::emptyContract() {
    contract.empty_contract();
    notify();
}

void ServiceDiscipline::generateContract(int nr) {
    contract.generare_contract(nr,repo.get_all());
    notify();
}

void ServiceDiscipline::export_contract(const std::string & nume) {
    contract.export_contract(nume);
}

int ServiceDiscipline::add_to_contract(const std::string &denumire) {
    auto filtru_nume= filtrare_denumire(denumire);
    auto seed=std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(filtru_nume.begin(),filtru_nume.end(),std::default_random_engine(seed));
    // auto gasit=repo.gaseste_disciplina(denumire,cd);
    if(!filtru_nume.empty()){
        auto cd = filtru_nume[0].get_cadru_didactic();
        auto D=repo.get_disciplina(denumire,cd);
        contract.add_contract(D);
        notify();
        return 0;
    }
    return -1;
}

void ServiceDiscipline::Undo() {
    /*  if (Actiuni_Undo.empty()) {
          throw RepoException{"Nu mai exista operatii"};
      }*/
    Actiuni_Undo.back()->doUndo();
    Actiuni_Undo.pop_back();
}

//repo
void ServiceDiscipline:: add(const string& denumire, float nr_ore, const string &tip,const string &cadru_didactic){
    Disciplina d ={denumire,nr_ore,tip,cadru_didactic};
    val.validare_disciplina(d);
    repo.store(d);

    Actiuni_Undo.push_back(std::make_unique<Undo_add>(d,repo));
}

const vector<Disciplina> &ServiceDiscipline::getall() {
    return repo.get_all();
}

void ServiceDiscipline::sterge(const std::string &denumire, const std::string &cadru_didactic) {
    Disciplina d = repo.get_disciplina(denumire,cadru_didactic);
    repo.sterge_disciplina(denumire,cadru_didactic);

    Actiuni_Undo.push_back(std::make_unique<Undo_sterge>(d,repo));
}

void ServiceDiscipline::modifica(const Disciplina &d, const Disciplina &ot) {
    repo.modifica_disciplina(d,ot);

    Actiuni_Undo.push_back(std::make_unique<Undo_modifica>(d,ot,repo));
}

/*
vector<Disciplina>ServiceDiscipline::filter(const function<bool(const Disciplina &)> &fct){
    vector<Disciplina> result;
    for(const auto & i : repo.get_all()) {
        if (fct(i))
            result.push_back(i);
    }
    return result;}*/

vector<Disciplina>ServiceDiscipline::filtrare_denumire(const string &denumire) {
    vector<Disciplina> result;
    copy_if(repo.get_all().begin(),repo.get_all().end(),std::back_inserter(result),[denumire](const Disciplina &d) {return d.get_denumire() == denumire;});
    return result;}

vector<Disciplina>ServiceDiscipline::filtrare_ore(float ore) {
    vector<Disciplina> result;
    copy_if(repo.get_all().begin(),repo.get_all().end(),std::back_inserter(result),[ore](const Disciplina &d) {return d.get_nr_ore() == ore;});
    return result;}

vector<Disciplina>ServiceDiscipline::filtrare_cd(const string& cd) {
    vector<Disciplina> result;
    copy_if(repo.get_all().begin(),repo.get_all().end(),std::back_inserter(result),[cd](const Disciplina &d) {return d.get_cadru_didactic() == cd;});
    return result;}

vector<Disciplina>ServiceDiscipline::filtrare_tip(const string& tip) {
    vector<Disciplina> result;
    copy_if(repo.get_all().begin(),repo.get_all().end(),std::back_inserter(result),[tip](const Disciplina &d) {return d.get_tip() == tip;});
    return result;}

/*
vector<Disciplina>ServiceDiscipline::sort(bool (*cmp_key)(const Disciplina &, const Disciplina &))  {
    vector<Disciplina> d = repo.get_all();
    for(int i=0; i<d.size()-1; i++)
        for(int j=i+1; j<d.size(); j++)
            if(cmp_key(d[i],d[j])){
                Disciplina aux =  d[i];
                d[i] = d[j];
                d[j] = aux;
            }
    return d;}
*/

vector<Disciplina>ServiceDiscipline::sort_nr_ore() {
    vector<Disciplina> d =repo.get_all();
    sort(d.begin(),d.end(), cmp_ore);
    return d;}

vector<Disciplina>ServiceDiscipline::sort_denumire() {
    vector<Disciplina> d =repo.get_all();
    sort(d.begin(),d.end(), cmp_denumire);
    return d;}

vector<Disciplina>ServiceDiscipline::sort_cd_tip() {
    vector<Disciplina> d =repo.get_all();
    sort(d.begin(),d.end(), cmp_cd_tip);
    return d;}

DTO ServiceDiscipline::get_raport(const string& cd) {
    map<string, DTO> report = repo.generare_raport();
    return (*report.find(cd)).second;

}


/*set<string>ServiceDiscipline::nr_tip() {
    set<string> tipuri;
    for(const auto&i:getall()){
        tipuri.insert(i.get_tip());
    }
    return tipuri;}

map<string,vector<Disciplina>>ServiceDiscipline::creeaza() {
    map<string,vector<Disciplina>>d;
    set<string>tipuri=nr_tip();
    for(const auto&tip:tipuri){
        vector<Disciplina>filtru = filtrare_tip(tip);
        d[tip]=filtru;
    }
    return d;
}
*/


void test_add(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",5,"b","c");
    serv.add("b",5,"b","c");
    serv.add("c",5,"b","c");
    auto materii = serv.getall();
    assert(materii.size()==3);

}

void test_sterge(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",5,"b","c");
    serv.add("x",5,"b","c");
    serv.sterge("a","c");
    auto materii = serv.getall();
    assert(materii.size()==1);
}

void test_serviceup(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",5,"b","c");
    const Disciplina& d ={"a",5,"b","c"};
    const Disciplina& ot ={"x",4,"d","d"};
    serv.modifica(d,ot);
    auto materii = serv.getall();
    assert(materii[0].get_denumire()=="x");
    assert(materii[0].get_nr_ore()==4);
    assert(materii[0].get_tip()=="d");
    assert(materii[0].get_cadru_didactic()=="d");

}

void test_filtrare1(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",5,"b","c");
    serv.add("x",4,"b","c");
    serv.add("b",5,"b","c");
    serv.add("c",3,"b","c");
    vector<Disciplina>filter;
    filter=serv.filtrare_ore(5);
    assert(filter.size()==2);
    filter=serv.filtrare_cd("c");
    assert(filter.size()==4);
    filter=serv.filtrare_tip("b");
    assert(filter.size()==4);

}


void test_filtrare2(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a1",5,"b","c");
    serv.add("a2",4,"b","b");
    auto materii = serv.sort_nr_ore();
    assert(materii.size()==2);
    assert(materii[0].get_nr_ore()==4);
    assert(materii[1].get_nr_ore()==5);
    materii = serv.sort_denumire();
    assert(materii[0].get_denumire()=="a1");
    assert(materii[1].get_denumire()=="a2");
    serv.add("a3",4,"b","d");
    serv.add("a4",4,"a","b");
    materii = serv.sort_cd_tip();
    assert(materii[0].get_cadru_didactic()=="b");
    assert(materii[0].get_tip()=="a");
    assert(materii[1].get_cadru_didactic()=="b");
    assert(materii[1].get_tip()=="b");
    assert(materii[2].get_cadru_didactic()=="c");
    assert(materii[2].get_tip()=="b");
    assert(materii[3].get_cadru_didactic()=="d");
    assert(materii[3].get_tip()=="b");
}

void test_contract_service(){
    RepoDiscipline rep;
    RepoContract c;
    Validator val;
    ServiceDiscipline ser{rep,val,c};
    // Disciplina d{"a",1,"a","a"};
    ser.emptyContract();
    ser.add("a1",1,"a","a");
    ser.add("a2",1,"a","a");
    ser.add("a3",1,"a","a");
    assert(ser.add_to_contract("a1")==0);
    assert(ser.add_to_contract("a5")==-1);
    assert(ser.get_contractsize()==1);
    assert(ser.getall_contract().size()==1);
    assert(ser.add_to_contract("a2")==0);
    ser.generateContract(2);
    assert(ser.get_contractsize()==2);

}

void test_map(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a1",5,"b","c");
    serv.add("a2",4,"b","c");
    serv.get_raport("c");
    DTO d;
    d.setNr(0);
    assert(d.getNr()==0);
    d.incNr();
    d.setTip("a");
    assert(d.getTip()=="a");

}

void test_export(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",2,"a","a");
    serv.add_to_contract("a");
    serv.export_contract(R"(D:\OOP\lab10\test.html)");
}

void test_undo(){
    RepoDiscipline repo;
    Validator val;
    RepoContract repo_contract;
    ServiceDiscipline serv{repo,val,repo_contract};
    serv.add("a",2,"a","a");
    serv.Undo();
    assert(serv.getall().empty());
    serv.add("a",2,"a","a");
    serv.sterge("a","a");
    serv.Undo();
    assert(!serv.getall().empty());
    //   serv.add("a",2,"a","a");
    Disciplina d{"a",2,"a","a"};
    Disciplina d2{"b",2,"b","b"};
    serv.modifica(d,d2);
    serv.Undo();
    assert(serv.getall()[0].get_denumire()=="a");

}

/*
void test_MyVector(){
    MyVector<Disciplina> tests;
    assert(tests.size()==0);
    Disciplina ver{"1",1,"1","1"};
    tests.push_back(ver);
    MyVector<Disciplina> moved;
    moved.push_back({"2",2,"2","2"});
    moved.push_back({"3",2,"3","3"});
    tests=std::move(moved);
    assert(tests.size()==2);
    tests=std::move(tests);
    tests.erase(0);
    assert(tests.size()==1);
    tests.push_back({"2",2,"3","4"});
    tests.push_back({"4",2,"5","6"});
    MyVector<Disciplina> test2;
    test2.push_back({"4",2,"5","6"});
    assert(tests.size()==3);
    assert(tests.size()==3);

}
*/