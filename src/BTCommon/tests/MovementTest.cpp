/*
Copyright (C) 2014-2015 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
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

#include <initializer_list>
#include "BTCommon/Grid.h"
#include "BTCommon/Hex.h"
#include "BTCommon/tests/MovementTest.h"
#include "BTCommon/tests/Utils.h"

static const int MovePointsInfinite = 99;

void MovementTest::initTestCase()
{
	QVector <Hex *> hexes;
	for (const auto &hex : std::initializer_list <HexDescriptor> {
			{BTech::Terrain::Clear, {1, 2}, 0, 0},
			{BTech::Terrain::Clear, {1, 3}, 0, 0},
			{BTech::Terrain::Clear, {2, 1}, 0, 0},
			{BTech::Terrain::Clear, {2, 2}, 0, 0},
			{BTech::Terrain::Clear, {2, 3}, 0, 0},
			{BTech::Terrain::Clear, {3, 2}, 0, 0},
			{BTech::Terrain::Clear, {3, 3}, 0, 0}
		}) {
		Hex *newHex = new Hex;
		newHex->setTerrain(hex.terrain);
		newHex->setCoordinate(hex.coord);
		newHex->setHeight(hex.height);
		hexes.append(newHex);
	}

	grid = new Grid;
	grid->initGrid(hexes);
}

void MovementTest::cleanupTestCase()
{
	delete grid;
}

void MovementTest::simpleRotationTest()
{
	const Coordinate originCoord{2, 2};
	const Position origin{originCoord, BTech::DirectionN};
	const Position destination{originCoord, BTech::DirectionSE};
	const MovementObject originObject{origin, 2, BTech::MovementAction::Walk};
	const QList <Position> expectedPath {
		{originCoord, BTech::DirectionNE},
		{originCoord, BTech::DirectionSE},
	};
	const MoveObject destinationObject{originObject, destination, 2, 0, expectedPath};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QVERIFY(possibleMoves.contains(destinationObject));
}

void MovementTest::simpleWalkTest()
{
	const Position origin{{2, 2}, BTech::DirectionS};
	const Position destination{{2, 3}, BTech::DirectionS};
	const MovementObject originObject{origin, 1, BTech::MovementAction::Walk};
	const QList <Position> expectedPath {
		{{2, 3}, BTech::DirectionS},
	};
	const MoveObject destinationObject{originObject, destination, 1, 1, expectedPath};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QVERIFY(possibleMoves.contains(destinationObject));
}

void MovementTest::walkBackwardsTest()
{
	const Position origin{{2, 2}, BTech::DirectionS};
	const Position destination{{2, 1}, BTech::DirectionS};
	const MovementObject originObject{origin, 1, BTech::MovementAction::Walk};
	const QList <Position> expectedPath {
		{{2, 1}, BTech::DirectionS},
	};
	const MoveObject destinationObject{originObject, destination, 1, 1, expectedPath};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QVERIFY(possibleMoves.contains(destinationObject));
}

void MovementTest::rotateAndWalkTest()
{
	const Position origin{{2, 2}, BTech::DirectionSW};
	const Position destination{{2, 1}, BTech::DirectionN};
	const MovementObject originObject{origin, 3, BTech::MovementAction::Walk};
	const QList <Position> expectedPath {
		{{2, 2}, BTech::DirectionNW},
		{{2, 2}, BTech::DirectionN},
		{{2, 1}, BTech::DirectionN},
	};
	const MoveObject destinationObject{originObject, destination, 3, 1, expectedPath};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QVERIFY(possibleMoves.contains(destinationObject));
}

void MovementTest::rotateAndWalkBackwardsTest()
{
	const Position origin{{2, 2}, BTech::DirectionSW};
	const Position suboptimalDestination{{2, 1}, BTech::DirectionN};
	const Position destination{{2, 1}, BTech::DirectionS};
	const MovementObject originObject{origin, 2, BTech::MovementAction::Walk};
	const QList <Position> suboptimalPath {
		{{2, 2}, BTech::DirectionNW},
		{{2, 2}, BTech::DirectionN},
		{{2, 1}, BTech::DirectionN},
	};
	const MoveObject suboptimalDestinationObject{originObject, suboptimalDestination, 3, 1, suboptimalPath};

	const QList <Position> optimalPath {
		{{2, 2}, BTech::DirectionS},
		{{2, 1}, BTech::DirectionS},
	};
	const MoveObject destinationObject{originObject, destination, 2, 1, optimalPath};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QVERIFY(possibleMoves.contains(destinationObject));
	QVERIFY(!possibleMoves.contains(suboptimalDestinationObject));
}

QTEST_APPLESS_MAIN(MovementTest);
