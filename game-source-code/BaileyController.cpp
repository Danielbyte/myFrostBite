#include "BaileyController.h"

BaileyController::BaileyController():
	frame_counter{0}
{}

void BaileyController::update_bailey(vector2f& prev_position, bool& bailey_moving,
	const float& current_x_pos, const float& current_y_pos)
{
	if (prev_position.x == current_x_pos && prev_position.y == current_y_pos)
	{
		bailey_moving = false;
	}
	else
	{
		prev_position.x = current_x_pos;
		prev_position.y = current_y_pos;
		bailey_moving = true;
	}
}

void BaileyController::reset_frame()
{
	frame_counter = 0;
}

int BaileyController::get_frame() const
{
	return frame_counter;
}

void BaileyController::increment_frame()
{
	++frame_counter;
}

void BaileyController::animate_bailey(Bailey& bailey_object, Sprite& bailey_sprite)
{
	auto right = bailey_object.get_if_moving_right();
	auto left = bailey_object.get_if_moving_left();
	auto at_safe_zone = bailey_object.get_if_bailey_in_safe_zone();

	if (right && at_safe_zone)
	{
		increment_frame();
		if (frame_counter == 1)
		{
			bailey_texture.loadFromFile("resources/bailey.png");
			bailey_sprite.setTexture(bailey_texture);
		}
		else if (frame_counter == 2)
		{
			bailey_texture.loadFromFile("resources/bailey1.png");
			bailey_sprite.setTexture(bailey_texture);
			reset_frame();
		}

	}
}
