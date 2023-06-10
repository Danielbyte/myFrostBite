#include "screen.h"

Screen::Screen():
    startedTempDecrease{false},
    timeUp{false},
    temperature{45}, //temperature starts at 45 degrees
    window(VideoMode(windowWidth, windowHeight), "Frostbite", sf::Style::Default),
    is_playing{false},
    is_game_over{false},
    quit_game{false},
    isJumping{false}, //bailey is initially at standstill
    isJumpingUp{false},
    isJumpingDown{false},
    igloorDoorOffset{14.5f},
    goingInIgloo_X_speed{100.0f},
    goingInIgloo_Y_speed{9.5f},
    multiPlayer{false}
{
    load_textures();
    initialize_cursor();
    initialize_screen();
    initialise_player();
    initialise_background();
    create_ice_blocks();
    initialize_igloo();
    initialise_bear();
}

void Screen::initialize_screen()
{
    splash_screen_display.setFont(splash_screen_font);
    splash_screen_display.setCharacterSize(20);
    splash_screen_display.setStyle(Text::Regular);
    splash_screen_display.setFillColor(Color::Red);
    splash_screen_display.setPosition(10,180);
    /*splash_screen_display.setString("Welcome to Frostbite");*/

    _mainscreen.setTexture(mainscreen);
    _instructions.setTexture(instructions);

    temperature_disp.setFont(splash_screen_font);
    temperature_disp.setCharacterSize(20);
    temperature_disp.setStyle(Text::Bold);
    temperature_disp.setFillColor(Color::Cyan);
    temperature_disp.setPosition(0.0f, 3.0f);

    degree_symbol.setFont(splash_screen_font);
    degree_symbol.setCharacterSize(15);
    degree_symbol.setStyle(Text::Bold);
    degree_symbol.setFillColor(Color::Cyan);
    degree_symbol.setPosition(188.0f, 0.0f);
    degree_symbol.setString("o");

    line_sprite.setTexture(line);
    line_sprite.setOrigin(0.5f, windowHeight / 2.0f);
    line_sprite.setPosition(200.01f, 300.0f);
}

void Screen::initialise_player()
{
    bailey_sprite.setTexture(bailey_texture);
    bailey_sprite.setPosition(logic.bailey_object.get_Xpos(),logic.bailey_object.get_Ypos());
    bailey_sprite.setOrigin(bailey_width/2,bailey_height/2);
}

void Screen::initialise_background()
{
    background_sprite.setTexture(background_texture);
}

void Screen::initialise_bear()
{
    bear_sprite.setTexture(bear_texture);
    auto initialPosistion = logic.bear_object.get_position();
    bear_sprite.setPosition(initialPosistion);
    bear_sprite.setOrigin(bear_with / 2.0f, bear_height / 2.0f);
}

void Screen::initialize_cursor()
{
    _cursor.setTexture(cursor);
    cursor_position.x = cursor_level1_x;
    cursor_position.y = cursor_level1_y;
    _cursor.setPosition(cursor_position);
    _cursor.setOrigin(cursor_width / 2.0f, cursor_height / 2.0f);
}

void Screen::run()
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        auto deltaTime = time.restart().asSeconds();
        process_user_inputs(deltaTime);

        if (is_playing || multiPlayer)
        {
            if (multiPlayer)
            {
                twoPlayerGameScreen();
                bailey_sprite.move(1.0f, 0);
                std::cout << bailey_sprite.getPosition().x << std::endl;
            }
            if (is_playing)
            {
                draw_game_entities();
                //Update screen according to game play
                update_game(deltaTime); //update
                //draw game objects
                draw_game_objects(); //draw game entities
            }
        }
        else
        {
            window.draw(splash_screen_display);

            if (!is_game_over)
            {
                window.draw(_mainscreen);

                window.draw(_cursor);
            }
        }
        window.display();
        window.clear();
    }
}

void Screen::process_user_inputs(const float& deltaTime)
{
    Event event;
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Escape)
            {
                quit_game = true;
                is_playing = false;
                window.close();
            }
            else if(event.key.code == Keyboard::Space)
            {
                //call a function that causes the block to reverse direcrtion
               auto igloo_blocks = logic.get_number_of_igloo_blocks();
               auto bailey_in_safe_zone = logic.bailey_object.get_if_bailey_in_safe_zone();
               if (!bailey_in_safe_zone && (igloo_blocks > 0 && igloo_blocks < 14))
               {
                   logic.reverse_ice_direction(Igloo_house_sprite);
               }
            }

            else if (is_game_over)
            {
                window.close();
            }
            else
                keyboard_handling(event.key.code,true,deltaTime);
            break;

           case Event::KeyReleased:
           keyboard_handling(event.key.code, false,deltaTime);
           break;
        
        case Event::Closed:
            quit_game = true;
            window.close();
            break;

        default:
           break;
        }
    }
}

void Screen::keyboard_handling(Keyboard key, bool keyPressed, const float& deltaTime)
{
    auto level = cursor_position.y;
    if (key == Keyboard::Enter && keyPressed) //player wants to play
    {
        if (level == cursor_level1_y)
        {
            is_playing = true;
            initialize_temperature();
        }
        if (level == cursor_level2_y)
        {
            //multiplayer mode
            multiPlayer = true;
            InitTwoPlayerModeScreen();
        }
        if (level == cursor_level3_y)
        {
            RenderWindow instructions_window(VideoMode(windowWidth, windowHeight),"",
                sf::Style::Resize);
            _cursor.setPosition(instructions_back_x, instructions_back_y);
            while (instructions_window.isOpen())
            {
                Event instructionsEvent;
                while (instructions_window.pollEvent(instructionsEvent))
                {
                    switch (instructionsEvent.type)
                    {
                    case Event::KeyPressed:
                        if (instructionsEvent.key.code == Keyboard::Enter)
                        {
                            _cursor.setPosition(cursor_level3_x, cursor_level3_y); //reset position back
                            instructions_window.close();
                        }
                        break;
                    case Event::Closed:
                        _cursor.setPosition(cursor_level3_x, cursor_level3_y); //reset cursor position
                        instructions_window.close();
                        break;
                    default:
                        break;
                    }
                }
                window.clear();
                instructions_window.draw(_instructions);
                instructions_window.draw(_cursor);
                instructions_window.display();
            }
        }
        if (level == cursor_level4_y)
        {
            quit_game = true;
            window.close(); //quit game;
        }
    }
    if (key == Keyboard::Up && (keyPressed && !is_playing))
    {
        _cursor.move(0.0f, -cursor_step);
        cursor_position.y = _cursor.getPosition().y;
        set_cursor_x_position();
        _cursor.setPosition(cursor_position.x, cursor_position.y);
        if (cursor_position.y <= cursor_level1_y)
        {
            cursor_position.y = cursor_level1_y;
            set_cursor_x_position();
            _cursor.setPosition(cursor_position.x, cursor_position.y);
        }
    }
    if (key == Keyboard::Down && (keyPressed && !is_playing))
    {
        _cursor.move(0.0f, cursor_step);
        cursor_position.y = _cursor.getPosition().y;
        set_cursor_x_position();
        _cursor.setPosition(cursor_position.x, cursor_position.y);
        if (cursor_position.y >= cursor_level4_y)
        {
            cursor_position.y = cursor_level4_y;
            set_cursor_x_position();
            _cursor.setPosition(cursor_position.x, cursor_position.y);
        }
    }

    if (is_playing)
    {
            //player movements
         if (key == Keyboard::Up && keyPressed && !isJumping)
         {
              window.setKeyRepeatEnabled(false);
              auto jumpForce = logic.bailey_object.get_up_jumping_force();
              auto mass = logic.bailey_object.get_bailey_mass();
              auto speed = jumpForce / mass;
              logic.bailey_object.set_speed(speed);
              isJumping = true;
              isJumpingUp = true;
         }
         else if (key == Keyboard::Down && keyPressed && !isJumping)
         {
              window.setKeyRepeatEnabled(false);
              auto jumpForce = logic.bailey_object.get_jump_force();
              auto mass = logic.bailey_object.get_bailey_mass();
              auto speed = jumpForce / mass;
              logic.bailey_object.set_speed(speed);
              isJumping = true;
              isJumpingDown = true;
         }
         else if (key == Keyboard::Left)
         {
              window.setKeyRepeatEnabled(true);
              logic.bailey_object.move_bailey(deltaTime, bailey_sprite);
         }
         else if (key == Keyboard::Right)
         {
             window.setKeyRepeatEnabled(true);
             logic.bailey_object.move_bailey(deltaTime, bailey_sprite);
         }
    }
}

void Screen::set_cursor_x_position()
{
    if (cursor_position.y == cursor_level1_y) { cursor_position.x = cursor_level1_x; }
    if (cursor_position.y == cursor_level2_y) { cursor_position.x = cursor_level2_x; }
    if (cursor_position.y == cursor_level3_y) { cursor_position.x = cursor_level3_x; }
    if (cursor_position.y == cursor_level4_y) { cursor_position.x = cursor_level4_x; }
}

void Screen::initialize_temperature()
{
    if (!startedTempDecrease)
    {
        tempStopWatch.restart_timer();
        startedTempDecrease = true;
    }
}

void Screen::update_temperature()
{
    if (startedTempDecrease)
    {
        auto _time = tempStopWatch.elapsed_time();
        if (_time >= 1.0f) // decrease temperature every 1 second
        {
            --temperature; //decrease the temperature
            tempStopWatch.restart_timer();
        }

        if (temperature == 0)
        {
            timeUp = true;
        }
    }
}

void Screen::draw_game_objects()
{
    window.draw(bailey_sprite);
    window.draw(bear_sprite);
}

void Screen::draw_igloo_house()
{
     window.draw(*Igloo_house_sprite);
}

void Screen::draw_ice_blocks()
{
//Draw moving ice blocks
    for(auto& ice_blocks : ice_blocks_sprites)
    {
        window.draw(*ice_blocks);
    }
}

void Screen::draw_crabs()
{
    if (!crabs.empty())
    {
        for (auto& crab : crabs)
        {
            window.draw(*crab);
        }
    }
}

void Screen::draw_clamps()
{
    if (!crabs.empty())
    {
        for (auto& clamp : clamps)
        {
            window.draw(*clamp);
        }
    }
}

void Screen::draw_fish()
{
    if (!fish.empty())
    {
        for (auto& _fish : fish)
        {
            window.draw(*_fish);
        }
    }
}

void Screen::draw_birds()
{
    if (!birds.empty())
    {
        for (auto& bird : birds)
        {
            window.draw(*bird);
        }
    }
}

void Screen::update_game(const float& deltaTime)
{
    update_game_sprites(deltaTime); // update game entities
//update game state -> update game
    update_game_state(deltaTime);
}

void Screen::update_game_sprites(const float& deltaTime)
{
    logic.update_bailey_jumps(bailey_sprite,isJumping,deltaTime,isJumpingUp,isJumpingDown);
    logic.update_bailey(bailey_sprite);
    logic.update_ice(ice_blocks_sprites, deltaTime);
    logic.update_bear(bear_sprite, deltaTime);
    logic.update_enemies(crabs, clamps, birds, fish, deltaTime);
    logic.frostbite_bear_collisions();
    logic.updateBaileyAndSeaAnimalCollisions(crabs, clamps, birds, fish);
    update_temperature();
    //only update collisions if frostbite is not in safe zone
    auto isBaileyInSafeZone = logic.bailey_object.get_if_bailey_in_safe_zone();
    if (!isJumping && !isBaileyInSafeZone) //frostbite either stepped on ice or drowned
    {
        auto isCollided = logic.bailey_and_ice_collision(Igloo_house_sprite, bailey_sprite, deltaTime);
         if(!isCollided)
        {
            auto isAnimating = true;
            Stopwatch s_watch;
            logic.bailey_object.set_bailey_to_dead(true);
            while (isAnimating)
            {
                auto TimeElapsed = s_watch.elapsed_time();
                logic.drowning_bailey_animation(TimeElapsed, bailey_sprite);
                draw_game_entities();
                //draw game objects
                draw_game_objects(); //draw game entities
                window.draw(temperature_disp);
                window.draw(degree_symbol);
                window.display();
                window.clear();
                if (TimeElapsed >= 1.03f)
                {
                    isAnimating = false;
                }

            }
        }

         auto collidedWithSeaCreatures = logic.getIfCollidedWithSeaAnimal();
         if (collidedWithSeaCreatures)
         {
             auto isAnimating = true;
             Stopwatch s_watch;
             logic.bailey_object.set_bailey_to_dead(true);
             while (isAnimating)
             {
                 auto TimeElapsed = s_watch.elapsed_time();
                 logic.baileyCollisionWithSeaCreatureAnimation(TimeElapsed, bailey_sprite);
                 draw_game_entities();
                 //draw game objects
                 draw_game_objects(); //draw game entities
                 window.draw(temperature_disp);
                 window.draw(degree_symbol);
                 window.display();
                 window.clear();
                 if (TimeElapsed >= 1.03f)
                 {
                     isAnimating = false;
                 }

             }
         }       
    }

    string _temperature = std::to_string(temperature);
    temperature_disp.setString("TEMPERATURE: " + _temperature);
    window.draw(temperature_disp);
    window.draw(degree_symbol);

    if (timeUp)
    {
        auto isAnimating = true;
        Stopwatch s_watch;
        logic.bailey_object.set_bailey_to_dead(true);
        while (isAnimating)
        {
            auto TimeElapsed = s_watch.elapsed_time();
            logic.freezing_bailey_animation(TimeElapsed, bailey_sprite);
            draw_animations();
            if (TimeElapsed >= 1.1f)
            {
                isAnimating = false;
            }
        }
    }
}

void Screen::create_ice_blocks()
{
    auto [pos1, pos2, pos3, pos4] = logic.create_ice_block_objects();

    auto ice_sprite1 = std::make_shared<Sprite>(Sprite());
    ice_sprite1 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite1 -> setTexture(ice_block_texture);
    ice_sprite1 -> setPosition(pos1);
    ice_blocks_sprites.push_back(ice_sprite1);

    auto ice_sprite2 = std::make_shared<Sprite>(Sprite());
    ice_sprite2 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite2 -> setTexture(ice_block_texture);
    ice_sprite2 -> setPosition(pos2);
    ice_blocks_sprites.push_back(ice_sprite2);

    auto ice_sprite3 = std::make_shared<Sprite>(Sprite());
    ice_sprite3 -> setOrigin(ice_width/2.0f,ice_height/2.0f);
    ice_sprite3 -> setTexture(ice_block_texture);
    ice_sprite3 -> setPosition(pos3);
    ice_blocks_sprites.push_back(ice_sprite3);

    auto ice_sprite4 = std::make_shared<Sprite>(Sprite());
    ice_sprite4 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite4 -> setTexture(ice_block_texture);
    ice_sprite4 -> setPosition(pos4);
    ice_blocks_sprites.push_back(ice_sprite4);
}


void Screen::update_game_state(const float& deltaTime)
{
    splash_screen_display.setPosition(125,208);
    splash_screen_display.setCharacterSize(20);

    auto bailey_in_safe_zone = logic.bailey_object.get_if_bailey_in_safe_zone();
    auto bailey_is_dead = logic.bailey_object.get_if_bailey_dead();
  
    if (bailey_is_dead && bailey_in_safe_zone)
    {
        auto isAnimating = true;
        Stopwatch s_watch;
        
        while (isAnimating)
        {
            auto TimeElapsed = s_watch.elapsed_time();
            logic.animate_bailey_death(TimeElapsed,bailey_sprite);
            logic.bear_object.update_bear(bear_sprite, 0.0f);//bear is stationary, attacking frosty
            draw_animations();
            if (TimeElapsed >= 1.09)
            {
                isAnimating = false;
            }
        }
    }
 
    if (bailey_is_dead)
    {
        is_playing = false;
        is_game_over = true;
        window.clear();
        splash_screen_display.setString("YOU LOST!"
                                        "\nGAME OVER");
    }

    auto igloo_complete = logic.mark_if_igloo_is_complete();
    auto [distance, igloo_door_Xpos, igloo_door_Ypos] = calculateDistanceBetweenBaileyAndDoor();
    if (bailey_in_safe_zone && igloo_complete && distance.x <= 35.0f)
    {
        Stopwatch s_watch;
        float bailey_y_position;
        float bailey_x_position;
        bool isInside = false;
        while (!isInside)
        {
            auto [distance, igloo_door_Xpos, igloo_door_Ypos] = calculateDistanceBetweenBaileyAndDoor();
            auto TimeElapsed = s_watch.elapsed_time();
            bailey_x_position = logic.bailey_object.get_Xpos();
            bailey_y_position = logic.bailey_object.get_Ypos();
            if (bailey_x_position > igloo_door_Xpos)
            { 
                if (distance.x > igloorDoorOffset) 
                {
                    bailey_sprite.move(-TimeElapsed*goingInIgloo_X_speed, 0);
                     bailey_x_position = bailey_sprite.getPosition().x;
                    logic.bailey_object.setXposition(bailey_x_position);
                }
            }

            if (bailey_x_position < igloo_door_Xpos) 
            { 
                if (distance.x > igloorDoorOffset) 
                { 
                    bailey_sprite.move(TimeElapsed*goingInIgloo_X_speed, 0);
                    bailey_x_position = bailey_sprite.getPosition().x;
                    logic.bailey_object.setXposition(bailey_x_position); 
                }
            }

            if (bailey_y_position > igloo_door_Ypos) 
            { 
                bailey_sprite.move(0, -TimeElapsed*goingInIgloo_Y_speed);
                bailey_y_position = bailey_sprite.getPosition().y;
                logic.bailey_object.setYposition(bailey_y_position);
            }

            logic.go_inside_igloo(bailey_y_position, bailey_sprite);
            draw_animations();

            if (bailey_y_position < 133)
            {
                isInside = true;
                is_playing = false;
                is_game_over = true;
                window.setKeyRepeatEnabled(false);
            }
        }
        window.clear();
        splash_screen_display.setString("YOU WON!"
                                        "\nRETURNED SAFELY TO SAFE ZONE FROM BOTTOM");
    }
}

std::tuple<vector2f&, float&, float&> Screen::calculateDistanceBetweenBaileyAndDoor()
{
    auto bailey_x_position = logic.bailey_object.get_Xpos();
    auto bailey_y_position = logic.bailey_object.get_Ypos();
    auto igloo_door_Xpos = (logic.igloo_object)->get_x_position();
    auto igloo_door_Ypos = (logic.igloo_object)->get_y_position();
    distanceBetweenDoorAndBailey.x = abs(bailey_x_position - igloo_door_Xpos);
    distanceBetweenDoorAndBailey.y = abs(bailey_y_position - igloo_door_Ypos);
    return { distanceBetweenDoorAndBailey, igloo_door_Xpos, igloo_door_Ypos };
}

void Screen::twoPlayerGameScreen()
{
    window.setView(player1View);
    window.draw(background_sprite);
    window.draw(bailey_sprite);

    window.setView(player2View);
    window.draw(background_sprite);
    window.draw(line_sprite);

}

void Screen::InitTwoPlayerModeScreen()
{
    player1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
    player1View.setSize(windowWidth / 2.0f, windowHeight);
    player1View.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);

    player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
    player2View.setSize(windowWidth / 2.0f, windowHeight);
    player2View.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);
}

void Screen::draw_animations()
{
    draw_game_entities();
    window.draw(temperature_disp);
    window.draw(degree_symbol);
    //draw game objects
    draw_game_objects(); //draw game entities
    window.display();
    window.clear();
}

void Screen::initialize_igloo()
{
    vector2f Initposition;
    Initposition.x = (logic.igloo_object)->get_x_position();
    Initposition.y = (logic.igloo_object)->get_y_position();
    Igloo_house_sprite ->setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
    Igloo_house_sprite -> setTexture(igloo_texture);
    Igloo_house_sprite -> setPosition(Initposition);
}

void Screen::load_textures()
{
    displays.loadFromFile("resources/sansation.ttf");
    splash_screen_font.loadFromFile("resources/sansation.ttf");

    ice_block_texture2.loadFromFile("resources/whiteIce.png");
    ice_block_texture.loadFromFile("resources/whiteIce.png");

    if (!bailey_texture.loadFromFile("resources/bailey.png")) throw CouldNotLoadPicture{};
    if (!background_texture.loadFromFile("resources/background.png")) throw CouldNotLoadPicture{};
    igloo_texture.loadFromFile("resources/igloo0.png");
    if (!bear_texture.loadFromFile("resources/bear1_left.png")) throw CouldNotLoadPicture{};
    mainscreen.loadFromFile("resources/mainscreen.png");
    cursor.loadFromFile("resources/cursor.png");
    instructions.loadFromFile("resources/instructions.png");
    line.loadFromFile("resources/line.png");
}

void Screen::draw_game_entities()
{
    window.draw(background_sprite);
    draw_ice_blocks();
    draw_igloo_house();
    draw_crabs();
    draw_clamps();
    draw_fish();
    draw_birds();
}

Screen::~Screen() 
{
    //Free memory
    ice_blocks_sprites.clear();
    crabs.clear();
    clamps.clear();
    birds.clear();
    fish.clear();
}
