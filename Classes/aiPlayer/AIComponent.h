// Refactored with Composite Pattern

#pragma once

class AIComponent
{
public:
    virtual ~AIComponent() = default;

    // 执行 AI 行为
    virtual void execute() = 0;
};