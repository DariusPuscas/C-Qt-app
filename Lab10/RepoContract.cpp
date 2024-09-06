#include "RepoContract.h"
#include "Exception.h"

using std::ifstream;
using std::ofstream;

long long int RepoContract::cauta(const string &denumire, const string& cadru_didactic){
    auto it = find_if(contract.begin(),contract.end(),[denumire,cadru_didactic](const Disciplina& d){
        if(d.get_denumire()==denumire && d.get_cadru_didactic()==cadru_didactic) return true; return false;});
    if (it!=contract.end()) {
        auto poz=distance(contract.begin(),it);
        return poz;
    }
    return -1;
}

void RepoContract::empty_contract() {
    contract.clear();
}

void RepoContract::add_contract(const Disciplina &d) {

    const string& denumire = d.get_denumire();
    const string& cd = d.get_cadru_didactic();
    if(cauta(denumire,cd)!=-1)
        throw RepoException("Disciplina exista deja");
    else
        contract.push_back(d);
    notify();

}

void RepoContract::generare_contract(int nr_materii, const vector<Disciplina> &repomemo) {

    empty_contract();
    auto c = repomemo;
    auto seed=std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(c.begin(),c.end(),std::default_random_engine (seed));
    while(nr_materii && !c.empty()){
        add_contract(c.back());
        c.pop_back();
        nr_materii--;
    }
    notify();
}

const vector<Disciplina> &RepoContract::get_contract() {
    return contract;
}

string RepoContract::export_contract(const std::string &name_file) {

    std::ofstream fout(name_file);
    fout<<"<html>\n"
          "<body>\n"
          "<head>\n"
          "    <h3 style=\" font-family: 'Caviar Dreams',serif; color:mediumpurple; \">Discipline contractate</h3>\n"
          "    </head>\n"
          "<style>\n"
          "    p {\n"
          "        color: #D7BDE2 ;\n"
          "        background-color: #A9CCE3 ;\n"
          "        border: 1px solid black; }\n"
          "    table,th,td{\n"
          "        border: 1px solid black;\n"
          "    }\n"
          "    th{\n"
          "        color: darkviolet;\n"
          "    }\n"
          "    body{\n"
          "        background-color: #CACFD2;\n"
          "    }\n"
          "</style>\n";
    fout<<"<table>\n"
          "\n"
          "        <th>Denumire</th>\n"
          "        <th>Ore</th>\n"
          "        <th>Tip</th>\n"
          "        <th>Cadru didactic</th>";
    for(const Disciplina& d:get_contract())
    {
        fout<<"<tr>\n";
        fout<<"<th>"<<d.get_denumire()<<"</th>\n"
            <<"<th>"<<d.get_nr_ore()<<"</th>\n"
            <<"<th>"<<d.get_tip()<<"</th>\n"
            <<"<th>\n"<<d.get_cadru_didactic()<<"</th>\n"
            <<"</tr>\n";


    }
    fout<<"</table>\n"
          "\n"
          "\n"
          "</body>\n"
          "</html>";
    return name_file;
}

void test_add_contract(){
    RepoContract repo{};
    repo.empty_contract();
    const Disciplina& d ={"a",3,"a","a"};
    repo.add_contract(d);
    try{
        repo.add_contract(d);
    }catch(RepoException & ve){
        assert(ve.get_mesaj()=="Disciplina exista deja");
    }
    vector<Disciplina> D = repo.get_contract();
    assert(D.size()==1);
}

void test_generare(){
    RepoContract repo;
    RepoContract repo2;
    const Disciplina& d1 ={"a1",3,"a","a"};
    const Disciplina& d2 ={"a2",3,"a","a"};
    const Disciplina& d3 ={"a3",3,"a","a"};
    const Disciplina& d4 ={"a4",3,"a","a"};
    repo.add_contract(d1);
    repo.add_contract(d2);
    repo.add_contract(d3);
    repo.add_contract(d4);
    repo2.generare_contract(3,repo.get_contract());
    assert(repo2.get_contract().size()==3);
}