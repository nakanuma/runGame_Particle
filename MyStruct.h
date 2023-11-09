#pragma once

// 構造体 //

template <typename T>
struct Vector2 {
	T x;
	T y;

	// operator overload //
	// Add
	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}
	void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	// Subtract
	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}
	void operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	// Multiply
	Vector2 operator*(const Vector2& other) const {
		return { x * other.x, y * other.y };
	}
	void operator*=(const Vector2& other) {
		x *= other.x;
		y *= other.y;
	}
};