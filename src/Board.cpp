#include "Board.h"

Board::Board() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m_elements_array[i][j] = -1;
        }
    }
    m_player_turn = 1;
    is_game_over = false;

    Display *d = XOpenDisplay(nullptr);
    Screen *s = DefaultScreenOfDisplay(d);

    int height = s->height;
    int width = s->width;

    m_window_width = 1.f / 3.f * width;
    m_window_height = m_window_width;

    gap = 20;
    block_size = 100;

    int board_size = 3 * block_size + 2 * gap;
    offset.x = m_window_width / 2.0f - board_size / 2.0f;
    offset.y = offset.x + 50;
    is_game_over = false;
    m_winner = -2;
    draw = false;
    clicked = false;
    play_count = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window.create(sf::VideoMode(m_window_width, m_window_height), "TicTacToe",
                    sf::Style::Close | sf::Style::Titlebar, settings);
    m_window.setPosition(sf::Vector2i(width / 2 - m_window_width / 2,
                                      height / 2 - m_window_height / 2));

    player = 0;
    opponent = 1;

    font.loadFromFile("assets/fonts/ubuntu.ttf");

    m_zero_texture.loadFromFile("assets/images/zero.png");
    m_zero_sprite.setTexture(m_zero_texture);

    m_x_texture.loadFromFile("assets/images/x.png");
    m_x_sprite.setTexture(m_x_texture);

    m_back_texture.loadFromFile("assets/images/back.jpg");
    m_back_sprite.setTexture(m_back_texture);

    m_background_texture.loadFromFile("assets/images/full_background.jpg");
    m_background_sprite.setTexture(m_background_texture);

    m_title_texture.loadFromFile("assets/images/ttt.png");
    m_title_sprite.setOrigin(m_title_texture.getSize().x / 2.0f, 0);
    m_title_sprite.setTexture(m_title_texture);
    m_title_sprite.setPosition(m_window_width / 2.0f, 20);

    m_restart_texture.loadFromFile("assets/images/restart.png");
    m_restart_sprite.setTexture(m_restart_texture);
    m_restart_sprite.setPosition(m_window_width - m_restart_texture.getSize().x,
                                 m_window_height -
                                     m_restart_texture.getSize().y);

    m_game_over_texture.loadFromFile("assets/images/game_over.jpg");
    m_game_over_sprite.setOrigin(m_game_over_texture.getSize().x / 2.0f, 0);
    m_game_over_sprite.setTexture(m_game_over_texture);
    m_game_over_sprite.setPosition(m_window_width / 2.0f, 20);

    m_o_turn_texture.loadFromFile("assets/images/o_turn.png");
    m_x_turn_texture.loadFromFile("assets/images/x_turn.png");
    if (m_player_turn == 0) {
        m_turn_sprite.setTexture(m_o_turn_texture);
    } else {
        m_turn_sprite.setTexture(m_x_turn_texture);
    }
    m_turn_sprite.setPosition(
        m_window_width / 2.0f - m_x_turn_texture.getSize().x / 2.0f,
        m_window_width - m_x_turn_texture.getSize().y - 20);

    m_o_winner_texture.loadFromFile("assets/images/o_wins.png");
    m_x_winner_texture.loadFromFile("assets/images/x_wins.png");
    m_draw_texture.loadFromFile("assets/images/draw.png");

    m_winner_sprite.setPosition(m_window_width / 2.0f,
                                20 + m_game_over_texture.getSize().y + 10);
}

void Board::run() {
    while (m_window.isOpen()) {

        ProcessEvents();
        Update();
        Render();
    }
}

void Board::ProcessEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                clicked = true;
                mouse_position = sf::Mouse::getPosition(m_window);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                clicked = false;
            }
        }
    }
}

void Board::Update() {

    if (is_game_over) {
        if (clicked) {
            sf::Vector2i s_index = sf::Mouse::getPosition(m_window);
            sf::Vector2f position = m_restart_sprite.getPosition();
            sf::Vector2u size = m_restart_texture.getSize();
            if (s_index.x >= position.x && s_index.x <= (position.x + size.x) &&
                s_index.y >= position.y && s_index.y <= (position.y + size.y)) {
                int count = 1;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        m_elements_array[i][j] = -1;
                    }
                }
                clicked = false;
                draw = false;
                is_game_over = false;
                m_player_turn = 1;
                play_count++;
            }
        }
    } else {

        if (m_player_turn) {
            if (clicked) {
                sf::Vector2i s_index = MapCoordinateToElementArray(
                    sf::Mouse::getPosition(m_window));
                if (s_index.x >= 0 && s_index.x <= 2 && s_index.y >= 0 &&
                    s_index.y <= 2) {
                    if (m_elements_array[s_index.x][s_index.y] == -1) {
                        m_elements_array[s_index.x][s_index.y] = 1;
                        clicked = false;
                        m_player_turn = 0;
                        m_turn_sprite.setTexture(m_o_turn_texture);
                        play_count++;
                    }
                }
            }
        } else {
            // sf::Vector2i s_index =
            //     MapCoordinateToElementArray(sf::Mouse::getPosition(m_window));
            // if (s_index.x >= 0 && s_index.x <= 2 && s_index.y >= 0 &&
            //     s_index.y <= 2)
            // {
            //   if (m_elements_array[s_index.x][s_index.y] > 0)
            //   {
            //     m_elements_array[s_index.x][s_index.y] = -1;
            //     clicked = false;
            //     m_player_turn = 1;
            //     m_turn_sprite.setTexture(m_x_turn_texture);
            //   }
            // }
            sf::sleep(sf::seconds(1));
            sf::Vector2i best_move = FindBestMove(m_elements_array);
            m_elements_array[best_move.x][best_move.y] = 0;
            clicked = false;
            m_player_turn = 1;
            m_turn_sprite.setTexture(m_x_turn_texture);
        }
    }
    CheckGame();
}

sf::Vector2i Board::MapCoordinateToElementArray(sf::Vector2i mouse_position) {
    int x, y;
    int offseted_x = mouse_position.x - offset.x;
    int offseted_y = mouse_position.y - offset.y;
    x = static_cast<int>(offseted_x / block_size);
    y = static_cast<int>(offseted_y / block_size);
    return sf::Vector2i(y, x);
}

void Board::Render() {
    m_window.clear(sf::Color::Black);
    m_background_sprite.setPosition(0, 0);
    m_window.draw(m_background_sprite);
    m_window.draw(m_title_sprite);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_elements_array[i][j] == 0) {
                sf::Vector2f position{j * block_size + offset.x + (j)*gap,
                                      i * block_size + offset.y + (i)*gap};
                m_zero_sprite.setPosition(position);
                m_window.draw(m_zero_sprite);
            } else if (m_elements_array[i][j] == 1) {
                sf::Vector2f position{j * block_size + offset.x + (j)*gap,
                                      i * block_size + offset.y + (i)*gap};
                m_x_sprite.setPosition(position);
                m_window.draw(m_x_sprite);
            } else {
                sf::Vector2f position{j * block_size + offset.x + (j)*gap,
                                      i * block_size + offset.y + (i)*gap};
                m_back_sprite.setPosition(position);
                m_window.draw(m_back_sprite);
            }
        }
        if (!is_game_over)
            m_window.draw(m_turn_sprite);
    }
    if (is_game_over) {
        m_window.draw(m_game_over_sprite);
        m_window.draw(m_restart_sprite);
        m_window.draw(m_winner_sprite);
    }
    m_window.display();
}

void Board::CheckGame() {

    int winner;

    // any of the rows is same
    for (int i = 0; i <= 2; i++) {
        if (m_elements_array[i][0] == m_elements_array[i][1] &&
            m_elements_array[i][1] == m_elements_array[i][2] &&
            m_elements_array[i][0] != -1) {
            m_winner = m_elements_array[i][0];
            is_game_over = true;
            ChangeSprite();
            return;
        }
    }

    // any of the columns is same
    for (int i = 0; i <= 2; i++) {
        if (m_elements_array[0][i] == m_elements_array[1][i] &&
            m_elements_array[1][i] == m_elements_array[2][i] &&
            m_elements_array[0][i] != -1) {
            m_winner = m_elements_array[0][i];
            is_game_over = true;
            ChangeSprite();
            return;
        }
    }

    // 1st diagonal is same
    if (m_elements_array[0][0] == m_elements_array[1][1] &&
        m_elements_array[1][1] == m_elements_array[2][2] &&
        m_elements_array[0][0] != -1) {
        m_winner = m_elements_array[0][0];
        is_game_over = true;
        ChangeSprite();
        return;
    }

    // 2nd diagonal is same
    if (m_elements_array[0][2] == m_elements_array[1][1] &&
        m_elements_array[1][1] == m_elements_array[2][0] &&
        m_elements_array[0][2] != -1) {
        m_winner = m_elements_array[0][2];
        is_game_over = true;
        ChangeSprite();
        return;
    }
    // Checking the game is in continue mode or not
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_elements_array[i][j] > -1)
                ++count;

    // Checking the if game already draw
    if (count == 9) {
        is_game_over = true;
        draw = true;
        m_winner = -1;
        ChangeSprite();
    }
}

void Board::ChangeSprite() {
    if (m_winner == 0) {
        m_winner_sprite.setTexture(m_o_winner_texture);
        m_winner_sprite.setOrigin(m_o_winner_texture.getSize().x / 2.0f, 0);
    } else if (m_winner == 1) {
        m_winner_sprite.setTexture(m_x_winner_texture);
        m_winner_sprite.setOrigin(m_x_winner_texture.getSize().x / 2.0f, 0);
    } else if (m_winner == -1) {
        m_winner_sprite.setTexture(m_draw_texture);
        m_winner_sprite.setOrigin(m_draw_texture.getSize().x / 2.0f, 0);
    }
}

sf::Vector2i Board::FindBestMove(int board[3][3]) {
    int bestVal = -1000;
    sf::Vector2i bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == -1) {
                board[i][j] = player;
                int moveVal = MiniMax(board, 0, false);
                board[i][j] = -1;
                if (moveVal > bestVal) {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
int Board::MiniMax(int board[3][3], int depth, bool isMax) {
    int score = Evaluate(board);
    int best = 0;
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (!IsMovesLeft(board))
        return 0;
    if (isMax == true) {
        best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == -1) {
                    board[i][j] = player;
                    best = std::max(best, MiniMax(board, depth + 1, false));
                    board[i][j] = -1;
                }
            }
        }
    } else {
        best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == -1) {
                    board[i][j] = opponent;
                    best = std::min(best, MiniMax(board, depth + 1, true));
                    board[i][j] = -1;
                }
            }
        }
    }
    return best;
}
bool Board::IsMovesLeft(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == -1)
                return true;
        }
    }
    return false;
}

int Board::Evaluate(int b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == 0) {
                return +10;
            } else if (b[row][0] == 1)
                return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == 0) {
                return +10;
            } else if (b[0][col] == 1) {
                return -10;
            }
        }
    }
    if (b[0][0] == b[1][1] && b[0][0] == b[2][2]) {
        if (b[0][0] == 0)
            return +10;
        else if (b[0][0] == 1)
            return -10;
    }
    if (b[0][2] == b[1][1] && b[2][0] == b[1][1]) {
        if (b[1][1] == 0)
            return +10;
        else if (b[1][1] == 1)
            return -10;
    }
    return 0;
}
