//
// Created by balac on 5/31/2025.
//

#include "undo_redo.h"

void undo_redo::executeCommand(std::unique_ptr<command> cmd) {
    cmd->execute();
    undoStack.push_back(std::move(cmd));
    redoStack.clear();
}
void undo_redo::undo() {
    if (undoStack.empty()) return;
    auto cmd = std::move(undoStack.back());
    undoStack.pop_back();
    cmd->undo();
    redoStack.push_back(std::move(cmd));
}

void undo_redo::redo() {
    if (redoStack.empty()) return;
    auto cmd = std::move(redoStack.back());
    redoStack.pop_back();
    cmd->execute();
    undoStack.push_back(std::move(cmd));
}