#include "util.h"

#include "iostream"

// std::random_device device;
// std::mt19937 seed(device());

std::mt19937 seed(getAgora());
std::uniform_real_distribution<> generate(0.0, 1.0);

int inteiroAleatorio(int min, int max) {
	return (max - min) * generate(seed) + min;
}

void paraMaiuscula(std::string& palavra) {
	int tamanho = palavra.length();

	for (int i = 0; i < tamanho; i++) {
		palavra[i] = std::toupper(palavra[i]);
	}
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

	for (int b = 0; b < tamanho2; b++) {
		bool letra = false;

		for (int a = 0; a < tamanho; a++) {
			if (palavra2[b] == palavra[a]) {
				letra = true;

				break;
			}
		}

		if (letra == false) {
			return false;
		}
	}

	return true;
}

std::string embaralharPalavra(std::string palavra) {
	int tamanho = palavra.length();

	for (int i = 0; i < tamanho - 1; i++) {
		int index = inteiroAleatorio(i + 1, tamanho);

		palavra = palavra.substr(index, 1) + palavra.substr(0, index) + palavra.substr(index + 1);
	}

	return palavra;
}

long long getAgora() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

std::string formatarNumero(int numero, int tamanho) {
	std::string resultado = std::to_string(numero);

	while (resultado.length() < tamanho) {
		resultado = "0" + resultado;
	}

	return resultado;
}

std::string formatarTempo(long long tempo) {
	int S = 1000;
	int M = S * 60;
	int H = M * 60;

	int h = tempo / H;

	tempo -= (h * H);

	int m = tempo / M;
	
	tempo -= (m * M);

	int s = tempo / S;

	return formatarNumero(h, 2) + ":" + formatarNumero(m, 2) + ":" + formatarNumero(s, 2);
}