#pragma once

#include <vector>
#include <memory>

class SystemLogic {
    public:
        SystemLogic() =default;
        ~SystemLogic() =default;

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void end() = 0;
};