
#ifndef __FIXED_COLOR_VERLET_H__
#define __FIXED_COLOR_VERLET_H__

#include "verlet.h"

class VerletPool;

class FixedColorVerlet : public Verlet {
    friend class VerletPool;

private:
    FixedColorVerlet() {} // only verlet pool can create instances of this class
    void updateColor(float dt) override {}

    uint32_t type() const override
    {
        return FIXED_COLOR;
    }
};

#endif // __FIXED_COLOR_VERLET_H__
