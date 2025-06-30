#include "palavras.h"
#include <random>

std::random_device device;
std::mt19937 seed(device());
std::uniform_real_distribution<> generate(0.0, 1.0);

int inteiroAleatorio(int min, int max) {
	return (max - min) * generate(seed) + min;
}

void embaralharPalavra(TInfo& item) {
	for (int i = 0; i < item.palavra.length(); i++) {
		int index = inteiroAleatorio(i, item.palavra.length());

		item.palavra = item.palavra.substr(index, 1) + item.palavra.substr(0, index) + item.palavra.substr(index + 1);
	}
}

int main() {
	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

	// imprimirPalavras(palavras);

	for (int i = 0; i < 25; i++) {
		TInfo item = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade));

		embaralharPalavra(item);

		std::cout << "Palavra: " << item.palavra;
		std::cout << "\n";
	}

	return 0;
}