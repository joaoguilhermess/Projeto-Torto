#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "palavras.h"
#include <string>

#define COR_BRANCO 255, 255, 255, 255
#define COR_PRETO 0, 0, 0, 255
#define COR_VERMELHO 255, 0, 0, 255

#define ZOOM 1

#define ESPACAMENTO 50 / ZOOM
#define LARGURA_BORDA 2

int larguraTela = 0;
int alturaTela = 0;

#define FONTE_MUITO_GRANDE 80 / ZOOM
#define FONTE_GRANDE 80 / ZOOM
#define FONTE_MEDIA 40 / ZOOM
#define FONTE_PEQUENA 20 / ZOOM

#define ESQUERDA 0
#define MEIO 1.0f / 2
#define DIREITA 1

SDL_Window* janela;
SDL_Renderer* renderTela;
TTF_TextEngine* renderTexto;

TTF_Font* fonteMuitoGrande;
TTF_Font* fonteGrande;
TTF_Font* fonteMedia;
TTF_Font* fontePequena;

float mouseX = 0;
float mouseY = 0;

bool mouseApertado = false;

void desenharRetangulo(float x, float y, float largura, float altura) {
	SDL_FRect retangulo = {x, y, largura, altura};

	SDL_RenderFillRect(renderTela, &retangulo);
}

void escreverTexto(float offset, std::string conteudo, TTF_Font* fonte, float x, float y) {
	TTF_Text* texto = TTF_CreateText(renderTexto, fonte, conteudo.c_str(), 0);

	TTF_SetTextColor(texto, COR_PRETO);

	int largura;
	int altura;

	TTF_GetTextSize(texto, &largura, &altura);

	TTF_DrawRendererText(texto, x - (largura * offset), y - (TTF_GetFontSize(fonte) / 3));

	TTF_DestroyText(texto);
}

void desenharBotao(float offset, std::string conteudo, TTF_Font* fonte, float x, float y, float espacamento, int tamanho, bool &mouseDentro) {
	TTF_Text* texto = TTF_CreateText(renderTexto, fonte, conteudo.c_str(), 0);

	int largura;
	int altura;

	TTF_GetTextSize(texto, &largura, &altura);

	float L = espacamento + largura + espacamento;
	float A = espacamento + tamanho + espacamento;

	x -= L * offset;

	float X = x;
	float Y = y;

	mouseDentro = mouseX >= X && mouseX <= X + L && mouseY >= Y && mouseY <= Y + A;

	if (mouseDentro) {
		SDL_SetRenderDrawColor(renderTela, COR_PRETO);
	} else {
		SDL_SetRenderDrawColor(renderTela, COR_BRANCO);
	}

	desenharRetangulo(X, Y, L, A);

	if (mouseDentro) {
		TTF_SetTextColor(texto, COR_BRANCO);
	} else {
		TTF_SetTextColor(texto, COR_PRETO);
	}

	TTF_DrawRendererText(texto, x + espacamento, y - (TTF_GetFontSize(fonte) / 3) + espacamento);

	TTF_DestroyText(texto);
}

bool iniciarSDL() {
	if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) return false;

	janela = SDL_CreateWindow("Jogo Torto", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN);
	// janela = SDL_CreateWindow("Jogo Torto", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	renderTela = SDL_CreateRenderer(janela, NULL);
	renderTexto = TTF_CreateRendererTextEngine(renderTela);

	fonteMuitoGrande = TTF_OpenFont("./fonts/Poppins-Black.ttf", FONTE_MUITO_GRANDE * 1.4);
	TTF_SetFontLineSkip(fonteMuitoGrande, FONTE_MUITO_GRANDE * 1.4);
	if (!fonteMuitoGrande) return false;

	fonteGrande = TTF_OpenFont("./fonts/Poppins-Medium.ttf", FONTE_GRANDE * 1.4);
	TTF_SetFontLineSkip(fonteGrande, FONTE_GRANDE * 1.4);
	if (!fonteGrande) return false;

	fonteMedia = TTF_OpenFont("./fonts/Poppins-SemiBold.ttf", FONTE_MEDIA * 1.4);
	TTF_SetFontLineSkip(fonteMedia, FONTE_MEDIA * 1.4);
	if (!fonteMedia) return false;

	fontePequena = TTF_OpenFont("./fonts/Poppins-Medium.ttf", FONTE_PEQUENA * 1.4);
	TTF_SetFontLineSkip(fontePequena, FONTE_PEQUENA * 1.4);
	if (!fontePequena) return false;

	return true;
}

void limparTela() {
	SDL_SetRenderDrawColor(renderTela, COR_BRANCO);
	SDL_RenderClear(renderTela);
}

void fecharSDL() {
	TTF_CloseFont(fonteMuitoGrande);
	TTF_CloseFont(fonteGrande);
	TTF_CloseFont(fonteMedia);
	TTF_CloseFont(fontePequena);
	TTF_Quit();

	SDL_DestroyRenderer(renderTela);
	SDL_DestroyWindow(janela);
	SDL_Quit();
}

void desenharTitulos(int &topo, int &base) {
	topo += ESPACAMENTO;

	SDL_SetRenderDrawColor(renderTela, COR_PRETO);

	desenharRetangulo(ESPACAMENTO, topo, larguraTela - (ESPACAMENTO + ESPACAMENTO), LARGURA_BORDA);

	topo += LARGURA_BORDA + ESPACAMENTO;

	escreverTexto(ESQUERDA, "JOGO TORTO", fonteMuitoGrande, ESPACAMENTO + ESPACAMENTO, topo);

	escreverTexto(DIREITA, "GRUPO 4", fonteMuitoGrande, larguraTela - (ESPACAMENTO + ESPACAMENTO), topo);

	topo += FONTE_MUITO_GRANDE + ESPACAMENTO;

	desenharRetangulo(ESPACAMENTO, topo, larguraTela - (ESPACAMENTO + ESPACAMENTO), LARGURA_BORDA);

	base -= ESPACAMENTO + LARGURA_BORDA;

	desenharRetangulo(ESPACAMENTO, base, larguraTela - (ESPACAMENTO + ESPACAMENTO), LARGURA_BORDA);

	topo += ESPACAMENTO;	
}

void desenharLetras(std::string letras, float tamanhoFonte, int &topo) {
	int tamanho = letras.length();

	int k = tamanhoFonte * 1.6;

	desenharRetangulo(ESPACAMENTO + ESPACAMENTO, topo, (tamanho + 1) * LARGURA_BORDA + tamanho * k, LARGURA_BORDA);

	topo += LARGURA_BORDA;

	for (int i = 0; i < tamanho + 1; i++) {
		std::string letra = "";

		letra += letras[i];

		int x = ESPACAMENTO + ESPACAMENTO + i * LARGURA_BORDA + i * k;

		desenharRetangulo(x, topo, LARGURA_BORDA, k);

		if (i < tamanho) {
			escreverTexto(MEIO, letra, fonteMedia, x + LARGURA_BORDA + (k / 2), topo + (k - tamanhoFonte) / 2);
		}
	}

	topo += k;

	desenharRetangulo(ESPACAMENTO + ESPACAMENTO, topo, (tamanho + 1) * LARGURA_BORDA + tamanho * k, LARGURA_BORDA);

	topo += LARGURA_BORDA;
}

void menuJogar(bool &rodando) {
	SDL_Event evento;

	bool rodandoJogar = true;

	while (rodandoJogar) {
		mouseApertado = false;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodandoJogar = false;
				rodando = false;
			} else if (evento.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			} else if (evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				mouseApertado = true;
			}
		}

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		limparTela();

		int topo = 0;
		int base = alturaTela;

		desenharTitulos(topo, base);

		escreverTexto(ESQUERDA, "Nível 1", fonteMedia, ESPACAMENTO + ESPACAMENTO, topo);
		
		escreverTexto(DIREITA, "TEMPO 00:00:00", fonteMedia, larguraTela - (ESPACAMENTO + ESPACAMENTO), topo);

		topo += FONTE_MEDIA + ESPACAMENTO;

		// std::string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string abc = "ABCDEFGHIJ";

		desenharLetras(abc, FONTE_MEDIA, topo);

		topo += ESPACAMENTO;

		desenharLetras("PRESEPADA ", FONTE_MEDIA, topo);

		base -= FONTE_GRANDE + ESPACAMENTO + ESPACAMENTO + ESPACAMENTO;

		bool mouseDentro = false;

		desenharBotao(DIREITA, "Voltar", fonteGrande, larguraTela - ESPACAMENTO - ESPACAMENTO, base, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

		if (mouseDentro && mouseApertado) {
			mouseApertado = false;

			rodandoJogar = false;
		}

		SDL_RenderPresent(renderTela);
	}
}

void menuAjuda(bool &rodando) {
	SDL_Event evento;

	bool rodandoAjuda = true;

	while (rodandoAjuda) {
		mouseApertado = false;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodandoAjuda = false;
				rodando = false;
			} else if (evento.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			} else if (evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				mouseApertado = true;
			}
		}

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		limparTela();

		int topo = 0;
		int base = alturaTela;

		desenharTitulos(topo, base);

		escreverTexto(ESQUERDA, "Objetivos do Jogo", fonteMedia, ESPACAMENTO + ESPACAMENTO, topo);

		topo += FONTE_MEDIA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Ensinar Novas Palavras em Português ou Inglês e Seus Significados ao Jogador.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_PEQUENA + ESPACAMENTO + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Como Jogar", fonteMedia, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_MEDIA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Jogue o Jogo Usando as Teclas Alfabéticas do seu Teclado.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);

		topo += FONTE_PEQUENA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Use ENTER para Submeter a Palavra Digitada.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_PEQUENA + ESPACAMENTO;

		base -= FONTE_GRANDE + ESPACAMENTO + ESPACAMENTO + ESPACAMENTO;

		bool mouseDentro = false;

		desenharBotao(DIREITA, "Voltar", fonteGrande, larguraTela - ESPACAMENTO - ESPACAMENTO, base, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

		if (mouseDentro && mouseApertado) {
			mouseApertado = false;

			rodandoAjuda = false;
		}
		
		SDL_RenderPresent(renderTela);
	}
}

int main() {
	if (!iniciarSDL()) return 1;

	std::string menus[3] = {
		"JOGAR",
		"AJUDA",
		"SAIR"
	};

	std::string participantes[4] = {
		"Felipe Oliveira de Andrade Santos",
		"Ives Rayllan do Nascimento Souza",
		"João Guilherme Santos Silva",
		"ULisses Dorenski Lima Ribeiro"
	};

	SDL_Event evento;

	bool rodando = true;

	menuJogar(rodando);

	return 1;

	while (rodando) {
		mouseApertado = false;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodando = false;
			} else if (evento.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			} else if (evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				mouseApertado = true;
			}
		}

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		limparTela();

		int topo = 0;
		int base = alturaTela;

		desenharTitulos(topo, base);

		float k = (base - ESPACAMENTO - topo - (3 * (ESPACAMENTO + FONTE_GRANDE + ESPACAMENTO))) / (3 + 1);

		for (int i = 0; i < 3; i++) {
			topo += k;

			bool mouseDentro = false;

			desenharBotao(ESQUERDA, menus[i], fonteGrande, ESPACAMENTO + ESPACAMENTO, topo, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

			if (mouseDentro && mouseApertado) {
				mouseApertado = false;

				limparTela();

				if (i == 0) {
					menuJogar(rodando);
				} else if (i == 1) {
					menuAjuda(rodando);
				} else if (i == 2) {
					rodando = false;
				}

				limparTela();
			}

			topo += ESPACAMENTO + FONTE_GRANDE + ESPACAMENTO;
		}

		for (int i = 4 - 1; i >= 0; i--) {
			base -= FONTE_PEQUENA + ESPACAMENTO;

			escreverTexto(DIREITA, participantes[i], fontePequena, larguraTela - ESPACAMENTO - ESPACAMENTO, base);
		}

		base -= FONTE_MEDIA + ESPACAMENTO;

		escreverTexto(DIREITA, "Feito Com Amor Por", fonteMedia, larguraTela - ESPACAMENTO - ESPACAMENTO, base);

		SDL_RenderPresent(renderTela);
	}

	fecharSDL();

	return 0;
}