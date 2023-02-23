#ifndef SCREEN_H
#define SCREEN
#include "SfmlLibrary.h"
#include "Logic.h"

class Screen {
public:
    Screen();
    ~Screen();
    void run();

    //Vectors for game objects
    vector<shared_ptr<Sprite>> ice_blocks_sprites;
    vector<shared_ptr<Sprite>> ice_blocks_sprites2;
    bool can_create_new_batch_of_ice_blocks;
    void initialize_igloo();

    //Enemy sprite vectors
    vector<shared_ptr<Sprite>> crabs;
    vector<shared_ptr<Sprite>> clamps;
    vector<shared_ptr<Sprite>> birds;
    vector<shared_ptr<Sprite>> fish;

private:
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

    Texture igloo_texture;
    vector<shared_ptr<Sprite>> Igloo_house_sprites;
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

    //Create a new batch of ice blocks
    void create_ice_block_batch(vector<shared_ptr<Sprite>>&, int);

    bool new_ice_created;
    int vector1;
    int vector2;

    void update_game_state(const float&);

    bool collided1;
    bool collided2;

    void load_textures();

    Clock time;

    bool isJumping;
    bool isJumpingUp;
    bool isJumpingDown;

};

#endif // SCREEN_H
