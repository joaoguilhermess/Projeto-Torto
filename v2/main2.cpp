#include "palavras.h"

#include "util.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define BRANCO 255, 255, 255, 255
#define PRETO 0, 0, 0, 255
#define VERMELHO 50, 0, 0, 255

void desenharRetangulo(SDL_Renderer* tela, float x, float y, float largura, float altura) {
	SDL_FRect retangulo = {x, y, largura, altura};

	SDL_RenderFillRect(tela, &retangulo);
}

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
		SDL_Log("Erro: ", SDL_GetError());

		return 1;
	}

	SDL_Window* janela = SDL_CreateWindow("Projeto Torto", 800, 640, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	SDL_Renderer* tela = SDL_CreateRenderer(janela, NULL);

	TTF_TextEngine* textRender = TTF_CreateRendererTextEngine(tela);

	TTF_Font* fonte = TTF_OpenFont("./fonts/Poppins-Black.ttf", 100);

	if (fonte == nullptr) {
		SDL_Log(SDL_GetError());
	}

	TTF_Text* texto = TTF_CreateText(textRender, fonte, "JOGO\nTORTO", 0);

	SDL_Event evento;

	int larguraTela = 0;
	int alturaTela = 0;

	bool rodando = true;

	while (rodando) {
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodando = false;
			}
		}

		SDL_SetRenderDrawColor(tela, PRETO);
		SDL_RenderClear(tela);

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		SDL_SetRenderDrawColor(tela, VERMELHO);

		// desenharRetangulo(tela, 0, 0, larguraTela, alturaTela / 2);

		TTF_SetTextColor(texto, BRANCO);

		TTF_DrawRendererText(texto, 50, 50);

		SDL_RenderPresent(tela);
	}

	SDL_DestroyRenderer(tela);
	SDL_DestroyWindow(janela);

	TTF_Quit();

	SDL_Quit();

	return 0;
}