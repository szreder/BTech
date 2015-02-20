/*
Copyright (C) 2015 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
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
#include "BTCommon/tests/TerrainTest.h"
#include "BTCommon/tests/Utils.h"

void TerrainTest::initTestCase()
{
	QVector <Hex *> hexes;
	for (const auto &hex : std::initializer_list <HexDescriptor> {
			{BTech::Terrain::Water,      {1, 2}, 0, 0},
			{BTech::Terrain::HeavyWoods, {2, 1}, 0, 0},
			{BTech::Terrain::Clear,      {2, 2}, 0, 0},
			{BTech::Terrain::Clear,      {2, 3}, 0, 0},
			{BTech::Terrain::LightWoods, {3, 2}, 0, 0},
			{BTech::Terrain::Clear,      {3, 3}, 2, 0}
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

void TerrainTest::cleanupTestCase()
{
	delete grid;
}

void TerrainTest::terrainMovementTest()
{
	const Position origin{{2, 3}, BTech::DirectionN};
	const MovementObject originObject{origin, 4, BTech::MovementAction::Walk};

	const QList <MoveObject> possibleMoves = grid->getWalkRange(originObject);

	QFETCH(Position, destination);
	QFETCH(int, distance);
	QFETCH(QList <Position>, path);

	const MoveObject destinationObject{originObject, destination, 4, distance, path};
	QVERIFY(possibleMoves.contains(destinationObject));
}

void TerrainTest::terrainMovementTest_data()
{
	QTest::addColumn<Position>("destination");
	QTest::addColumn<int>("distance");
	QTest::addColumn<QList <Position> >("path");

	QTest::newRow("heavy woods") << Position{{2, 1}, BTech::DirectionN} << 2 << QList <Position>{
		{{2, 2}, BTech::DirectionN},
		{{2, 1}, BTech::DirectionN},
	};

	QTest::newRow("light woods") << Position{{3, 2}, BTech::DirectionNE} << 2 << QList <Position>{
		{{2, 2}, BTech::DirectionN},
		{{2, 2}, BTech::DirectionNE},
		{{3, 2}, BTech::DirectionNE},
	};

	QTest::newRow("water") << Position{{1, 2}, BTech::DirectionNW} << 2 << QList <Position>{
		{{2, 2}, BTech::DirectionN},
		{{2, 2}, BTech::DirectionNW},
		{{1, 2}, BTech::DirectionNW},
	};

	QTest::newRow("climb") << Position{{3, 3}, BTech::DirectionNE} << 1 << QList <Position>{
		{{2, 3}, BTech::DirectionNE},
		{{3, 3}, BTech::DirectionNE},
	};
}

QTEST_APPLESS_MAIN(TerrainTest);
