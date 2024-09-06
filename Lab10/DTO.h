#pragma once

#include <string>

using std::string;

class DTO
{
private:
    string tip;
    int nr = 0;
public:
    string getTip();
    [[nodiscard]] int getNr() const noexcept;
    void setTip(string newType);
    void setNr(int newNr) noexcept;
    void incNr() noexcept;
};
