#include "RepoLab.h"
#include <random>
#include <cassert>

RepoLab::RepoLab(float prob) {
    this->prob=prob;
    elems.clear();
}

void RepoLab::get_prob() const {
    auto prb=int(prob*10);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    int nr = dis(gen);

    if(nr<=prb) //daca nr e mai mic decat prob de a arunca exceptie
        return;
    throw RepoException("Ghinion!\n");
}

void RepoLab::store(const Disciplina &d) {
    get_prob();
    elems.insert(std::make_pair(elems.size(),d));
}

long long int RepoLab::gaseste_disciplina(const string &denumire, const string &cd){
    for(auto& it : elems)
        if(it.second.get_cadru_didactic()==cd && it.second.get_denumire()==denumire)
            return it.first;
}


void RepoLab::sterge_disciplina(const string &denumire, const string &cd) {
    get_prob();
    auto poz = gaseste_disciplina(denumire,cd);
    elems.erase(int(poz));

    map<int,Disciplina> aux;
    aux.clear();
    for(auto& it : elems){
        aux.insert(std::make_pair(aux.size(),it.second));
    }
    elems=aux;
}

void RepoLab::modifica_disciplina(const Disciplina &D, const Disciplina &d) {
    get_prob();
    const string& denumire=d.get_denumire();
    const string& cd=d.get_cadru_didactic();

    auto poz = gaseste_disciplina(denumire,cd);
    poz=int(poz);

    for(auto& it : elems){
        if(it.first==poz){
            elems.erase(int(poz));
            elems.insert(std::make_pair(poz,D));
            break;
        }
    }
}

vector<Disciplina>d;
const vector<Disciplina> &RepoLab::get_all() {
    get_prob();
    for(auto& it:elems){
        d.push_back(it.second);
    }
    return d;
}

Disciplina dnull;
const Disciplina &RepoLab::get_disciplina(const string &denumire, const string &cd) {
    return dnull;
}

map<string,DTO> mapavida ;
map<string, DTO> RepoLab::generare_raport() {
    return mapavida;
}

void test_labrepo(){
    RepoLab rep{0};
    Disciplina d1{"a",2,"a","a"};
    try{
        rep.store(d1);
    }catch (RepoException& e){}
    try{
        rep.get_all();
    }catch (RepoException& e){}
    try{
        rep.sterge_disciplina(d1.get_denumire(),d1.get_cadru_didactic());
    }catch (RepoException&e){}

    RepoLab rep2{1};
    rep2.store(d1);
    rep2.store(d1);
    rep2.modifica_disciplina(d1,d1);
    rep2.sterge_disciplina(d1.get_denumire(),d1.get_cadru_didactic());
    rep2.get_all();
    d1=rep2.get_disciplina(d1.get_denumire(),d1.get_cadru_didactic());
    assert(d1.get_denumire()!="a");
    map<string ,DTO>m1=rep2.generare_raport();



}