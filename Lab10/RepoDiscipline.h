#pragma once
#include <vector>
#include "Disciplina.h"
#include "RepoAbstract.h"
#include "Exception.h"
#include <algorithm>
//#include "MyVector.h"
#include "DTO.h"
#include <map>
using std::vector;
using std::find_if;
using std::distance;
using std::map;

class RepoDiscipline:public RepoAbstract{

private:
    vector<Disciplina> discipline;

public:

    RepoDiscipline() = default;

    RepoDiscipline(const RepoDiscipline &ot) = delete;

    ~RepoDiscipline() override =default;

    /*
     * adauga o disciplina in lista de discipline
     */
    void store(const Disciplina &disc) override;

    /*
     * returneaza lista de discipline
     */
    const vector<Disciplina> &get_all() override;

    /*
     * gaseste o disciplina
     * param denumirea si cadrul didactic al disciplinei
     * return poz daca se afla in lista
     *             -1 altfel
     */
    long long int gaseste_disciplina(const string &denumire, const string & cadru_didiactic) override;

    /*
     * returneaza o disciplina
     * param: denumirea si cadrul didactic al disciplinei
     * return: disciplina daca exita
     * throws:RepoException daca disciplina nu exista
     * type param:string
     * type return:Disciplina
     */
    const Disciplina& get_disciplina(const string &denumire, const string& cd) override;

    /*
     * sterge o disciplina
     * param: numele si prof.
     * return: lista modificata
     */
    void sterge_disciplina( const string &denumire,const string &cadru_didactic) override;

    /*
     * modifica o disciplina
     * param: disciplina de modificat
     */
    void modifica_disciplina(const Disciplina &D,const Disciplina&d) override;

    map<string,DTO> generare_raport() override;

};

void test_repo();
void test_cauta_sterge();
void test_modifica();


