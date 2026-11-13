//
// Created by balac on 5/31/2025.
//

#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "command.h"
#include "vector"
#include <memory>

class undo_redo {
private:
    std::vector<std::unique_ptr<command>> undoStack;
    std::vector<std::unique_ptr<command>> redoStack;
public:
    void executeCommand(std::unique_ptr<command> cmd);
    void undo();
    void redo();
};



#endif //UNDO_REDO_H
