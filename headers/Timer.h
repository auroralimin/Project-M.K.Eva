#pragma once

/***************************************************************************/ /**
  * Manages time.
  ******************************************************************************/
class Timer
{
  public:
    /**
     * Initialises the timer time with 0.0.
     */
    Timer();

    /**
     * Increments time with an given delta time.
     * @param dt an int argument that has an delta time
     */
    void Update(float dt);

    /**
     * Resets timer time to zero.
     */
    void Restart(void);

    /**
     * Gets timer time.
     * @return Returns timer time
     */
    float Get(void);

  private:
    float time;
};

