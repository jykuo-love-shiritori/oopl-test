#pragma once

namespace Unity {
	template<typename T>
	struct Vector2 {
		T x, y;
		Vector2<T>() = default;
		Vector2<T>(T x, T y) : x(x), y(y) {}
		template<typename U>
		Vector2<T> operator+(const Vector2<U>& other) const {
			return Vector2<T>(
				this->x + other.x,
				this->y + other.y
			);
		};
		template<typename U>
		Vector2<T> operator-(const Vector2<U>& other) const {
			return Vector2<T>(
				this->x - other.x,
				this->y - other.y
			);
		};
		template<typename U>
		Vector2<T> operator*(const U& other) const {
			return Vector2<T>(
				this->x * other,
				this->y * other
			);
		}
		template<typename U>
		Vector2<T> operator/(const U& other) const {
			return Vector2<T>(
				this->x / other,
				this->y / other
			);
		};
		template<typename U>
		bool operator==(const Vector2<U>& other) const {
			return this->x == other.x && this->y == other.y;
		}
		template<typename U>
		Vector2<T>(Vector2<U> const & origin) {
			x = (T)origin.x;
			y = (T)origin.y;
		}
	};
	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;
}
