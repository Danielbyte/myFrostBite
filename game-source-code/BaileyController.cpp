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

	//textures to animate the death of bailey due to the bear
	death1_bailey.loadFromFile("resources/death1_bailey.png");
	death2_bailey.loadFromFile("resources/death2_bailey.png");
	death3_bailey.loadFromFile("resources/death3_bailey.png");
	death4_bailey.loadFromFile("resources/death4_bailey.png");
	death5_bailey.loadFromFile("resources/death5_bailey.png");
	death6_bailey.loadFromFile("resources/death6_bailey.png");
	death7_bailey.loadFromFile("resources/death7_bailey.png");
	death8_bailey.loadFromFile("resources/death8_bailey.png");
	death9_bailey.loadFromFile("resources/death9_bailey.png");
	death10_bailey.loadFromFile("resources/death10_bailey.png");
	death11_bailey.loadFromFile("resources/death11_bailey.png");
	death12_bailey.loadFromFile("resources/death12_bailey.png");
	death13_bailey.loadFromFile("resources/death13_bailey.png");
	death14_bailey.loadFromFile("resources/death14_bailey.png");

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

void BaileyController::bailey_death(const float& deltaTime,Sprite& bailey_sprite)
{
	
	if (deltaTime >0 && deltaTime <= 0.07)
	{
		bailey_sprite.setTexture(death1_bailey);

	}

	if (deltaTime > 0.07 && deltaTime <= 0.14)
	{
		bailey_sprite.setTexture(death2_bailey);
	}

	if (deltaTime > 0.14 && deltaTime <= 0.21)
	{
		bailey_sprite.setTexture(death3_bailey);
	}
	if (deltaTime > 0.21 && deltaTime <= 0.28)
	{
		bailey_sprite.setTexture(death4_bailey);
	}
	if (deltaTime > 0.28 && deltaTime <= 0.35)
	{
		bailey_sprite.setTexture(death5_bailey);
	}
	if (deltaTime >0.35 && deltaTime <= 0.42)
	{
		bailey_sprite.setTexture(death6_bailey);
	}
	if (deltaTime > 0.42 && deltaTime <= 0.49)
	{
		bailey_sprite.setTexture(death7_bailey);
	}
	if (deltaTime > 0.49 && deltaTime <= 0.56)
	{
		bailey_sprite.setTexture(death8_bailey);
	}
	if (deltaTime > 0.56 && deltaTime <= 0.63)
	{
		bailey_sprite.setTexture(death9_bailey);
	}
	if (deltaTime > 0.63 && deltaTime <= 0.7)
	{
		bailey_sprite.setTexture(death10_bailey);
	}
	if (deltaTime > 0.77 && deltaTime <= 0.84)
	{
		bailey_sprite.setTexture(death11_bailey);
	}
	if (deltaTime > 0.84 && deltaTime <= 0.91)
	{
		bailey_sprite.setTexture(death12_bailey);
	}
	if (deltaTime > 0.91 && deltaTime <= 0.98)
	{
		bailey_sprite.setTexture(death13_bailey);
	}
	if (deltaTime > 0.98 && deltaTime <= 1.05)
	{
		bailey_sprite.setTexture(death14_bailey);
	}
}
