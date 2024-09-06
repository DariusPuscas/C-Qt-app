#include "Disciplina.h"
#include <cassert>

Disciplina::Disciplina() {
    this->denumire="";
    this->nr_ore=-1;
    this->tip="";
    this->cadru_didactic="";
}

Disciplina::~Disciplina() = default;

string Disciplina::get_denumire() const {
    return denumire;
}

float Disciplina::get_nr_ore() const {
    return nr_ore;
}

string Disciplina::get_tip() const {
    return tip;
}

string Disciplina::get_cadru_didactic() const {
    return cadru_didactic;
}

void Disciplina::set_denumire(const std::string &denumire_noua) {
    denumire = denumire_noua;
}

void Disciplina::set_nr_ore(float ora_noua) {
    nr_ore = ora_noua;
}

void Disciplina::set_tip(const std::string& tip_nou) {
    tip = tip_nou;
}

void Disciplina::set_cd(const std::string &cadru_didactic_nou) {
    cadru_didactic = cadru_didactic_nou;
}

void test_get_set(){
    Disciplina d{"ASC",4,"x","y"};
    assert(d.get_denumire()=="ASC");
    assert(d.get_nr_ore()==4);
    assert(d.get_tip()=="x");
    assert(d.get_cadru_didactic()=="y");
    d.set_denumire("FP");
    d.set_nr_ore(12);
    d.set_tip("z");
    d.set_cd("ap");
    assert(d.get_denumire()=="FP");
    assert(d.get_nr_ore()==12);
    assert(d.get_tip()=="z");
    assert(d.get_cadru_didactic()=="ap");
    Disciplina d2=Disciplina();
    assert(d2.get_denumire().empty());
    assert(d2.get_nr_ore()==-1);
    assert(d2.get_tip().empty());
    assert(d2.get_cadru_didactic().empty());

}