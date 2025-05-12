/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 24/04/25.                                          
**         |___/ 
*/

#ifndef COLOR_HPP
#define COLOR_HPP



class Color {
    public:
    float r, g, b;

    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color() = default;

    Color operator*(float f)        const { return {r * f,   g * f,   b * f  }; }
    Color operator*(const Color& c) const { return {r * c.r, g * c.g, b * c.b}; }
    Color operator+(const Color& c) const { return {r + c.r, g + c.g, b + c.b}; }
    Color operator+=(const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
    Color operator-=(const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }

};



#endif //COLOR_HPP
