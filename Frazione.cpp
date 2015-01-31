#ifndef FRAZIONE_CPP
#define FRAZIONE_CPP

#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
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

std::istream &operator>>(std::istream& is, Frazione &fraz) {
	std::string s;
	is >> s;
	int index = s.find_first_of('/');
	if(index != string::npos) {
		#if __cplusplus >= 201103L
		fraz.set_num(stoi(s.substr(0, index)));
		fraz.set_den(stoi(s.substr(index + 1)));
		#else
		fraz.set_num(::atoi(s.substr(0, index).c_str()));
		fraz.set_den(::atoi(s.substr(index + 1).c_str()));
		#endif
	} else if(s.find_first_of('.') != string::npos) {
		#if __cplusplus >= 201103L
		fraz = stold(s);
		#else
		fraz = ::strtold(s.c_str(), NULL);
		#endif
	} else {
		#if __cplusplus >= 201103L
		fraz.set_num(stoi(s));
		#else
		fraz.set_num(::atoi(s.c_str()));
		#endif
		fraz.set_den(1);
	}
	return is;
}

Frazione &Frazione::operator=(const Frazione &altra) {
	if(this != &altra) {
		this->num = altra.num;
		this->den = altra.den;
	}
	return *this;
}

Frazione &Frazione::operator=(const int &n) {
	return (*this = Frazione(n, 1));
}

Frazione &Frazione::operator=(const long double &d) {
	return (*this = Frazione(d));
}

Frazione &Frazione::operator+=(const Frazione &altra) {
	int old_den = this->den;
	this->den = mcm(this->den, altra.den);
	this->num = (this->den / old_den  * this->num) +
				(this->den / altra.den * altra.num);
	return *this;
}

Frazione &Frazione::operator+=(const int &n) {
	return (*this += Frazione(n, 1));
}

Frazione &Frazione::operator-=(const Frazione &altra) {
	return (*this += -altra);
}

Frazione &Frazione::operator-=(const int &n) {
	return (*this -= Frazione(n, 1));
}

Frazione &Frazione::operator*=(const Frazione &altra) {
	this->num *= altra.num;
	this->den *= altra.den;
	this->semplifica();
	return *this;
}

Frazione &Frazione::operator*=(const int &n) {
	return (*this *= Frazione(n, 1));
}

Frazione &Frazione::operator/=(const Frazione &altra) {
	return (*this *= Frazione(altra.den, altra.num));
}

Frazione &Frazione::operator/=(const int &n) {
	return (*this /= Frazione(n, 1));
}

Frazione &Frazione::operator^=(const int &pow) {
	if(pow == 0) {
		this->num = 1;
		this->den = 1;
	} else {
		int p = pow, n = this->num, d = this->den;
		if(pow < 0) {
			p = -p;
			this->num = d;
			this->den = n;
		}
		for(int i = 1; i < p; i++) {
			this->num *= n;
			this->den *= d;
		}
	}
	return *this;
}

void Frazione::semplifica() {
	int mcd = MCD(this->num, this->den);
	this->num /= mcd;
	this->den /= mcd;
}

#endif //FRAZIONE_CPP
