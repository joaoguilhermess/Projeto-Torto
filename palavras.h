#ifndef PILHA_PALAVRAS
	#define PILHA_PALAVRAS

	#include <iostream>
	#include <fstream>

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

	void adicionarItem(TPilha& pilha);

	TInfo pegarItem(TPilha& pilha);

	TInfo pegarItem(TPilha& pilha, int index);

	void removerItem(TPilha& pilha);

	void deletarPilha(TPilha& pilha);

	TPilha lerPalavras(std::string caminho);

	void imprimirPalavras(TPilha& pilha);
#endif