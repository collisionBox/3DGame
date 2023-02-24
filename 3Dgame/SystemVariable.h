#pragma once
#include "DxLib.h"

using namespace std;
const VECTOR moveModelScale = VGet(0.135f, 0.135f, 0.135f);
const VECTOR initVec = VGet(0.0f, 0.0f, 0.0f);// ベクトル初期化変数.

const float windowSizeXMin = -873.0f;
const float windowSizeXMax = windowSizeXMin * -1;
const float windowSizeZMin = -495.0f;
const float windowSizeZMax = windowSizeZMin * -1;

const int screenMagni = 120;// 画面比率にかける倍率.
const int screenSizeX = 16 * screenMagni;
const int screenSizeY = 9 * screenMagni;
