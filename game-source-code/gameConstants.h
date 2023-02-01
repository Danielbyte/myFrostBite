#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <string>
#include <list>
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <algorithm>
using std::vector;
using std::shared_ptr;
using std::string;

const auto windowWidth = 800ul;
const auto windowHeight = 600ul;

const auto bailey_height = 48.0f;
const auto bailey_width = 48.0f;

const auto ice_width = 320.0f;
const auto ice_height = 32.0f;

const auto bailey_width_offset = 24;
const auto bailey_height_offset = 24;
const auto ice_width_offset = 160;
const auto ice_height_offset = 16;

const auto igloo_height = 80;
const auto igloo_width = 256;

class CouldNotLoadPicture{};

enum class Direction {Up, Down, Left, Right,unknown};

#endif // GAMECONSTANTS_H
