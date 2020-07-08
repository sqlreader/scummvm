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

#ifndef EAGLEEYE_KD_H
#define EAGLEEYE_KD_H

#include "common/scummsys.h"

namespace EagleEye {

struct InitBlockStruct {
    uint8 AnimationType;
    uint8 crimeScene;
    ClueChainStruct IntroClues;
};

struct ClueChainStruct {
    uint8 number;
    DisplayClueStruct clues[16];
};

struct DisplayClueStruct {
    uint8 picNum;
    uint8 boypicx;
    uint8 boypicy;
    uint8 girlpicx;
    uint8 girlpicy;
    uint8 boyText;
    uint8 girlText;
    uint8 boyBubble;
    uint8 girlBubble;
    uint8 boybubblex;
    uint8 boybubbley;
    uint8 girlbubblex;
    uint8 girlbubbley;
    uint8 boysound;
    uint8 girlsound;
    uint8 enableSites[5];
    uint8 addGallery[5];
    uint8 KDAdmin;
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

struct BalloonDataStruct {
    uint8 textx;
    uint8 texty;
    uint8 textw;
    uint8 iconx;
    uint8 icony;
};

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

} // End of namespace EagleEye

#endif
