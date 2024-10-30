#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "UserInterface.hpp"

class Dropdownbox: public UserInterface {
private:
    sf::RectangleShape m_button;
    sf::Text m_text;

    std::vector<sf::RectangleShape> m_itemButtons;
    std::vector<sf::Text> m_itemTexts;

    sf::Vector2f m_pos  = { 10.0f, 10.0f };
    sf::Vector2f m_size = { 200.0f, 40.0f };

    sf::Color m_colors[4] = { {20, 25, 30, 255}, {146, 134, 148, 255}, {255, 255, 255, 128}, {255, 255, 255, 200} };

    sf::Color m_fillColor    = m_colors[0];
    sf::Color m_clickColor   = m_colors[1];
    sf::Color m_outlineColor = m_colors[2];
    sf::Color m_labelColor   = m_colors[3];

    float m_thickness = 2.0f;
    int m_selectedItem = -1;
    bool m_isOpen = false;
    bool m_openUpwards = false;
    bool m_mousePressed = false;
    float m_characterSize = 0.0f;

    void toggleMenu();
    void selectItem(unsigned int index);
    void adjustMenuDirection(const sf::RenderWindow& surface);

public:
    Dropdownbox(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& label, const std::vector<std::string>& items);

    void update(const sf::Vector2f& mousePos);
    std::string getSelectedItem() const;

    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface) override;
};