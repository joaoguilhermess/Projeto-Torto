#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define COR_BRANCO 255, 255, 255, 255
#define COR_PRETO 0, 0, 0, 255
#define COR_VERMELHO 255, 0, 0, 255

#define ESPACAMENTO 50
#define LARGURA_BORDA 2

#define TAMANHO_TITULO 50

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
		return 1;
	}

	SDL_Window* janela = SDL_CreateWindow("Jogo Torto", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN);
	SDL_Renderer* tela = SDL_CreateRenderer(janela, NULL);

	TTF_TextEngine* texto = TTF_CreateRendererTextEngine(tela);
	TTF_Font* fonteTitulo = TTF_OpenFont("./fonts/Poppins-Black.ttf", TAMANHO_TITULO);

	if (!fonteTitulo) {
		return 1;
	}

	SDL_FRect retangulo = {0, 0, 0, 0};
	SDL_Event evento;

	TTF_Text* titulo = TTF_CreateText(texto, fonteTitulo, "JOGO TORTO", 0);
	int larguraTitulo;
	int alturaTitulo;

	TTF_GetTextSize(titulo, &larguraTitulo, &alturaTitulo);

	int larguraTela = 0;
	int alturaTela = 0;

	bool rodando = true;

	while (rodando) {
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodando = false;
			}
		}

		SDL_SetRenderDrawColor(tela, COR_BRANCO);
		SDL_RenderClear(tela);

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		retangulo.x = ESPACAMENTO;
		retangulo.y = ESPACAMENTO;
		retangulo.w = larguraTela - (ESPACAMENTO * 2);
		retangulo.h = LARGURA_BORDA;

		SDL_SetRenderDrawColor(tela, COR_PRETO);
		SDL_RenderFillRect(tela, &retangulo);

		TTF_SetTextColor(titulo, COR_PRETO);
		TTF_DrawRendererText(titulo, ESPACAMENTO, 0);

		retangulo.x = 0;
		retangulo.y = alturaTitulo;
		retangulo.w = 500;
		retangulo.h = LARGURA_BORDA;

		SDL_SetRenderDrawColor(tela, COR_VERMELHO);
		SDL_RenderFillRect(tela, &retangulo);

		SDL_RenderPresent(tela);
	}

	TTF_DestroyText(titulo);
	TTF_CloseFont(fonteTitulo);
	TTF_Quit();

	SDL_DestroyRenderer(tela);
	SDL_DestroyWindow(janela);
	SDL_Quit();

	return 0;
}