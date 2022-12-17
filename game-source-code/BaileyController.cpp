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
