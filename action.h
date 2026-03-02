#pragma once
#include "code/repo.h"
#include "code/event.h"

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    virtual ~Action() = default;
};

class ActionAdd : public Action {
private:
    Event addedEvent;
    Repo& repo;
public:
    ActionAdd(Event addedEvent, Repo& repo) : repo(repo), addedEvent(addedEvent) {}
    void executeUndo() override;
    void executeRedo() override;
};

class ActionRemove : public Action {
private:
    Event deletedEvent;
    Repo& repo;
public:
    ActionRemove(Event deletedEvent, Repo& repo) : repo(repo), deletedEvent(deletedEvent) {}
    void executeUndo() override;
    void executeRedo() override;
};

class ActionUpdate : public Action {
private:
    Event oldEvent, newEvent;
    Repo& repo;
public:
    ActionUpdate(Event oldEvent, Event newEvent, Repo& repo) : repo(repo), oldEvent(oldEvent), newEvent(newEvent) {}
    void executeUndo() override;
    void executeRedo() override;
};

