/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_SPIN_BUTTON_HPP
#define TGUI_SPIN_BUTTON_HPP


#include <TGUI/Renderers/SpinButtonRenderer.hpp>
#include <TGUI/Widgets/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Spin button widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API SpinButton : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<SpinButton> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const SpinButton> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpinButton();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new spin button widget
        ///
        /// @param minimum  The minimum value of the spin button
        /// @param maximum  The maximum value of the spin button
        ///
        /// @return The new spin button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static SpinButton::Ptr create(int minimum = 0, int maximum = 10);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another spin button
        ///
        /// @param spinButton  The other spin button
        ///
        /// @return The new spin button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static SpinButton::Ptr copy(SpinButton::ConstPtr spinButton);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpinButtonRenderer* getSharedRenderer();
        const SpinButtonRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpinButtonRenderer* getRenderer();
        const SpinButtonRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the spin button
        ///
        /// @param size  The new size of the spin button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a minimum value
        ///
        /// @param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(int minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum value
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMinimum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value
        ///
        /// @param value  The new value
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value
        ///
        /// @return The current value
        ///
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void widgetFocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(std::string signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the arrows
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getArrowSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<SpinButton>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalInt onValueChange = {"ValueChanged"}; ///< Value of the scrollbar changed. Optional parameter: new value


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // Is the spin button draw vertically (arrows on top of each other)?
        bool m_verticalScroll = true;

        int m_minimum = 0;
        int m_maximum = 10;
        int m_value = 0;

        // On which arrow is the mouse?
        bool m_mouseHoverOnTopArrow = false;
        bool m_mouseDownOnTopArrow = false;

        Sprite m_spriteArrowUp;
        Sprite m_spriteArrowUpHover;
        Sprite m_spriteArrowDown;
        Sprite m_spriteArrowDownHover;

        // Cached renderer properties
        Borders m_bordersCached;
        Color   m_borderColorCached;
        Color   m_backgroundColorCached;
        Color   m_backgroundColorHoverCached;
        Color   m_arrowColorCached;
        Color   m_arrowColorHoverCached;
        float   m_spaceBetweenArrowsCached = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SPIN_BUTTON_HPP
