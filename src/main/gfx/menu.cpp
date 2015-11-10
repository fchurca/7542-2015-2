#include "game_window.h"
#include "menu.h"

Menu::Menu(GameWindow& owner) :
	owner(owner),
	size(3 * owner.ancho_pantalla / 4, owner.alto_pantalla / 4),
	offset(0, 3 * owner.alto_pantalla / 4)
{
}

Menu::~Menu() {
}


void Menu::draw(SDL_Renderer* renderer) {
	//Dibujo fondo
	SDL_Rect destinoFondoMenu = { (int)offset.x, (int)offset.y, (int)size.x, (int)size.y };
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderFillRect(renderer, &destinoFondoMenu);
	if (owner.font) {
		std::string primerColumna = "", segundaColumnaActivos = "", segundaColumnaInactivos = "", terceraColumna = "";
		SDL_Color colorBlanco = { 255, 255, 255 };
		SDL_Color colorGris = { 127, 127, 127 };
		//Primer Columna//
		primerColumna = owner.completeLine(owner.player.name, size.x / 3);
		for (auto r : owner.player.getResources()) {
			primerColumna = primerColumna + owner.completeLine(r.first + "=" + std::to_string(r.second), size.x / 3);
		}
		//
		//Segunda Columna//
		for (auto p : owner.player.board.getPlayers()) {
			if (!(p->getAlive())) {
				segundaColumnaInactivos = segundaColumnaInactivos + owner.completeLine("[X] " + p->name, size.x / 3);
			} else {
				if (p->getActive()) {
					segundaColumnaActivos = segundaColumnaActivos + owner.completeLine("[A] " + p->name, size.x / 3);
				} else {
					segundaColumnaInactivos = segundaColumnaInactivos + owner.completeLine("[I]  " + p->name, size.x / 3);
				}
			}
		}

		//Tercer Columna//
		std::shared_ptr<Entity> s = owner.getSelection();
		if (s != nullptr) {
			terceraColumna = terceraColumna + owner.completeLine(s->name, size.x / 3);
			terceraColumna = terceraColumna + owner.completeLine("(" + s->owner.name + ")", size.x / 3);
		}
		int access1, w1, h1, access2A, w2A, h2A, access2I, w2I, h2I, access3, w3, h3;
		Uint32 format1, format2A, format2I, format3;
		SDL_Surface * c1 = TTF_RenderText_Blended_Wrapped(owner.font, primerColumna.c_str(), colorBlanco, (Uint32)(size.x / 3));
		SDL_Texture * textureMenu1 = SDL_CreateTextureFromSurface(renderer, c1);
		SDL_Surface * c2A = TTF_RenderText_Blended_Wrapped(owner.font, segundaColumnaActivos.c_str(), colorBlanco, (Uint32)(size.x / 3));
		SDL_Texture * textureMenu2A = SDL_CreateTextureFromSurface(renderer, c2A);
		SDL_Surface * c2I = TTF_RenderText_Blended_Wrapped(owner.font, segundaColumnaInactivos.c_str(), colorGris, (Uint32)(size.x / 3));
		SDL_Texture * textureMenu2I = SDL_CreateTextureFromSurface(renderer, c2I);
		SDL_Surface * c3 = TTF_RenderText_Blended_Wrapped(owner.font, terceraColumna.c_str(), colorBlanco, (Uint32)(size.x / 3));
		SDL_Texture * textureMenu3 = SDL_CreateTextureFromSurface(renderer, c3);

		SDL_QueryTexture(textureMenu1, &format1, &access1, &w1, &h1);
		SDL_Rect panel1 = { 0, 0, w1 , h1 };
		SDL_Rect text1 = { (int)offset.x, (int)offset.y,
			(int)((w1>size.x/3)? size.x/3 : w1), (int)((h1>size.y) ? size.y : h1) };
		SDL_RenderCopy(renderer, textureMenu1, &panel1, &text1);

		SDL_QueryTexture(textureMenu2A, &format2A, &access2A, &w2A, &h2A);
		SDL_Rect panel2A = { 0, 0, w2A, h2A };
		SDL_Rect text2A = { (int)(size.x / 3), (int)offset.y,
			(int)((w2A>size.x / 3) ? size.x / 3 : w2A), (int)((h2A>size.y) ? size.y : h2A) };
		SDL_RenderCopy(renderer, textureMenu2A, &panel2A, &text2A);
		SDL_QueryTexture(textureMenu2I, &format2I, &access2I, &w2I, &h2I);
		if (segundaColumnaInactivos != "" && (size.y - h2A > h2I)) {
			SDL_Rect panel2I = { 0, 0, w2I, h2I };
			SDL_Rect text2I = { (int)(size.x/3), (int)(h2A + offset.y),
				(int)((w2I>size.x / 3) ? size.x / 3 : w2I), (int)h2I };
			SDL_RenderCopy(renderer, textureMenu2I, &panel2I, &text2I);
		}

		SDL_QueryTexture(textureMenu3, &format3, &access3, &w3, &h3);
		SDL_Rect panel3 = { 0, 0, w3, h3 };
		SDL_Rect text3 = { (int)(2 * size.x/3), (int)(offset.y),
			(int)((w3>size.x / 3) ? size.x / 3 : w3), (int)((h3>size.y) ? size.y : h3) };
		SDL_RenderCopy(renderer, textureMenu3, &panel3, &text3);
		SDL_FreeSurface(c1);
		SDL_FreeSurface(c2A);
		SDL_FreeSurface(c2I);
		SDL_FreeSurface(c3);
		SDL_DestroyTexture(textureMenu1);
		SDL_DestroyTexture(textureMenu2A);
		SDL_DestroyTexture(textureMenu2I);
		SDL_DestroyTexture(textureMenu3);
	}
}
