#pragma once
#include <DxLib.h>

// MyDxLib.h

inline float DegToRad(float d) {
	return d / 180.0f * DX_PI;
}

inline float RadToDeg(float r) {
	return r / DX_PI * 180.0f;
}

inline VECTOR operator +(VECTOR a, VECTOR b) {
	VECTOR r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return r;
}

inline VECTOR operator -(VECTOR a, VECTOR b) {
	return VSub(a, b);
}

inline VECTOR operator *(VECTOR a, float s) {
	return VScale(a, s);
}