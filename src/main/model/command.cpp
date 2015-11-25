#include "board.h"

Command::Command(size_t entityId) : entityId(entityId){}

Command::~Command() {}


StopCommand::StopCommand(size_t entityId) : Command(entityId){}

void StopCommand::execute(ABoard& board) {
	board.execute(*this);
}


PositionalCommand::PositionalCommand(r2 position) :
	position(position)
{}

PositionalCommand::~PositionalCommand() {}


MoveCommand::MoveCommand(size_t entityId, r2 position) :
	Command(entityId),
	PositionalCommand(position)
{}

void MoveCommand::execute(ABoard& board) {
	board.execute(*this);
}


InteractionCommand::InteractionCommand(size_t targetId) :
	targetId(targetId)
{}

InteractionCommand::~InteractionCommand() {}


RepairCommand::RepairCommand(size_t entityId, size_t targetId) :
	Command(entityId),
	InteractionCommand(targetId)
{}

void RepairCommand::execute(ABoard& board) {
	board.execute(*this); // TODO
}


GatherCommand::GatherCommand(size_t entityId, size_t targetId) :
	Command(entityId),
	InteractionCommand(targetId)
{}

void GatherCommand::execute(ABoard& board) {
	board.execute(*this); // TODO
}


AttackCommand::AttackCommand(size_t entityId, size_t targetId) :
	Command(entityId),
	InteractionCommand(targetId)
{}

void AttackCommand::execute(ABoard& board) {
	board.execute(*this); // TODO
}


EntityTypeCommand::EntityTypeCommand(string entityType) :
	entityType(entityType)
{}

EntityTypeCommand::~EntityTypeCommand() {}


BuildCommand::BuildCommand(size_t entityId, r2 position, string entityType) :
	Command(entityId),
	PositionalCommand(position),
	EntityTypeCommand(entityType)
{}

void BuildCommand::execute(ABoard& board) {
	board.execute(*this); // TODO
}


CreateCommand::CreateCommand(size_t entityId, string entityType) :
	Command(entityId),
	EntityTypeCommand(entityType)
{}

void CreateCommand::execute(ABoard& board) {
	board.execute(*this); // TODO
}

