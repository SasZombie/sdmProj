#include "../include/UI.hpp"
#include <iostream>

UI::TextBoxes::TextBoxes(size_t textAreasNumber) noexcept
    : index(textAreasNumber)
{
    this->strings.resize(index);
    this->textAreas.resize(index);
}

void UI::TextBoxes::addButton(const Rectangle &rec) noexcept
{
    this->button = rec;
}

void UI::TextBoxes::addTextAreas(const Rectangle& rec, int ind) noexcept
{
    if(ind == -1)
        ind = this->currentIndex;
    else
        if(static_cast<size_t>(ind) > this->index)
            ind = this->currentIndex;
    
    // textAreas.push_back(rec);
    this->textAreas.at(ind) = rec;
    this->currentIndex = this->currentIndex + 1;
}

void UI::TextBoxes::addLabel(const std::string &nLabel) noexcept
{
    this->label = nLabel;
}

void UI::TextBoxes::addOption(const std::vector<std::string> &alloptions) noexcept
{
}

void UI::TextBoxes::writting() noexcept
{   
    this->checkText();
    if(isWritting == -1)
        return;

    int key = GetKeyPressed();
    if(key == 259)
        this->strings[isWritting].pop_back();
    else if(key == 32 || (key > 64 && key < 123 ))
    {
        // std::cout << key << '\n';
            if(IsKeyDown(KEY_LEFT_SHIFT))
                this->strings[isWritting].push_back(static_cast<char>(key));
            else
                this->strings[isWritting].push_back(static_cast<char>(key + 32));
    }
    else if(key > 47 && key < 58)
    {
        this->strings[isWritting].push_back(key);
    }
}

void UI::TextBoxes::checkText() noexcept
{
    for(size_t i = 0; i < this->textAreas.size(); ++i)
    {

        if(CheckCollisionCircleRec(GetMousePosition(), 10, this->textAreas[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->isWritting = i;
            return;
        }
    }
    
    for(size_t i = 0; i < this->textAreas.size(); ++i)
    {

        if(!CheckCollisionCircleRec(GetMousePosition(), 10, this->textAreas[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->isWritting = -1;
            return;
        }
    }
}

bool UI::TextBoxes::checkButton() const noexcept
{
   
    return (CheckCollisionCircleRec(GetMousePosition(), 5, this->button)  && std::all_of(this->strings.begin(), this->strings.end(), 
    [](const std::string& field) 
    {
        return !field.empty();
    }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

void UI::TextBoxes::draw() const noexcept
{

    const size_t allAreas = this->textAreas.size();
    for(size_t i = 0; i < allAreas; ++i)
    {
        textAreas[i].Draw(RAYWHITE);
        raylib::DrawText(this->strings[i], textAreas[i].x, textAreas[i].y, 10, RED);
    }
    raylib::DrawText(label, ((this->textAreas[0].x - label.size() * 10) / this->textAreas.size()) , this->textAreas[0].y, 15, RAYWHITE);
    this->button.Draw(RED);
}
void UI::TextBoxes::clear() noexcept
{
    for(auto &str : this->strings)
    {
        str.clear();
    }

}
const std::vector<std::string> &UI::TextBoxes::getTexts() const noexcept
{
    return this->strings;
}

UI::UI::UI(size_t x, size_t y, size_t maxWidth, size_t maxHeight) noexcept
    :currentX(x), currentY(y), WIDTH(maxWidth), HEIGHT(maxHeight)
{

}

void UI::UI::addBox(const std::string &label, size_t texAreas) noexcept
{
    constexpr float areaWidth = 100, areaHight = 25;

    TextBoxes box{texAreas};
    box.addLabel(label);
    float newX, newY;
    float padd = 10;
    for(size_t i = 0; i < texAreas; ++i)
    {
        const raylib::Rectangle textArea{((WIDTH/2 + (areaWidth/2))/texAreas) + i * (padd + areaWidth), currentY/2 - areaHight/2, areaWidth, areaHight};
        box.addTextAreas(textArea);
        newX = textArea.x;
        newY = textArea.y;
    }
    const raylib::Rectangle button{newX + areaWidth + padd, newY, 25, 25};
    box.addButton(button);
    this->boxes.push_back(box);
    this->currentY = this->currentY + 100;
}

void UI::UI::addCheckBox(const std::vector<std::string>& options, std::vector<int> verified) noexcept
{
    constexpr float areaWidth = 15, areaHight = 15;

    CheckBox allBoxes{options, verified};
    for(size_t i = 0; i < options.size(); ++i)
    {
        const raylib::Rectangle checkArea{((WIDTH/2 + (areaWidth/2))), currentY/2 - areaHight/2, areaWidth, areaHight};
        this->currentY = this->currentY + 100;
        allBoxes.addBox(checkArea);
    }
    
    this->checkBoxes.push_back(allBoxes);
    
    
}
void UI::UI::drawBoxes() noexcept
{
    for(auto& box : this->boxes)
    {
        box.writting();
        box.draw();
    }
}

std::vector<UI::TextBoxes>& UI::UI::getBoxes() noexcept
{
    return this->boxes;
}


UI::CheckBox::CheckBox(const std::vector<std::string> &nOptions, std::vector<int> verified) noexcept
    : labels(nOptions), options(verified)
{

}

std::optional<size_t> UI::CheckBox::checkButton() noexcept
{
    size_t size = this->actualBoxes.size();
    for(size_t i = 0; i < size; ++i)
    {
        if((CheckCollisionCircleRec(GetMousePosition(), 5, this->actualBoxes[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            auto it = std::find(this->options.begin(), this->options.end(), i);
            if( it != this->options.end())
            {
                this->options.erase(it);
            }
            else
            {
                this->options.push_back(i);
            }
            return i;
        }
    }   
    return std::nullopt;
}

void UI::CheckBox::addBox(const raylib::Rectangle &rect) noexcept
{
    this->actualBoxes.push_back(rect);
}

void UI::CheckBox::draw() const noexcept
{
   size_t size = this->actualBoxes.size();

   for(size_t i = 0; i < size; ++i)
   {
        this->actualBoxes[i].Draw((std::find(this->options.begin(), this->options.end(), i) != this->options.end()) ? RED : BLACK);
        raylib::DrawText(this->labels[i], this->actualBoxes[i].x - (this->labels[i].size() * 10), this->actualBoxes[i].y, 15, RED);
   }

}

std::vector<UI::CheckBox> &UI::UI::getCheckBoxes() noexcept
{
    return this->checkBoxes;
}