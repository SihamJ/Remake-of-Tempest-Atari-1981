#include "../headers/Level.hpp"

Level::Level(){}

Level::Level(int a){
    std::cout << "Level constructor" << std::endl;
}

Level::~Level(){}

std::shared_ptr<Tube> Level::get_map(){
    return this->map;
}

std::map<int, Color> Level::get_enemies(){
    return this->current_enemies;
}

const int Level::get_nb_enemies(){
    return this->current_enemies.size();
}

Color Level::get_player_color(){
    return this->current_player_color;
}

Color Level::get_map_color(){
    return this->map->get_color();
}

void Level::print(){
    std::cout << "This is level " << this->current_level << std::endl;
    std::cout << "The tube is " << this->map->get_name() << std::endl;
}

void Level::set_current_level(int level){
    this->current_level = level;
}
int Level::get_current_level(){
    return this->current_level;
}

// TO DO: create the other maps and uncomment this code
void Level::set_map(){

    Color c;

    if(this->current_level > 0 && this->current_level < 17){
        c = level1_16_map_color;
    }
    else if(this->current_level >= 17 && this->current_level < 33){
        c = level17_32_map_color;
    }
    else if(this->current_level >= 33 && this->current_level < 49){
        c = level33_48_map_color;
    }
    else if(this->current_level >= 49 && this->current_level < 65){
        c = level49_64_map_color;
    }
    else if (this->current_level >= 65 && this->current_level < 81){
        c = level65_80_map_color;
    }
    else if(this->current_level >= 81){
        c = level81_96_map_color;
    }

    switch ( (this->current_level-1) % 16 )
    {
    // case maps_list::circle:
    //     this->map = std::make_shared<Circle>();
    //     break;
    // case maps_list::square:
    //     this->map = std::make_shared<Square>();
    //     break;
    // case maps_list::plussymbol:
    //     this->map = std::make_shared<PlusSymbol>();
    //     break;
    // case maps_list::blowtie:
    //     this->map = std::make_shared<BlowTie>();
    //     break;
    // case maps_list::stylizedcross:
    //     this->map = std::make_shared<StylizedCross>();
    //     break;
    case maps_list::triangle:
        this->map = std::make_shared<TriangleMap>(9, WIDTH, HEIGHT, c);
        break;
    // case maps_list::clover:
    //     this->map = std::make_shared<Clover>();
    //     break;
    // case maps_list::v:
    //     this->map = std::make_shared<V>();
    //     break;
    // case maps_list::steps:
    //     this->map = std::make_shared<Steps>();
    //     break;
    // case maps_list::u:
    //     this->map = std::make_shared<U>();
    //     break;
    // case maps_list::completelyflat:
    //     this->map = std::make_shared<CompletelyFlat>();
    //     break;
    // case maps_list::heart:
    //     this->map = std::make_shared<Heart>();
    //     break;
    // case maps_list::star:
    //     this->map = std::make_shared<Star>();
    //     break;
    // case maps_list::w:
    //     this->map = std::make_shared<W>();
    //     break;
    // case maps_list::fan:
    //     this->map = std::make_shared<Fan>();
    //     break;
    // case maps_list::infinitysymbol:
    //     this->map = std::make_shared<InfinitySymbol>();
    //     break;
    default:
        this->map = std::make_shared<TriangleMap>(9, WIDTH, HEIGHT, c);
        break;
    }
}

// Depending on which level we are, we retrieve the current enemies colors from the const static variables of the class 
void Level::set_enemies(){
    if(this->current_level > 0 && this->current_level < 17){
        this->current_enemies = level1_16_characters;
    }
    else if(this->current_level >= 17 && this->current_level < 33){
        this->current_enemies = level17_32_characters;
    }
    else if(this->current_level >= 33 && this->current_level < 49){
        this->current_enemies = level33_48_characters;
    }
    else if(this->current_level >= 49 && this->current_level < 65){
        this->current_enemies = level49_64_characters;
    }
    else if (this->current_level >= 65 && this->current_level < 81){
        this->current_enemies = level65_80_characters;
    }
    else if(this->current_level >= 81 && this->current_level < 97){
        this->current_enemies = level81_96_characters;
    }
    else if(this->current_level >= 97){
        this->current_enemies = level81_96_characters;
    }
}

void Level::set_player_color(){

    if(this->current_level > 0 && this->current_level < 17){
        this->current_player_color = level1_16_player_color;
    }
    else if(this->current_level >= 17 && this->current_level < 33){
        this->current_player_color = level17_32_player_color;
    }
    else if(this->current_level >= 33 && this->current_level < 49){
        this->current_player_color = level33_48_player_color;
    }
    else if(this->current_level >= 49 && this->current_level < 65){
        this->current_player_color = level49_64_player_color;
    }
    else if (this->current_level >= 65 && this->current_level < 81){
        this->current_player_color = level65_80_player_color;
    }
    else if(this->current_level >= 81 && this->current_level < 97){
        this->current_player_color = level81_96_player_color;
    }
    else if(this->current_level >= 97){
        this->current_player_color = level81_96_player_color;
    }
}

// at this stage, we only have triangle map, so we will play at level 6 only
void Level::next_level(){
    //this->current_level++;    
    this->set_current_level(6);
    this->set_map();
    this->set_enemies();
    this->set_player_color();
}


// TO DO: create the other enemies classes and uncomment the code

std::shared_ptr<Enemy> Level::new_enemy(){
    // affiche que des flippers et spikers
    // int i = rand() % 2;
    // if (i == 1) i++;

    // force à afficher que des flippers
    // int i = 0;
    
    //force à afficher que des tankers
    int i = 1;

    // force à afficher que des spikers
    // int i = 2;

    Color color = this->current_enemies.at(i);
    std::shared_ptr<Enemy> e;
    
    switch (i)
    {
    case enemies_list::flippers:
        e = std::make_shared<Flippers>("flippers", std::move(color));
        break;
    case enemies_list::spikers:
        e = std::make_shared<Spikers>("spikers", std::move(color));
        break;
    case enemies_list::tankers:
        e = std::make_shared<Tankers>("tankers", std::move(color));
        break;
    // case enemies_list::superzapper:
    //     e = std::make_shared<SuperZapper>("superzapper", std::move(color));
    //     break;
    // case enemies_list::pulsars:
    //     e = std::make_shared<Pulsars>("pulsars", std::move(color));
    //     break;
    // case enemies_list::fuseballs:
    //     e = std::make_shared<Fuseballs>("fuseballs", std::move(color));
    //     break;

    // we don't have the other enemies for now, so we generate only flippers by default
    default:
        e = std::make_shared<Flippers>("flippers", std::move(color));
        break;
    }
    return e;
}