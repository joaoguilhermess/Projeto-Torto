#include "palavras.h"

#include "util.h"

// int main2() {
// 	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

// 	// imprimirPalavras(palavras);

// 	for (int i = 0; i < 10; i++) {
// 		TInfo item = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

// 		std::cout << "Palavra: " << item.palavra;
// 		std::cout << "\n";

// 		// item.palavra = "amar";

// 		// std::cout << "Verificar: " << (verificarPalavra(palavras, item) ? "Encontrada" : "Não Encontrada");
// 		// std::cout << "\n";

// 		embaralharPalavra(item);

// 		std::cout << "Palavra: " << item.palavra;
// 		std::cout << "\n";
// 	}

// 	return 0;
// }

#define MAX_PONTOS 100
#define MIN_PONTOS 25

int main() {
	TPilha palavras = lerPalavras("./dicionarios/portugues.txt");

	std::string digitada = "";

	int nivel = 1;

	int pontos = 0;

	while (true) {
		TInfo sorteada = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

		if (sorteada.palavra == "") {
			std::cout << "Erro: Acabaram as Palavras";
			std::cout << "\n";

			break;
		}

		std::string embaralhada = embaralharPalavra(sorteada.palavra);

		std::cout << "Nivel: " << nivel;
		std::cout << "\n";

		std::cout << "Pontos: " << pontos;
		std::cout << "\n";

		std::cout << "Palavra Original: " << sorteada.palavra;
		std::cout << "\n";

		std::cout << "Embaralhada: " << embaralhada;
		std::cout << "\n";

		while (true) {
			std::cout << "Palavra: ";

			std::cin >> digitada;

			formatarPalavra(digitada);

			paraMinuscula(digitada);

			if (!verificarLetras(embaralhada, digitada)) {
				std::cout << "Erro: Palavra Invalida";
				std::cout << "\n";
			} else {
				break;
			}
		}

		if (digitada == sorteada.palavra) {
			pontos += MAX_PONTOS;

			nivel += 1;

			std::cout << "Parabens!";
			std::cout << "\n";
		} else if (verificarPalavra(palavras, digitada)) {
			pontos += inteiroAleatorio(MIN_PONTOS, MAX_PONTOS);
		} else if (digitada == "") {
			break;
		}
	}

	return 0;
}