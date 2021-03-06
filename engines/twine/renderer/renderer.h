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

#ifndef TWINE_RENDERER_H
#define TWINE_RENDERER_H

#include "common/endian.h"
#include "common/rect.h"
#include "common/scummsys.h"
#include "twine/parser/body.h"
#include "twine/twine.h"

#define POLYGONTYPE_FLAT 0
#define POLYGONTYPE_COPPER 1
#define POLYGONTYPE_BOPPER 2
#define POLYGONTYPE_MARBLE 3
#define POLYGONTYPE_TELE 4
#define POLYGONTYPE_TRAS 5
#define POLYGONTYPE_TRAME 6
#define POLYGONTYPE_GOURAUD 7
#define POLYGONTYPE_DITHER 8
#define POLYGONTYPE_UNKNOWN 9

namespace Common {
class MemoryReadStream;
}

namespace TwinE {

class TwinEEngine;

struct Vertex {
	int16 colorIndex = 0;
	int16 x = 0;
	int16 y = 0;
};

struct CmdRenderPolygon {
	uint8 renderType = 0;
	uint8 numVertices = 0;
	int16 colorIndex = 0;
	// followed by Vertex array
};

struct IMatrix3x3 {
	IVec3 row1;
	IVec3 row2;
	IVec3 row3;
};

inline IMatrix3x3 operator*(const IMatrix3x3 &matrix, const IVec3 &vec) {
	IMatrix3x3 out;
	out.row1[0] = matrix.row1[0] * vec.x;
	out.row1[1] = matrix.row1[1] * vec.x;
	out.row1[2] = matrix.row1[2] * vec.x;

	out.row2[0] = matrix.row2[0] * vec.y;
	out.row2[1] = matrix.row2[1] * vec.y;
	out.row2[2] = matrix.row2[2] * vec.y;

	out.row3[0] = matrix.row3[0] * vec.z;
	out.row3[1] = matrix.row3[1] * vec.z;
	out.row3[2] = matrix.row3[2] * vec.z;
	return out;
}

#include "common/pack-start.h"
struct BonesBaseData {
	int16 firstPoint = 0;  // data1
	int16 numOfPoints = 0; // data2
	int16 basePoint = 0;   // data3
	int16 baseElement = 0; // param
	int16 flag = 0;
	int16 rotateZ = 0;
	int16 rotateY = 0;
	int16 rotateX = 0;
	int16 unk1 = 0; // field_10
	int16 numOfShades = 0;
	int16 unk2 = 0;
	int32 field_18 = 0;
	int32 y = 0;
	int32 field_20 = 0;
	int32 field_24 = 0;
};
#include "common/pack-end.h"
static_assert(sizeof(BonesBaseData) == 38, "Unexpected elementEntry size");

class Model {
private:
	static uint8 *getBonesData(uint8 *bodyPtr) {
		uint8 *verticesBase = getData(bodyPtr);
		const int16 numVertices = READ_LE_INT16(verticesBase);
		return verticesBase + 2 + numVertices * 6;
	}

	static const uint8 *getBonesData(const uint8 *bodyPtr) {
		const uint8 *verticesBase = getData(bodyPtr);
		const int16 numVertices = READ_LE_INT16(verticesBase);
		return verticesBase + 2 + numVertices * 6;
	}

	static uint8 *getData(uint8 *bodyPtr) {
		return bodyPtr + 0x1A;
	}

	static const uint8 *getData(const uint8 *bodyPtr) {
		return bodyPtr + 0x1A;
	}
public:
	static inline bool isAnimated(const uint8 *bodyPtr) {
		const int16 bodyHeader = READ_LE_INT16(bodyPtr);
		return (bodyHeader & 2) != 0;
	}

	static const uint8 *getVerticesBaseData(const uint8 *bodyPtr) {
		return getData(bodyPtr) + 2;
	}

	static const BoneFrame *getBonesStateData(const uint8 *bodyPtr, int boneIdx) {
		assert(boneIdx <= getNumBones(bodyPtr));
		return (const BoneFrame*)((const uint8*)getBonesBaseData(bodyPtr) + 8 + (boneIdx * sizeof(BonesBaseData)));
	}

	static BoneFrame *getBonesStateData(uint8 *bodyPtr, int boneIdx) {
		assert(boneIdx <= getNumBones(bodyPtr));
		return (BoneFrame*)((uint8*)getBonesBaseData(bodyPtr) + 8 + (boneIdx * sizeof(BonesBaseData)));
	}

	static BonesBaseData *getBonesBaseData(uint8 *bodyPtr, int boneIdx = 0) {
		assert(boneIdx <= getNumBones(bodyPtr));
		return (BonesBaseData *)(getBonesData(bodyPtr) + 2 + (boneIdx * sizeof(BonesBaseData)));
	}

	static const BonesBaseData *getBonesBaseData(const uint8 *bodyPtr, int boneIdx = 0) {
		assert(boneIdx <= getNumBones(bodyPtr));
		return (const BonesBaseData *)(getBonesData(bodyPtr) + 2 + (boneIdx * sizeof(BonesBaseData)));
	}

	static int16 getNumBones(const uint8 *bodyPtr) {
		const uint8 *bonesBase = getBonesData(bodyPtr);
		return READ_LE_INT16(bonesBase);
	}

	static int16 getNumVertices(const uint8 *bodyPtr) {
		const uint8 *verticesBase = getData(bodyPtr);
		return READ_LE_INT16(verticesBase);
	}

	static const uint8 *getShadesBaseData(const uint8 *bodyPtr, int16 shadeIdx = 0) {
		assert(shadeIdx <= getNumShades(bodyPtr));
		return getShadesData(bodyPtr) + 2 + (shadeIdx * 8);
	}

	static const uint8 *getShadesData(const uint8 *bodyPtr) {
		const int16 numBones = getNumBones(bodyPtr);
		return (const uint8 *)getBonesBaseData(bodyPtr, numBones);
	}

	static int16 getNumShades(const uint8 *bodyPtr) {
		const uint8 *shadesBase = getShadesData(bodyPtr);
		return READ_LE_INT16(shadesBase);
	}

	static int16 getNumShadesBone(const uint8 *bodyPtr, int boneIdx) {
		return getBonesBaseData(bodyPtr, boneIdx)->numOfShades;
	}

	static const uint8 *getPolygonData(const uint8 *bodyPtr) {
		const uint8 *shades = getShadesBaseData(bodyPtr);
		const int16 numShades = getNumShades(bodyPtr);
		if (numShades <= 0) {
			return shades;
		}
		const int16 bones = getNumBones(bodyPtr);
		for (int16 boneIdx = 0; boneIdx < bones; ++boneIdx) {
			int16 numOfShades = getNumShadesBone(bodyPtr, boneIdx);
			shades += numOfShades * 8;
		}
		return shades;
	}
};

class Renderer {
private:
	TwinEEngine *_engine;

	struct RenderCommand {
		int16 depth = 0;
		int16 renderType = 0;
		/**
		 * Pointer to the command data
		 * @sa renderCoordinatesBuffer
		 */
		uint8 *dataPtr = nullptr;
	};

	/**
	 * @brief A render command payload for drawing a line
	 *
	 * @sa RenderCommand
	 */
	struct CmdRenderLine {
		uint8 colorIndex = 0;
		uint8 unk1 = 0;
		uint8 unk2 = 0;
		uint8 unk3 = 0;
		int16 x1 = 0;
		int16 y1 = 0;
		int16 x2 = 0;
		int16 y2 = 0;
	};

	/**
	 * @brief A render command payload for drawing a sphere
	 *
	 * @sa RenderCommand
	 */
	struct CmdRenderSphere {
		int8 colorIndex = 0;
		int16 x = 0;
		int16 y = 0;
		int16 radius = 0;
	};

#include "common/pack-start.h"
	struct pointTab {
		int16 x = 0;
		int16 y = 0;
		int16 z = 0;
	};
#include "common/pack-end.h"
	static_assert(sizeof(pointTab) == 6, "Unexpected pointTab size");

	struct polyVertexHeader {
		int16 shadeEntry = 0;
		int16 dataOffset = 0;
	};

	struct ModelData {
		pointTab computedPoints[800];
		pointTab flattenPoints[800];
		int16 shadeTable[500]{0};
	};

	ModelData _modelData;

	bool renderAnimatedModel(ModelData *modelData, const uint8 *bodyPtr, RenderCommand *renderCmds, const IVec3 &angleVec, const IVec3 &renderPos);
	void circleFill(int32 x, int32 y, int32 radius, uint8 color);
	bool renderModelElements(int32 numOfPrimitives, const uint8 *polygonPtr, RenderCommand **renderCmds, ModelData *modelData);
	void getCameraAnglePositions(int32 x, int32 y, int32 z);
	void applyRotation(IMatrix3x3 *targetMatrix, const IMatrix3x3 *currentMatrix, const IVec3 &angleVec);
	void applyPointsRotation(const pointTab *pointsPtr, int32 numPoints, pointTab *destPoints, const IMatrix3x3 *rotationMatrix);
	void processRotatedElement(IMatrix3x3 *targetMatrix, const pointTab *pointsPtr, int32 rotZ, int32 rotY, int32 rotX, const BonesBaseData *boneData, ModelData *modelData);
	void applyPointsTranslation(const pointTab *pointsPtr, int32 numPoints, pointTab *destPoints, const IMatrix3x3 *translationMatrix, const IVec3 &angleVec);
	void processTranslatedElement(IMatrix3x3 *targetMatrix, const pointTab *pointsPtr, int32 rotX, int32 rotY, int32 rotZ, const BonesBaseData *boneData, ModelData *modelData);
	void translateGroup(int32 x, int32 y, int32 z);

	IVec3 _baseTransPos;
	IVec3 _orthoProjPos;

	int32 _cameraDepthOffset = 0;
	int32 _cameraScaleY = 0;
	int32 _cameraScaleZ = 0;

	IMatrix3x3 _baseMatrix;
	IMatrix3x3 _matricesTable[30 + 1];
	IMatrix3x3 _shadeMatrix;
	IVec3 _lightPos;

	RenderCommand _renderCmds[1000];
	/**
	 * @brief Raw buffer for holding the render commands. This is a type followed by the command data
	 * that is needed to render the primitive.
	 */
	uint8 _renderCoordinatesBuffer[10000]{0};

	int32 _polyTabSize = 0;
	int16 *_polyTab = nullptr;
	int16 *_polyTab2 = nullptr;
	int16* _holomap_polytab_1_1 = nullptr;
	int16* _holomap_polytab_1_2 = nullptr;
	int16* _holomap_polytab_1_3 = nullptr;
	int16* _holomap_polytab_2_3 = nullptr;
	int16* _holomap_polytab_2_2 = nullptr;
	int16* _holomap_polytab_2_1 = nullptr;
	int16* _holomap_polytab_1_2_ptr = nullptr;
	int16* _holomap_polytab_1_3_ptr = nullptr;

	bool _isUsingOrthoProjection = false;

	void renderPolygonsCopper(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsBopper(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsFlat(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsTele(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsTras(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsTrame(uint8 *out, int vtop, int32 vsize, uint8 color) const;
	void renderPolygonsGouraud(uint8 *out, int vtop, int32 vsize) const;
	void renderPolygonsDither(uint8 *out, int vtop, int32 vsize) const;
	void renderPolygonsMarble(uint8 *out, int vtop, int32 vsize, uint8 color) const;

	void computeBoundingBox(Vertex *vertices, int32 numVertices, int &vleft, int &vright, int &vtop, int &vbottom) const;
	void computePolygons(int16 polyRenderType, const Vertex *vertices, int32 numVertices);

	const RenderCommand *depthSortRenderCommands(int32 numOfPrimitives);
	uint8 *preparePolygons(Common::MemoryReadStream &stream, int32 &numOfPrimitives, RenderCommand **renderCmds, uint8 *renderBufferPtr, ModelData *modelData);
	uint8 *prepareSpheres(Common::MemoryReadStream &stream, int32 &numOfPrimitives, RenderCommand **renderCmds, uint8 *renderBufferPtr, ModelData *modelData);
	uint8 *prepareLines(Common::MemoryReadStream &stream, int32 &numOfPrimitives, RenderCommand **renderCmds, uint8 *renderBufferPtr, ModelData *modelData);

	void baseMatrixTranspose();

	void renderHolomapPolygons(int32 top, int32 bottom);
	void computeHolomapPolygon(int32 y1, int32 x1, int32 y2, int32 x2, int16 *polygonTabPtr);
	void fillHolomapPolygons(const Vertex &vertex1, const Vertex &vertex2, const Vertex &vertex3, const Vertex &vertex4, int32 &top, int32 &bottom);

public:
	Renderer(TwinEEngine *engine);
	~Renderer();

	void init(int32 w, int32 h);

	IVec3 projPosScreen;
	IVec3 projPos;
	IVec3 baseRotPos;
	IVec3 destPos;
	IVec3 getHolomapRotation(const int32 angleX, const int32 angleY, const int32 angleZ) const;

	void setLightVector(int32 angleX, int32 angleY, int32 angleZ);
	void getBaseRotationPosition(int32 x, int32 y, int32 z);

	void renderPolygons(const CmdRenderPolygon &polygon, Vertex *vertices);

	inline int32 projectPositionOnScreen(const IVec3& pos) {
		return projectPositionOnScreen(pos.x, pos.y, pos.z);
	}

	int32 projectPositionOnScreen(int32 cX, int32 cY, int32 cZ);

	inline void projectXYPositionOnScreen(const IVec3& pos) {
		projectXYPositionOnScreen(pos.x, pos.y, pos.z);
	}
	void projectXYPositionOnScreen(int32 x,int32 y,int32 z);
	void setCameraPosition(int32 x, int32 y, int32 depthOffset, int32 scaleY, int32 scaleZ);
	void setCameraAngle(int32 transPosX, int32 transPosY, int32 transPosZ, int32 rotPosX, int32 rotPosY, int32 rotPosZ, int32 param6);
	void setBaseTranslation(int32 x, int32 y, int32 z);
	void setBaseRotation(int32 x, int32 y, int32 z, bool transpose = false);
	void setOrthoProjection(int32 x, int32 y, int32 z);

	bool renderIsoModel(int32 x, int32 y, int32 z, int32 angleX, int32 angleY, int32 angleZ, const uint8 *bodyPtr);

	/**
	 * @param angle A value of @c -1 means that the model is automatically rotated
	 */
	void renderBehaviourModel(int32 boxLeft, int32 boxTop, int32 boxRight, int32 boxBottom, int32 y, int32 angle, const uint8 *bodyPtr);
	/**
	 * @param angle A value of @c -1 means that the model is automatically rotated
	 */
	void renderBehaviourModel(const Common::Rect &rect, int32 y, int32 angle, const uint8 *bodyPtr);

	void renderInventoryItem(int32 x, int32 y, const uint8 *bodyPtr, int32 angle, int32 param);

	void renderHolomapVertices(const Vertex vertexCoordinates[3], const Vertex vertexAngles[3]);
};

} // namespace TwinE

#endif
