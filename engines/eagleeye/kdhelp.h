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

#ifndef EAGLEEYE_KDHELP_H
#define EAGLEEYE_KDHELP_H

#include "common/scummsys.h"

namespace EagleEye {

struct HelpStruct {
	char numPics;
    uint8 pics[2];
};

struct GrPicStruct {
    uint8 miscflags;
    uint8 height;
    uint8 width;
    int rowoff;
    int coloff;
    uint8 length;
    char *picpntr;
};

struct BalloonDataStruct {
    uint8 textx;
    uint8 texty;
    uint8 textw;
    uint8 iconx;
    uint8 icony;
};


} // End of namespace EagleEye

#endif
