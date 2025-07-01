#ifndef UTIL
	#define UTIL

	#include <chrono>
	#include <random>
	#include <cctype>

	int inteiroAleatorio(int min, int max);

	void paraMinuscula(std::string& palavra);

	void formatarPalavra(std::string& palavra);

	bool verificarLetras(std::string palavra, std::string palavra2);
#endif