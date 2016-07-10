#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <string>
#include <memory>

/***************************************************************************/ /**
  * Manages a game sprite loaded from a sprite sheet file.
  ******************************************************************************/
class Sprite
{
  public:
    /**
     * Initializes the sprite attributes with default values.
     */
    Sprite(void);

    /**
     * Loads the sprite from a given file and sets frameCount and frameTime.
     * @param file a string argument with the sprite file path
     * @param frameCount a int argument containing how many frames does the
     * sprite have
     * @param frameTime a int argument containing how long will a frame be
     * displayed
     */
    Sprite(std::string file, int frameCount = 1, float frameTime = 1.0,
           int rows = 1);

    /**
     * Loads a sprite from a given file.
     * @param file a string argument with the sprite file path
     */
    void Open(std::string file);

    /**
     * Updates sprite frames.
     * @param dt a float argument containing the game delta time
     */
    void Update(float dt);

    /**
     * Sets the sprite frame.
     * @param frame a int argument containing the sprite frame
     */
    void SetFrame(int frame);

    /**
     * Sets the sprite frameCount.
     * @param frameCount a int argument containing the sprite frameCount
     */
    void SetFrameCount(int frameCount);

    /**
     * Sets the sprite frameTime.
     * @param frame a int argument containing the sprite frameTime
     */
    void SetFrameTime(float frameTime);

    /**
     * Sets the sprite's number of rows
     * @param rows the ammount of rows to be set
     */
    void SetRows(int rows);

    /**
     * Sets the sprite clip.
     * @param x a int argument containing the x coordinate of the clip
     * @param y a int argument containing the y coordinate of the clip
     * @param w a int argument containing the w coordinate of the clip
     * @param h a int argument containing the h coordinate of the clip
     */
    void SetClip(int x, int y, int w, int h);

    /**
     * Renders the sprite frame.
     * @param x a int argument containing the x of the render position
     * @param y a int argument containing the y of the render position
     * @param angle a float argument containing the angle to render the sprite
     */
    void Render(int x = 0, int y = 0, float angle = 0.0);

    /**
     * Gets the frame width.
     * @return Returns the frame width
     */
    int GetWidth(void);

    /**
     * Gets the frame height.
     * @return Returns the frame height
     */
    int GetHeight(void);

    /**
     * Checks if the sprite is loaded.
     * @return If the sprite is open.
     */
    bool IsOpen(void);

    /**
     * Sets the frame scale on X.
     * @param x a float argument containing the x scale value
     */
    void SetScaleX(float x);

    /**
     * Sets the frame scale on Y.
     * @param y a float argument containing the y scale value
     */
    void SetScaleY(float y);

    /**
     * Gets the current frame
     * @return Returns the current frame of the sprite
     */
    int GetCurrentFrame(void);

    /**
     * Returns the sprite's frame count
     * @return Returns the frame count
     */
    int GetFrameCount(void);

  private:
    int width, height, frameCount, currentFrame, rows;
    float frameTime, timeElapsed, scaleX, scaleY;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect clipRect;
    SDL_Rect dstRect;
};

