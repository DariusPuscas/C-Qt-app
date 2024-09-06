#pragma once
#include "Disciplina.h"
#include "RepoDiscipline.h"

class ActiuneUndo {
public:
    virtual void doUndo()=0;
    virtual ~ActiuneUndo()=default;
};

class Undo_add:public  ActiuneUndo{
    Disciplina disciplina_adaugata;
    RepoAbstract& repo;
public:
    Undo_add(const Disciplina& d, RepoAbstract& repo) :disciplina_adaugata{d},repo{repo}{};
    void doUndo() override{
        repo.sterge_disciplina(disciplina_adaugata.get_denumire(),disciplina_adaugata.get_cadru_didactic());
    }
};

class Undo_sterge:public ActiuneUndo{
    Disciplina disciplina_stearsa;
    RepoAbstract& repo;
public:
    Undo_sterge(const Disciplina& d, RepoAbstract& repo): disciplina_stearsa{d},repo{repo}{};
    void doUndo() override{
        repo.store(disciplina_stearsa);
    }
};

class Undo_modifica:public ActiuneUndo{
    Disciplina disciplina_de_modificat;
    Disciplina disciplina_cu_care_modific;
    RepoAbstract &repo;
public:
    Undo_modifica(const Disciplina& d,const Disciplina&D, RepoAbstract& repo):disciplina_de_modificat{d},disciplina_cu_care_modific{D},repo{repo}{};
    void doUndo() override{
        repo.modifica_disciplina(disciplina_cu_care_modific,disciplina_de_modificat);
    }

};



