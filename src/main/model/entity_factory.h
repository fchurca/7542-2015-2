#ifndef _MODEL_ENTITY_FACTORY_H_
#define _MODEL_ENTITY_FACTORY_H_

#include <string>

#include "board.h"
#include "entity.h"

class EntityFactory {
	public:
		const std::string name;
		const int size_x;
		const int size_y;
		const double speed;
		const Board& board;
		EntityFactory(std::string name, int size_x, int size_y, double speed, const Board& board);
		~EntityFactory();
};

#endif // _MODEL_ENTITY_FACTORY_H_
