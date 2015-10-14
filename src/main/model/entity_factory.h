#ifndef _MODEL_ENTITY_FACTORY_H_
#define _MODEL_ENTITY_FACTORY_H_

#include <string>
#include <memory>

#include "board.h"
#include "entity.h"

class ResourceEntityFactory;

class EntityFactory {
	public:
		const std::string name;
		r2 size;
		const double speed;
		int sight_radius;
		bool solid;
		int capacity;
		Board& board;

		EntityFactory(std::string name, r2 size, double speed, int sight_radius, bool solid, int capacity, Board& board);
		~EntityFactory();

		std::shared_ptr<Entity> createEntity(Player& player, r2 position);
		virtual void update();
};

class ResourceEntityFactory: public EntityFactory {
	public:
		ResourceEntityFactory(std::string name, r2 size, double speed, int sight_radius, bool solid, int capacity, Board& board);
		void update();
};

#endif // _MODEL_ENTITY_FACTORY_H_
