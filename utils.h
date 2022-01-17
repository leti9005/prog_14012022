#pragma once

#include "base/IShape.h"

// Поместить p над q
void up(IShape* p, const IShape* q)
{
    auto ps = p->south();
    auto qn = q->north();

    p->move(qn.x - ps.x, qn.y - ps.y + 1);
}
