#include "CoreEngine.hpp"

namespace Core
{
    TextRenderer::TextRenderer()
        : _text(""), _fontSize(20), _color(BLACK), _position({10.0f, 10.0f})
    {
        _font = GetFontDefault();
    }
    TextRenderer::~TextRenderer()
    {
    }

    void TextRenderer::OnDraw2D()
    {
        if (_font.texture.id == 0)
        {
            DrawTextEx(GetFontDefault(), _text.c_str(), _position, (float)_fontSize, 1, _color);
        }
        else
        {
            DrawTextEx(_font, _text.c_str(), _position, (float)_fontSize, 1, _color);
        }
    }
    void TextRenderer::SetFont(std::string fontPath)
    { // TODO: Resource Management
        _font = LoadFont(fontPath.c_str());
    }

}