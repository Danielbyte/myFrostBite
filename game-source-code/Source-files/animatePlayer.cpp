#include "../Header-files/AnimatePlayer.h"

AnimatePlayer::AnimatePlayer():
	frame_counter{0},
	drowningTimePerFrame{0.06f},
	CWSCTPF{0.17f},
	freezingFrameTime{0.063f},
	standardAnimDur{1.03f},
	freezeAnimDur{1.1f}
{
	load_textures();
}

void AnimatePlayer::reset_frame()
{
	frame_counter = 0;
}

int AnimatePlayer::get_frame() const
{
	return frame_counter;
}

void AnimatePlayer::increment_frame()
{
	++frame_counter;
}

void AnimatePlayer::load_textures()
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

void AnimatePlayer::animateAndSetState(Player& player, vector<shared_ptr<Crab>>& _crabs,
	vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, shared_ptr<Bear>& _bear,
	vector<shared_ptr<IceBlocks>>& _iceblocks, bool& createIce, OverWorld& _overworld, shared_ptr<Igloo>& igloo)
{
	auto state = player.getState();

	switch (state)
	{
	case PlayerState::Dead:
		return;
		break;
	case PlayerState::Alive:
		animate_player(player);
		break;
	case PlayerState::Drowning:
		drowning_player(player,_crabs, _clamps, _birds, _bear, _iceblocks, createIce);
		break;
	case PlayerState::Freezing:
		freezing_animation(player, _crabs, _clamps, _birds, _bear, _iceblocks, createIce, _overworld);
		break;
	case PlayerState::AttackedBySeaAnimal:
		collision_with_sea_animal(player, _crabs, _clamps, _birds, _bear, _iceblocks, createIce);
		break;
	case PlayerState::AttackedByBear:
		killed_by_bear(player, _crabs, _clamps, _birds, _bear, _iceblocks, createIce);
		break;
	case PlayerState::Winning:
		go_inside_igloo(player, igloo);
		break;
	default:
		break;
	}
}

void AnimatePlayer::animate_player(Player& player)
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

void AnimatePlayer::collision_with_sea_animal(Player& player, vector<shared_ptr<Crab>>& _crabs,
	vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, shared_ptr<Bear>& _bear, 
	vector<shared_ptr<IceBlocks>>& _iceblocks, bool& createIce)
{
	auto deltaTime = player.getTime();
	if (deltaTime >= 0 && deltaTime <= CWSCTPF)
	{
		player.updateSprite(die1);
	}
	if (deltaTime >= CWSCTPF && deltaTime <= 2*CWSCTPF)
	{
		player.updateSprite(die2);
	}
	if (deltaTime >= 2 * CWSCTPF && deltaTime <= 3 * CWSCTPF)
	{
		player.updateSprite(die3);
	}
	if (deltaTime >= 3 * CWSCTPF && deltaTime <= 4 * CWSCTPF)
	{
		player.updateSprite(die4);
	}
	if (deltaTime >= 4 * CWSCTPF && deltaTime <= 5 * CWSCTPF)
	{
		player.updateSprite(die5);
	}
	if (deltaTime >= 5 * CWSCTPF && deltaTime <= 6 * CWSCTPF)
	{
		player.updateSprite(die6);
	}

	if (deltaTime >= standardAnimDur)
	{
		player.stopWatch();
		player.setState(PlayerState::Alive);
		player.spawnPlayer();
		_bear->spawnBear();
		_iceblocks.clear();
		createIce = true;
		_clamps.clear();
		_birds.clear();
		_crabs.clear();

		if (player.getNumberOfLives() == 0) { player.setState(PlayerState::Dead); }
	}
}

void AnimatePlayer::killed_by_bear(Player& player, vector<shared_ptr<Crab>>& _crabs,
	vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, shared_ptr<Bear>& _bear,
	vector<shared_ptr<IceBlocks>>& _iceblocks, bool& createIce)
{
	auto deltaTime = player.getTime();
	if (deltaTime >0 && deltaTime <= 0.07)
	{
		player.updateSprite(death1_bailey);

	}

	if (deltaTime > 0.07 && deltaTime <= 0.14)
	{
		player.updateSprite(death2_bailey);
	}

	if (deltaTime > 0.14 && deltaTime <= 0.21)
	{
		player.updateSprite(death3_bailey);
	}
	if (deltaTime > 0.21 && deltaTime <= 0.28)
	{
		player.updateSprite(death4_bailey);
	}
	if (deltaTime > 0.28 && deltaTime <= 0.35)
	{
		player.updateSprite(death5_bailey);
	}
	if (deltaTime >0.35 && deltaTime <= 0.42)
	{
		player.updateSprite(death6_bailey);
	}
	if (deltaTime > 0.42 && deltaTime <= 0.49)
	{
		player.updateSprite(death7_bailey);
	}
	if (deltaTime > 0.49 && deltaTime <= 0.56)
	{
		player.updateSprite(death8_bailey);
	}
	if (deltaTime > 0.56 && deltaTime <= 0.63)
	{
		player.updateSprite(death9_bailey);
	}
	if (deltaTime > 0.63 && deltaTime <= 0.7)
	{
		player.updateSprite(death10_bailey);
	}
	if (deltaTime > 0.77 && deltaTime <= 0.84)
	{
		player.updateSprite(death11_bailey);
	}
	if (deltaTime > 0.84 && deltaTime <= 0.91)
	{
		player.updateSprite(death12_bailey);
	}
	if (deltaTime > 0.91 && deltaTime <= 0.98)
	{
		player.updateSprite(death13_bailey);
	}
	if (deltaTime > 0.98 && deltaTime <= 1.05)
	{
		player.updateSprite(death14_bailey);
	}

	if (deltaTime >= standardAnimDur)
	{
		player.setState(PlayerState::Alive);
		player.stopWatch();
		player.spawnPlayer();
		_bear->spawnBear();
		_iceblocks.clear();
		createIce = true;
		_clamps.clear();
		_birds.clear();
		_crabs.clear();

		if (player.getNumberOfLives() == 0) { player.setState(PlayerState::Dead); }
	}
}

void AnimatePlayer::drowning_player(Player& player, vector<shared_ptr<Crab>>& _crabs,
	vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, shared_ptr<Bear>& _bear,
	vector<shared_ptr<IceBlocks>>& _iceblocks, bool& createIce)
{
	auto deltaTime = player.getTime();
	if (deltaTime >= 0 && deltaTime <= drowningTimePerFrame)
	{
		player.updateSprite(drown1);
	}
	if (deltaTime > drowningTimePerFrame && deltaTime <= 2*drowningTimePerFrame)
	{
		player.updateSprite(drown2);
	}
	if (deltaTime > 2*drowningTimePerFrame && deltaTime <= 3*drowningTimePerFrame)
	{
		player.updateSprite(drown3);
	}
	if (deltaTime > 3*drowningTimePerFrame && deltaTime <= 4*drowningTimePerFrame)
	{
		player.updateSprite(drown4);
	}
	if (deltaTime > 4*drowningTimePerFrame && deltaTime <= 5*drowningTimePerFrame)
	{
		player.updateSprite(drown5);
	}
	if (deltaTime > 5 * drowningTimePerFrame && deltaTime <= 6*drowningTimePerFrame)
	{
		player.updateSprite(drown6);
	}
	if (deltaTime > 6*drowningTimePerFrame && deltaTime <= 7*drowningTimePerFrame)
	{
		player.updateSprite(drown7);
	}
	if (deltaTime > 7*drowningTimePerFrame && deltaTime <= 8*drowningTimePerFrame)
	{
		player.updateSprite(drown8);
	}
	if (deltaTime > 8*drowningTimePerFrame && deltaTime <= 9*drowningTimePerFrame)
	{
		player.updateSprite(drown9);
	}
	if (deltaTime > 9*drowningTimePerFrame && deltaTime <= 10*drowningTimePerFrame)
	{
		player.updateSprite(drown10);
	}
	if (deltaTime > 10*drowningTimePerFrame && deltaTime <= 11*drowningTimePerFrame)
	{
		player.updateSprite(drown11);
	}
	if (deltaTime > 11*drowningTimePerFrame && deltaTime <= 12*drowningTimePerFrame)
	{
		player.updateSprite(drown12);
	}
	if (deltaTime > 12 * drowningTimePerFrame && deltaTime <= 13*drowningTimePerFrame)
	{
		player.updateSprite(drown13);
	}
	if (deltaTime > 13 * drowningTimePerFrame && deltaTime <= 14*drowningTimePerFrame)
	{
		player.updateSprite(drown14);
	}
	if (deltaTime > 14 * drowningTimePerFrame && deltaTime <= 15*drowningTimePerFrame)
	{
		player.updateSprite(drown15);
	}
	if (deltaTime > 15 * drowningTimePerFrame && deltaTime <= 16*drowningTimePerFrame)
	{
		player.updateSprite(drown16);
	}
	if (deltaTime > 16 * drowningTimePerFrame && deltaTime <= 17*drowningTimePerFrame)
	{
		player.updateSprite(drown17);
	}

	if (deltaTime >= standardAnimDur)
	{
		player.setState(PlayerState::Alive);
		player.stopWatch();
		player.spawnPlayer();
		_bear->spawnBear();
		_iceblocks.clear();
		createIce = true;
		_clamps.clear();
		_birds.clear();
		_crabs.clear();

		if (player.getNumberOfLives() == 0) { player.setState(PlayerState::Dead); }
	}
}

void AnimatePlayer::freezing_animation(Player& player, vector<shared_ptr<Crab>>& _crabs,
	vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, shared_ptr<Bear>& _bear,
	vector<shared_ptr<IceBlocks>>& _iceblocks, bool& createIce, OverWorld& _overworld)
{
	auto deltaTime = player.getTime();
	if (deltaTime >= 0 && deltaTime <= freezingFrameTime)
	{
		player.updateSprite(freeze1);
	}
	if (deltaTime >= freezingFrameTime && deltaTime <= 2 * freezingFrameTime)
	{
		player.updateSprite(freeze2);
	}
	if (deltaTime >= 2 * freezingFrameTime && deltaTime <= 3 * freezingFrameTime)
	{
		player.updateSprite(freeze3);
	}
	if (deltaTime >= 3 * freezingFrameTime && deltaTime <= 4 * freezingFrameTime)
	{
		player.updateSprite(freeze4);
	}
	if (deltaTime >= 4 * freezingFrameTime && deltaTime <= 5 * freezingFrameTime)
	{
		player.updateSprite(freeze5);
	}
	if (deltaTime >= 5 * freezingFrameTime && deltaTime <= 6 * freezingFrameTime)
	{
		player.updateSprite(freeze6);
	}
	if (deltaTime >= 6 * freezingFrameTime && deltaTime <= 7 * freezingFrameTime)
	{
		player.updateSprite(freeze7);
	}
	if (deltaTime >= 7 * freezingFrameTime && deltaTime <= 8 * freezingFrameTime)
	{
		player.updateSprite(freeze8);
	}
	if (deltaTime >= 8 * freezingFrameTime && deltaTime <= 9 * freezingFrameTime)
	{
		player.updateSprite(freeze9);
	}
	if (deltaTime >= 9 * freezingFrameTime && deltaTime <= 10 * freezingFrameTime)
	{
		player.updateSprite(freeze10);
	}
	if (deltaTime >= 10 * freezingFrameTime && deltaTime <= 11 * freezingFrameTime)
	{
		player.updateSprite(freeze11);
	}
	if (deltaTime >= 0 && deltaTime <= 12 * freezingFrameTime)
	{
		player.updateSprite(freeze12);
	}
	if (deltaTime >= 12 * freezingFrameTime && deltaTime <= 13 * freezingFrameTime)
	{
		player.updateSprite(freeze13);
	}
	if (deltaTime >= 13 * freezingFrameTime && deltaTime <= 14 * freezingFrameTime)
	{
		player.updateSprite(freeze14);
	}
	if (deltaTime >= 14 * freezingFrameTime && deltaTime <= 15 * freezingFrameTime)
	{
		player.updateSprite(freeze15);
	}
	if (deltaTime >= 15 * freezingFrameTime && deltaTime <= 16 * freezingFrameTime)
	{
		player.updateSprite(freeze16);
	}

	if (deltaTime >= freezeAnimDur)
	{
		player.setState(PlayerState::Alive);
		player.stopWatch();
		player.spawnPlayer();
		_bear->spawnBear();
		_iceblocks.clear();
		createIce = true;
		_clamps.clear();
		_birds.clear();
		_crabs.clear();
		_overworld.resetTemperature();

		if (player.getNumberOfLives() == 0) { player.setState(PlayerState::Dead); }
	}
}

void AnimatePlayer::go_inside_igloo(Player& player, shared_ptr<Igloo>& igloo)
{
	movePlayerTowardsDoor(player, igloo);
	auto y_pos = player.getPosition().y;

	if (y_pos <= 199.0f && y_pos >= 160.0f)
	{
		player.updateSprite(enterIgloo1);
	}

	if (y_pos < 160 && y_pos >= 135)
	{
		player.updateSprite(enterIgloo2);
	}

	if (y_pos < 135 && y_pos >= 133)
	{
		player.updateSprite(enterIgloo3);
	}

	if (y_pos < 133)
	{
		player.updateSprite(enterIgloo4);
	}
}

void AnimatePlayer::movePlayerTowardsDoor(Player& player, shared_ptr<Igloo>& _igloo)
{

	auto [playerDistanceToDoor, iglooDoorPos] = player.distanceToDoor(_igloo);
	auto TimeElapsed = player.getTime();
	vector2f playerPos = player.getPosition();
	float goingInIgloo_X_speed = 100.0f;
	float goingInIgloo_Y_speed = 9.5f;
	auto igloorDoorOffset = 14.5f;

	if (playerPos.x > iglooDoorPos.x)
	{
		if (playerDistanceToDoor.x > 1.0f)
		{
			vector2f pos = player.getPosition();
			pos.x -= TimeElapsed * goingInIgloo_X_speed;
			player.setPosition(pos);
		}
	}

	if (playerPos.x < iglooDoorPos.x)
	{
		if (playerDistanceToDoor.x > igloorDoorOffset)
		{
			vector2f pos = player.getPosition();
			pos.x += TimeElapsed * goingInIgloo_X_speed;
			player.setPosition(pos);
		}
	}

	if (playerPos.y > iglooDoorPos.y)
	{
		vector2f pos = player.getPosition();
		pos.y -= TimeElapsed * goingInIgloo_Y_speed;
		player.setPosition(pos);
	}

	if (playerPos.y < 133.0f)
	{
		player.setToWin();
		player.stopWatch();
	}

}