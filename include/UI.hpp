#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "/home/saszombie/raylib-cpp/include/raylib-cpp.hpp"

namespace UI
{
    class TextBoxes
    {
    private:
        size_t index;
        size_t currentIndex = 0;
        int isWritting = -1;
        std::string label;
        raylib::Rectangle button;
        std::vector<std::string> strings;
        std::vector<raylib::Rectangle> textAreas;
    public:
        TextBoxes(size_t textAreaNumber) noexcept;

        void addButton(const Rectangle& rec) noexcept;
        void addTextAreas(const Rectangle& rec, int ind = -1) noexcept;
        void addLabel(const std::string &nLabel) noexcept;

        void addOption(const std::vector<std::string> &allOptions) noexcept;
        void writting() noexcept;

        void checkText() noexcept;
        bool checkButton() const noexcept;
        void draw() const noexcept;

        void clear() noexcept;

        const std::vector<std::string>& getTexts() const noexcept;
        ~TextBoxes() noexcept = default;
    };
    
    class CheckBox
    {
    private:
        size_t all;
        std::vector<std::string> labels;
        std::vector<int> options;
        std::vector<raylib::Rectangle> actualBoxes;
    public:
        CheckBox(const std::vector<std::string>& nOptions, std::vector<int> verified = {}) noexcept;
        std::optional<size_t> checkButton() noexcept;
        void addBox(const raylib::Rectangle& rect) noexcept;
        void draw() const noexcept;

        ~CheckBox() noexcept = default;
    };
    
    class UI
    {
    private:
        size_t currentX, currentY, WIDTH, HEIGHT;
        std::vector<TextBoxes>boxes;
        std::vector<CheckBox>checkBoxes;
    public:
        UI(size_t x, size_t y, size_t maxWidth, size_t maxHeight) noexcept;
        void addBox(const std::string& box, size_t areas) noexcept;
        void addCheckBox(const std::vector<std::string> &options, std::vector<int> verified = {}) noexcept;
        void drawBoxes() noexcept;
        std::vector<TextBoxes>& getBoxes() noexcept;
        std::vector<CheckBox>& getCheckBoxes() noexcept;

        ~UI() = default;
    };
    
    
    
} // namespace UI
