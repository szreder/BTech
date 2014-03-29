#ifndef HEX_H
#define HEX_H

#include <QtWidgets>
#include "BTCommon/AttackObject.h"
#include "BTCommon/MechEntity.h"
#include "BTCommon/MoveObject.h"
#include "BTCommon/Position.h"
#include "BTCommon/Weapon.h"

namespace BTech {
	static const int NODES_NUMBER = 6;
}

/**
 * \class Hex
 * This is a game-system representation of a hex.
 * Inheriting QObject is required, so the children can be killed, when the Hex is destroyed.
 * In order to make instances of this class work properly, static function setVisibilityManager require to be called.
 */
class Hex : public QObject, public MechPosition
{

public:
	Hex();
	virtual ~Hex();

	static void setVisibilityManager(const VisibilityManager *manager);

	void setNeighbour(Direction direction, Hex *neighbour);
	Hex * getNeighbour(Direction direction) const;
	void setNumber(int number);
	int getNumber() const;
	void setPoint(const QPoint &point);
	QPoint getPoint() const;

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
	static const VisibilityManager *visibilityManager;

	Hex *neighbour[BTech::NODES_NUMBER];
	int number;
	QPoint point;

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
