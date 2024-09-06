#pragma once
#include "RepoAbstract.h"
#include "Exception.h"
#include <map>

using std::map;

class RepoLab :public RepoAbstract{
private:
    double prob=0.5;
    map<int,Disciplina> elems;
    void get_prob() const;

public:
    RepoLab()=default;

    explicit RepoLab(float prob);

    void store(const Disciplina& d) override ;

    void sterge_disciplina(const string& denumire, const string& cd) override ;

    void modifica_disciplina(const Disciplina& D, const Disciplina& d) override ;

    const vector<Disciplina>& get_all() override ;


    long long int gaseste_disciplina(const string &denumire, const string & cadru_didiactic) override;
    const Disciplina& get_disciplina(const string &denumire, const string& cd) override;
    map<string,DTO> generare_raport() override;
};


void test_labrepo();
