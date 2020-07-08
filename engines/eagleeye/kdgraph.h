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

#ifndef EAGLEEYE_KDGRAPH_H
#define EAGLEEYE_KDGRAPH_H

#include "common/scummsys.h"

namespace EagleEye {

struct PalEntry {
    char red;
    char green;
    char blue;
};

struct HimemDataStruct {
    uint8 num;
    uint8 han;
};

struct DBIndexStruct {
    ulong DiskAddress;
    uint8 Compressed;
    ulong Size;
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

struct BYTEREGS {
    char al;
    char ah;
    char bl;
    char bh;
    char cl;
    char ch;
    char dl;
    char dh;
};

struct WORDREGS {
    uint8 ax;
    uint8 bx;
    uint8 cx;
    uint8 dx;
    uint8 si;
    uint8 di;
    uint8 cflag;
    uint8 flags;
};

union REGS {
    WORDREGS x;
    BYTEREGS h;
};

} // End of namespace EagleEye

#endif
