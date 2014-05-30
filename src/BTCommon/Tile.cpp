/*
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

#include "BTCommon/Tile.h"
#include "BTCommon/TileManager.h"

Tile::Tile(QImage image)
{
	Q_ASSERT(image.height() == TileSize && image.width() % TileSize == 0);

	int frames = image.width() / TileSize;
	for (int i = 0; i < frames; ++i)
		frames_.push_back(image.copy(i * TileSize, 0, TileSize, TileSize));
}

QImage Tile::currentFrame() const
{
	return frames_[TileManager::currentFrame() % frames()];
}

QString Tile::fileName() const
{
	return TileManager::fileName(this);
}

QImage Tile::frame(unsigned int frame) const
{
	return frames_[frame % frames()];
}

int Tile::frames() const
{
	return frames_.count();
}
