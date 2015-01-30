#ifndef FRAZIONE_CPP
#define FRAZIONE_CPP

#include <algorithm>
#include "Frazione.hpp"

unsigned int Frazione::mcm(unsigned int a, unsigned int b) {
	return a / MCD(a, b) * b;
}

unsigned int Frazione::MCD(unsigned int a, unsigned int b) {
	while(b) b ^= a ^= b ^= a %= b;
	return a;
}

Frazione::Frazione() {}

Frazione::Frazione(const int &numeratore, const int &denominatore = 1) {
	if(denominatore == 0)
		throw std::invalid_argument("Il denominatore non puo' essere 0!");
	this->num = numeratore;
	this->den = denominatore;
	if(this->den < 0) {
        this->num *= -1;
        this->den *= -1;
	}
	this->semplifica();
}

Frazione::Frazione(const Frazione &altra) {
	this->num = altra.num;
	this->den = altra.den;
}

Frazione::~Frazione() {}

void Frazione::set_num(int n) {
	this->num = n;
}

void Frazione::set_den(int d) {
	this->den = d;
}

int Frazione::get_num() const {
	return this->num;
}

int Frazione::get_den() const {
	return this->den;
}

#endif //FRAZIONE_CPP
