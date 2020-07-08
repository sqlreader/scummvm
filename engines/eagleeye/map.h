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

#ifndef EAGLEEYE_MAP_H
#define EAGLEEYE_MAP_H

#include "common/scummsys.h"

namespace EagleEye {

struct MapButtonStruct {
    uint8 buttonNum;
    uint8 buttonSite;
    uint8 mapx;
    uint8 mapy;
    uint8 markerx;
    uint8 markery;
    uint8 scene;
};

struct AniObj {
    uint8 active;
    uint8 num_pics;
    uint8 last_pic;
    uint8 restart;
    uint8 priority;
    uint8 x;
    uint8 y;
    uint8 *sequence;
    GrPicStruct *pics;
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

struct Rect {
    uint8 x1;
    uint8 y1;
    uint8 x2;
    uint8 y2;
};

} // End of namespace EagleEye

#endif
