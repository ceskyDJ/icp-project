/**
 * @file SceneUpdateObserver.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_SCENE_UPDATE_OBSERVER_H
#define ICP_PROJECT_SCENE_UPDATE_OBSERVER_H

/**
 * Observer for scene updates
 */
class SceneUpdateObserver
{
  public:
    /**
     * Logs scene change
     */
    virtual void logChanges() noexcept = 0;
};

#endif //ICP_PROJECT_SCENE_UPDATE_OBSERVER_H
