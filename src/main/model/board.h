#ifndef _MODEL_BOARD_H_
#define _MODEL_BOARD_H_
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
#include "../model/entity.h"
#include "../parser_yaml/parser_yaml.h"
//-----------------------------------------------------------------------------
class Board {

private:
	std::vector<Entity*> entities;

public:
	Board();
	~Board();

	void update();
	void buildBoard(ParserYAML* parser);
};
//-----------------------------------------------------------------------------
#endif /* _MODEL_BOARD_H_ */
//-----------------------------------------------------------------------------
