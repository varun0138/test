#include "Dropdownbox.hpp"

Dropdownbox::Dropdownbox(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& label, const std::vector<std::string>& items) : m_pos(pos), m_size(size){

    m_text.setFont(font);
    m_text.setString(label);

    for(unsigned int i = 0; i < items.size(); i++) {
        sf::RectangleShape itemButton;
        m_itemButtons.push_back(itemButton);

        sf::Text itemText;
        itemText.setFont(font);
        itemText.setString(items[i]);
        m_itemTexts.push_back(itemText);
    }

    m_characterSize = m_size.x / m_text.getString().getSize();
    for(unsigned int i = 0; i < m_itemTexts.size(); i++) {
        m_characterSize = std::min(m_characterSize, m_size.x / (float)m_itemTexts[i].getString().getSize());
    }
    m_characterSize = std::min(m_characterSize, m_size.y / 2.0f);
}

void Dropdownbox::update(const sf::Vector2f& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mousePressed) {
        if(m_button.getGlobalBounds().contains(mousePos)) {
            toggleMenu();
        }
        else if(m_isOpen) {
            for(unsigned int i = 0; i < m_itemTexts.size(); i++) {
                if(m_itemButtons[i].getGlobalBounds().contains(mousePos)) {
                    selectItem(i);
                    break;
                }
            }
        }
        m_mousePressed = true;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mousePressed) {
        m_mousePressed = false;
    }
}

std::string Dropdownbox::getSelectedItem() const {
    if(m_selectedItem >= 0 && m_selectedItem < (int)m_itemTexts.size()) {
        return m_itemTexts[m_selectedItem].getString();
    }
    return "";
}

void Dropdownbox::setMode(Mode mode) {
    m_fillColor    = convertMode(m_colors[0], mode);
    m_clickColor   = convertMode(m_colors[1], mode);
    m_outlineColor = convertMode(m_colors[2], mode);
    m_labelColor   = convertMode(m_colors[3], mode);
}

void Dropdownbox::draw(sf::RenderWindow& surface) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(surface);
    update(mousePos);

    m_button.setPosition(m_pos);
    m_button.setSize(m_size);
    m_button.setFillColor(m_fillColor);
    m_button.setOutlineColor(m_outlineColor);
    m_button.setOutlineThickness(m_thickness);

    m_text.setFillColor(m_labelColor);
    m_text.setCharacterSize(m_characterSize);

    const sf::FloatRect bounds = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { m_pos.x + m_size.x / 2.0f - bounds.width / 2.0f - bounds.left, m_pos.y + m_size.y / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);

    surface.draw(m_button);
    surface.draw(m_text);

    if(m_isOpen) {
        adjustMenuDirection(surface);
        for(unsigned int i = 0; i < m_itemTexts.size(); i++) {
            surface.draw(m_itemButtons[i]);
            surface.draw(m_itemTexts[i]);
        }
    }
}

void Dropdownbox::toggleMenu() {
    m_isOpen = !m_isOpen;
}

void Dropdownbox::selectItem(unsigned int index) {
    m_selectedItem = index;
    m_text.setString(m_itemTexts[index].getString());
    m_isOpen = false;
}

void Dropdownbox::adjustMenuDirection(const sf::RenderWindow& surface) {
    float spaceBelow = surface.getSize().y - m_pos.y - m_size.y;
    float dropboxHeight = m_itemButtons.size() * m_pos.y;

    if(dropboxHeight > spaceBelow) {
        m_openUpwards = true;
    }
    else {
        m_openUpwards = false;
    }

    for(unsigned int i = 0; i < m_itemButtons.size(); i++) {
        float y = m_openUpwards ? m_pos.y - ((i + 1) * m_size.y) : m_pos.y + ((i + 1) * m_size.y);

        m_itemButtons[i].setPosition(sf::Vector2f(m_pos.x, y));
        m_itemButtons[i].setSize(m_size);
        m_itemButtons[i].setFillColor(m_fillColor);
        m_itemButtons[i].setOutlineColor(m_outlineColor);
        m_itemButtons[i].setOutlineThickness(m_thickness);

        m_itemTexts[i].setFillColor(m_labelColor);
        m_itemTexts[i].setCharacterSize(m_characterSize);

        const sf::FloatRect bounds = m_itemTexts[i].getLocalBounds();
        const sf::Vector2f labelPos = { m_pos.x + m_size.x / 2.0f - bounds.width / 2.0f - bounds.left, y + m_size.y / 2.0f - bounds.height / 2.0f - bounds.top };
        m_itemTexts[i].setPosition(labelPos);
    }

}