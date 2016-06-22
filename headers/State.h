#pragma once
#include <vector>
#include <memory>

#include "GameObject.h"

/***************************************************************************/ /**
  * Its an virtual interface for all game states.
  ******************************************************************************/
class State
{
  public:
    /**
     * Initializes the sprite attributes with default values.
     */
    State(void);

    /**
     * Allows a instance of a derivade class to be deleted through a
     * pointer to this class.
     */
    virtual ~State(){};

    /**
     * When implemented, it should update the object.
     */
    virtual void Update(float dt) = 0;

    /**
     * When implemented, it should update the object.
     * @param dt a float argument contaning the delta time
     */
    virtual void Render(void) = 0;

    /**
     * When implemented, it should pause the state.
     */
    virtual void Pause(void) = 0;

    /**
     * When implemented, it should resume the state.
     */
    virtual void Resume(void) = 0;

    /**
     * When implementated, it should add an object to state list of objects.
     * @param obj a GameObject argument containing the object to be saved.
     */
    virtual void AddObject(GameObject *obj);

    /**
     * When implementated, it should return if this state is requesting to be
     * poped.
     * @return If the state is requesting to be poped
     */
    bool IsPopRequested(void);

    /**
     * When implementated, it should return if this state is requesting to be
     * quit.
     * @return If the state is requesting to be quit
     */
    bool IsQuitRequested(void);

    virtual bool IsCollidingWithWall(GameObject *o) = 0;

    virtual void CheckMovementCollisions() = 0;

  protected:
    bool popRequested, quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    virtual void UpdateArray(float dt);
    virtual void RenderArray(void);
};

