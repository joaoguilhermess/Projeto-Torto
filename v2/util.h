#ifndef UTIL
	#define UTIL

	#include <chrono>
	#include <random>
	#include <cctype>
	#include <string>

	int inteiroAleatorio(int min, int max);

	void paraMaiuscula(std::string& palavra);

	void paraMinuscula(std::string& palavra);

	void formatarPalavra(std::string& palavra);

	bool verificarLetras(std::string palavra, std::string palavra2);

	std::string embaralharPalavra(std::string palavra);

	long long getAgora();

	std::string formatarNumero(int numero, int tamanho);

	std::string formatarTempo(long long tempo);
#endif