#pragma once
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <memory>
#include "Disciplina.h"
#include "RepoDiscipline.h"
#include "RepoContract.h"
#include "Validator.h"
#include "Undo.h"

#include <map>
#include <set>
#include "Observer.h"
using std::map;
using std::set;

using std::vector;
using std::string;
using std::function;
using std::unique_ptr;
using std::sort;
using std::copy_if;

class ServiceDiscipline: public Observable{

private:
    RepoAbstract &repo;
    Validator &val;
    RepoContract &contract;
    vector<unique_ptr<ActiuneUndo>> Actiuni_Undo;

public:
    explicit ServiceDiscipline(RepoAbstract &repo, Validator &val,RepoContract & contract):repo{repo},val{val},contract{contract}{

    }
    ServiceDiscipline(const ServiceDiscipline &ot) = delete;

    /*
     * contract
     */

    /*
     * returneaza toate disciplinele din contract
     */
    const vector<Disciplina> & getall_contract();
    /*
     * returneaza dimensiunea contractului
     */
    int get_contractsize();
    /*
     * adauga o diciplina in contract
     * param: denumire, nr ore,v tip, cadru didactic
     * type_param: string, float, string , string
     */
    int add_to_contract(const string& denumire);
    /*
     * genereaza contract random
     * param:nr de obicete ce trebuie generate
     * type param:int
     */
    void generateContract(int nrSubjects);

    /*
     * goleste contractul
     */
    void emptyContract();
    /*
     * export contract
     */
    void export_contract(const string &filename);

    /*
     * end contract
     */


    void Undo();

    /*
     * adauga in service o disciplina
     * param: denumire, nr ore,v tip, cadru didactic
     * type_param: string, float, string , string
     */
    void add(const string& denumire, float nr_ore, const string &tip,const string &cadru_didactic);

    /*
     * returneaza toate disciplinele din service
     */
    const vector<Disciplina> &getall();

    /*
     * sterge disciplina
     * param denumirea si cadrul didactic
     * tyoe param:: string string
     * return:: lista service cu entitatea stearsa
     */
    void sterge(const string &denumire, const string &cadru_didactic);

    /*
     * modifica disciplina
     * param1: disciplina de moficiat
     * param2: disciplina cu care se modifica
     * type param:: Disciplina
     */
    void modifica(const Disciplina& d,const Disciplina& ot);

    /*
     * filtru general
     * param: bool function
     * return: vector filtrat
     */
    //  vector<Disciplina> filter(const function<bool(const Disciplina &)> &fct);
    /*
     * filtreaza dupa denumire
     */
    vector<Disciplina>filtrare_denumire(const string& denumire);

    /*
     * filtreaza dupa nr ore
     */
    vector<Disciplina> filtrare_ore(float ore);

    /*
    * filtreaza dupa cadru didactic
    */
    vector<Disciplina> filtrare_cd(const string& cd);

    /*
     * filtreaza dupa tip
     */
    vector<Disciplina> filtrare_tip(const string& tip);

    /*
     * sort general
     */
    // vector<Disciplina>sort(bool(*cmp_key)(const Disciplina &,const Disciplina &));
    /*
     * sorteaza dupa ore
     */
    vector<Disciplina> sort_nr_ore();
    /*
     * sorteaza dupa denumire
     */
    vector<Disciplina> sort_denumire();

    /*
     * sorteaza dupa cadru didactic si tip
     */
    vector<Disciplina>sort_cd_tip();

    static bool cmp_ore(const Disciplina& d1, const Disciplina& d2){
        return d1.get_nr_ore()<d2.get_nr_ore();
    }

    static bool cmp_denumire(const Disciplina& d1, const Disciplina& d2){
        return d1.get_denumire()<d2.get_denumire();
    }

    static bool cmp_cd_tip(const Disciplina& d1, const Disciplina& d2){
        if(d1.get_cadru_didactic()<d2.get_cadru_didactic())
            return true;
        if(d1.get_cadru_didactic()>d2.get_cadru_didactic())
            return false;

        return d1.get_tip()<d2.get_tip();
    }

//   map<string,vector<Disciplina>> creeaza();
//   set<string> nr_tip();

    DTO get_raport(const string& cd);

};

void test_add();
void test_sterge();
void test_serviceup();
void test_filtrare1();
void test_filtrare2();
void test_contract_service();
void test_map();
void test_export();
void test_undo();
//void test_MyVector();


