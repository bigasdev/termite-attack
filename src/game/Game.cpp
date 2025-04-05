#include "Game.hpp"
#include "../renderer/Camera.hpp"
#include "../tools/Cooldown.hpp"
#include "../core/Engine.hpp"
#include "../core/InputManager.hpp"
#include "../renderer/Renderer.hpp"
#include "../res/Res.hpp"
#include "../core/global.hpp"
#include "../core/Timer.hpp"
#include "../tools/Math.hpp"
#include "../entity/Wisp.hpp"
#include "../entity/Termite.hpp"
#include "../renderer/Sprite.hpp"
#include "../tools/Logger.hpp"
#include "SDL.h"
#include <memory>
#include <string>

#include "../entity/Entity.hpp"

bool moving_right = false;
bool moving_left = false;
bool attack_press = false;

int hero_x = 2;
float timer = 0;

float dx, dy, dwood;
vec2 hero_pos;
vec2 wood_pos = {20, 40};

std::unique_ptr<Wisp> hero;
std::unique_ptr<Entity> board;
std::unique_ptr<Entity> map_bg;


int get_game_area_x() {
  return GAME_AREA_X / 2;
}

int get_game_area_y() {
  return GAME_AREA_Y / 2;
}

//termites 
std::vector<Termite*> termites;

Game::Game() {
}

Game::~Game() {
}

void spawn_termites() {
  for(int j = -get_game_area_y(); j < 0; j+= 36){
    for(int i = -get_game_area_x(); i < GAME_AREA_X - 300; i+= 36){
      Termite* t = new Termite("termite", vec2(i, j));
      t->life = 10;
      t->max_life = 20;
      termites.push_back(t);
    }
  }
}

void Game::init() {
  m_camera = new Camera(g_engine->get_window_size());
  m_cooldown = new Cooldown();

  g_cooldown = m_cooldown;
  g_camera = m_camera;

  g_input_manager->bind_keyboard(SDLK_e, &moving_right);
  g_input_manager->bind_keyboard(SDLK_q, &moving_left);
  g_input_manager->bind_keyboard(SDLK_SPACE, &attack_press);

  g_camera->track_pos(&hero_pos);

  map_bg = std::make_unique<Entity>("map_bg", vec2{0, 0});
  hero = std::make_unique<Wisp>("wisp", vec2{0, 350});
  board = std::make_unique<Entity>("board", vec2{0, 350});

  spawn_termites();
}

void Game::fixed_update(double tmod) {
  hero->fixed_update(tmod);
  board->fixed_update(tmod);
  for (auto& t : termites) {
    t->fixed_update(tmod);
  }

  dx += (g_input_manager->get_raw_axis().x * 37.5) * tmod;
  dx *= Math::pow(0.92f, tmod);
}

void Game::update(double dt) {
  m_cooldown->update(dt);

  board->dx = dx;
  board->dy = dy;

  //game bounds
  if (board->pos.x < -get_game_area_x()) {
    dx = 0;
    board->pos.x = -get_game_area_x();
  }
  if (board->pos.x > get_game_area_x() - 16 * g_camera->get_game_scale()) {
    dx = 0;
    board->pos.x = get_game_area_x() - 16 * g_camera->get_game_scale();
  }

  if(hero.get()->pos.x < -get_game_area_x()){
    hero.get()->wall_bump(1);
  }
  if(hero.get()->pos.x > get_game_area_x() - 16 * g_camera->get_game_scale()){
    hero.get()->wall_bump(-1);
  }
  
  if(hero.get()->pos.y > BOTTOM_AREA_Y){
    hero.get()->life -= 10 - hero.get()->endurance;
    hero->is_attached = true;
  }

  //attached wisp
  if(hero->is_attached){
    hero.get()->pos = vec2{board->pos.x, board->pos.y - 10};
  }else{
    for(auto& t : termites) {
      if(!t->can_collide())continue;
      if(hero.get()->get_collision_box().intersects(t->get_collision_box())){
        t->damage(hero.get()->attack);
        if(t->life <= 0)continue;
        hero.get()->bump(t->pos);
        
        continue;
      }
    }

    if(hero.get()->get_collision_box().intersects(board.get()->get_collision_box())){
      hero.get()->launch(board->pos);
    }
  }

  hero->update(dt);
  board->update(dt);
  for (auto& t : termites) {
    t->update(dt);
  }

  if (moving_left)
    m_camera->track_pos(&wood_pos);
  if(moving_right)
    m_camera->track_pos(&hero_pos);

  if(dx > 0){
    if(hero->is_attached){
      hero->spr.dir = 1;
    }
  }else if(dx < 0){
    if(hero->is_attached){
      hero->spr.dir = -1;
    }
  }

  timer += 1*dt;
  if(timer >= .1f){
    hero_x++;
    if(hero_x >= 6){
      hero_x = 2;
    }
    timer = 0;
  }

  if(attack_press && hero->is_attached){
    hero->dettach();
  }
  
}

void Game::post_update(double dt) {
  m_camera->move();
  m_camera->update();
}

void Game::draw_root() {
  g_renderer->draw(*g_res->get_texture(map_bg->spr.sheet), map_bg->spr, map_bg->pos);
}

void Game::draw_ent(){
  g_renderer->draw(*g_res->get_texture(board->spr.sheet), board->spr, board->pos);
  g_renderer->draw(*g_res->get_texture(hero->spr.sheet), hero->spr, hero->pos);

  for (auto& t : termites) {
    if(t->life <= 0)continue;
    g_renderer->draw(*g_res->get_texture(t->spr.sheet), t->spr, t->pos);
    t->draw();
  }
}
void Game::draw_ui(){
}

void Game::clean() {
}


