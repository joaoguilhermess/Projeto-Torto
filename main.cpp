#include "palavras.h"

#include "util.h"

#define MAX_PONTOS 100
#define MIN_PONTOS 25

int main() {
	system("color f0");

	TPilha palavras = lerPalavras("./dicionarios/verbos.txt");

	std::string digitada = "";

	int nivel = 1;

	int pontos = 0;

	TPilha historico = criarPilha();

	TInfo item;

	while (true) {
		system("cls");

		TInfo sorteada = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

		if (sorteada.palavra == "") {
			std::cout << "Erro: Acabaram as Palavras";
			std::cout << "\n";

			break;
		}

		std::string embaralhada = embaralharPalavra(sorteada.palavra);

		while (true) {
			while (true) {
				system("cls");

				// std::cout << "Projeto Torto";
				// std::cout << "\n";

				std::cout << "Historico:";
				std::cout << "\n";

				imprimirPalavras(historico);

				std::cout << "\n";

				std::cout << "Nivel: " << nivel;
				std::cout << "\n";

				std::cout << "Pontos: " << pontos;
				std::cout << "\n";
				
				std::cout << "\n";

				// std::cout << "Palavra Original: " << sorteada.palavra;
				// std::cout << "\n";

				std::cout << "Embaralhada: " << embaralhada;
				std::cout << "\n";

				std::cout << "\n";

				std::cout << "Palavra: ";

				std::cin >> digitada;

				formatarPalavra(digitada);

				paraMinuscula(digitada);

				if (digitada == ".fechar") {
					break;
				}

				if (!verificarLetras(embaralhada, digitada) || verificarPalavra(historico, digitada)) {
					std::cout << "Erro: Palavra Invalida";
					std::cout << "\n";
				} else {
					break;
				}
			}

			if (digitada == sorteada.palavra) {
				pontos += MAX_PONTOS;

				nivel += 1;

				break;
			} else if (verificarPalavra(palavras, digitada)) {
				pontos += inteiroAleatorio(MIN_PONTOS, MAX_PONTOS);

				item.palavra = digitada;

				adicionarItem(historico, item);				
			} else if (digitada == ".fechar") {
				break;
			}
		}

		while (!pilhaVazia(historico)) {
			removerItem(historico);
		}

		if (digitada == ".fechar") {
			break;
		}
	}

	return 0;
}