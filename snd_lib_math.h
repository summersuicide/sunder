#pragma once

#include "snd_lib.h"

#define SUNDER_TAU 6.28318530718f // full turn in radians

struct sunder_v2_t
{
	f32 x = 0;
	f32 y = 0;
};

struct sunder_v3_t
{
	f32 x = 0;
	f32 y = 0;
	f32 z = 0;
};

struct sunder_v4_t
{
	f32 x = 0;
	f32 y = 0;
	f32 z = 0;
	f32 w = 0;
};

struct sunder_m4_t
{
	// memory layout (column major)
	// row	row  row	row
	// x0		y0		z0		w0	// column
	// x1		y1		z1		w1	// column
	// x2		y2		z2		w2	// column
	// x3		y3		z3		w3	// column

	// what is read by glsl
	// column	column  column	 column
	// x0			x1			x2			x3		// row
	// y0			y1			y2			y3		// row
	// z0			z1			z2			z3		// row
	// w0			w1		w2		w3	// row

	f32 x0{}, y0{}, z0{}, w0{};
	f32 x1{}, y1{}, z1{}, w1{};
	f32 x2{}, y2{}, z2{}, w2{};
	f32 x3{}, y3{}, z3{}, w3{};
};

typedef sunder_v4_t sunder_quat_t;

inline f32 sunder_square_f32(f32 f)
{
	return f * f;
}

inline f32 sunder_radians(f32 degrees)
{
	return degrees * SUNDER_CAST2(f32)0.01745329251994329576923690768489;
}

//////////////////////////////////////////////////////////////////////////////////// v2 //////////////////////////////////////////////////////////////////////////

inline sunder_v2_t sunder_v2(f32 x, f32 y)
{
	sunder_v2_t result{};
	result.x = x;
	result.y = y;

	return  result;
}

inline sunder_v2_t sunder_v2_scalar(f32 scalar)
{
	sunder_v2_t result{};
	result.x = scalar;
	result.y = scalar;

	return result;
}

inline sunder_v2_t operator+(sunder_v2_t a, sunder_v2_t b)
{
	sunder_v2_t result{};
	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return result;
}

inline sunder_v2_t operator-(sunder_v2_t a, sunder_v2_t b)
{
	sunder_v2_t result{};
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return result;
}

inline sunder_v2_t operator*(sunder_v2_t a, f32 scalar)
{
	sunder_v2_t result{};
	result.x = a.x * scalar;
	result.y = a.y * scalar;

	return result;
}

inline sunder_v2_t operator*(f32 scalar, sunder_v2_t a)
{
	sunder_v2_t result{};
	result.x = a.x * scalar;
	result.y = a.y * scalar;

	return result;
}

inline sunder_v2_t operator*(sunder_v2_t a, sunder_v2_t b)
{
	sunder_v2_t result{};
	result.x = a.x * b.x;
	result.y = a.y * b.y;

	return result;
}

inline sunder_v2_t operator/(sunder_v2_t a, f32 scalar)
{
	sunder_v2_t result{};
	result.x = a.x / scalar;
	result.y = a.y / scalar;

	return result;
}

inline sunder_v2_t operator/(f32 scalar, sunder_v2_t a)
{
	sunder_v2_t result{};
	result.x = a.x / scalar;
	result.y = a.y / scalar;

	return result;
}

inline sunder_v2_t operator/(sunder_v2_t a, sunder_v2_t b)
{
	sunder_v2_t result{};
	result.x = a.x / b.x;
	result.y = a.y / b.y;

	return result;
}

inline sunder_v2_t operator-(sunder_v2_t a)
{
	sunder_v2_t result{};
	result.x = -a.x;
	result.y = -a.y;

	return result;
}

inline f32 sunder_dot_v2(sunder_v2_t a, sunder_v2_t b)
{
	return (a.x * b.x) + (a.y * b.y);
}

inline f32 sunder_magnitude_v2(sunder_v2_t v2)
{
	return sqrt(sunder_square_f32(v2.x) + sunder_square_f32(v2.y));
}

inline sunder_v2_t sunder_normalize_v2(sunder_v2_t a)
{
	const f32 magnitude = sunder_magnitude_v2(a);

	if (magnitude < 1e-6f)
	{
		return sunder_v2_scalar(0.0f);
	}

	return a / magnitude;
}

inline f32 sunder_distance_v2(sunder_v2_t a, sunder_v2_t b)
{
	return sunder_magnitude_v2(a - b);
}

inline void sunder_log_v2(sunder_v2_t v)
{
	SUNDER_LOG("(");
	SUNDER_LOG(v.x);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.y);
	SUNDER_LOG(")");
}

//////////////////////////////////////////////////////////////////////////////////// v3 //////////////////////////////////////////////////////////////////////////

inline sunder_v3_t sunder_v3(f32 x, f32 y, f32 z)
{
	sunder_v3_t result{};
	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

inline sunder_v3_t sunder_v3_scalar(f32 scalar)
{
	sunder_v3_t result{};
	result.x = scalar;
	result.y = scalar;
	result.z = scalar;

	return result;
}

inline sunder_v3_t operator+(const sunder_v3_t& a, const sunder_v3_t& b)
{
	sunder_v3_t result{};
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

inline sunder_v3_t&  operator+=(sunder_v3_t& a, const sunder_v3_t& b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	a.z = a.z + b.z;

	return a;
}

inline sunder_v3_t operator-(const sunder_v3_t& a, const sunder_v3_t& b)
{
	sunder_v3_t result{};
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}

inline sunder_v3_t operator-(const sunder_v3_t& a)
{
	sunder_v3_t result{};
	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;

	return result;
}

inline sunder_v3_t operator*(const sunder_v3_t& a, f32 scalar)
{
	sunder_v3_t result{};
	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;

	return result;
}

inline sunder_v3_t operator*(f32 scalar, const sunder_v3_t& a)
{
	sunder_v3_t result{};
	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;

	return result;
}

inline sunder_v3_t operator*(const sunder_v3_t& a, const sunder_v3_t& b)
{
	sunder_v3_t result{};
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;

	return result;
}

inline sunder_v3_t operator/(const sunder_v3_t& a, f32 scalar)
{
	sunder_v3_t result{};
	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;

	return result;
}

inline sunder_v3_t operator/(f32 scalar, const sunder_v3_t& a)
{
	sunder_v3_t result{};
	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;

	return result;
}

inline sunder_v3_t operator/(const sunder_v3_t& a, const sunder_v3_t& b)
{
	sunder_v3_t result{};
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;

	return result;
}

inline f32 sunder_dot_v3(const sunder_v3_t& a, const sunder_v3_t& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline f32 sunder_magnitude_v3(const sunder_v3_t& a)
{
	return sqrt(sunder_square_f32(a.x) + sunder_square_f32(a.y) + sunder_square_f32(a.z));
}

inline sunder_v3_t sunder_normalize_v3(const sunder_v3_t& a)
{
	const f32 magnitude = sunder_magnitude_v3(a);

	if (magnitude < 1e-6f)
	{
		return sunder_v3_scalar(0.0f);
	}

	return a / magnitude;
}

inline f32 sunder_distance_v3(const sunder_v3_t& a, const sunder_v3_t& b)
{
	return sunder_magnitude_v3(a - b);
}

inline sunder_v3_t sunder_cross_v3(const sunder_v3_t& a, const sunder_v3_t& b)
{
	sunder_v3_t result{};
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}

inline void sunder_log_v3(const sunder_v3_t& v)
{
	SUNDER_LOG("(");
	SUNDER_LOG(v.x);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.y);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.z);
	SUNDER_LOG(")");
}

//////////////////////////////////////////////////////////////////////////////////// v4 //////////////////////////////////////////////////////////////////////////

inline sunder_v4_t sunder_v4(f32 x, f32 y, f32 z, f32 w)
{
	sunder_v4_t result{};
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}

inline void sunder_log_v4(const sunder_v4_t& v)
{
	SUNDER_LOG("(");
	SUNDER_LOG(v.x);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.y);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.z);
	SUNDER_LOG(", ");
	SUNDER_LOG(v.w);
	SUNDER_LOG(")");
}

inline sunder_v4_t operator/(const sunder_v4_t& a, f32 scalar)
{
	sunder_v4_t result{};
	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;
	result.w = a.w / scalar;

	return result;
}

inline f32 sunder_dot_v4(const sunder_v4_t& a, const sunder_v4_t& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

inline f32 sunder_magnitude_v4(const sunder_v4_t& a)
{
	return sqrt(sunder_square_f32(a.x) + sunder_square_f32(a.y) + sunder_square_f32(a.z) + sunder_square_f32(a.w));
}

inline sunder_v4_t sunder_normalize_v4(const sunder_v4_t& a)
{
	return a / sunder_magnitude_v4(a);
}

//////////////////////////////////////////////////////////////////////////////////// quat //////////////////////////////////////////////////////////////////////////

inline sunder_quat_t  sunder_quat_raw(f32 x, f32 y, f32 z, f32 w)
{
	sunder_quat_t result{};
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}

inline sunder_quat_t sunder_quat_degrees(const sunder_v3_t& axis, f32 degrees)
{
	sunder_quat_t result{};
	const f32 rad = sunder_radians(degrees);
	const f32 half_rad = rad / 2.0f;
	const f32 half_rad_sin = sin(half_rad);
	const f32 half_rad_cos = cos(half_rad);
	const sunder_v3_t normalized_axis = sunder_normalize_v3(axis);

	result.x = half_rad_sin * normalized_axis.x;
	result.y = half_rad_sin * normalized_axis.y;
	result.z = half_rad_sin * normalized_axis.z;
	result.w = half_rad_cos;

	return result;
}

inline sunder_quat_t sunder_quat_radians(const sunder_v3_t& axis, f32 radians)
{
	sunder_quat_t result{};
	const f32 half_rad = radians / 2.0f;
	const f32 half_rad_sin = sin(half_rad);
	const f32 half_rad_cos = cos(half_rad);

	result.x = half_rad_sin * axis.x;
	result.y = half_rad_sin * axis.y;
	result.z = half_rad_sin * axis.z;
	result.w = half_rad_cos;

	return result;
}

inline f32 sunder_dot_quat(const sunder_quat_t& a, const sunder_quat_t& b)
{
	return sunder_dot_v4(SUNDER_CAST2(sunder_quat_t)a, SUNDER_CAST2(sunder_quat_t)b);
}

inline sunder_quat_t sunder_normalize_quat(const sunder_quat_t& q)
{
	return SUNDER_CAST2(sunder_quat_t)sunder_normalize_v4(SUNDER_CAST2(sunder_quat_t)q);
}

inline sunder_quat_t sunder_quat_slerp(const sunder_quat_t& q0, const sunder_quat_t& q1, f32 t)
{
	f32 dot = sunder_dot_quat(q0, q1);

	// If dot < 0, negate q1 to take the shortest path
	sunder_quat_t q1_copy = q1;
	if (dot < 0.0f)
	{
		dot = -dot;
		q1_copy.x = -q1_copy.x;
		q1_copy.y = -q1_copy.y;
		q1_copy.z = -q1_copy.z;
		q1_copy.w = -q1_copy.w;
	}

	dot = fminf(fmaxf(dot, -1.0f), 1.0f); // clamp to [-1,1]

	const f32 EPSILON = 1e-6f;

	// If quaternions are close, linearly interpolate
	if (dot > 1.0f - EPSILON)
	{
		sunder_quat_t result;
		result.x = q0.x + t * (q1_copy.x - q0.x);
		result.y = q0.y + t * (q1_copy.y - q0.y);
		result.z = q0.z + t * (q1_copy.z - q0.z);
		result.w = q0.w + t * (q1_copy.w - q0.w);
		return sunder_normalize_quat(result);
	}

	// Compute angle between quaternions
	f32 theta = acosf(dot);
	f32 sin_theta = sinf(theta);

	f32 w0 = sinf((1.0f - t) * theta) / sin_theta;
	f32 w1 = sinf(t * theta) / sin_theta;

	sunder_quat_t result;
	result.x = q0.x * w0 + q1_copy.x * w1;
	result.y = q0.y * w0 + q1_copy.y * w1;
	result.z = q0.z * w0 + q1_copy.z * w1;
	result.w = q0.w * w0 + q1_copy.w * w1;

	return sunder_normalize_quat(result);
}

//////////////////////////////////////////////////////////////////////////////////// m4 //////////////////////////////////////////////////////////////////////////

inline sunder_m4_t sunder_m4(f32 x0, f32 x1, f32 x2, f32 x3,
												f32 y0, f32 y1, f32 y2, f32 y3,
												f32 z0, f32 z1, f32 z2, f32 z3, 
												f32 w0, f32 w1, f32 w2, f32 w3)
{
	sunder_m4_t m{};
	m.x0 = x0;
	m.y0 = y0;
	m.z0 = z0;
	m.w0 = w0;

	m.x1 = x1;
	m.y1 = y1;
	m.z1 = z1;
	m.w1 = w1;

	m.x2 = x2;
	m.y2 = y2;
	m.z2 = z2;
	m.w2 = w2;

	m.x3 = x3;
	m.y3 = y3;
	m.z3 = z3;
	m.w3 = w3;

	return m;
}

inline sunder_m4_t operator*(const sunder_m4_t& a, const sunder_m4_t& b)
{
	sunder_m4_t m{};
	// memory layout (column major)
	// row	row  row	row
	// x0		y0		z0		w0	// column
	// x1		y1		z1		w1	// column
	// x2		y2		z2		w2	// column
	// x3		y3		z3		w3	// column

	// what is read by glsl
	// column	column  column	 column
	// x0			x1			x2			x3		// row
	// y0			y1			y2			y3		// row
	// z0			z1			z2			z3		// row
	// w0			w1		w2		w3	// row

	// different axes with the same index form a column
	// same axes with different indices form a row

	const sunder_v4_t a_row_0 = sunder_v4(a.x0, a.x1, a.x2, a.x3);
	const sunder_v4_t a_row_1 = sunder_v4(a.y0, a.y1, a.y2, a.y3);
	const sunder_v4_t a_row_2 = sunder_v4(a.z0, a.z1, a.z2, a.z3);
	const sunder_v4_t a_row_3 = sunder_v4(a.w0, a.w1, a.w2, a.w3);

	const sunder_v4_t b_col_0 = sunder_v4(b.x0, b.y0, b.z0, b.w0);
	const sunder_v4_t b_col_1 = sunder_v4(b.x1, b.y1, b.z1, b.w1);
	const sunder_v4_t b_col_2 = sunder_v4(b.x2, b.y2, b.z2, b.w2);
	const sunder_v4_t b_col_3 = sunder_v4(b.x3, b.y3, b.z3, b.w3);

	m.x0 = sunder_dot_v4(a_row_0, b_col_0);
	m.x1 = sunder_dot_v4(a_row_0, b_col_1);
	m.x2 = sunder_dot_v4(a_row_0, b_col_2);
	m.x3 = sunder_dot_v4(a_row_0, b_col_3);

	m.y0 = sunder_dot_v4(a_row_1, b_col_0);
	m.y1 = sunder_dot_v4(a_row_1, b_col_1);
	m.y2 = sunder_dot_v4(a_row_1, b_col_2);
	m.y3 = sunder_dot_v4(a_row_1, b_col_3);

	m.z0 = sunder_dot_v4(a_row_2, b_col_0);
	m.z1 = sunder_dot_v4(a_row_2, b_col_1);
	m.z2 = sunder_dot_v4(a_row_2, b_col_2);
	m.z3 = sunder_dot_v4(a_row_2, b_col_3);

	m.w0 = sunder_dot_v4(a_row_3, b_col_0);
	m.w1 = sunder_dot_v4(a_row_3, b_col_1);
	m.w2 = sunder_dot_v4(a_row_3, b_col_2);
	m.w3 = sunder_dot_v4(a_row_3, b_col_3);

	return m;
}

inline sunder_m4_t sunder_m4_identity()
{
	return sunder_m4(1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f);
}

inline sunder_m4_t sunder_m4_translation(const sunder_v3_t& position)
{
	return sunder_m4(1.0f, 0.0f, 0.0f, position.x,
								0.0f, 1.0f, 0.0f, position.y,
								0.0f, 0.0f, 1.0f, position.z,
								0.0f, 0.0f, 0.0f, 1.0f);
}

inline sunder_m4_t sunder_m4_rotation(const sunder_quat_t& q)
{
	const f32 xx = q.x * q.x;
	const f32 yy = q.y * q.y;
	const f32 zz = q.z * q.z;
	const f32 xy = q.x * q.y;
	const f32 xz = q.x * q.z;
	const f32 yz = q.y * q.z;
	const f32 wx = q.w * q.x;
	const f32 wy = q.w * q.y;
	const f32 wz = q.w * q.z;

	return sunder_m4(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy), 0.0f,
		2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx), 0.0f,
		2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f,
		0.0f,					 0.0f,					   0.0f,							  1.0f
	);
}

inline sunder_m4_t sunder_m4_scale(const sunder_v3_t& scale)
{
	return sunder_m4(scale.x, 0.0f,		  0.0f,	  0.0f,
								0.0f,		 scale.y,  0.0f,      0.0f,
								0.0f,		 0.0f,		  scale.z,  0.0f,
								0.0f,		 0.0f,		  0.0f,      1.0f);
}

inline sunder_v4_t operator*(const sunder_m4_t& m, const sunder_v4_t& v4)
{
	sunder_v4_t result{};

	const sunder_v4_t m_row_0 = sunder_v4(m.x0, m.x1, m.x2, m.x3);
	const sunder_v4_t m_row_1 = sunder_v4(m.y0, m.y1, m.y2, m.y3);
	const sunder_v4_t m_row_2 = sunder_v4(m.z0, m.z1, m.z2, m.z3);
	const sunder_v4_t m_row_3 = sunder_v4(m.w0, m.w1, m.w2, m.w3);

	result.x = sunder_dot_v4(m_row_0, v4);
	result.y = sunder_dot_v4(m_row_1, v4);
	result.z = sunder_dot_v4(m_row_2, v4);
	result.w = sunder_dot_v4(m_row_3, v4);

	return result;
}

inline b32 sunder_m4_is_rigid(const sunder_m4_t& m)
{
	const f32 epsilon = 1e-3f;

	const sunder_v3_t right = { m.x0, m.y0, m.z0 };
	const sunder_v3_t up = { m.x1, m.y1, m.z1 };
	const sunder_v3_t forward = { m.x2, m.y2, m.z2 };

	const f32 dot_ru = sunder_dot_v3(right, up);
	const f32 dot_rf = sunder_dot_v3(right, forward);
	const f32 dot_uf = sunder_dot_v3(up, forward);

	const f32 len_r = sunder_magnitude_v3(right);
	const f32 len_u = sunder_magnitude_v3(up);
	const f32 len_f = sunder_magnitude_v3(forward);

	const b32 ortho = (fabs(dot_ru) < epsilon &&
		fabs(dot_rf) < epsilon &&
		fabs(dot_uf) < epsilon);

	const b32 unit = (fabs(len_r - 1.0f) < epsilon &&
		fabs(len_u - 1.0f) < epsilon &&
		fabs(len_f - 1.0f) < epsilon);

	const b32 proper_last_col = (fabs(m.w3 - 1.0f) < epsilon);

	return ortho && unit && proper_last_col;
}

inline sunder_m4_t sunder_m4_inverse_rigid(const sunder_m4_t& m)
{
	sunder_m4_t r{};
	r.x0 = m.x0; r.x1 = m.y0; r.x2 = m.z0;
	r.y0 = m.x1; r.y1 = m.y1; r.y2 = m.z1;
	r.z0 = m.x2; r.z1 = m.y2; r.z2 = m.z2;

	const f32 tx = m.x3;
	const f32 ty = m.y3;
	const f32 tz = m.z3;

	r.x3 = -(r.x0 * tx + r.x1 * ty + r.x2 * tz);
	r.y3 = -(r.y0 * tx + r.y1 * ty + r.y2 * tz);
	r.z3 = -(r.z0 * tx + r.z1 * ty + r.z2 * tz);

	r.w0 = 0.0f;
	r.w1 = 0.0f;
	r.w2 = 0.0f;
	r.w3 = 1.0f;

	return r;
}

inline sunder_m4_t sunder_m4_inverse(const sunder_m4_t& m)
{
	sunder_m4_t out{};

	if (sunder_m4_is_rigid(m))
	{
		return sunder_m4_inverse_rigid(m);
	}

	const f32* a = &m.x0;
	f32* inv = &out.x0;

    inv[0] =  a[5]*a[10]*a[15] - a[5]*a[11]*a[14] - a[9]*a[6]*a[15] 
            + a[9]*a[7]*a[14] + a[13]*a[6]*a[11] - a[13]*a[7]*a[10];

    inv[4] = -a[4]*a[10]*a[15] + a[4]*a[11]*a[14] + a[8]*a[6]*a[15] 
            - a[8]*a[7]*a[14] - a[12]*a[6]*a[11] + a[12]*a[7]*a[10];

    inv[8] =  a[4]*a[9]*a[15] - a[4]*a[11]*a[13] - a[8]*a[5]*a[15] 
            + a[8]*a[7]*a[13] + a[12]*a[5]*a[11] - a[12]*a[7]*a[9];

    inv[12] = -a[4]*a[9]*a[14] + a[4]*a[10]*a[13] + a[8]*a[5]*a[14] 
             - a[8]*a[6]*a[13] - a[12]*a[5]*a[10] + a[12]*a[6]*a[9];

    inv[1] = -a[1]*a[10]*a[15] + a[1]*a[11]*a[14] + a[9]*a[2]*a[15] 
            - a[9]*a[3]*a[14] - a[13]*a[2]*a[11] + a[13]*a[3]*a[10];

    inv[5] =  a[0]*a[10]*a[15] - a[0]*a[11]*a[14] - a[8]*a[2]*a[15] 
            + a[8]*a[3]*a[14] + a[12]*a[2]*a[11] - a[12]*a[3]*a[10];

    inv[9] = -a[0]*a[9]*a[15] + a[0]*a[11]*a[13] + a[8]*a[1]*a[15] 
            - a[8]*a[3]*a[13] - a[12]*a[1]*a[11] + a[12]*a[3]*a[9];

    inv[13] = a[0]*a[9]*a[14] - a[0]*a[10]*a[13] - a[8]*a[1]*a[14] 
             + a[8]*a[2]*a[13] + a[12]*a[1]*a[10] - a[12]*a[2]*a[9];

    inv[2] =  a[1]*a[6]*a[15] - a[1]*a[7]*a[14] - a[5]*a[2]*a[15] 
            + a[5]*a[3]*a[14] + a[13]*a[2]*a[7] - a[13]*a[3]*a[6];

    inv[6] = -a[0]*a[6]*a[15] + a[0]*a[7]*a[14] + a[4]*a[2]*a[15] 
            - a[4]*a[3]*a[14] - a[12]*a[2]*a[7] + a[12]*a[3]*a[6];

    inv[10] = a[0]*a[5]*a[15] - a[0]*a[7]*a[13] - a[4]*a[1]*a[15] 
             + a[4]*a[3]*a[13] + a[12]*a[1]*a[7] - a[12]*a[3]*a[5];

    inv[14] = -a[0]*a[5]*a[14] + a[0]*a[6]*a[13] + a[4]*a[1]*a[14] 
             - a[4]*a[2]*a[13] - a[12]*a[1]*a[6] + a[12]*a[2]*a[5];

    inv[3] = -a[1]*a[6]*a[11] + a[1]*a[7]*a[10] + a[5]*a[2]*a[11] 
            - a[5]*a[3]*a[10] - a[9]*a[2]*a[7] + a[9]*a[3]*a[6];

    inv[7] =  a[0]*a[6]*a[11] - a[0]*a[7]*a[10] - a[4]*a[2]*a[11] 
            + a[4]*a[3]*a[10] + a[8]*a[2]*a[7] - a[8]*a[3]*a[6];

    inv[11] = -a[0]*a[5]*a[11] + a[0]*a[7]*a[9] + a[4]*a[1]*a[11] 
             - a[4]*a[3]*a[9] - a[8]*a[1]*a[7] + a[8]*a[3]*a[5];

    inv[15] = a[0]*a[5]*a[10] - a[0]*a[6]*a[9] - a[4]*a[1]*a[10] 
             + a[4]*a[2]*a[9] + a[8]*a[1]*a[6] - a[8]*a[2]*a[5];

    f32 det = a[0]*inv[0] + a[1]*inv[4] + a[2]*inv[8] + a[3]*inv[12];

	if (fabs(det) < 1e-8f)
	{
		return sunder_m4_identity();
	}

    det = 1.0f / det;
	for (int i = 0; i < 16; ++i)
	{
		inv[i] *= det;
	}

	return out;
}

inline sunder_m4_t sunder_m4_transpose(const sunder_m4_t& m)
{
	return sunder_m4(m.x0, m.y0, m.z0, m.w0,
								m.x1, m.y1, m.z1, m.w1,
								m.x2, m.y2, m.z2, m.w2,
								m.x3, m.y3, m.z3, m.w3);
}

inline sunder_m4_t sunder_m4_perspective(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane)
{
	const f32 fov_radians = sunder_radians(fov);

	const f32 f = 1.0f / tanf(fov_radians * 0.5f);
	const f32 nf = 1.0f / (near_plane - far_plane);

	sunder_m4_t m{};
	m.x0 = f / aspect_ratio;
	m.y1 = -f; // vulkan y flip
	m.z2 = far_plane * nf;
	m.z3 = (far_plane * near_plane) * nf;
	m.w2 = -1.0f; // vulkan [0, 1] depth values
	m.w3 = 0.0f;

	return m;
}

inline sunder_m4_t sunder_m4_orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_plane, f32 far_plane)
{
	sunder_m4_t m{};
	m.x0 = 2.0f / (right - left);
	m.y1 = -2.0f / (top - bottom); // y flip for Vulkan
	m.z2 = 1.0f / (near_plane - far_plane); // depth [0, 1]

	m.x3 = -(right + left) / (right - left);
	m.y3 = (top + bottom) / (top - bottom);
	m.z3 = -near_plane / (far_plane - near_plane);
	m.w3 = 1.0f;

	return m;
}

inline sunder_m4_t sunder_m4_look_at(const sunder_v3_t& eye, const sunder_v3_t& target, const sunder_v3_t& up)
{
	sunder_m4_t m{};

	sunder_v3_t f = sunder_normalize_v3(target - eye);
	sunder_v3_t r = sunder_normalize_v3(sunder_cross_v3(f, up));
	sunder_v3_t u = sunder_cross_v3(r, f);

	// memory layout (column major)
	// row	row  row	row
	// x0		y0		z0		w0	// column
	// x1		y1		z1		w1	// column
	// x2		y2		z2		w2	// column
	// x3		y3		z3		w3	// column

		// what is read by glsl
	// column	column  column	 column
	// x0			x1			x2			x3		// row
	// y0			y1			y2			y3		// row
	// z0			z1			z2			z3		// row
	// w0			w1		w2		w3	// row

	// different axes with the same index form a column
	// same axes with different indices form a row

	m.x0 = r.x;
	m.x1 = r.y;
	m.x2 = r.z;
	m.x3 = -sunder_dot_v3(r, eye);

	m.y0 = u.x;
	m.y1 = u.y;
	m.y2 = u.z;
	m.y3 = -sunder_dot_v3(u, eye);

	m.z0 = -f.x;
	m.z1 = -f.y;
	m.z2 = -f.z;
	m.z3 = sunder_dot_v3(f, eye);

	m.w0 = 0.0f;
	m.w1 = 0.0f;
	m.w2 = 0.0f;
	m.w3 = 1.0f;

	return m;
}

inline void sunder_log_m4(const sunder_m4_t& m)
{
	SUNDER_LOG("\n");

	SUNDER_LOG(m.x0);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.x1);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.x2);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.x3);
	SUNDER_LOG("\n");

	SUNDER_LOG(m.y0);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.y1);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.y2);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.y3);
	SUNDER_LOG("\n");

	SUNDER_LOG(m.z0);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.z1);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.z2);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.z3);
	SUNDER_LOG("\n");

	SUNDER_LOG(m.w0);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.w1);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.w2);
	SUNDER_LOG(" | ");
	SUNDER_LOG(m.w3);
	SUNDER_LOG("\n");
}
