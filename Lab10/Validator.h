#pragma once

#include <string>
#include "Exception.h"
#include "Disciplina.h"

using std::string;

class Validator {

private:

    static void validare_denumire (const string & denumire);

    static void validare_ore(float ore);

    static void validare_tip(const string& tip);

    static void validare_cd(const string & cd);


public:

    void validare_disciplina(const Disciplina& d);

};

void test_validator();

