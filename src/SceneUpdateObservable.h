/**
 * @file SceneUpdateObservable.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_SCENE_UPDATE_OBSERVABLE_H
#define ICP_PROJECT_SCENE_UPDATE_OBSERVABLE_H

#include <vector>
#include "SceneUpdateObserver.h"

/**
 * Observable for scene updates
 */
class SceneUpdateObservable
{
    /**
     * Registered observers
     */
    std::vector<SceneUpdateObserver *> observers;

  public:
    /**
     * Registers new observer
     *
     * @param observer Observer wants to get scene updates notifications
     */
    void registerObserver(SceneUpdateObserver *observer)
    {
        observers.push_back(observer);
    }

    /**
     * Notify about scene change
     */
    void sceneChanged()
    {
        for (const auto &item: observers) {
            item->logChanges();
        }
    }
};

#endif //ICP_PROJECT_SCENE_UPDATE_OBSERVABLE_H
