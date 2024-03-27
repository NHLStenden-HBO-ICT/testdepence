
#pragma once





//hier cev 2 komen

//wist je dat chat gp actueel heeft geholpem
// ja ik weet dat het raar klinkt maar ik miste ergens een ;
//het is nog wel over...kopieeerd
class vec2 // adapted from https://github.com/dcow/RayTracer
{
public:
    union {
        struct
        {
            float x, y;
        };
        float cell[2];
    };
    vec2() = default;
    vec2(float v) : x(v), y(v) {}
    vec2(float x, float y) : x(x), y(y) {}
    vec2 operator-() const { return vec2(-x, -y); }
    vec2 operator+(const vec2& addOperand) const { return vec2(x + addOperand.x, y + addOperand.y); }
    vec2 operator-(const vec2& operand) const { return vec2(x - operand.x, y - operand.y); }
    vec2 operator*(const vec2& operand) const { return vec2(x * operand.x, y * operand.y); }
    vec2 operator*(float operand) const { return vec2(x * operand, y * operand); }
    vec2 operator/(float operand) const { return vec2(x / operand, y / operand); }
    bool operator==(const vec2& operand) const { return (x == operand.x && y == operand.y); }
    bool operator!=(const vec2& operand) const { return !(*this == operand); }
    void operator-=(const vec2& a)
    {
        x -= a.x;
        y -= a.y;
    }
    void operator+=(const vec2& a)
    {
        x += a.x;
        y += a.y;
    }
    void operator*=(const vec2& a)
    {
        x *= a.x;
        y *= a.y;
    }
    void operator*=(float a)
    {
        x *= a;
        y *= a;
    }
    void operator/=(float a)
    {
        x /= a;
        y /= a;
    }
    // https://learning.oreilly.com/library/view/real-time-collision-detection/9781558607323/xhtml/c11.xhtml#:-:text=If%20the%20segment%20is%20parallel,ed%20by%20the%20following%20code.
    float length() const { return sqrtf(x * x + y * y); } // added const keyword
    float sqr_length() const { return x * x + y * y; } // added const keyword
    vec2 normalized() const // added const keyword
    {
        float r = 1.0f / length();
        return vec2(x * r, y * r);
    }
    void normalize()
    {
        float r = 1.0f / length();
        x *= r;
        y *= r;
    }
    static vec2 normalize(vec2 v) { return v.normalized(); }
    float dot(const vec2& operand) const { return x * operand.x + y * operand.y; }
}; // added semicolon at the end of class definition

