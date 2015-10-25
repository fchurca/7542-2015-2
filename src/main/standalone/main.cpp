#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../parser_yaml/graphics_parser.h"
#include "../parser_yaml/ruleset_parser.h"
#include "../parser_yaml/scenario_parser.h"
#include "../log/logger.h"
#include "../model/game.h"
#include "../gfx/game_window.h"

#include "../remote_client/remote_client.h"

int main(int argc, char* argv[]) {

	auto & logger = *Logger::getInstance();
	logger.writeInformation("Start game");

	bool standalone = false, daemon = false, client = false;
	if (argc >= 2) {
		switch (argv[1][0]) {
			case 'd': case 'D':
				daemon = true;
				logger.writeInformation("Starting game as daemon");
				break;
			case 'c': case 'C':
				client = true;
				logger.writeInformation("Starting game as client");
				break;
			default:
				standalone = true;
				logger.writeInformation("Starting game as standalone");
				break;
		}
	}

	bool restart = true;
	do {
		Game game;
		ScenarioParser scenarioParser(SCENARIO_CONFIG_FILE_PATH, SCENARIO_CONFIG_FILE_PATH_DEFAULT);
		GraphicsParser graphicsParser(GRAPHICS_CONFIG_FILE_PATH, GRAPHICS_CONFIG_FILE_PATH_DEFAULT);
		RulesetParser rulesetParser(RULESET_CONFIG_FILE_PATH, RULESET_CONFIG_FILE_PATH_DEFAULT);
		scenarioParser.parse();
		graphicsParser.parse();
		rulesetParser.parse();
		if (client) {
			// Acá estamos levantando el cliente. Lo siguiente en realidad es un RemoteBoard que se conecta por TCP/IP al daemon
			game.setBoard(make_shared<SmartBoard>(graphicsParser,rulesetParser,scenarioParser));
		} else {
			game.setBoard(make_shared<SmartBoard>(graphicsParser, rulesetParser, scenarioParser));
		}
		if (daemon) {
			// Acá estamos levantando el server. Todo el siguiente bloque es por cliente nuevo
			auto remotePlayer = game.getAvailablePlayer();
			if (remotePlayer) {
				game.addClient(make_shared<RemoteClient>(game, *(remotePlayer)));
			}
		}
		auto graphicPlayer = game.getAvailablePlayer();
		if (graphicPlayer) {
			game.addClient(make_shared<GameWindow>(game, *(graphicPlayer), graphicsParser, rulesetParser));
		}
		game.start();
		restart = game.willRestart();
	} while (restart);

	logger.writeInformation("Closing down");

	exit(0);
}

