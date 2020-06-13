#pragma once
#include <ostream>

class Vector3 {
public:
	Vector3(float _x, float _y, float _z = 0) : m_x(_x), m_y(_y), m_z(_z){}

	float m_x;
	float m_y;
	float m_z;
};

inline Vector3 operator* (const Vector3& _lhs, const Vector3& _rhs) {
	const float i = (_lhs.m_y * _rhs.m_z) - (_lhs.m_z * _rhs.m_y);
	const float j = (_lhs.m_x * _rhs.m_z) - (_lhs.m_z * _rhs.m_x);
	const float k = (_lhs.m_x * _rhs.m_y) -(_lhs.m_y * _rhs.m_x);
	return { i, -j, k };
}

inline Vector3 operator* (const Vector3& _v, const float _scalar) {
	return{ _v.m_x * _scalar, _v.m_y * _scalar, _v.m_z * _scalar };
}

inline const std::ostream& operator <<(std::ostream& _os, const Vector3& _v) {
	_os << "X: " << _v.m_x << " Y: " << _v.m_y << " Z: " << _v.m_z << std::endl;
	return _os;
}



