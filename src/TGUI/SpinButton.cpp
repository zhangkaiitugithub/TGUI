/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Container.hpp>
#include <TGUI/SpinButton.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::SpinButton() :
    m_verticalScroll      (true),
    m_minimum             (0),
    m_maximum             (10),
    m_value               (0),
    m_separateHoverImage  (false),
    m_mouseHoverOnTopArrow(false),
    m_mouseDownOnTopArrow (false)
    {
        m_callback.widgetType = Type_SpinButton;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::SpinButton(const SpinButton& copy) :
    ClickableWidget       (copy),
    m_loadedConfigFile    (copy.m_loadedConfigFile),
    m_verticalScroll      (copy.m_verticalScroll),
    m_minimum             (copy.m_minimum),
    m_maximum             (copy.m_maximum),
    m_value               (copy.m_value),
    m_separateHoverImage  (copy.m_separateHoverImage),
    m_mouseHoverOnTopArrow(copy.m_mouseHoverOnTopArrow),
    m_mouseDownOnTopArrow (copy.m_mouseDownOnTopArrow)
    {
        TGUI_TextureManager.copyTexture(copy.m_textureArrowUpNormal, m_textureArrowUpNormal);
        TGUI_TextureManager.copyTexture(copy.m_textureArrowUpHover, m_textureArrowUpHover);
        TGUI_TextureManager.copyTexture(copy.m_textureArrowDownNormal, m_textureArrowDownNormal);
        TGUI_TextureManager.copyTexture(copy.m_textureArrowDownHover, m_textureArrowDownHover);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::~SpinButton()
    {
        if (m_textureArrowUpNormal.getData() != nullptr)    TGUI_TextureManager.removeTexture(m_textureArrowUpNormal);
        if (m_textureArrowUpHover.getData() != nullptr)     TGUI_TextureManager.removeTexture(m_textureArrowUpHover);
        if (m_textureArrowDownNormal.getData() != nullptr)  TGUI_TextureManager.removeTexture(m_textureArrowDownNormal);
        if (m_textureArrowDownHover.getData() != nullptr)   TGUI_TextureManager.removeTexture(m_textureArrowDownHover);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton& SpinButton::operator= (const SpinButton& right)
    {
        // Make sure it is not the same widget
        if (this != &right)
        {
            SpinButton temp(right);
            this->ClickableWidget::operator=(right);

            std::swap(m_loadedConfigFile,       temp.m_loadedConfigFile);
            std::swap(m_verticalScroll,         temp.m_verticalScroll);
            std::swap(m_minimum,                temp.m_minimum);
            std::swap(m_maximum,                temp.m_maximum);
            std::swap(m_value,                  temp.m_value);
            std::swap(m_separateHoverImage,     temp.m_separateHoverImage);
            std::swap(m_mouseHoverOnTopArrow,   temp.m_mouseHoverOnTopArrow);
            std::swap(m_mouseDownOnTopArrow,    temp.m_mouseDownOnTopArrow);
            std::swap(m_textureArrowUpNormal,   temp.m_textureArrowUpNormal);
            std::swap(m_textureArrowUpHover,    temp.m_textureArrowUpHover);
            std::swap(m_textureArrowDownNormal, temp.m_textureArrowDownNormal);
            std::swap(m_textureArrowDownHover,  temp.m_textureArrowDownHover);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton* SpinButton::clone()
    {
        return new SpinButton(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SpinButton::load(const std::string& configFileFilename)
    {
        m_loadedConfigFile = getResourcePath() + configFileFilename;

        // When everything is loaded successfully, this will become true.
        m_loaded = false;

        // If the button was loaded before then remove the old textures first
        if (m_textureArrowUpNormal.getData() != nullptr)   TGUI_TextureManager.removeTexture(m_textureArrowUpNormal);
        if (m_textureArrowUpHover.getData() != nullptr)    TGUI_TextureManager.removeTexture(m_textureArrowUpHover);
        if (m_textureArrowDownNormal.getData() != nullptr) TGUI_TextureManager.removeTexture(m_textureArrowDownNormal);
        if (m_textureArrowDownHover.getData() != nullptr)  TGUI_TextureManager.removeTexture(m_textureArrowDownHover);

        // Open the config file
        ConfigFile configFile;
        if (!configFile.open(m_loadedConfigFile))
        {
            TGUI_OUTPUT("TGUI error: Failed to open " + m_loadedConfigFile + ".");
            return false;
        }

        // Read the properties and their values (as strings)
        std::vector<std::string> properties;
        std::vector<std::string> values;
        if (!configFile.read("SpinButton", properties, values))
        {
            TGUI_OUTPUT("TGUI error: Failed to parse " + m_loadedConfigFile + ".");
            return false;
        }

        // Close the config file
        configFile.close();

        // Find the folder that contains the config file
        std::string configFileFolder = "";
        std::string::size_type slashPos = m_loadedConfigFile.find_last_of("/\\");
        if (slashPos != std::string::npos)
            configFileFolder = m_loadedConfigFile.substr(0, slashPos+1);

        // Handle the read properties
        for (unsigned int i = 0; i < properties.size(); ++i)
        {
            std::string property = properties[i];
            std::string value = values[i];

            if (property == "separatehoverimage")
            {
                m_separateHoverImage = configFile.readBool(value, false);
            }
            else if (property == "arrowupnormalimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_textureArrowUpNormal))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for ArrowUpNormalImage in section SpinButton in " + m_loadedConfigFile + ".");
                    return false;
                }
            }
            else if (property == "arrowuphoverimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_textureArrowUpHover))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for ArrowUpHoverImage in section SpinButton in " + m_loadedConfigFile + ".");
                    return false;
                }
            }
            else if (property == "arrowdownnormalimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_textureArrowDownNormal))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for ArrowDownNormalImage in section SpinButton in " + m_loadedConfigFile + ".");
                    return false;
                }
            }
            else if (property == "arrowdownhoverimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_textureArrowDownHover))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for ArrowDownHoverImage in section SpinButton in " + m_loadedConfigFile + ".");
                    return false;
                }
            }
            else
                TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section SpinButton in " + m_loadedConfigFile + ".");
        }

        // Make sure the required textures were loaded
        if ((m_textureArrowUpNormal.getData() != nullptr) && (m_textureArrowDownNormal.getData() != nullptr))
        {
            m_size.x = static_cast<float>(m_textureArrowUpNormal.getSize().x);
            m_size.y = static_cast<float>(m_textureArrowUpNormal.getSize().y + m_textureArrowDownNormal.getSize().y);
        }
        else
        {
            TGUI_OUTPUT("TGUI error: Not all needed images were loaded for the spin button. Is the SpinButton section in " + m_loadedConfigFile + " complete?");
            return false;
        }

        return m_loaded = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::string& SpinButton::getLoadedConfigFile() const
    {
        return m_loadedConfigFile;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setSize(float width, float height)
    {
        // Don't do anything when the spin button wasn't loaded correctly
        if (m_loaded == false)
            return;

        // Store the new size
        m_size.x = width;
        m_size.y = height;

        // A negative size is not allowed for this widget
        if (m_size.x < 0) m_size.x = -m_size.x;
        if (m_size.y < 0) m_size.y = -m_size.y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setMinimum(unsigned int minimum)
    {
        // Set the new minimum
        m_minimum = minimum;

        // The minimum can never be greater than the maximum
        if (m_minimum > m_maximum)
            m_maximum = m_minimum;

        // When the value is below the minimum then adjust it
        if (m_value < m_minimum)
            m_value = m_minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setMaximum(unsigned int maximum)
    {
        m_maximum = maximum;

        // The maximum can never be below the minimum
        if (m_maximum < m_minimum)
            m_minimum = m_maximum;

        // When the value is above the maximum then adjust it
        if (m_value > m_maximum)
            m_value = m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setValue(unsigned int value)
    {
        // Set the new value
        m_value = value;

        // When the value is below the minimum or above the maximum then adjust it
        if (m_value < m_minimum)
            m_value = m_minimum;
        else if (m_value > m_maximum)
            m_value = m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int SpinButton::getMinimum() const
    {
        return m_minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int SpinButton::getMaximum() const
    {
        return m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int SpinButton::getValue() const
    {
        return m_value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setVerticalScroll(bool verticalScroll)
    {
        m_verticalScroll = verticalScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SpinButton::getVerticalScroll() const
    {
        return m_verticalScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setTransparency(unsigned char transparency)
    {
        ClickableWidget::setTransparency(transparency);

        m_textureArrowUpNormal.setColor(sf::Color(255, 255, 255, m_opacity));
        m_textureArrowUpHover.setColor(sf::Color(255, 255, 255, m_opacity));
        m_textureArrowDownNormal.setColor(sf::Color(255, 255, 255, m_opacity));
        m_textureArrowDownHover.setColor(sf::Color(255, 255, 255, m_opacity));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::leftMousePressed(float x, float y)
    {
        m_mouseDown = true;

        // Check if the mouse is on top of the upper/right arrow
        if (m_verticalScroll)
        {
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x, m_size.y / 2.f)).contains(x, y))
                m_mouseDownOnTopArrow = true;
            else
                m_mouseDownOnTopArrow = false;
        }
        else
        {
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x / 2.f, m_size.y)).contains(x, y))
                m_mouseDownOnTopArrow = false;
            else
                m_mouseDownOnTopArrow = true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::leftMouseReleased(float x, float y)
    {
        // Check if the mouse went down on the spin button
        if (m_mouseDown)
        {
            m_mouseDown = false;

            // Check if the arrow went down on the top/right arrow
            if (m_mouseDownOnTopArrow)
            {
                // Check if the mouse went up on the same arrow
                if (((m_verticalScroll == true)  && (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x, m_size.y / 2.f)).contains(x, y)))
                 || ((m_verticalScroll == false) && (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x / 2.f, m_size.y)).contains(x, y) == false)))
                {
                    // Increment the value
                    if (m_value < m_maximum)
                        ++m_value;
                    else
                        return;
                }
                else
                    return;
            }
            else // The mouse went down on the bottom/left arrow
            {
                // Check if the mouse went up on the same arrow
                if (((m_verticalScroll == true)  && (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x, m_size.y / 2.f)).contains(x, y) == false))
                 || ((m_verticalScroll == false) && (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x / 2.f, m_size.y)).contains(x, y))))
                {
                    // Decrement the value
                    if (m_value > m_minimum)
                        --m_value;
                    else
                        return;
                }
                else
                    return;
            }

            // Add the callback (if the user requested it)
            if (m_callbackFunctions[ValueChanged].empty() == false)
            {
                m_callback.trigger = ValueChanged;
                m_callback.value   = static_cast<int>(m_value);
                addCallback();
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::mouseMoved(float x, float y)
    {
        // Check if the mouse is on top of the upper/right arrow
        if (m_verticalScroll)
        {
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x, m_size.y / 2.f)).contains(x, y))
                m_mouseHoverOnTopArrow = true;
            else
                m_mouseHoverOnTopArrow = false;
        }
        else
        {
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_size.x / 2.f, m_size.y)).contains(x, y))
                m_mouseHoverOnTopArrow = false;
            else
                m_mouseHoverOnTopArrow = true;
        }

        if (m_mouseHover == false)
            mouseEnteredWidget();

        m_mouseHover = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::widgetFocused()
    {
        // A spin button can't be focused
        unfocus();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SpinButton::setProperty(std::string property, const std::string& value)
    {
        property = toLower(property);

        if (property == "configfile")
        {
            load(value);
        }
        else if (property == "minimum")
        {
            setMinimum(std::stoi(value));
        }
        else if (property == "maximum")
        {
            setMaximum(std::stoi(value));
        }
        else if (property == "value")
        {
            setValue(std::stoi(value));
        }
        else if (property == "verticalscroll")
        {
            if ((value == "true") || (value == "True"))
                setVerticalScroll(true);
            else if ((value == "false") || (value == "False"))
                setVerticalScroll(false);
            else
                TGUI_OUTPUT("TGUI error: Failed to parse 'VerticalScroll' property.");
        }
        else if (property == "callback")
        {
            ClickableWidget::setProperty(property, value);

            std::vector<sf::String> callbacks;
            decodeList(value, callbacks);

            for (auto it = callbacks.begin(); it != callbacks.end(); ++it)
            {
                if ((*it == "ValueChanged") || (*it == "valuechanged"))
                    bindCallback(ValueChanged);
            }
        }
        else // The property didn't match
            return ClickableWidget::setProperty(property, value);

        // You pass here when one of the properties matched
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SpinButton::getProperty(std::string property, std::string& value) const
    {
        property = toLower(property);

        if (property == "configfile")
            value = getLoadedConfigFile();
        else if (property == "minimum")
            value = std::to_string(getMinimum());
        else if (property == "maximum")
            value = std::to_string(getMaximum());
        else if (property == "value")
            value = std::to_string(getValue());
        else if (property == "verticalscroll")
            value = m_verticalScroll ? "true" : "false";
        else if (property == "callback")
        {
            std::string tempValue;
            ClickableWidget::getProperty(property, tempValue);

            std::vector<sf::String> callbacks;

            if ((m_callbackFunctions.find(ValueChanged) != m_callbackFunctions.end()) && (m_callbackFunctions.at(ValueChanged).size() == 1) && (m_callbackFunctions.at(ValueChanged).front() == nullptr))
                callbacks.push_back("ValueChanged");

            encodeList(callbacks, value);

            if (value.empty())
                value = tempValue;
            else if (!tempValue.empty())
                value += "," + tempValue;
        }
        else // The property didn't match
            return ClickableWidget::getProperty(property, value);

        // You pass here when one of the properties matched
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::list< std::pair<std::string, std::string> > SpinButton::getPropertyList() const
    {
        auto list = ClickableWidget::getPropertyList();
        list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
        list.push_back(std::pair<std::string, std::string>("Minimum", "uint"));
        list.push_back(std::pair<std::string, std::string>("Maximum", "uint"));
        list.push_back(std::pair<std::string, std::string>("Value", "uint"));
        list.push_back(std::pair<std::string, std::string>("VerticalScroll", "bool"));
        return list;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't draw when the spin button wasn't loaded correctly
        if (m_loaded == false)
            return;

        // Adjust the transformation
        states.transform *= getTransform();

        // Check if the image is drawn in the same direction than it was loaded
        if (m_verticalScroll)
        {
            states.transform.scale(m_size.x / m_textureArrowUpNormal.getSize().x, m_size.y / (m_textureArrowUpNormal.getSize().y + m_textureArrowDownNormal.getSize().y));

            // Draw the first arrow
            if (m_separateHoverImage)
            {
                if (m_mouseHover && m_mouseHoverOnTopArrow && m_textureArrowUpHover.getData())
                    target.draw(m_textureArrowUpHover, states);
                else
                    target.draw(m_textureArrowUpNormal, states);
            }
            else // The hover image should be drawn on top of the normal image
            {
                target.draw(m_textureArrowUpNormal, states);

                if (m_mouseHover && m_mouseHoverOnTopArrow && m_textureArrowUpHover.getData())
                    target.draw(m_textureArrowUpHover, states);
            }

            // Set the second arrow on the correct position
            states.transform.translate(0, static_cast<float>(m_textureArrowUpNormal.getSize().y));

            // Draw the second arrow
            if (m_separateHoverImage)
            {
                if (m_mouseHover && !m_mouseHoverOnTopArrow && m_textureArrowDownHover.getData())
                    target.draw(m_textureArrowDownHover, states);
                else
                    target.draw(m_textureArrowDownNormal, states);
            }
            else // The hover image should be drawn on top of the normal image
            {
                target.draw(m_textureArrowDownNormal, states);

                if (m_mouseHover && !m_mouseHoverOnTopArrow && m_textureArrowDownHover.getData())
                    target.draw(m_textureArrowDownHover, states);
            }
        }
        else // The image is not drawn in the same direction than the loaded image
        {
            states.transform.scale(m_size.x / (m_textureArrowUpNormal.getSize().y + m_textureArrowDownNormal.getSize().y), m_size.y / m_textureArrowUpNormal.getSize().x);

            // Rotate the arrow
            states.transform.rotate(-90, static_cast<float>(m_textureArrowUpNormal.getSize().x), static_cast<float>(m_textureArrowUpNormal.getSize().y));

            // Set the left arrow on the correct position
            states.transform.translate(static_cast<float>(m_textureArrowUpNormal.getSize().y), 0);

            // Draw the first arrow
            if (m_separateHoverImage)
            {
                if (m_mouseHover && !m_mouseHoverOnTopArrow && m_textureArrowUpHover.getData())
                    target.draw(m_textureArrowUpHover, states);
                else
                    target.draw(m_textureArrowUpNormal, states);
            }
            else // The hover image should be drawn on top of the normal image
            {
                target.draw(m_textureArrowUpNormal, states);

                if (m_mouseHover && !m_mouseHoverOnTopArrow && m_textureArrowUpHover.getData())
                    target.draw(m_textureArrowUpHover, states);
            }

            // Set the right arrow on the correct position
            states.transform.translate(0, static_cast<float>(m_textureArrowUpNormal.getSize().y));

            // Draw the second arrow
            if (m_separateHoverImage)
            {
                if (m_mouseHover && m_mouseHoverOnTopArrow && m_textureArrowDownHover.getData())
                    target.draw(m_textureArrowDownHover, states);
                else
                    target.draw(m_textureArrowDownNormal, states);
            }
            else // The hover image should be drawn on top of the normal image
            {
                target.draw(m_textureArrowDownNormal, states);

                if (m_mouseHover && m_mouseHoverOnTopArrow && m_textureArrowDownHover.getData())
                    target.draw(m_textureArrowDownHover, states);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
