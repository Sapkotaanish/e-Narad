#pragma once
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <cstdint>
#include <iostream>
class Board
{
public:
  Board();
  void run();

private:
  int m_elements_array[3][3];
  int m_player_turn;
  sf::RenderWindow m_window;
  int m_window_height, m_window_width;
  sf::Texture m_zero_texture, m_x_texture, m_back_texture, m_background_texture,
      m_title_texture, m_restart_texture, m_x_turn_texture, m_o_turn_texture,
      m_game_over_texture, m_x_winner_texture, m_draw_texture,
      m_o_winner_texture;
  sf::Sprite m_zero_sprite, m_x_sprite, m_back_sprite, m_background_sprite,
      m_title_sprite, m_restart_sprite, m_turn_sprite, m_game_over_sprite,
      m_winner_sprite;
  sf::Font font;
  bool is_game_over, clicked, draw;
  sf::Vector2i mouse_position;
  sf::Vector2f offset;
  int gap, block_size, m_winner, play_count;

  sf::Vector2i FindBestMove(int board[3][3]);
  int MiniMax(int board[3][3], int depth, bool isMax);
  bool IsMovesLeft(int board[3][3]);
  int Evaluate(int board[3][3]);
  int player, opponent;

private:
  void Update();
  void ProcessEvents();
  void Render();
  void CheckGame();
  void ChangeSprite();
  sf::Vector2i MapCoordinateToElementArray(sf::Vector2i mouse_position);
};
