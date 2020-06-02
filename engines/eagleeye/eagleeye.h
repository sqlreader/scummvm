/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef EAGLEEYE_H
#define EAGLEEYE_H

#include "engines/engine.h"
#include "common/rect.h"
#include "common/file.h"
#include "common/savefile.h"
#include "common/util.h"
#include "common/random.h"

/**
 * This is the namespace of the EagleEye engine.
 *
 * Status of this engine: In progress
 *
 * Games using this engine:
 * - Eagle Eye Mysteries
 */
namespace EagleEye {

struct EagleEyeGameDescription;

class EagleEyeEngine : public Engine {
private:
	const EagleEyeGameDescription *_gameDescription;

public:
	EagleEyeEngine(OSystem *system, const EagleEyeGameDescription *gameDesc);
	~EagleEyeEngine() override;

	Common::Platform getPlatform() const;

};
} // End of namespace EagleEye

#endif
