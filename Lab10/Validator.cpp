#include "Validator.h"
#include <cassert>

void Validator::validare_denumire(const std::string &denumire) {
    if (denumire.empty())
        throw RepoException("Denumire invalida\n");
}

void Validator::validare_ore(float ore) {
    if(ore<0)
        throw RepoException("Ora invalida\n");
}

void Validator::validare_tip(const std::string &tip) {
    if(tip.empty())
        throw RepoException("Tip invalid\n");
}

void Validator::validare_cd(const std::string &cd) {
    if(cd.empty())
        throw RepoException("Cadru didactic invalid\n");
}

void Validator::validare_disciplina(const Disciplina &d) {
    const string& denumire = d.get_denumire();
    float ore = d.get_nr_ore();
    const string& tip = d.get_tip();
    const string& cd = d.get_cadru_didactic();
    string execeptii;

    try{
        validare_denumire(denumire);
    }catch(RepoException &ve) {
        execeptii += ve.get_mesaj();
    }

    try{
        validare_ore(ore);
    }catch(RepoException &ve) {
        execeptii += ve.get_mesaj();
    }

    try{
        validare_tip(tip);
    }catch(RepoException &ve) {
        execeptii += ve.get_mesaj();
    }

    try{
        validare_cd(cd);
    }catch(RepoException &ve) {
        execeptii += ve.get_mesaj();
    }

    if (!execeptii.empty())
        throw RepoException(execeptii);

}
void test_validator(){
    Validator val;
    Disciplina d{};
    try{
        val.validare_disciplina(d);
    }catch (RepoException & val){
        assert(true);
        assert(val.get_mesaj()=="Denumire invalida\nOra invalida\nTip invalid\nCadru didactic invalid\n");
    }
}
