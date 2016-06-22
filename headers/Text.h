#pragma once
#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Rect.h"

/***************************************************************************/ /**
  * Manages a game text which the font is loaded from a .ttf file.
  ******************************************************************************/
class Text
{
  public:
    /**
     * Typifies text styles.
     */
    enum TextStyle {
        SOLID,  /**< solid font. */
        SHADED, /**< shaded font (with a black contrast box behind). */
        BLENDED /**< blended font. */

    };

    /**
     * Initializes the sprite attributes with default values.
     */
    Text(void);

    /**
     * Initializes the sprite attributes with the given values.
     * @param fontFile a string argument containing the font file path
     * @param fontSize a int argument containing the font size
     * @param style a TextStyle argument containing the font style
     * @param text a string argument containing the text content
     * @param color a SDL_Color argument containing the text color
     * @param x a int argument with the x coordinate of the text
     * @param y a int argument with the y coordinate of the text
     */
    Text(std::string fontFile, int fontSize, TextStyle style, std::string text,
         SDL_Color color, int x = 0, int y = 0);

    /**
     * Destroys the text texture.
     */
    ~Text(void);

    /**
     * Renders the text.
     * @param x a int argument containing the x of the render position
     * @param y a int argument containing the y of the render position
     */
    void Render(int CameraX = 0, int CameraY = 0);

    /**
     * Sets the text position.
     * @param x a int argument containing the x of the text position
     * @param y a int argument containing the y of the text position
     * @param centerX a bool argument containg if the text should be centralised
     * in x
     * @param centerY a bool argument containg if the text should be centralised
     * in y
     */
    void SetPos(int x, int y, bool centerX = false, bool centerY = false);

    /**
     * Sets the text content.
     * @param text a string argument containing the text content
     */
    void SetText(std::string text);

    /**
     * Sets the text color.
     * @param color a SDL_Color argument containing the text color
     */
    void SetColor(SDL_Color color);

    /**
     * Sets the text style.
     * @param style a TextStyle argument containing the text style
     */
    void SetStyle(TextStyle style);

    /**
     * Sets the text font size.
     * @param fontSize a int argument containing the text font size
     */
    void SetFontSize(int fontSize);

  private:
    SDL_Texture *texture;
    int fontSize;
    TextStyle style;
    std::string text;
    SDL_Color color;
    std::shared_ptr<TTF_Font> font;
    Rect box;
    SDL_Rect clipRect, dstRect;

    void RemakeTexture(void);
};

