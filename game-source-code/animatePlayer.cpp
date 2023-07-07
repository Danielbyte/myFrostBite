#include "BaileyController.h"

BaileyController::BaileyController():
	frame_counter{0},
	drowningTimePerFrame{0.06f},
	CWSCTPF{0.17f},
	freezingFrameTime{0.063f}
{
	load_textures();
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

	//Textures to animate drowning frostbite
	drown1.loadFromFile("resources/drown1.png");
	drown2.loadFromFile("resources/drown2.png");
	drown3.loadFromFile("resources/drown3.png");
	drown4.loadFromFile("resources/drown4.png");
	drown5.loadFromFile("resources/drown5.png");
	drown6.loadFromFile("resources/drown6.png");
	drown7.loadFromFile("resources/drown7.png");
	drown8.loadFromFile("resources/drown8.png");
	drown9.loadFromFile("resources/drown9.png");
	drown10.loadFromFile("resources/drown10.png");
	drown11.loadFromFile("resources/drown11.png");
	drown12.loadFromFile("resources/drown12.png");
	drown13.loadFromFile("resources/drown13.png");
	drown14.loadFromFile("resources/drown14.png");
	drown15.loadFromFile("resources/drown15.png");
	drown16.loadFromFile("resources/drown16.png");
	drown17.loadFromFile("resources/drown17.png");

	//Tecture to animate when frostbite collides with sea animal
	die1.loadFromFile("resources/die1.png");
	die2.loadFromFile("resources/die2.png");
	die3.loadFromFile("resources/die3.png");
	die4.loadFromFile("resources/die4.png");
	die5.loadFromFile("resources/die5.png");
	die6.loadFromFile("resources/die6.png");

	//Textures to animate frostbite when frozen
	freeze1.loadFromFile("resources/freeze1.png");
	freeze2.loadFromFile("resources/freeze2.png");
	freeze3.loadFromFile("resources/freeze3.png");
	freeze4.loadFromFile("resources/freeze4.png");
	freeze5.loadFromFile("resources/freeze5.png");
	freeze6.loadFromFile("resources/freeze6.png");
	freeze7.loadFromFile("resources/freeze7.png");
	freeze8.loadFromFile("resources/freeze8.png");
	freeze9.loadFromFile("resources/freeze9.png");
	freeze10.loadFromFile("resources/freeze10.png");
	freeze11.loadFromFile("resources/freeze11.png");
	freeze12.loadFromFile("resources/freeze12.png");
	freeze13.loadFromFile("resources/freeze13.png");
	freeze14.loadFromFile("resources/freeze14.png");
	freeze15.loadFromFile("resources/freeze15.png");
	freeze16.loadFromFile("resources/freeze16.png");

	//Textures to animate frostbite when he goes into an igloo
	enterIgloo1.loadFromFile("resources/enterIgloo1.png");
	enterIgloo2.loadFromFile("resources/enterIgloo2.png");
	enterIgloo3.loadFromFile("resources/enterIgloo3.png");
	enterIgloo4.loadFromFile("resources/enterIgloo4.png");
}

void BaileyController::animate_bailey(Player& player)
{
	auto facing_right = player.isFacingRight();
	auto facing_left = player.isFacingLeft();
	auto isRightKeyPressed = player.isRightPressed();
	auto isLeftKeyPressed = player.isLeftPressed();
	auto isBaileyJumping = player.isPlayerJumping();

	if (facing_right && isRightKeyPressed && !isBaileyJumping)
	{
		increment_frame();
		if (frame_counter <= 10)
		{
			player.updateSprite(bailey_texture1);
		}
		else if (frame_counter > 10 && frame_counter <= 20)
		{
			player.updateSprite(bailey_texture2);
		}
		else
		{
			reset_frame();
		}

	}

    if (facing_left && isLeftKeyPressed && !isBaileyJumping)
	{
		increment_frame();
		if (frame_counter <= 10)
		{
			player.updateSprite(bailey_texture3);
		}
		else if (frame_counter > 10 && frame_counter <= 20)
		{
			player.updateSprite(bailey_texture4);
		}

		else
		{
			reset_frame();
		}
	}

	 if (isBaileyJumping && facing_left)
	{
		player.updateSprite(bailey_texture5);
	}

	 if (isBaileyJumping && facing_right)
	 {
		 player.updateSprite(bailey_texture6);
	 }

	 if (!isBaileyJumping && (facing_right && !isRightKeyPressed))
	 {
		 player.updateSprite(bailey_texture1);
	 }

	 if (!isBaileyJumping && (facing_left && !isLeftKeyPressed))
	 {
		 player.updateSprite(bailey_texture3);
	 }
}

void BaileyController::collision_with_sea_animal(const float& deltaTime, Sprite& bailey_sprite)
{
	if (deltaTime >= 0 && deltaTime <= CWSCTPF)
	{
		bailey_sprite.setTexture(die1);
	}
	if (deltaTime >= CWSCTPF && deltaTime <= 2*CWSCTPF)
	{
		bailey_sprite.setTexture(die2);
	}
	if (deltaTime >= 2 * CWSCTPF && deltaTime <= 3 * CWSCTPF)
	{
		bailey_sprite.setTexture(die3);
	}
	if (deltaTime >= 3 * CWSCTPF && deltaTime <= 4 * CWSCTPF)
	{
		bailey_sprite.setTexture(die4);
	}
	if (deltaTime >= 4 * CWSCTPF && deltaTime <= 5 * CWSCTPF)
	{
		bailey_sprite.setTexture(die5);
	}
	if (deltaTime >= 5 * CWSCTPF && deltaTime <= 6 * CWSCTPF)
	{
		bailey_sprite.setTexture(die6);
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

void BaileyController::drowning_bailey(const float& deltaTime, Sprite& bailey_sprite)
{
	if (deltaTime >= 0 && deltaTime <= drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown1);
	}
	if (deltaTime > drowningTimePerFrame && deltaTime <= 2*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown2);
	}
	if (deltaTime > 2*drowningTimePerFrame && deltaTime <= 3*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown3);
	}
	if (deltaTime > 3*drowningTimePerFrame && deltaTime <= 4*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown4);
	}
	if (deltaTime > 4*drowningTimePerFrame && deltaTime <= 5*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown5);
	}
	if (deltaTime > 5 * drowningTimePerFrame && deltaTime <= 6*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown6);
	}
	if (deltaTime > 6*drowningTimePerFrame && deltaTime <= 7*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown7);
	}
	if (deltaTime > 7*drowningTimePerFrame && deltaTime <= 8*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown8);
	}
	if (deltaTime > 8*drowningTimePerFrame && deltaTime <= 9*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown9);
	}
	if (deltaTime > 9*drowningTimePerFrame && deltaTime <= 10*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown10);
	}
	if (deltaTime > 10*drowningTimePerFrame && deltaTime <= 11*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown11);
	}
	if (deltaTime > 11*drowningTimePerFrame && deltaTime <= 12*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown12);
	}
	if (deltaTime > 12 * drowningTimePerFrame && deltaTime <= 13*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown13);
	}
	if (deltaTime > 13 * drowningTimePerFrame && deltaTime <= 14*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown14);
	}
	if (deltaTime > 14 * drowningTimePerFrame && deltaTime <= 15*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown15);
	}
	if (deltaTime > 15 * drowningTimePerFrame && deltaTime <= 16*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown16);
	}
	if (deltaTime > 16 * drowningTimePerFrame && deltaTime <= 17*drowningTimePerFrame)
	{
		bailey_sprite.setTexture(drown17);
	}
}

void BaileyController::freezing_animation(const float& deltaTime, Sprite& bailey_sprite)
{
	if (deltaTime >= 0 && deltaTime <= freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze1);
	}
	if (deltaTime >= freezingFrameTime && deltaTime <= 2 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze2);
	}
	if (deltaTime >= 2 * freezingFrameTime && deltaTime <= 3 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze3);
	}
	if (deltaTime >= 3 * freezingFrameTime && deltaTime <= 4 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze4);
	}
	if (deltaTime >= 4 * freezingFrameTime && deltaTime <= 5 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze5);
	}
	if (deltaTime >= 5 * freezingFrameTime && deltaTime <= 6 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze6);
	}
	if (deltaTime >= 6 * freezingFrameTime && deltaTime <= 7 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze7);
	}
	if (deltaTime >= 7 * freezingFrameTime && deltaTime <= 8 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze8);
	}
	if (deltaTime >= 8 * freezingFrameTime && deltaTime <= 9 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze9);
	}
	if (deltaTime >= 9 * freezingFrameTime && deltaTime <= 10 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze10);
	}
	if (deltaTime >= 10 * freezingFrameTime && deltaTime <= 11 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze11);
	}
	if (deltaTime >= 0 && deltaTime <= 12 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze12);
	}
	if (deltaTime >= 12 * freezingFrameTime && deltaTime <= 13 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze13);
	}
	if (deltaTime >= 13 * freezingFrameTime && deltaTime <= 14 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze14);
	}
	if (deltaTime >= 14 * freezingFrameTime && deltaTime <= 15 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze15);
	}
	if (deltaTime >= 15 * freezingFrameTime && deltaTime <= 16 * freezingFrameTime)
	{
		bailey_sprite.setTexture(freeze16);
	}
}

void BaileyController::go_inside_igloo(const float& y_pos, Sprite& bailey_sprite)
{
	if (y_pos <= 199.0f && y_pos >= 160.0f)
	{
		bailey_sprite.setTexture(enterIgloo1);
	}

	if (y_pos < 160 && y_pos >= 135)
	{
		bailey_sprite.setTexture(enterIgloo2);
	}

	if (y_pos < 135 && y_pos >= 133)
	{
		bailey_sprite.setTexture(enterIgloo3);
	}

	if (y_pos < 133)
	{
		bailey_sprite.setTexture(enterIgloo4);
	}
}
