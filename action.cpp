#include "action.h"

void ActionAdd::executeUndo() {
    string title = addedEvent.getTitle();
    repo.remove_event(title);
}

void ActionAdd::executeRedo() {
    repo.add_event(addedEvent);
}

void ActionRemove::executeUndo() {
    repo.add_event(deletedEvent);
}

void ActionRemove::executeRedo() {
    string title = deletedEvent.getTitle();
    repo.remove_event(title);
}

void ActionUpdate::executeUndo() {
    string title = newEvent.getTitle();
    repo.remove_event(title);
    repo.add_event(oldEvent);
}

void ActionUpdate::executeRedo() {
    string title = oldEvent.getTitle();
    repo.remove_event(title);
    repo.add_event(newEvent);
}
