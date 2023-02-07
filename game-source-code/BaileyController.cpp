#include "BaileyController.h"

BaileyController::BaileyController():
	frame_counter{0}
{
	load_textures();
}

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

void BaileyController::load_textures()
{
	//load textures once for optimization
	bailey_texture1.loadFromFile("resources/bailey.png");
	bailey_texture2.loadFromFile("resources/bailey1.png");
	bailey_texture3.loadFromFile("resources/bailey_left.png");
	bailey_texture4.loadFromFile("resources/bailey1_left.png");
	bailey_texture5.loadFromFile("resources/jump_left.png");
	bailey_texture6.loadFromFile("resources/jump_right.png");
}

void BaileyController::animate_bailey(Bailey& bailey_object, Sprite& bailey_sprite)
{
	auto right = bailey_object.get_if_moving_right();
	auto left = bailey_object.get_if_moving_left();
	auto isRightKeyPressed = bailey_object.get_if_right_key_pressed();
	auto isLeftKeyPressed = bailey_object.get_if_left_key_pressed();
	auto isBaileyJumping = bailey_object.isBaileyJumping();

	if (right && isRightKeyPressed && !isBaileyJumping)
	{
		increment_frame();
		if (frame_counter <= 10)
		{
			bailey_sprite.setTexture(bailey_texture1);
		}
		else if (frame_counter > 10 && frame_counter <= 20)
		{
			bailey_sprite.setTexture(bailey_texture2);
		}
		else
		{
			reset_frame();
		}

	}

    if (left && isLeftKeyPressed && !isBaileyJumping)
	{
		increment_frame();
		if (frame_counter <= 10)
		{
			bailey_sprite.setTexture(bailey_texture3);
		}
		else if (frame_counter > 10 && frame_counter <= 20)
		{
			bailey_sprite.setTexture(bailey_texture4);
		}

		else
		{
			reset_frame();
		}
	}

	 if (isBaileyJumping && left)
	{
		bailey_sprite.setTexture(bailey_texture5);
	}

	 if (isBaileyJumping && right)
	 {
		 bailey_sprite.setTexture(bailey_texture6);
	 }

	 if (!isBaileyJumping && (right && !isRightKeyPressed))
	 {
		 bailey_sprite.setTexture(bailey_texture1);
	 }

	 if (!isBaileyJumping && (left && !isLeftKeyPressed))
	 {
		 bailey_sprite.setTexture(bailey_texture3);
	 }
}
