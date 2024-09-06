#include "RepoDiscipline.h"
#include <cassert>


void RepoDiscipline::store(const Disciplina &disc) {
    for(const auto & i : discipline){
        if(i.get_denumire()==disc.get_denumire() && i.get_cadru_didactic()==disc.get_cadru_didactic())
            throw RepoException("Disciplina exista deja\n");
    }
    discipline.push_back(disc);
}

const vector<Disciplina> &RepoDiscipline::get_all(){
    return discipline;
}


long long int RepoDiscipline::gaseste_disciplina(const string &denumire, const string& cadru_didactic){
    auto it = find_if(discipline.begin(),discipline.end(),[denumire,cadru_didactic](const Disciplina& d){
        if(d.get_denumire()==denumire && d.get_cadru_didactic()==cadru_didactic) return true; return false;});
    if (it!=discipline.end()) {
        auto poz=distance(discipline.begin(),it);
        return poz;
    }
    return -1;
}

const Disciplina &RepoDiscipline::get_disciplina(const string &denumire, const string &cd) {
    return discipline[gaseste_disciplina(denumire,cd)];
}

void RepoDiscipline::sterge_disciplina(const std::string &denumire, const std::string &cadru_didactic) {

    auto index = gaseste_disciplina(denumire,cadru_didactic);
    if(index!=-1) {
        auto first = discipline.begin();
        discipline.erase( first+index); //va trebui modificat
    }
    else
        throw RepoException("NU exista disciplina\n");
}

void RepoDiscipline::modifica_disciplina(const Disciplina&D,const Disciplina &d) {
    const string & denumire= D.get_denumire();
    const string & prof = D.get_cadru_didactic();
    auto id = gaseste_disciplina(denumire,prof);
    if(id!=-1){
        discipline[id] = d;
    }
    /*else
        throw RepoException("NU exista disciplina\n");*/
}

map<string, DTO> RepoDiscipline::generare_raport() {
    map<string, DTO> raport;
    vector<Disciplina> AllD = discipline;
    for (const auto & i : AllD)
    {
        if (raport.find(i.get_cadru_didactic()) != raport.end())
        {
            raport.at(i.get_cadru_didactic()).incNr();
        }
        else
        {
            DTO raport_nou;
            raport_nou.setNr(1);
            raport_nou.setTip(i.get_cadru_didactic());
            raport.insert({ i.get_cadru_didactic(), raport_nou });
        }
    }
    return raport;

}

void test_repo(){
    RepoDiscipline rep;
    Disciplina d{"ASC",4,"x","y"};
    rep.store(d);
    Disciplina d1 = rep.get_disciplina("ASC","y");
    assert(d1.get_nr_ore()==4);
    auto dicipline = rep.get_all();
    assert(dicipline.size()==1);
    try{
        rep.store(d);
        //   assert(false); //trb facut exceptii
    }catch(RepoException & e){
        assert(true);
        assert(e.get_mesaj()=="Disciplina exista deja\n");

    }
}

void test_cauta_sterge() {
    RepoDiscipline rep;
    Disciplina d{"ASC",4,"x","y"};
    Disciplina d2{"FP",4,"x","y"};
    rep.store(d);
    rep.store(d2);
    rep.sterge_disciplina("ASC","y");
    auto discipline = rep.get_all();
    assert (discipline.size()==1);
    const string& a="ASC";
    const string&b ="y";
    try{
        rep.sterge_disciplina(a,b);
    }catch (RepoException & e){
        assert(e.get_mesaj()=="NU exista disciplina\n");
    }

}

void test_modifica(){
    RepoDiscipline rep;
    Disciplina d{"ASC",4,"x","y"};
    Disciplina d2{"FP",4,"z","t"};
    Disciplina d3{"oop",4,"z","t"};
    rep.store(d);
    rep.modifica_disciplina(d,d2);
    auto discipline = rep.get_all();
    assert(discipline[0].get_denumire()=="FP");
    assert(discipline[0].get_nr_ore()==4);
    assert(discipline[0].get_tip()=="z");
    assert(discipline[0].get_cadru_didactic()=="t");
    /* try{
         rep.modifica_disciplina(d3,d2);
     }catch (RepoException & e){
         assert(e.get_mesaj()=="NU exista disciplina\n");
     }*/
}