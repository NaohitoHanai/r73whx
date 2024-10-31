#pragma once
// myDxLib.h
#include <DxLib.h>

// —ˆTÚ‚µ‚­à–¾‚·‚é
inline VECTOR operator +(VECTOR v1, VECTOR v2) {
	return VAdd(v1, v2);
}

inline VECTOR operator +=(VECTOR& v1, VECTOR v2) {
	v1 = VAdd(v1, v2);
	return v1;
}

inline VECTOR operator *(VECTOR v1, MATRIX m) {
	return VTransform(v1, m);
}
