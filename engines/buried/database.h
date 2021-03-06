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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BURIED_DATABASE_H
#define BURIED_DATABASE_H

namespace Common {
class WinResources;
class String;
}

namespace Graphics {
struct WinCursorGroup;
}

namespace Buried {

/**
 * Simple wrapper class around the game's binaries to load
 * data between them (without needing too much code different
 * between Win16 and Win32 versions).
 */
class Database {
public:
	virtual ~Database() {}

	virtual bool load(const Common::String &fileName) = 0;
	virtual void close() = 0;

	virtual Common::String loadString(uint32 stringID) = 0;
	virtual Common::SeekableReadStream *getBitmapStream(uint32 bitmapID) = 0;
	virtual Graphics::WinCursorGroup *getCursorGroup(uint32 cursorGroupID) = 0;
	virtual Common::SeekableReadStream *getResourceStream(const Common::String &resourceType, uint32 resourceID) = 0;
	virtual uint32 getVersion() = 0;
};

/**
 * A database loaded from an NE executable/library
 */
class DatabaseNE : public Database {
public:
	DatabaseNE();
	virtual ~DatabaseNE();

	virtual bool load(const Common::String &fileName);
	void close();

	Common::String loadString(uint32 stringID);
	Common::SeekableReadStream *getBitmapStream(uint32 bitmapID);
	Graphics::WinCursorGroup *getCursorGroup(uint32 cursorGroupID);
	Common::SeekableReadStream *getResourceStream(const Common::String &resourceType, uint32 resourceID);
	uint32 getVersion();

protected:
	Common::WinResources *_exe;
};

/**
 * A database loaded from a compressed NE executable/library
 */
class DatabaseNECompressed : public DatabaseNE {
public:
	bool load(const Common::String &fileName);
};

class DatabasePE : public Database {
public:
	DatabasePE();
	~DatabasePE();

	bool load(const Common::String &fileName);
	void close();

	Common::String loadString(uint32 stringID);
	Common::SeekableReadStream *getBitmapStream(uint32 bitmapID);
	Graphics::WinCursorGroup *getCursorGroup(uint32 cursorGroupID);
	Common::SeekableReadStream *getResourceStream(const Common::String &resourceType, uint32 resourceID);
	uint32 getVersion();

private:
	Common::WinResources *_exe;
};

} // End of namespace Buried

#endif
