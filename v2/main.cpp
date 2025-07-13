#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "palavras.h"
#include "util.h"

#include <filesystem>

#define COR_BRANCO 255, 255, 255, 255
#define COR_PRETO 0, 0, 0, 255
#define COR_VERMELHO 255, 0, 0, 255

#define ZOOM 1.6

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

#define MAX_PONTOS 100
#define MIN_PONTOS 25

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

float escreverTexto(float offset, std::string conteudo, TTF_Font* fonte, float x, float y) {
	TTF_Text* texto = TTF_CreateText(renderTexto, fonte, conteudo.c_str(), 0);

	TTF_SetTextColor(texto, COR_PRETO);

	int largura;
	int altura;

	TTF_GetTextSize(texto, &largura, &altura);

	TTF_DrawRendererText(texto, x - (largura * offset), y - (TTF_GetFontSize(fonte) / 3));

	TTF_DestroyText(texto);

	return largura;
}

float desenharBotao(float offset, std::string conteudo, TTF_Font* fonte, float x, float y, float espacamento, float tamanho, bool &mouseDentro) {
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

	return L;
}

bool iniciarSDL() {
	if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) return false;

	// janela = SDL_CreateWindow("Jogo Torto", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN);
	janela = SDL_CreateWindow("Jogo Torto", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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

void desenharTitulos(float &topo, float &base) {
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

float desenharLetras(float offset, std::string letras, int tamanho, float tamanhoFonte, float x, float &topo) {
	float k = tamanhoFonte * 1.6;

	SDL_SetRenderDrawColor(renderTela, COR_PRETO);

	float L = (tamanho + 1) * LARGURA_BORDA + tamanho * k;

	desenharRetangulo(x - (L * offset), topo, L, LARGURA_BORDA);

	topo += LARGURA_BORDA;

	for (int i = 0; i < tamanho + 1; i++) {
		std::string letra = "";

		letra += letras[i];

		float X = x + (i * LARGURA_BORDA + i * k) - (L * offset);

		desenharRetangulo(X, topo, LARGURA_BORDA, k);

		if (i < letras.length()) {
			escreverTexto(MEIO, letra, fonteMedia, X + LARGURA_BORDA + (k / 2), topo + (k - tamanhoFonte) / 2);
		}
	}

	topo += k;

	desenharRetangulo(x - (L * offset), topo, L, LARGURA_BORDA);

	topo += LARGURA_BORDA;

	return L;
}

std::string getLetra(int code) {
	if (code == SDL_SCANCODE_A) return "A";
	if (code == SDL_SCANCODE_B) return "B";
	if (code == SDL_SCANCODE_C) return "C";
	if (code == SDL_SCANCODE_D) return "D";
	if (code == SDL_SCANCODE_E) return "E";
	if (code == SDL_SCANCODE_F) return "F";
	if (code == SDL_SCANCODE_G) return "G";
	if (code == SDL_SCANCODE_H) return "H";
	if (code == SDL_SCANCODE_I) return "I";
	if (code == SDL_SCANCODE_J) return "J";
	if (code == SDL_SCANCODE_K) return "K";
	if (code == SDL_SCANCODE_L) return "L";
	if (code == SDL_SCANCODE_M) return "M";
	if (code == SDL_SCANCODE_N) return "N";
	if (code == SDL_SCANCODE_O) return "O";
	if (code == SDL_SCANCODE_P) return "P";
	if (code == SDL_SCANCODE_Q) return "Q";
	if (code == SDL_SCANCODE_R) return "R";
	if (code == SDL_SCANCODE_S) return "S";
	if (code == SDL_SCANCODE_T) return "T";
	if (code == SDL_SCANCODE_U) return "U";
	if (code == SDL_SCANCODE_V) return "V";
	if (code == SDL_SCANCODE_W) return "W";
	if (code == SDL_SCANCODE_X) return "X";
	if (code == SDL_SCANCODE_Y) return "Y";
	if (code == SDL_SCANCODE_Z) return "Z";

	return "";
}

void menuJogar(bool &rodando, std::string dicionario) {
	SDL_Event evento;

	TPilha palavrasOriginais = lerPalavras(dicionario, 6);
	TPilha palavras = lerPalavras(dicionario, 6);

	TPilha historico = criarPilha();

	TInfo item;

	int nivel = 1;
	int pontos = 0;

	std::string palavraSignificado = "";
	std::string significado = "Alguma Porra Muito Maluca.";

	bool rodandoJogar = true;

	while (rodandoJogar) {
		long long inicio = getAgora();

		TInfo sorteada = pegarItem(palavras, inteiroAleatorio(0, palavras.quantidade), true);

		std::string embaralhada = embaralharPalavra(sorteada.palavra);

		if (sorteada.palavra == "") {
			break;
		}

		std::string digitada = "";

		bool rodandoPalavra = true;

		while (rodandoPalavra) {
			mouseApertado = false;

			while (SDL_PollEvent(&evento)) {
				if (evento.type == SDL_EVENT_QUIT) {
					rodandoPalavra = false;
					rodandoJogar = false;
					rodando = false;
				} else if (evento.type == SDL_EVENT_MOUSE_MOTION) {
					SDL_GetMouseState(&mouseX, &mouseY);
				} else if (evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
					mouseApertado = true;
				} else if (evento.type == SDL_EVENT_KEY_DOWN) {
					if (evento.key.scancode == SDL_SCANCODE_BACKSPACE) {
						if (digitada.length() > 0) {
							digitada = digitada.substr(0, digitada.length() - 1);
						}
					} else if (evento.key.scancode == SDL_SCANCODE_RETURN) {
						if (digitada == sorteada.palavra) {
							nivel += 1;

							pontos += MAX_PONTOS;

							rodandoPalavra = false;

							palavraSignificado = digitada;
						} else if (verificarPalavra(palavrasOriginais, digitada) && !verificarPalavra(historico, digitada) && verificarLetras(embaralhada, digitada)) {
							pontos += inteiroAleatorio(MIN_PONTOS, MAX_PONTOS); 

							item.palavra = digitada;

							adicionarItem(historico, item);

							palavraSignificado = digitada;

							digitada = "";
						}
					} else {
						if (digitada.length() < sorteada.palavra.length()) {
							digitada += getLetra(evento.key.scancode);
						}
					}
				}
			}

			SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

			limparTela();

			if ((getAgora() - inicio) > 1000 * 60) {
				rodandoPalavra = false;

				palavraSignificado = sorteada.palavra;
			}

			float topo = 0;
			float base = alturaTela;
			float esquerda = 0;
			float direita = larguraTela;

			desenharTitulos(topo, base);

			bool mouseDentro = false;

			direita -= ESPACAMENTO + ESPACAMENTO;

			base -= ESPACAMENTO + LARGURA_BORDA + FONTE_GRANDE + ESPACAMENTO + ESPACAMENTO;

			desenharBotao(DIREITA, "Voltar", fonteGrande, direita, base, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

			if (mouseDentro && mouseApertado) {
				mouseApertado = false;

				rodandoPalavra = false;
				rodandoJogar = false;
			}

			base = alturaTela - ESPACAMENTO - LARGURA_BORDA - FONTE_MEDIA - ESPACAMENTO;

			esquerda += ESPACAMENTO + ESPACAMENTO;

			if (palavraSignificado.length() > 0) {
				escreverTexto(ESQUERDA, significado, fonteMedia, esquerda, base);

				base -= LARGURA_BORDA + (FONTE_MEDIA * 1.6) + LARGURA_BORDA + ESPACAMENTO;

				desenharLetras(ESQUERDA, palavraSignificado, palavraSignificado.length(), FONTE_MEDIA, esquerda, base);
			}

			escreverTexto(ESQUERDA, "Histórico " + std::to_string(historico.quantidade), fonteMedia, esquerda, topo);

			float coluna = (direita - esquerda) / 4;

			float topo2 = topo + FONTE_MEDIA + ESPACAMENTO;

			TPilha historico2 = criarPilha();

			float esquerda2 = esquerda;

			while (!pilhaVazia(historico)) {
				item = pegarItem(historico);

				adicionarItem(historico2, item);

				removerItem(historico);

				esquerda2 = std::max(esquerda2, esquerda + desenharLetras(ESQUERDA, item.palavra, item.palavra.length(), FONTE_MEDIA, esquerda, topo2));

				topo2 += ESPACAMENTO;

				if (topo2 >= base) break;
			}

			while (!pilhaVazia(historico2)) {
				adicionarItem(historico, pegarItem(historico2));

				removerItem(historico2);
			}

			deletarPilha(historico2);

			esquerda = std::max((float) (ESPACAMENTO + ESPACAMENTO + coluna), esquerda2);

			esquerda += ESPACAMENTO + ESPACAMENTO;

			float esquerda3 = esquerda;

			esquerda3 += escreverTexto(ESQUERDA, "Nível " + std::to_string(nivel), fonteMedia, esquerda3, topo);

			esquerda3 += ESPACAMENTO + ESPACAMENTO;

			esquerda3 += escreverTexto(ESQUERDA, "Pontos " + std::to_string(pontos), fonteMedia, esquerda3, topo);

			escreverTexto(DIREITA, "Tempo " + formatarTempo(getAgora() - inicio), fonteMedia, direita, topo);

			topo += FONTE_MEDIA + ESPACAMENTO;

			desenharLetras(ESQUERDA, embaralhada, embaralhada.length(), FONTE_MEDIA, esquerda, topo);

			topo += ESPACAMENTO;

			desenharLetras(ESQUERDA, digitada, embaralhada.length(), FONTE_MEDIA, esquerda, topo);

			SDL_RenderPresent(renderTela);
		}

		while (!pilhaVazia(historico)) {
			removerItem(historico);
		}
	}

	deletarPilha(palavrasOriginais);
	deletarPilha(palavras);
	deletarPilha(historico);
}

void menuDicionario(bool &rodando) {
	SDL_Event evento;

	TPilha dicionarios = criarPilha();

	TInfo item;

	std::string caminho = ".\\palavras\\";
	std::string extensaoDicionario = ".txt";

	for (std::filesystem::directory_entry arquivo : std::filesystem::directory_iterator(caminho)) {
		std::string nome = arquivo.path().filename().string();

		size_t extensao = nome.rfind(".");

		if (extensao == std::string::npos) continue;
		if (nome.substr(extensao) != ".txt") continue;

		item.palavra = nome.substr(0, extensao);

		adicionarItem(dicionarios, item);
	}

	bool rodandoDicionario = true;

	while (rodandoDicionario) {
		mouseApertado = false;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_EVENT_QUIT) {
				rodandoDicionario = false;
				rodando = false;
			} else if (evento.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			} else if (evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				mouseApertado = true;
			}
		}

		SDL_GetWindowSize(janela, &larguraTela, &alturaTela);

		limparTela();

		float topo = 0;
		float base = alturaTela;
		float esquerda = 0;

		esquerda += ESPACAMENTO + ESPACAMENTO;

		desenharTitulos(topo, base);

		TPilha dicionarios2 = criarPilha();

		float k = (base - ESPACAMENTO - topo - (dicionarios.quantidade * (ESPACAMENTO + FONTE_GRANDE + ESPACAMENTO))) / (dicionarios.quantidade + 1);

		while (!pilhaVazia(dicionarios)) {
			topo += k;

			item = pegarItem(dicionarios);

			adicionarItem(dicionarios2, item);

			removerItem(dicionarios);

			bool mouseDentro2 = false;

			desenharBotao(ESQUERDA, item.palavra, fonteGrande, esquerda, topo, ESPACAMENTO, FONTE_GRANDE, mouseDentro2);

			if (mouseDentro2 && mouseApertado) {
				mouseApertado = false;
			
				menuJogar(rodando, caminho + item.palavra + extensaoDicionario);
			}

			topo += ESPACAMENTO + FONTE_GRANDE + ESPACAMENTO;
		}

		while (!pilhaVazia(dicionarios2)) {
			adicionarItem(dicionarios, pegarItem(dicionarios2));

			removerItem(dicionarios2);
		}

		deletarPilha(dicionarios2);

		bool mouseDentro = false;

		base -= ESPACAMENTO + LARGURA_BORDA + FONTE_GRANDE + ESPACAMENTO + ESPACAMENTO;

		desenharBotao(DIREITA, "Voltar", fonteGrande, larguraTela - ESPACAMENTO - ESPACAMENTO, base, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

		if (mouseDentro && mouseApertado) {
			mouseApertado = false;

			rodandoDicionario = false;
		}

		SDL_RenderPresent(renderTela);
	}

	deletarPilha(dicionarios);
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

		float topo = 0;
		float base = alturaTela;

		desenharTitulos(topo, base);

		escreverTexto(ESQUERDA, "Objetivos Do Jogo", fonteMedia, ESPACAMENTO + ESPACAMENTO, topo);

		topo += FONTE_MEDIA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Ensinar Novas Palavras Em Português Ou Inglês E Seus Significados Ao Jogador.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);
	
		topo += FONTE_PEQUENA + ESPACAMENTO + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Como Jogar", fonteMedia, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_MEDIA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Usando As Teclas Alfabéticas Do Seu Teclado.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_PEQUENA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Tente Adivinhar Qual Palavra É A Palavra Sorteada.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);
		
		topo += FONTE_PEQUENA + ESPACAMENTO;
		
		escreverTexto(ESQUERDA, "Isso Tudo Antes De Acabar O Tempo De 60 Segundos.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);

		topo += FONTE_PEQUENA + ESPACAMENTO;

		escreverTexto(ESQUERDA, "Use ENTER Para Submeter A Palavra Digitada.", fontePequena, ESPACAMENTO + ESPACAMENTO, topo);

		topo += FONTE_PEQUENA + ESPACAMENTO;

		base -= ESPACAMENTO + LARGURA_BORDA + FONTE_GRANDE + ESPACAMENTO + ESPACAMENTO;

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
		"Jogar",
		"Ajuda",
		"Sair"
	};

	std::string participantes[4] = {
		"Felipe Oliveira de Andrade Santos",
		"Ives Rayllan do Nascimento Souza",
		"João Guilherme Santos Silva",
		"ULisses Dorenski Lima Ribeiro"
	};

	SDL_Event evento;

	bool rodando = true;

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

		float topo = 0;
		float base = alturaTela;
		float esquerda = 0;

		desenharTitulos(topo, base);

		esquerda += ESPACAMENTO + ESPACAMENTO;

		float k = (base - ESPACAMENTO - topo - (3 * (ESPACAMENTO + FONTE_GRANDE + ESPACAMENTO))) / (3 + 1);

		for (int i = 0; i < 3; i++) {
			topo += k;

			bool mouseDentro = false;

			desenharBotao(ESQUERDA, menus[i], fonteGrande, esquerda, topo, ESPACAMENTO, FONTE_GRANDE, mouseDentro);

			if (mouseDentro && mouseApertado) {
				mouseApertado = false;

				limparTela();

				if (i == 0) {
					menuDicionario(rodando);
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