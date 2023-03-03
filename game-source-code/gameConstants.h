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
#include <cmath>
#include <random>
#include <queue>

using std::vector;
using std::shared_ptr;
using std::string;
using std::queue;

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

const auto bear_with = 85.0f;
const auto bear_height = 47.0f;

const auto crab_height = 22.0f;
const auto crab_width = 42.0f;

const auto fish_height = 19.0f;
const auto fish_width = 43.0f;

const auto clamp_height = 22.0f;
const auto clamp_width = 42.0f;

const auto bird_height = 38.0f;
const auto bird_width = 38.0f;

const auto ice_patch_width = 87.0f;
const auto water_patch_width = 29.5f;

class CouldNotLoadPicture{};

enum class Direction {Up, Down, Left, Right,unknown};
enum class Animal {crabs, clamps, birds, fish, none};

enum animals
{
	crab_ = 1,
	clamp_ = 2,
	bird_ = 3,
	fish_ = 4,
};

enum sides
{
	right = 1,
	left = 2,
};

#endif // GAMECONSTANTS_H
