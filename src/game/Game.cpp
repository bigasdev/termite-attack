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

//game area 
int game_area_x = 600, game_area_y = 900;

int get_game_area_x() {
  return game_area_x / 2;
}

int get_game_area_y() {
  return game_area_y / 2;
}

//termites 
std::vector<Termite*> termites;

Game::Game() {
}

Game::~Game() {
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

  hero = std::make_unique<Wisp>("wisp", vec2{0, 350});
  board = std::make_unique<Entity>("board", vec2{0, 350});
}

void Game::fixed_update(double tmod) {
  hero->fixed_update(tmod);
  board->fixed_update(tmod);

  dx += (g_input_manager->get_raw_axis().x * 17.5) * tmod;
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

  //attached wisp
  if(hero->is_attached){
    hero.get()->pos = vec2{board->pos.x, board->pos.y - 10};
  }

  hero->update(dt);
  board->update(dt);

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
  Rect playing_area = Rect(-get_game_area_x(), -get_game_area_y(), game_area_x, game_area_y);
  g_renderer->draw_rect(playing_area, Col{0,255,0,255}, false);
}

void Game::draw_ent(){
  g_renderer->draw(*g_res->get_texture(board->spr.sheet), board->spr, board->pos);
  g_renderer->draw(*g_res->get_texture(hero->spr.sheet), hero->spr, hero->pos);
}
void Game::draw_ui(){
}

void Game::clean() {
}


