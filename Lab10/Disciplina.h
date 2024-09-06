#pragma once
#include <iostream>
#include <string>
#include <utility>
using std::string;
using std::cout;

class Disciplina {

private:
    string denumire;
    float nr_ore;
    string tip;
    string cadru_didactic;

public:
    /*
     * returneaza denumirea unei discipline
     */
    [[nodiscard]] string get_denumire() const;
    /*
     * returneaza nr de ore al unei discipline
     */
    [[nodiscard]] float  get_nr_ore() const;
    /*
     * returneaza tipul unei discipline
     */
    [[nodiscard]] string get_tip() const;
    /*
     * returneaza cadrul didactic al unei discipline
     */
    [[nodiscard]] string get_cadru_didactic() const;

    /*
     * constructor
     */
    Disciplina(string denumire,float nr_ore, string tip, string cadru_didactic):denumire{std::move(denumire)},nr_ore{nr_ore},
                                                                                tip{std::move(tip)},cadru_didactic{std::move(cadru_didactic)}{

    }
    Disciplina(const Disciplina & other)= default;
    Disciplina();

    ~Disciplina();

    /*
     * seteaza denumirea unei discipline
     */
    void set_denumire(const string &denumire_noua);

    /*
     * seteaza numarul de ore al unei entitati
     */
    void set_nr_ore(float ora_noua);

    /*
     * seteaza tipul unei discipline
     */
    void set_tip(const string &tip_nou);

    /*
     * seteaza cadrul didactic al unei discipline
     */
    void set_cd(const string &cadru_didactic_nou);

};

void test_get_set();

