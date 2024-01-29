#pragma once
//-----------------------------------------------
#include <cstdint>
#include <utility>
#include <variant>
#include <vector>
#include <string>
//-----------------------------------------------
/*
 * @file Primitives.h
 * @brief Structures describing geometrics primitives
 * */
//-----------------------------------------------
typedef std::pair<int, int> Coordinate;
//-----------------------------------------------
struct Color
{
  uint8_t _r;
  uint8_t _g;
  uint8_t _b;
  uint8_t _a;
};
//-----------------------------------------------
struct ColorProperty
{
  Color _stroke;
  Color _fill;
};
//-----------------------------------------------
struct Rectangle
{
  Coordinate _pivot;
  float      _width;
  float      _height;
  Color      _colors;
};
//-----------------------------------------------
struct Circle
{
  Coordinate _pivot;
  float      _radius;
  Color      _colors;
};
//-----------------------------------------------
struct Line
{
  Coordinate _pivot;
  Coordinate _end;
  Color      _colors;
};
//-----------------------------------------------
typedef std::variant<Rectangle, Circle, Line> Primitive;
typedef std::vector<Primitive> VecPrimitives;
//-----------------------------------------------
