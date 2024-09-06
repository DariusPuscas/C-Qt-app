#pragma once

#include <vector>
#include "Disciplina.h"
#include "Observer.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <chrono>

using std::vector;
using std::shuffle;

class RepoContract: public Observable{

private:
    vector<Disciplina> contract;

public:
    /*
     * goleste contractul
     */
    void empty_contract();
    /*
     * adauga o disciplina in cotract
     * param:Disciplina de adaugat
     */
    void add_contract(const Disciplina& d);
    /*
     * genereaza contract cu materii aleatorii
     * param:
     * nr_materii:numarul de materii ce trebuie generat
     * type param:int
     * repomemo:disciplinele din memorie
     * type param:vector<Disciplina>
     */
    void generare_contract(int nr_materii,const vector<Disciplina>& repomemo);
    /*
     *cauta o disciplina in contract
     * param: denumire , cd
     * type param:string
     * return: pozitia pe care se afla in contract
     * type return: long long int
     */
    long long int cauta(const string& denumire, const string & cd);

    /*
     * returneaza contractul
     */
    const vector<Disciplina>& get_contract();

    /*
     * export contract
     */
    string export_contract(const string &name_file);


};

void test_add_contract();
void test_generare();


