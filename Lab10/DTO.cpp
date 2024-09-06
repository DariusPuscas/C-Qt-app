//#include <string>
#include <utility>

#include "DTO.h"

using std::string;

string DTO::getTip() { return tip; }

int DTO::getNr() const noexcept{ return nr; }

void DTO::setTip(string newType) { tip = std::move(newType); }

void DTO::setNr(int newNr) noexcept{ nr = newNr; }

void DTO::incNr() noexcept{nr++;}