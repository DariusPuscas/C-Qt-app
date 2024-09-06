#pragma once
#include <string>
#include <utility>
#include "RepoDiscipline.h"

using std::string;

class FileRepoDiscipline: public RepoDiscipline{
private:
    string file_name;
    void load_from_file();
    void save_to_file();
public:
    [[maybe_unused]] explicit FileRepoDiscipline(string file_name):RepoDiscipline(),file_name{std::move(file_name)}{
        load_from_file();
    }
    void store(const Disciplina& d) override{
        RepoDiscipline::store(d);
        save_to_file();
    }
    void sterge_disciplina(const string& denumire, const string& cd) override{
        RepoDiscipline::sterge_disciplina(denumire,cd);
        save_to_file();
    }
    void modifica_disciplina(const Disciplina& D, const Disciplina& d) override{
        RepoDiscipline::modifica_disciplina(D,d);
        save_to_file();
    }

};

void test_file_repo();

