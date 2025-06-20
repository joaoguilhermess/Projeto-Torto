#include "palavras.h"
#include <random>

std::random_device device;
std::mt19937 seed(device());
std::uniform_real_distribution<> generate(0.0, 1.0);

int inteiroAleatorio(int min, int max) {
	return (max - min) * generate(seed) + min;
}

int main() {
	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

	// imprimirPalavras(palavras);

	for (int i = 0; i < 25; i++) {
		TInfo item = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade));

		std::cout << "Palavra: " << item.palavra;
		std::cout << "\n";
	}

	return 0;
}