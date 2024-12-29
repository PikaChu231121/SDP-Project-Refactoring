// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include <vector>
#include <memory>

class AIComposite : public AIComponent
{
private:
    std::vector<std::unique_ptr<AIComponent>> children;

public:
    // 添加子行为
    void add(AIComponent *component)
    {
        children.emplace_back(component);
    }

    // 执行所有子行为
    void execute() override
    {
        for (auto &child : children)
        {
            child->execute();
        }
    }
};
