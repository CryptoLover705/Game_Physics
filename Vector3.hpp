#include <initializer_list>
#include <cmath>

class Vector3
{
    public:
        double v[3];
    public:
        Vector3();
        Vector3(double x, double y, double z);
        double &operator[](int index);
        double operator[](int index) const;
        Vector3 operator*(double scale) const;
        Vector3 operator/(double scale) const;
        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator-() const;
        const Vector3 &operator*=(double scale);
        const Vector3 &operator/=(double scale);
        const Vector3 &operator+=(const Vector3 &other);
        const Vector3 &operator-=(const Vector3 &other);
        double Magnitude() const;
        Vector3 Normalize() const;
        double Dot(const Vector3 &other) const;
        Vector3 Cross(const Vector3 &other) const;
		Vector3 Project(const Vector3 &other) const;
};
Vector3::Vector3() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}
Vector3::Vector3(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
double &Vector3::operator[](int index) {
    return v[index];
}
double Vector3::operator[](int index) const {
    return v[index];
}
Vector3 Vector3::operator*(double scale) const {
    return Vector3(v[0] * scale, v[1] * scale, v[2] * scale);
}
Vector3 Vector3::operator/(double scale) const {
    return Vector3(v[0] / scale, v[1] / scale, v[2] / scale);
}
Vector3 Vector3::operator+(const Vector3 &other)  const{
    return Vector3(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}
Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}
Vector3 Vector3::operator-() const {
    return Vector3(-v[0], -v[1], -v[2]);
}
const Vector3 &Vector3::operator*=(double scale) {
    v[0] *= scale;
    v[1] *= scale;
    v[2] *= scale;
    return *this;
}
const Vector3 &Vector3::operator/=(double scale) {
    v[0] /= scale;
    v[1] /= scale;
    v[2] /= scale;
    return *this;
}
const Vector3 &Vector3::operator+=(const Vector3 &other) {
    v[0] += other.v[0];
    v[1] += other.v[1];
    v[2] += other.v[2];
    return *this;
}
const Vector3 &Vector3::operator-=(const Vector3 &other) {
    v[0] -= other.v[0];
    v[1] -= other.v[1];
    v[2] -= other.v[2];
    return *this;
}
double Vector3::Magnitude() const {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

Vector3 Vector3::Normalize() const {
    double m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return Vector3(v[0] / m, v[1] / m, v[2] / m);
}
double Vector3::Dot(const Vector3 &other) const {
    return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}
Vector3 Vector3::Cross(const Vector3 &other) const {
    return Vector3(v[1] * other.v[2] - v[2] * other.v[1],
                 v[2] * other.v[0] - v[0] * other.v[2],
                 v[0] * other.v[1] - v[1] * other.v[0]);
}
Vector3 Vector3::Project(const Vector3 &other) const {
	// a.n(b) n(b) = |a|cos(theta) n(b);
	return other.Normalize() * Dot(other.Normalize());
}
