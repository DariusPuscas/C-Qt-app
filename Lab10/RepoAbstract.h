#pragma once
#include "Disciplina.h"
#include <vector>
#include <map>
#include "DTO.h"
using std::vector;
using std::map;

class RepoAbstract {
public:

    virtual ~RepoAbstract()=default;

    virtual  void store(const Disciplina& d)=0;
    virtual void sterge_disciplina(const string &denumire, const string& cd)=0;
    virtual void modifica_disciplina(const Disciplina&d, const Disciplina&D)=0;
    virtual const vector<Disciplina>& get_all()=0;

    virtual long long int gaseste_disciplina(const string &denumire, const string & cadru_didiactic)=0;
    virtual const Disciplina& get_disciplina(const string &denumire, const string& cd)=0;
    virtual map<string,DTO> generare_raport()=0;

};


