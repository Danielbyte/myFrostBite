#include "screen.h"

Screen::Screen():
    can_create_new_batch_of_ice_blocks{false},
    window(VideoMode(windowWidth, windowHeight), "Frostbite"),
    is_playing{false},
    is_game_over{false},
    quit_game{false},
    new_ice_created{false},
    vector1{1},
    vector2{2},
    collided1{false},
    collided2{false}
{
    initialize_screen();
    initialise_player();
    initialise_background();
    load_textures();
    create_ice_blocks();
    initialize_igloo();
}

void Screen::initialize_screen()
{
    displays.loadFromFile("resources/sansation.ttf");
    splash_screen_font.loadFromFile("resources/sansation.ttf");
    splash_screen_display.setFont(splash_screen_font);
    splash_screen_display.setCharacterSize(20);
    splash_screen_display.setStyle(Text::Regular);
    splash_screen_display.setFillColor(Color::Red);
    splash_screen_display.setPosition(10,180);
    splash_screen_display.setString("Welcome to Frostbite");

    //game instructions set up
    game_instructions.setFont(splash_screen_font);
    game_instructions.setCharacterSize(20);
    game_instructions.setStyle(Text::Regular);
    game_instructions.setFillColor(Color::Red);
    game_instructions.setPosition(10, 220);
    game_instructions.setString("INSTRUCTIONS: \nPress Enter to start game!"
                                "\nPress Escape(Esc) to quit!"
                                "\nUse keyboard arrows to move player"
                                "\nPress space to reverse block of ice!");


}

void Screen::initialise_player()
{
    if(!bailey_texture.loadFromFile("resources/bailey.png")) throw CouldNotLoadPicture{};
    bailey_sprite.setTexture(bailey_texture);
    bailey_sprite.setPosition(logic.bailey_object.get_Xpos(),logic.bailey_object.get_Ypos());
    bailey_sprite.setOrigin(bailey_width/2,bailey_height/2);
}

void Screen::initialise_background()
{
    if(!background_texture.loadFromFile("resources/background.png")) throw CouldNotLoadPicture{};
    background_sprite.setTexture(background_texture);
}

void Screen::run()
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        auto deltaTime = time.restart().asSeconds();
        process_user_inputs(deltaTime);
        if (is_playing)
        {
            window.draw(background_sprite);
            draw_ice_blocks();
            draw_igloo_house();
            //Update screen according to game play
            update_game(deltaTime); //update
            //draw game objects
            draw_game_objects(); //draw game entities

        }
        else
        {
            window.draw(splash_screen_display);

            if (!is_game_over)
            {
                window.draw(game_instructions);
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
                   logic.reverse_ice_direction(Igloo_house_sprites);
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
            ;
        }
    }
}

void Screen::keyboard_handling(Keyboard key, bool keyPressed, const float& deltaTime)
{
        auto bailey_speed = logic.bailey_object.getbailey_speed();
        if (key == Keyboard::Enter && keyPressed) //player wants to play
            is_playing = true;
        if (is_playing)
        {
            //player movements
            if (key == Keyboard::Up)
            {
                logic.bailey_object.set_bailey_movement(Direction::Up, bailey_speed, keyPressed,bailey_sprite,
                    deltaTime);
            }
            else if (key == Keyboard::Down)
            {
                logic.bailey_object.set_bailey_movement(Direction::Down, bailey_speed,keyPressed,bailey_sprite,
                    deltaTime);
            }
            else if (key == Keyboard::Left)
            {
                logic.bailey_object.set_bailey_movement(Direction::Left, bailey_speed,keyPressed,bailey_sprite,
                    deltaTime);
            }
            else if (key == Keyboard::Right)
            {
                logic.bailey_object.set_bailey_movement(Direction::Right, bailey_speed,keyPressed,bailey_sprite,
                    deltaTime);
            }
        }
    
}

void Screen::draw_game_objects()
{
    window.draw(bailey_sprite);
}

void Screen::draw_igloo_house()
{
    if(!Igloo_house_sprites.empty())
    {
        for(auto& igloo_blocks : Igloo_house_sprites)
        {
            window.draw(*igloo_blocks);
        }
    }
}

void Screen::draw_ice_blocks()
{
//Draw moving ice blocks
    for(auto& ice_blocks : ice_blocks_sprites)
    {
        window.draw(*ice_blocks);
    }

    for(auto& ice_blocks : ice_blocks_sprites2)
    {
        window.draw(*ice_blocks);
    }

}

void Screen::update_game(const float& deltaTime)
{
    update_game_sprites(deltaTime); // update game entities
//update game state -> update game
    update_game_state();
}

void Screen::update_game_sprites(const float& deltaTime)
{
    logic.update_bailey(bailey_sprite);
    logic.update_ice(ice_blocks_sprites, can_create_new_batch_of_ice_blocks, vector1);
   
    if (can_create_new_batch_of_ice_blocks && ice_blocks_sprites.size() == 0)
    {
        create_ice_block_batch(ice_blocks_sprites,vector1);
    }

    if (can_create_new_batch_of_ice_blocks && ice_blocks_sprites2.size() == 0)
    {
        create_ice_block_batch(ice_blocks_sprites2, vector2);
    }

    if (ice_blocks_sprites2.size() != 0)
    {
        logic.update_ice(ice_blocks_sprites2, can_create_new_batch_of_ice_blocks, vector2);
    }

    //Update collisions
    logic.bailey_and_ice_collision(Igloo_house_sprites,bailey_sprite,deltaTime);
    logic.bailey_and_water_collision1(collided1);
    logic.bailey_and_water_collision2(collided2);

    //Set bailey state
    auto bailey_in_safe_zone = logic.bailey_object.get_if_bailey_in_safe_zone();
    if ((collided1 || collided2))
    {
        logic.bailey_object.set_bailey_to_dead(false);
    }
    else if ((!bailey_in_safe_zone) && (!(collided1 || collided2)))
    {
        logic.bailey_object.set_bailey_to_dead(true);
    }
}

void Screen::create_ice_blocks()
{
    auto ice_sprite1 = std::make_shared<Sprite>(Sprite());
    ice_sprite1 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite1 -> setTexture(ice_block_texture);
    ice_sprite1 -> setPosition(550.0f, 305.0f);
    ice_blocks_sprites.push_back(ice_sprite1);

    auto ice_sprite2 = std::make_shared<Sprite>(Sprite());
    ice_sprite2 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite2 -> setTexture(ice_block_texture);
    ice_sprite2 -> setPosition(250.0f, 387.0f);
    ice_blocks_sprites.push_back(ice_sprite2);

    auto ice_sprite3 = std::make_shared<Sprite>(Sprite());
    ice_sprite3 -> setOrigin(ice_width/2.0f,ice_height/2.0f);
    ice_sprite3 -> setTexture(ice_block_texture);
    ice_sprite3 -> setPosition(550.0f, 469.0f);
    ice_blocks_sprites.push_back(ice_sprite3);

    auto ice_sprite4 = std::make_shared<Sprite>(Sprite());
    ice_sprite4 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite4 -> setTexture(ice_block_texture);
    ice_sprite4 -> setPosition(250.0f, 551.0f);
    ice_blocks_sprites.push_back(ice_sprite4);

    logic.create_ice_block_objects(ice_blocks_sprites, vector1);
}

//This function will create batch of ice blocks from the second batch until game ends
//Violation of dry principle and needs fixing
void Screen::create_ice_block_batch(vector<shared_ptr<Sprite>>& ice_sprites, int vector_)
{
    //ice_sprites.clear();
    auto ice_sprite1 = std::make_shared<Sprite>(Sprite());
    ice_sprite1 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite1 -> setTexture(ice_block_texture2);
    ice_sprite1 -> setPosition(960.0f, 305.0f);
    ice_sprites.push_back(ice_sprite1);

    auto ice_sprite2 = std::make_shared<Sprite>(Sprite());
    ice_sprite2 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite2 -> setTexture(ice_block_texture2);
    ice_sprite2 -> setPosition(-160.0f, 387.0f);
    ice_sprites.push_back(ice_sprite2);

    auto ice_sprite3 = std::make_shared<Sprite>(Sprite());
    ice_sprite3 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite3 -> setTexture(ice_block_texture2);
    ice_sprite3 -> setPosition(960.0f, 469.0f);
    ice_sprites.push_back(ice_sprite3);

    auto ice_sprite4 = std::make_shared<Sprite>(Sprite());
    ice_sprite4 -> setOrigin(ice_width/2.0f, ice_height/2.0f);
    ice_sprite4 -> setTexture(ice_block_texture2);
    ice_sprite4 -> setPosition(-160.0f, 551.0f);
    ice_sprites.push_back(ice_sprite4);

    new_ice_created = true;
    logic.create_ice_block_objects(ice_sprites,vector_);
}

void Screen::update_game_state()
{
    splash_screen_display.setPosition(125,208);
    splash_screen_display.setCharacterSize(20);

    auto bailey_in_safe_zone = logic.bailey_object.get_if_bailey_in_safe_zone();
    auto bailey_is_dead = logic.bailey_object.get_if_bailey_dead();

    if (bailey_is_dead)
    {
        is_playing = false;
        is_game_over = true;
        window.clear();
        splash_screen_display.setString("YOU LOST!"
                                        "\nGAME OVER");
    }

    auto igloo_complete = logic.mark_if_igloo_is_complete();
    if (bailey_in_safe_zone && igloo_complete)
    {
        window.setKeyRepeatEnabled(false);
        is_playing = false;
        is_game_over = true;
        logic.update_bailey(bailey_sprite);
        window.clear();
        splash_screen_display.setString("YOU WON!"
                                        "\nRETURNED SAFELY TO SAFE ZONE FROM BOTTOM");
    }
}

void Screen::initialize_igloo()
{
    auto position = logic.get_igloo_position();
    auto ptr = std::make_shared<Sprite>(Sprite());
    igloo_texture.loadFromFile("resources/igloo0.png");
    ptr ->setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
    ptr -> setTexture(igloo_texture);
    ptr -> setPosition(position.x, position.y);
    Igloo_house_sprites.push_back(ptr);
}

void Screen::load_textures()
{
    ice_block_texture2.loadFromFile("resources/whiteIce.png");
    ice_block_texture.loadFromFile("resources/whiteIce.png");
}

Screen::~Screen() 
{
    //Free memory
    ice_blocks_sprites.clear();
    ice_blocks_sprites2.clear();
    Igloo_house_sprites.clear();
}
