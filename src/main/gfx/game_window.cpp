#include <algorithm>
#define NOMINMAX // Para que nadie nos redefina min max
#include <sstream>

#include "game_window.h"

#include "../parser_yaml/graphics_parser.h"
#include "../parser_yaml/ruleset_parser.h"

using namespace std;

bool GameWindow::sdlInitialized = false;

bool GameWindow::initialize() {
	Logger::getInstance()->writeInformation("Initializing graphics");
	if (GameWindow::sdlInitialized) {
		Logger::getInstance()->writeWarning("SDL already initialized");
	} else {
		atexit(SDL_Quit);
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 || TTF_Init() == -1) {
			Logger::getInstance()->writeError("SDL could not initialize!");
			Logger::getInstance()->writeError(SDL_GetError());
			GameWindow::sdlInitialized = false;
		} else {
			GameWindow::sdlInitialized = true;
		}
	}
	return GameWindow::sdlInitialized;
}

GameWindow::GameWindow(Game& owner, Player& player, GraphicsParser& graphicsParser, RulesetParser& rulesetParser) :
	AClient(owner, player),
	board(player.board),
	ancho_pantalla(graphicsParser.getPantalla().ancho), alto_pantalla(graphicsParser.getPantalla().alto),
	margen_pantalla(graphicsParser.getPantalla().margen_scroll), scroll_speed(graphicsParser.getPantalla().velocidad_scroll)
{
	GameWindow::initialize(); 
	window = SDL_CreateWindow(("Trabajo Práctico 7542: " + owner.getBoard()->name).c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		ancho_pantalla, alto_pantalla,
		SDL_WINDOW_SHOWN);

	Logger::getInstance()->writeInformation("Creating renderer");
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color: negro opaco
	SDL_RenderClear(renderer); // Limpio pantalla inicialmente
	SDL_RenderPresent( renderer );

	auto tp = graphicsParser.getPantalla();
	if(player.entities().size() > 0)
		selection = player.entities().at(0);
	focus();
	minimap = std::make_shared<MiniMap>(*this);
	isoview = std::make_shared<IsoView>(*this, rulesetParser);
	menu = std::make_shared<Menu>(*this);
}

GameWindow::~GameWindow() {
	Logger::getInstance()->writeInformation("Destroying renderer");
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	Logger::getInstance()->writeInformation("Destroying window");
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	} else {
		Logger::getInstance()->writeWarning("Window never initialized");
	}
	clearSelection();
}

void GameWindow::render() {
	isoview->draw(renderer);
	SDL_Rect destinoFondoMenu = {0, 3*alto_pantalla/4, ancho_pantalla, alto_pantalla / 4};
	SDL_SetRenderDrawColor(renderer, 8, 8, 8, 255);
	SDL_RenderFillRect(renderer, &destinoFondoMenu);
	menu->draw(renderer);
	minimap->drawMinimap(renderer);

	SDL_RenderPresent(renderer);
	return;
}

void GameWindow::update(){
	if (getSelection()) {
		if (getSelection()->getDeletable()) {
			clearSelection();
		}
	}
	isoview->update();
	processInput();
	render();
	return;
}

void GameWindow::processInput(){
	SDL_GetMouseState(&mouse.x, &mouse.y);
	boardMouse = isoview->screenToBoardPosition(mouse);
	scroll();
	//	Procesar input del usuario
	while(SDL_PollEvent(EventHandler::getInstance()->getEvent())) {
		auto & e = *(EventHandler::getInstance()->getEvent());
		switch(e.type) {
			case SDL_QUIT:
				owner.exit();
				break;
			case SDL_KEYDOWN:
				Logger::getInstance()->writeInformation("Teclado");
				switch(e.key.keysym.sym) {
					case SDLK_r:
						owner.restart();
						break;
					case SDLK_s:
						if (selectionController()) {
							board.pushCommand(make_shared<StopCommand>(selection->getId()));
						}
						break;
					case SDLK_SPACE:
						focus();
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				ostringstream oss;
				oss << "Mouse en " << mouse.x << "," << mouse.y;
				// Conversion de coordenadas en pantalla a coordenadas mapa
				oss << "; mapa: " << boardMouse.x << "," << boardMouse.y;

				Logger::getInstance()->writeInformation(oss.str().c_str());
				if( EventHandler::getInstance()->getEvent()->button.button == SDL_BUTTON_LEFT ) {
					Logger::getInstance()->writeInformation("Boton Izquierdo");
					setSelection();
				}
				if( EventHandler::getInstance()->getEvent()->button.button == SDL_BUTTON_RIGHT) {
					Logger::getInstance()->writeInformation("Boton derecho");
					if (selectionController()) {
						if (!(SDL_GetModState()&KMOD_SHIFT)) {
							board.pushCommand(make_shared<StopCommand>(selection->getId()));
						}
						board.pushCommand(make_shared<MoveCommand>(selection->getId(), boardMouse));
					}
				}
				break;
		}
	}
}

void GameWindow::scroll(){
	double ds = (double)scroll_speed * (double)(board.dt) / 1000.0; //deltascroll
	r2 df;

	if(mouse.x <= margen_pantalla) {
		auto dsi = interpolate(mouse.x, 0, margen_pantalla, ds, 0);
		df += {-dsi, dsi};
		Logger::getInstance()->writeInformation("Scrolleando hacia la izquierda");
	}
	if(mouse.x >= ancho_pantalla - margen_pantalla){
		auto dsi = interpolate(mouse.x, ancho_pantalla - margen_pantalla, ancho_pantalla, 0, ds);
		df += {dsi, -dsi};
		Logger::getInstance()->writeInformation("Scrolleando hacia la derecha");
	}
	if(mouse.y <= margen_pantalla) {
		auto dsi = interpolate(mouse.y, 0, margen_pantalla, ds, 0);
		df += {-dsi, -dsi};
		Logger::getInstance()->writeInformation("Scrolleando hacia arriba");
	}
	if(mouse.y >= alto_pantalla - margen_pantalla) {
		auto dsi = interpolate(mouse.y, alto_pantalla - margen_pantalla, alto_pantalla, 0, ds);
		df += {dsi, dsi};
		Logger::getInstance()->writeInformation("Scrolleando hacia abajo");
	}
	focus(focusPosition + df);
}

void GameWindow::focus(r2 newFocus) {
	focusPosition.x = clip(newFocus.x, 0, board.sizeX - 1);
	focusPosition.y = clip(newFocus.y, 0, board.sizeY - 1);
}

void GameWindow::focus() {
	if (getSelection()) {
		focus(getSelection()->getPosition());
	}
}

r2 GameWindow::getFocus() {
	return focusPosition;
}

shared_ptr<Entity> GameWindow::getSelection() {
	return selection;
}

void GameWindow::clearSelection() {
	selection = nullptr;
}

void GameWindow::setSelection() {
	selection = (player.getVisibility(boardMouse) >= SEEN) ? board.findEntity(boardMouse) : nullptr;
}

bool GameWindow::selectionController() {
	if (!getSelection()) {
		return false;
	}
	return &(selection->owner) == &player;
}

