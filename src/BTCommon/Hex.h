/*
Copyright (C) 2014 by Piotr Majcherczyk <fynxor [at] gmail [dot] com>
Copyright (C) 2014 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
This file is part of BTech Project.

	BTech Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	BTech Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with BTech.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEX_H
#define HEX_H

#include <QtWidgets>
#include "BTCommon/MoveObject.h"
#include "BTCommon/Position.h"

class AttackObject;
class MechEntity;

namespace BTech {
	static const int NODES_NUMBER = 6;
}

/**
 * \class Hex
 * This is a game-system representation of a hex.
 * Inheriting QObject is required, so the children can be killed, when the Hex is destroyed.
 */
class Hex : public QObject, public MechPosition
{

public:
	Hex();
	virtual ~Hex();

	void setCoordinate(const Coordinate &coordinate);
	Coordinate getCoordinate() const;
	void setNeighbour(Direction direction, Hex *neighbour);
	Hex * getNeighbour(Direction direction) const;

	void setHeight(int height);
	int getHeight() const;
	void setDepth(int depth);
	int getDepth() const;
	void setTerrain(BTech::Terrain terrain);
	BTech::Terrain getTerrain() const;
	int travelPenalty() const;

	void setMech(MechEntity *mech);
	MechEntity * getMech() const;
	void removeMech();

	void setMoveObject(const MoveObject &move);
	void setMoveObject(int areaNumber);
	MoveObject getMoveObject(Direction direction) const;
	MoveObject getMoveObject() const;
	bool hasMoveObject() const;
	void removeMoveObject();
	void setAttackObject(const AttackObject &attack);
	AttackObject getAttackObject() const;
	bool hasAttackObject() const;
	void removeAttackObject();
	bool isAttackable() const;

	void clear();

	friend QDataStream & operator << (QDataStream &out, const Hex &hex);
	friend QDataStream & operator >> (QDataStream &in, Hex &hex);

private:
	Hex *neighbour[BTech::NODES_NUMBER];
	Coordinate coordinate;

	void initNeighbours();  /**< Sets all neighbours to nullptr. */

	int height;
	int depth;
	BTech::Terrain terrain;

	MechEntity *mech;

	int currentMovementObjectNumber;
	MoveObject moveObject[Direction::NUMBER];
	bool attackable;

	void clearData();
};

#endif // HEX_H
