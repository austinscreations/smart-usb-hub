#ifndef _ESP_COLOR_H_
#define _ESP_COLOR_H_

#define _ESP_COLOR_VERSION_ "1.0.0"

#include <cstddef>
#include <cstdint>
#include <type_traits>

class String;

namespace ESP_Color
{
  template <typename T>
  struct RGB
  {
    T R = T(0);
    T G = T(0);
    T B = T(0);
    T A = T(0);
  };
  using RGBf = RGB<float>;
  using RGBi = RGB<uint8_t>;

  template <typename T>
  struct HSV
  {
    T H = T(0);
    T S = T(0);
    T V = T(0);
    T A = T(0);
  };
  using HSVf = HSV<float>;
  using HSVi = HSV<uint8_t>;

  class Color final
  {
  public:
    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;
    float A = 0.0f;

    constexpr Color()
    {
    }

    Color(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 0xFFU) :
      R(red / 255.0F),
      G(green / 255.0F),
      B(blue / 255.0F),
      A(alpha / 255.0F)
    {
    }

    Color operator+(const Color& color) const
    {
      return Color(R + color.R,
        G + color.G,
        B + color.B,
        A + color.A);
    }

    Color operator-(const Color& color) const
    {
      return Color(R - color.R,
        G - color.G,
        B - color.B,
        A - color.A);
    }

    Color operator*(const float value) const
    {
      return Color(R * value,
        G * value,
        B * value,
        A * value);
    }

    Color operator/(const float value) const
    {
      return Color(R / value,
        G / value,
        B / value,
        A / value);
    }

    std::uint8_t R_Byte()
    {
      return static_cast<std::uint8_t>(R * 255.0F);
    }

    std::uint8_t G_Byte()
    {
      return static_cast<std::uint8_t>(G * 255.0F);
    }

    std::uint8_t B_Byte()
    {
      return static_cast<std::uint8_t>(B * 255.0F);
    }

    std::uint8_t A_Byte()
    {
      return static_cast<std::uint8_t>(A * 255.0F);
    }
    
     RGBi FromHsv(const float hue, const float saturation, const float value, const float alpha = 1.0)
    {
      float r, g, b;

      const auto i = static_cast<int>(hue * 6);
      const auto f = hue * 6 - i;
      const auto p = value * (1 - saturation);
      const auto q = value * (1 - f * saturation);
      const auto t = value * (1 - (1 - f) * saturation);

      switch (i % 6)
      {
      case 0:
        r = value, g = t, b = p;
        break;
      case 1:
        r = q, g = value, b = p;
        break;
      case 2:
        r = p, g = value, b = t;
        break;
      case 3:
        r = p, g = q, b = value;
        break;
      case 4:
        r = t, g = p, b = value;
        break;
      case 5:
        r = value, g = p, b = q;
        break;
      }

      RGBi RGB;
      RGB.R = (r * 255.0F);
      RGB.G = (g * 255.0F);
      RGB.B = (b * 255.0F);
      RGB.A = (alpha * 255.0F);
      return RGB;
    }

 

    HSVf ToHsv()
    {
      const auto max = threeway_max(R, G, B);
      const auto min = threeway_min(R, G, B);
      float h = 0, s, v = max;

      const auto d = max - min;
      s = max == 0 ? 0 : d / max;

      if (max == min)
      {
        h = 0;
      }
      else
      {
        if (max == R)
        {
          h = (G - B) / d + (G < B ? 6 : 0);
        }
        else if (max == G)
        {
          h = (B - R) / d + 2;
        }
        else if (max == B)
        {
          h = (R - G) / d + 4;
        }
        h /= 6;
      }

      HSVf hsv;
      hsv.H = h;
      hsv.S = s;
      hsv.V = v;
      hsv.A = A;
      return hsv;
    }

  private:
   
    static float threeway_max(float a, float b, float c)
    {
      return max(a, max(b, c));
    }

    static float threeway_min(float a, float b, float c)
    {
      return min(a, min(b, c));
    }
  };
}

#endif
