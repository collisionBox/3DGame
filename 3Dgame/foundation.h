#pragma once
#include "DxLib.h"
#include <string>
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "Math.h"

using namespace std;
const VECTOR moveModelScale = VGet(0.135f, 0.135f, 0.135f);
const VECTOR initVec = VGet(0.0f, 0.0f, 0.0f);// ベクトル初期化変数.

const float windowSizeXMin = -873.0f;
const float windowSizeXMax = windowSizeXMin * -1;
const float windowSizeZMin = -495.0f;
const float windowSizeZMax = windowSizeZMin * -1;
