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

#ifndef EAGLEEYE_MIDI_H
#define EAGLEEYE_MIDNI_H

#include "common/scummsys.h"

namespace EagleEye {

struct PlayerRecordStruct {
    char FirstName[12];
    char LastName[20];
    char FileName[9];
    uint8 searchBoxes;
    uint8 sex;
    uint8 sound;
    uint8 bookNum;
    uint8 solved[55];
};

struct drvr_desc {
    uint8 min_API_version;
    uint8 drvr_type;
    char data_suffix[4];
    void *dev_name_table;
    int default_IO;
    int default_IRQ;
    int default_DMA;
    int default_DRQ;
    int service_rate;
    uint8 display_size;
};

} // End of namespace EagleEye

#endif
