#include "UndoManager.h"

void UndoManager::push(const UndoModel& action) {
    _undoStack.push(action);
}

bool UndoManager::canUndo() const {
    return !_undoStack.empty();
}

UndoModel UndoManager::pop() {
    if (!_undoStack.empty()) {
        UndoModel top = _undoStack.top();
        _undoStack.pop();
        return top;
    }
    return UndoModel();
}