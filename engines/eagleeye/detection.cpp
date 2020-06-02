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

#include "base/plugins.h"

#include "engines/advancedDetector.h"
#include "engines/engine.h"
#include "common/savefile.h"
#include "common/system.h"
#include "common/translation.h"
#include "eagleeye/eagleeye.h"

namespace EagleEye {

struct EagleEyeGameDescription {
	ADGameDescription desc;

	uint32 features;
};

Common::Platform EagleEyeEngine::getPlatform() const { return _gameDescription->desc.platform; }

} // End of namespace EagleEye

static const PlainGameDescriptor eagleeyeGames[] = {
	{"eagleeye", "Eagle Eye Mysteries"},
	{0, 0}
};

namespace EagleEye {

static const EagleEyeGameDescription gameDescriptions[] = {
	{
		{
			"eageleeye",
			"VGA",
			AD_ENTRY1("TBD", ""),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO0()

		}
	},

	{ AD_TABLE_END_MARKER, 0 }
};

} // End of namespace EagleEye

class EagleEyeMetaEngine : public AdvancedMetaEngine {
public:
	EagleEyeMetaEngine() : AdvancedMetaEngine(EagleEye::gameDescriptions, sizeof(EagleEye::EagleEyeGameDescription), eagleeyeGames
			) {
		_md5Bytes = 1024;
	}

	const char *getEngineId() const override {
		return "eagleeye";
	}

	const char *getName() const override {
		return "Eagle Eye Mysteries";
	}

	const char *getOriginalCopyright() const override {
		return "(C) 1993 Electronic Arts, Inc.";
	}

	bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const override;
};

bool EagleEyeMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const EagleEye::EagleEyeGameDescription *gd = (const EagleEye::EagleEyeGameDescription *)desc;
	if (gd) {
		*engine = new EagleEye::EagleEyeEngine(syst, gd);
	}
	return gd != 0;
}

#if PLUGIN_ENABLED_DYNAMIC(EAGLEEYE)
	REGISTER_PLUGIN_DYNAMIC(EAGLEEYE, PLUGIN_TYPE_ENGINE, EagleEyeMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(EAGLEEYE, PLUGIN_TYPE_ENGINE, EagleEyeMetaEngine);
#endif
