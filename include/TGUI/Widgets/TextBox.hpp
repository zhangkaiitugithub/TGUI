/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_TEXT_BOX_HPP
#define TGUI_TEXT_BOX_HPP


#include <TGUI/CopiedSharedPtr.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/TextBoxRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Text box widget
    ///
    /// A text box is a multi-line input box which supports word-wrap and a vertical scrollbar.
    /// If you are looking for a single line input field (with options like setting a password character or displaying a
    /// default text when it is empty) then check out the EditBox class.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API TextBox : public Widget
    {
    public:

        typedef std::shared_ptr<TextBox> Ptr; //!< Shared widget pointer
        typedef std::shared_ptr<const TextBox> ConstPtr; //!< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new text box widget
        ///
        /// @return The new text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another text box
        ///
        /// @param textBox  The other text box
        ///
        /// @return The new text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr copy(TextBox::ConstPtr textBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBoxRenderer* getSharedRenderer();
        const TextBoxRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBoxRenderer* getRenderer();
        const TextBoxRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the text box
        ///
        /// This size does not include the borders.
        ///
        /// @param size  The new size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the text box
        ///
        /// @param text  New text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Appends some text to the text that was already in the text box
        ///
        /// @param text  Text that will be added to the text that is already in the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addText(const String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of the text box
        ///
        /// @return  The text that is currently inside the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default text of the textbox. This is the text drawn when the text box is empty
        ///
        /// @param text  The new default text
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDefaultText(const String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default text of the text box. This is the text drawn when the text box is empty
        ///
        /// @return The default text of the text box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const String& getDefaultText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes which part of the text is selected
        ///
        /// @param selectionStartIndex Amount of characters before the start of the selection
        /// @param selectionEndIndex   Amount of characters before the end of the selection
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedText(std::size_t selectionStartIndex, std::size_t selectionEndIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text that you currently have selected
        ///
        /// @return The selected text of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getSelectedText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the index where the selection starts
        ///
        /// When no text is selected, this function returns the same getSelectionEnd.
        ///
        /// Note that the start of the selection may be behind the end of the selection when the user selected the text from
        /// right to left or from bottom to top.
        ///
        /// @return Amount of characters before the start of the selection
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getSelectionStart() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the index where the selection ends
        ///
        /// The selection end always equals the caret position.
        ///
        /// Note that the start of the selection may be behind the end of the selection when the user selected the text from
        /// right to left or from bottom to top.
        ///
        /// @return Amount of characters before the end of the selection
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getSelectionEnd() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text
        ///
        /// @param size  The new text size.
        ///              The minimum text size is 8
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum character limit
        ///
        /// @param maxChars  The new character limit.
        ///                  Set it to 0 to disable the limit
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(std::size_t maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum character limit
        ///
        /// @return The character limit
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getMaximumCharacters() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the blinking caret to after a specific character
        ///
        /// @param charactersBeforeCaret  The new position
        ///
        /// This function will set both the selection start and selection end to the requested value.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretPosition(std::size_t charactersBeforeCaret);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns after which character the blinking cursor is currently located
        ///
        /// @return Characters before the caret
        ///
        /// This function is an alias for getSelectionEnd.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getCaretPosition() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes the text box read-only or make it writable again
        ///
        /// @param readOnly  Should the text box be read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setReadOnly(bool readOnly = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if the text box read-only or writable
        ///
        /// @return Is the text box read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isReadOnly() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes when the vertical scrollbar should be displayed
        /// @param policy  The policy for displaying the vertical scrollbar
        ///
        /// The default policy is Automatic, which means it only shows when the text doesn't fit inside the TextBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVerticalScrollbarPolicy(Scrollbar::Policy policy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns when the vertical scrollbar should be displayed
        /// @return The policy for displaying the vertical scrollbar
        ///
        /// The default policy is Automatic, which means it only shows when the text doesn't fit inside the TextBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar::Policy getVerticalScrollbarPolicy() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes when the horizontal scrollbar should be displayed
        /// @param policy  The policy for displaying the horizontal scrollbar
        ///
        /// The default policy is Never, which means word-wrap will be used to keep the text within the TextBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHorizontalScrollbarPolicy(Scrollbar::Policy policy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns when the horizontal scrollbar should be displayed
        /// @return The policy for displaying the horizontal scrollbar
        ///
        /// The default policy is Never, which means word-wrap will be used to keep the text within the TextBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar::Policy getHorizontalScrollbarPolicy() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of lines that the text occupies in the TextBox
        ///
        /// @return Lines of text
        ///
        /// Note that this is the amount of lines after word-wrap is applied.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getLinesCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focus or unfocus the widget
        /// @param focused  Is the widget focused?
        ///
        /// When a widget is focused, the previously focused widget will be unfocused.
        ///
        /// @warning This function only works properly when the widget was already added to its parent (e.g. the Gui).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocused(bool focused) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether an optimization is made that only works when using a monospaced font
        ///
        /// @param enable  Whether the optimization should be enabled
        ///
        /// Rearranging text when a horizontal scrollbar is enabled can be almost as expensive as the word-wrap which is
        /// performed when there is no horizontal scrollbar. When using a monospaced font there is no need for such expensive
        /// calculation. Call this function when using a monospaced font to make changing the text faster.
        ///
        /// This function has no effect when the horizontal scrollbar is disabled (default).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void enableMonospacedFontOptimization(bool enable = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the thumb position of the vertical scrollbar
        ///
        /// @param value  New value of the vertical scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVerticalScrollbarValue(unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the thumb position of the vertical scrollbar
        ///
        /// @return Value of the vertical scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getVerticalScrollbarValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the thumb position of the horizontal scrollbar
        ///
        /// @param value  New value of the horizontal scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHorizontalScrollbarValue(unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the thumb position of the horizontal scrollbar
        ///
        /// @return Value of the horizontal scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getHorizontalScrollbarValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isMouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void textEntered(char32_t key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseWheelScrolled(float delta, Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseButtonNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2<std::size_t> findCaretPosition(Vector2f position) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Gets the index of either m_selStart or m_selEnd
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getIndexOfSelectionPos(Vector2<std::size_t> selectionPos) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when you are selecting text.
        // It will find out which part of the text is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Rearrange the text inside the text box (by using word wrap).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rearrangeText(bool keepSelection);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the physical size of the scrollbars, as well as the viewport size.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateScrollbars();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will split the text into five pieces so that the text can be easily drawn.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectionTexts();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Backspace" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void backspaceKeyPressed();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Delete" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteKeyPressed();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+C" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void copySelectedTextToClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+X" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void cutSelectedTextToClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+V" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void pasteTextFromClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+A" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectAllText();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "PageUp" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretPageUp();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "PageDown" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretPageDown();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "ArrowLeft" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretLeft(bool shiftPressed);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "ArrowRight" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretRight(bool shiftPressed);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+ArrowLeft" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretWordBegin();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+ArrowRight" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretWordEnd();


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
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTime(Duration elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the positions of the contents of the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculatePositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates which lines are currently visible.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateVisibleLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(String signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<TextBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalString onTextChange = {"TextChanged"};     //!< The text was changed. Optional parameter: new text
        Signal onSelectionChange = {"SelectionChanged"}; //!< Selected text changed


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        String m_text;
        unsigned int m_lineHeight = 24;

        // The width of the largest line
        float m_maxLineWidth;

        std::vector<String> m_lines;

        // The maximum characters (0 by default, which means no limit)
        std::size_t m_maxChars = 0;

        // What is known about the visible lines?
        std::size_t m_topLine = 1;
        std::size_t m_visibleLines = 1;

        // Information about the selection
        Vector2<std::size_t> m_selStart;
        Vector2<std::size_t> m_selEnd;
        std::pair<Vector2<std::size_t>, Vector2<std::size_t>> m_lastSelection;

        // Information about the caret
        Vector2f m_caretPosition;
        bool m_caretVisible = true;

        Text m_textBeforeSelection;
        Text m_textSelection1;
        Text m_textSelection2;
        Text m_textAfterSelection1;
        Text m_textAfterSelection2;
        Text m_defaultText;

        std::vector<FloatRect> m_selectionRects;

        // The scrollbars
        CopiedSharedPtr<ScrollbarChildWidget> m_verticalScrollbar;
        CopiedSharedPtr<ScrollbarChildWidget> m_horizontalScrollbar;
        Scrollbar::Policy m_verticalScrollbarPolicy = Scrollbar::Policy::Automatic;
        Scrollbar::Policy m_horizontalScrollbarPolicy = Scrollbar::Policy::Never;

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        bool m_readOnly = false;

        bool m_monospacedFontOptimizationEnabled = false;

        Sprite m_spriteBackground;

        // Cached renderer properties
        Borders m_bordersCached;
        Padding m_paddingCached;
        Color   m_borderColorCached;
        Color   m_backgroundColorCached;
        Color   m_caretColorCached;
        Color   m_selectedTextBackgroundColorCached;
        float   m_caretWidthCached = 1;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
