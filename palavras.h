#ifndef PILHA_PALAVRAS
	#define PILHA_PALAVRAS

	#include <iostream>
	#include <fstream>

	#include "util.h"

	struct TInfo {
		std::string palavra;
	};

	struct TNodo {
		TInfo item;
		TNodo* proximo;
	};

	struct TPilha {
		TNodo* primeiro;
		TNodo* ultimo;
		int quantidade;
	};

	TPilha criarPilha();

	bool pilhaVazia(TPilha& pilha);

	void adicionarItem(TPilha& pilha, TInfo item);

	TInfo pegarItem(TPilha& pilha);

	TInfo pegarItem(TPilha& pilha, int index, bool remover);

	void removerItem(TPilha& pilha);

	void deletarPilha(TPilha& pilha);

	TPilha lerPalavras(std::string caminho);

	void imprimirPalavras(TPilha& pilha);

	void embaralharPalavra(TInfo& item);

	bool verificarPalavra(TPilha& pilha, TInfo& item);
#endif