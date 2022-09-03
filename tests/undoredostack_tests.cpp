#include "../src/commands/undoredostack.h"

#include <gtest/gtest.h>

using namespace TMSE;

namespace
{
class DumbCommand : public Command
{
public:
    DumbCommand() : Command{"DumbCommand"} {}
    void resetFlags()
    {
        mUndoWasCalled = false;
        mRedoWasCalled = false;
    }
    bool wasUndoCalled() const
    {
        return mUndoWasCalled;
    }
    bool wasRedoCalled() const
    {
        return mRedoWasCalled;
    }
    void redo() override
    {
        mRedoWasCalled = true;
    }
    void undo() override
    {
        mUndoWasCalled = true;
    }

private:
    bool mUndoWasCalled = false;
    bool mRedoWasCalled = false;
};
}

TEST(UndoRedoStack, CallingUndoOnAnEmptyStackDoesNothing)
{
    TMSE::UndoRedoStack stack;

    EXPECT_NO_THROW(stack.undo());
}

TEST(UndoRedoStack, CallingRedoOnAnEmptyStackDoesNothing)
{
    TMSE::UndoRedoStack stack;

    EXPECT_NO_THROW(stack.redo());
}

TEST(UndoRedoStack, IsDirtyIsFalseAfterCreation)
{
    TMSE::UndoRedoStack stack;

    EXPECT_FALSE(stack.isDirty());
}

TEST(UndoRedoStack, IsDirtyIsTrueAfterACommandIsPushed)
{
    TMSE::UndoRedoStack stack;

    stack.push(std::make_unique<DumbCommand>());

    EXPECT_TRUE(stack.isDirty());
}

TEST(UndoRedoStack, IsDirtyIsFalseAfterClearDirtyIsCalled)
{
    TMSE::UndoRedoStack stack;

    stack.push(std::make_unique<DumbCommand>());

    stack.clearDirty();

    EXPECT_FALSE(stack.isDirty());
}

TEST(UndoRedoStack, IsDirtyIsTrueAfterAUndo)
{
    TMSE::UndoRedoStack stack;

    stack.push(std::make_unique<DumbCommand>());

    stack.clearDirty();

    stack.undo();

    EXPECT_TRUE(stack.isDirty());
}

TEST(UndoRedoStack, PushingACommandMakesRedoBeCalled)
{
    TMSE::UndoRedoStack stack;

    auto command = std::make_unique<DumbCommand>();

    auto commandRaw = command.get();

    EXPECT_FALSE(commandRaw->wasRedoCalled());

    stack.push(std::move(command));

    EXPECT_TRUE(commandRaw->wasRedoCalled());
}

TEST(UndoRedoStack, CallingUndoMakesCommandUndoToBeCalled)
{
    TMSE::UndoRedoStack stack;

    auto command = std::make_unique<DumbCommand>();

    auto commandRaw = command.get();

    EXPECT_FALSE(commandRaw->wasUndoCalled());

    stack.push(std::move(command));

    EXPECT_FALSE(commandRaw->wasUndoCalled());

    stack.undo();

    EXPECT_TRUE(commandRaw->wasUndoCalled());
}

TEST(UndoRedoStack, PushUndoRedoMakesCommandRedoToBeCalled)
{
    TMSE::UndoRedoStack stack;

    auto command = std::make_unique<DumbCommand>();

    auto commandRaw = command.get();

    EXPECT_FALSE(commandRaw->wasUndoCalled());

    stack.push(std::move(command));

    EXPECT_FALSE(commandRaw->wasUndoCalled());

    stack.undo();

    EXPECT_TRUE(commandRaw->wasUndoCalled());

    commandRaw->resetFlags();

    stack.redo();

    EXPECT_TRUE(commandRaw->wasRedoCalled());
}
