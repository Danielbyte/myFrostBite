#ifndef SCREEN_H
#define SCREEN
#include "SfmlLibrary.h"
#include "Logic.h"
#include "stopwatch.h"

class Screen {
public:
    Screen();
    ~Screen();
    void run();

    //Vectors for game objects
    vector<shared_ptr<Sprite>> ice_blocks_sprites;
    void initialize_igloo();

    //Enemy sprite vectors
    vector<shared_ptr<Sprite>> crabs;
    vector<shared_ptr<Sprite>> clamps;
    vector<shared_ptr<Sprite>> birds;
    vector<shared_ptr<Sprite>> fish;

    //Draw sea animals
    void draw_crabs();
    void draw_clamps();
    void draw_fish();
    void draw_birds();

private:
    void update_temperature();
    void initialize_temperature();
    Stopwatch tempStopWatch;
    bool startedTempDecrease; //mark when started decreasig the temperature
    bool timeUp;
    int temperature;
    RenderWindow window;
    void initialize_screen();

    //DISPLAYS
    Font displays;

    //splash screen displays
    Font splash_screen_font;
    Text splash_screen_display;
    Text game_instructions;

    //Game control
    bool is_playing;
    bool is_game_over;
    bool quit_game;

    //HANDLE USER INPUTS
    void process_user_inputs(const float&);
    void keyboard_handling(Keyboard,bool,const float&);

    //GAME INITIALISATION
    void initialise_player();
    void initialise_background();
    void create_ice_blocks();
    void initialise_bear();

    //GAME GRAPHICS
    Texture bailey_texture;
    Sprite bailey_sprite;
    Texture background_texture;
    Sprite background_sprite;

    Texture ice_block_texture;
    Sprite ice_block_sprite;

    Texture ice_block_texture2;
    Sprite ice_block_sprite2;

    Texture mainscreen;
    Sprite _mainscreen;

    Texture cursor;
    Sprite _cursor;
    void initialize_cursor();
    vector2f cursor_position;
    void set_cursor_x_position();
    bool startGamePlay;

    Texture igloo_texture;
    shared_ptr<Sprite> Igloo_house_sprite = std::make_shared<Sprite>(Sprite());
    void draw_igloo_house();

    Texture bear_texture;
    Sprite bear_sprite;

    void draw_game_objects();
    void draw_ice_blocks();

    //Access the logic layer
    Logic logic;

    //Update game sprites
    void update_game_sprites(const float&);

    //Update game
    void update_game(const float&);

    void update_game_state(const float&);

    void load_textures();

    Clock time;

    bool isJumping;
    bool isJumpingUp;
    bool isJumpingDown;

    Text temperature_disp;
    Text degree_symbol;


    void draw_game_entities();
    vector2f distanceBetweenDoorAndBailey;
    std::tuple<vector2f&,float&,float&> calculateDistanceBetweenBaileyAndDoor();
    float igloorDoorOffset;
    float goingInIgloo_X_speed;
    float goingInIgloo_Y_speed;
    void draw_animations();

};

#endif // SCREEN_H
