#pragma once
#include <string>
#include <exception>
using std::string;

class RepoException{
private:
    string mesaj;
public:
    explicit RepoException(string m):mesaj{std::move(m)}{

    }
    string get_mesaj(){
        return mesaj;
    }
};
