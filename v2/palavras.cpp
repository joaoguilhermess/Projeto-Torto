#include "palavras.h"

TPilha criarPilha() {
	TPilha pilha;

	pilha.primeiro = new TNodo();

	pilha.primeiro->proximo = NULL;

	pilha.ultimo = pilha.primeiro;

	pilha.quantidade = 0;

	return pilha;
}

bool pilhaVazia(TPilha& pilha) {
	if (pilha.primeiro == pilha.ultimo) {
		// std::cout << "Erro: Pilha Vazia";
		// std::cout << "\n";

		return true;
	}

	return false;
}

void adicionarItem(TPilha& pilha, TInfo item) {
	TNodo* nodo = new TNodo();

	nodo->item = item;

	nodo->proximo = pilha.primeiro->proximo;

	pilha.primeiro->proximo = nodo;

	if (nodo->proximo == NULL) {
		pilha.ultimo = nodo;
	}

	pilha.quantidade += 1;
}

TInfo pegarItem(TPilha& pilha) {
	if (!pilhaVazia(pilha)) {
		return pilha.primeiro->proximo->item;
	}

	TInfo item;

	item.palavra = "";
	item.significado = "";

	return item;
}

TInfo pegarItem(TPilha& pilha, int index, bool remover) {
	TPilha pilha2 = criarPilha();

	TInfo item;

	item.palavra = "";
	item.significado = "";

	if (index >= 0 && index < pilha.quantidade) {
		while (pilha.quantidade - 1 > index) {
			adicionarItem(pilha2, pegarItem(pilha));

			removerItem(pilha);
		}

		item = pegarItem(pilha);

		if (remover) {
			removerItem(pilha);
		}

		while (!pilhaVazia(pilha2)) {
			adicionarItem(pilha, pegarItem(pilha2));

			removerItem(pilha2);
		}
	}

	deletarPilha(pilha2);

	return item;
}

TInfo pegarItem(TPilha& pilha, std::string palavra) {
	TPilha pilha2 = criarPilha();

	TInfo item;

	item.palavra = "";
	item.significado = "";

	while (!pilhaVazia(pilha)) {
		item = pegarItem(pilha);

		if (item.palavra == palavra) {
			break;
		}

		adicionarItem(pilha2, item);

		removerItem(pilha);
	}

	while (!pilhaVazia(pilha2)) {
		adicionarItem(pilha, pegarItem(pilha2));

		removerItem(pilha2);
	}

	deletarPilha(pilha2);

	return item;
}

void removerItem(TPilha& pilha) {
	if (!pilhaVazia(pilha)) {
		TNodo* nodo = pilha.primeiro->proximo;

		pilha.primeiro->proximo = nodo->proximo;

		if (pilha.primeiro->proximo == NULL) {
			pilha.ultimo = pilha.primeiro;
		}

		free(nodo);

		pilha.quantidade -= 1;
	}
}

void deletarPilha(TPilha& pilha) {
	while (!pilhaVazia(pilha)) {
		removerItem(pilha);
	}

	delete pilha.primeiro;
}

TPilha lerPalavras(std::string caminho, int maximoLetras) {
	TPilha pilha = criarPilha();

	std::ifstream arquivo;

	arquivo.open(caminho, std::ios::in);

	if (!arquivo.is_open()) {
		std::cout << "Erro: Arquivo Inacessivel";
		std::cout << "\n";

		return pilha;
	}

	TInfo item;

	while (true) {
		if (!getline(arquivo, item.palavra)) break;
		if (!getline(arquivo, item.significado)) break;

		// if (pilha.quantidade < 3) adicionarItem(pilha, item);

		paraMaiuscula(item.palavra);

		if (maximoLetras != 0 && item.palavra.length() > maximoLetras) continue; 
		if (item.palavra.length() < 3) continue;

		adicionarItem(pilha, item);
	}

	arquivo.close();

	return pilha;
}

void imprimirPalavras(TPilha& pilha) {
	TPilha pilha2 = criarPilha();

	TInfo item;

	while (!pilhaVazia(pilha)) {
		item = pegarItem(pilha);

		adicionarItem(pilha2, item);

		removerItem(pilha);

		std::cout << item.palavra;
		std::cout << "\n";
	}

	deletarPilha(pilha);

	pilha = pilha2;

	std::cout << "Quantidade: " << pilha.quantidade;
	std::cout << "\n";
}

bool verificarPalavra(TPilha& pilha, std::string palavra) {
	TPilha pilha2 = criarPilha();

	TInfo item;

	bool resultado = false;

	while (!pilhaVazia(pilha)) {
		item = pegarItem(pilha);

		if (item.palavra == palavra) {
			resultado = true;

			break;
		}

		adicionarItem(pilha2, item);

		removerItem(pilha);
	}

	while (!pilhaVazia(pilha2)) {
		adicionarItem(pilha, pegarItem(pilha2));

		removerItem(pilha2);
	}

	deletarPilha(pilha2);

	return resultado;
}