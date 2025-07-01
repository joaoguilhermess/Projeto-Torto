#include "palavras.h"

#include "util.h"

int main2() {
	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

	// imprimirPalavras(palavras);

	for (int i = 0; i < 10; i++) {
		TInfo item = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

		std::cout << "Palavra: " << item.palavra;
		std::cout << "\n";

		// item.palavra = "amar";

		// std::cout << "Verificar: " << (verificarPalavra(palavras, item) ? "Encontrada" : "Não Encontrada");
		// std::cout << "\n";

		embaralharPalavra(item);

		std::cout << "Palavra: " << item.palavra;
		std::cout << "\n";
	}

	return 0;
}

int main() {
	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

	for (int i = 0; i < 10; i++) {
		TInfo item = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

		std::cout << "Palavra: " << item.palavra;
		std::cout << "\n";
	}

	return 0;
}