#include "util.h"

#include "iostream"

// std::random_device device;
// std::mt19937 seed(device());

std::mt19937 seed(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<> generate(0.0, 1.0);

int inteiroAleatorio(int min, int max) {
	return (max - min) * generate(seed) + min;
}

void paraMinuscula(std::string& palavra) {
	int tamanho = palavra.length();

	for (int i = 0; i < tamanho; i++) {
		palavra[i] = std::tolower(palavra[i]);
	}
}

void formatarPalavra(std::string& palavra) {
	std::string palavra2 = "";

	int tamanho = palavra.length();

	for (int i = 0; i < tamanho; i++) {
		if (palavra[i] == '\n') continue;

		palavra2 += palavra[i];
	}

	palavra = palavra2;
}

bool verificarLetras(std::string palavra, std::string palavra2) {
	int tamanho = palavra.length();
	int tamanho2 = palavra2.length();

	bool resultado = true;

	for (int b = 0; b < tamanho2; b++) {
		bool letra = false;

		for (int a = 0; a < tamanho; a++) {
			if (palavra2[b] == palavra[a]) {
				letra = true;

				break;
			}
		}

		if (letra == false) {
			break;

			resultado = false;
		}
	}

	return resultado;
}