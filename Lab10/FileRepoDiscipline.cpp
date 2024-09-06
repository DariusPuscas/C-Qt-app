#include "FileRepoDiscipline.h"
#include <fstream>
#include <cassert>

void FileRepoDiscipline::load_from_file() {
    std::ifstream in(file_name);
    if(!in.is_open()){
        throw RepoException("NU s-a deschis fisierul");
    }

    string denumire,tip,cadru_didactic;
    float nr_ore;
    while (in>>denumire>>nr_ore>>tip>>cadru_didactic){
        Disciplina d{denumire,nr_ore,tip,cadru_didactic};
        RepoDiscipline::store(d);
    }
    in.close();
}

void FileRepoDiscipline::save_to_file() {
    std::ofstream out(file_name);
    for(const auto &d:get_all()){
        out<<d.get_denumire()<<std::endl;
        out<<d.get_nr_ore()<<std::endl;
        out<<d.get_tip()<<std::endl;
        out<<d.get_cadru_didactic()<<std::endl;
    }
    out.close();
}

void test_file_repo(){
    try{
        FileRepoDiscipline rep{"cdsc.txt"};
    }catch (RepoException &){
        assert(true);
    }
    std::ofstream out(R"(D:\OOP\lab10\test.txt)",std::ios::trunc);
    out.close();
    //FileRepoDiscipline rep2{R"(D:\OOP\lab6\test.txt)"};
    FileRepoDiscipline rep{R"(D:\OOP\lab10\test.txt)"};
    rep.store(Disciplina{"a",2,"a","a"});

    // FileRepoDiscipline rep2{R"(D:\OOP\lab6\test.txt)"};
    auto d=rep.get_disciplina("a","a");
    assert(d.get_nr_ore()==2);
    rep.sterge_disciplina("a","a");
    assert(rep.gaseste_disciplina("a","a")==-1);
    rep.store(Disciplina{"a",2,"a","a"});
    Disciplina d1=rep.get_disciplina("a","a");
    rep.modifica_disciplina(d1,d1);

}