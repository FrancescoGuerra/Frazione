#ifndef FRAZIONE_HPP
#define FRAZIONE_HPP

#include "Frazione.cpp"

class Frazione {
	private:
		int num, den;
		void semplifica();
	public:
		static unsigned int mcm(unsigned int a, unsigned int b);
		static unsigned int MCD(unsigned int a, unsigned int b);

		Frazione();
		Frazione(const int &numeratore, const int &denominatore);
		Frazione(const Frazione &altra);
		~Frazione();

		void set_num(int n);
		void set_den(int d);
		int get_num() const;
		int get_den() const;
};

#endif //FRAZIONE_HPP