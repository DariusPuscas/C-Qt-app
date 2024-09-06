#include <QApplication>
#include <QPushButton>
#include "GUI.h"

using namespace std;

void test_all(){
    test_get_set();
    test_add();
    test_repo();
    test_cauta_sterge();
    test_sterge();
    test_modifica();
    test_serviceup();
    test_filtrare1();
    test_filtrare2();
    test_validator();
    test_add_contract();
    test_generare();
    test_contract_service();
    test_map();
    test_export();
    test_undo();
    test_file_repo();
    test_labrepo();

}


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    test_all();

    FileRepoDiscipline file_repo{R"(D:\OOP\lab10\Discipline.txt)"};
    Validator val;
    RepoContract rep;
    ServiceDiscipline serv{file_repo,val,rep};

    GUI gui{serv};

    gui.show();

    return QApplication::exec();
}
