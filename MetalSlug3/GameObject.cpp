#include "GameObject.h"

void CGameObject::process(DWORD dt, vector<LPCGameObject>* coObjects)
{
    vector<LPCOLLISIONEVENT> coEvents;
    LPCOLLISIONEVENT colX = NULL;
    LPCOLLISIONEVENT colY = NULL;

    coEvents.clear();

    if (this->IsCollidable())
    {
        CalcPotentialCollisions(dt, coObjects, coEvents);
    }

    if (coEvents.size() == 0)
    {
        OnNoCollision(dt);
    }
    else
    {
        FilterCollision(coEvents, colX, colY);

        float dx, dy;
        dx = this->Obj_speed.x * dt;
        dy = this->Obj_speed.y * dt;

        if (colX != NULL && colY != NULL)
        {
            if (colY->t < colX->t) // va chạm trục y trước
            {
                this->Obj_Position.y += colY->t * dy + colY->ny * BLOCK_SPACING;

                OnCollisionWith(colY);

                LPCOLLISIONEVENT colX_other = NULL;
                colX->isDeleted = true;
                coEvents.push_back(SweptAABBEx(dt, colX->obj));

                FilterCollision(coEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

                if (colX_other != NULL)
                {
                    this->Obj_Position.x += colX_other->t * dx + colX_other->nx * BLOCK_SPACING;
                    OnCollisionWith(colX_other);
                }
                else
                {
                    this->Obj_Position.x += dx;
                }
            }
            else
            {
                this->Obj_Position.x += colX->t * dx + colX->nx * BLOCK_SPACING;

                OnCollisionWith(colX);

                LPCOLLISIONEVENT colY_other = NULL;

                colY->isDeleted = true;

                coEvents.push_back(SweptAABBEx(dt, colY->obj));

                FilterCollision(coEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

                if (colY_other != NULL)
                {
                    this->Obj_Position.y += colY_other->t * dy + colY_other->ny * BLOCK_SPACING;
                    OnCollisionWith(colY_other);
                }
                else
                {
                    this->Obj_Position.y += dy;
                }
            }
        }
        else if (colX != NULL)
        {
            this->Obj_Position.x += colX->t * dx + colX->nx * BLOCK_SPACING;
            this->Obj_Position.y += dy;
            OnCollisionWith(colX);
        }
        else if (colY != NULL)
        {
            this->Obj_Position.x += dx;
            this->Obj_Position.y += colY->t * dy + colY->ny * BLOCK_SPACING;
            OnCollisionWith(colY);
        }
        else
        {
            this->Obj_Position.x += dx;
            this->Obj_Position.y += dy;
        }
        //this->Obj_Position.x = x;
        //this->Obj_Position.y = y;
    }
    for (UINT i = 0; i < coEvents.size(); i++)
    {
        LPCOLLISIONEVENT e = coEvents[i];
        if (e->isDeleted) continue;
        if (e->obj->IsBlocking()) continue;  // blocking collisions were handled already, skip them

        OnCollisionWith(e);
    }

    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

/*
 * SweptAABB for one static + one moving objects.
 */
void CGameObject::SweptAABB(RECT movingRect,
    float dx, float dy,
    RECT staticRect,
    float& t, float& nx, float& ny) {

    float dx_entry, dx_exit, tx_entry, tx_exit;
    float dy_entry, dy_exit, ty_entry, ty_exit;

    float t_entry;
    float t_exit;

    t = -1.0f;			// no collision
    nx = ny = 0.0f;

    //
    // Broad-phase test
    //

    float bl = dx > 0 ? movingRect.left : movingRect.left + dx;
    float bt = dy > 0 ? movingRect.top : movingRect.top + dy;
    float br = dx > 0 ? movingRect.right + dx : movingRect.right;
    float bb = dy > 0 ? movingRect.bottom + dy : movingRect.bottom;

    if (br < staticRect.left || bl > staticRect.right ||
        bb < staticRect.top || bt > staticRect.bottom) return;


    if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

    if (dx > 0)
    {
        dx_entry = staticRect.left - movingRect.right;
        dx_exit = staticRect.right - movingRect.left;
    }
    else if (dx < 0)
    {
        dx_entry = staticRect.right - movingRect.left;
        dx_exit = staticRect.left - movingRect.right;
    }


    if (dy > 0)
    {
        dy_entry = staticRect.top - movingRect.bottom;
        dy_exit = staticRect.bottom - movingRect.top;
    }
    else if (dy < 0)
    {
        dy_entry = staticRect.bottom - movingRect.top;
        dy_exit = staticRect.top - movingRect.bottom;
    }

    if (dx == 0)
    {
        tx_entry = -999999.0f;
        tx_exit = 999999.0f;
    }
    else
    {
        tx_entry = dx_entry / dx;
        tx_exit = dx_exit / dx;
    }

    if (dy == 0)
    {
        ty_entry = -99999.0f;
        ty_exit = 99999.0f;
    }
    else
    {
        ty_entry = dy_entry / dy;
        ty_exit = dy_exit / dy;
    }

    //if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

    if ((tx_entry < 0.0f && ty_entry < 0.0f))
    {
        t = 0.0f;
        /*if (tx_entry > ty_entry)
        {
            ny = 0.0f;
            dx > 0 ? nx = -1.0f : nx = 1.0f;
        }
        else
        {
            nx = 0.0f;
            dy > 0 ? ny = -1.0f : ny = 1.0f;
        }*/
        return;
    }
    else if (tx_entry > 1.0f || ty_entry > 1.0f)
    {
        return;
    }

    t_entry = max(tx_entry, ty_entry);
    t_exit = min(tx_exit, ty_exit);

    if (t_entry > t_exit) return;

    t = t_entry;

    if (tx_entry > ty_entry)
    {
        ny = 0.0f;
        dx > 0 ? nx = -1.0f : nx = 1.0f;
    }
    else
    {
        nx = 0.0f;
        dy > 0 ? ny = -1.0f : ny = 1.0f;
    }
}

/*
 * SweptAABB with two moving objects.
 */
LPCOLLISIONEVENT CGameObject::SweptAABBEx(DWORD dt, LPCGameObject coO, bool isGetActiveRange)
{
    float t, nx, ny;
    t = 0;
    nx = 0;
    ny = 0;
    float mdx, mdy;
    mdx = this->Obj_speed.x * dt;
    mdy = this->Obj_speed.y * dt;
    RECT movingRect = this->getBoundingBox();
    if (isGetActiveRange)
        movingRect = this->getActiveRange();
    //Assume the other object is static.
    float sdx, sdy;
    sdx = coO->Obj_speed.x * dt;
    sdy = coO->Obj_speed.y * dt;
    RECT staticRect = coO->getBoundingBox();

    float dx, dy;
    dx = mdx - sdx;
    dy = mdy - sdy;

    if (isColliding(movingRect, staticRect))
    {
        t = 0;
        CCollisionEvent* e = new CCollisionEvent(t, nx, ny, dx, dy, coO);
        return e;
    }

    SweptAABB(
        movingRect,
        dx, dy,
        staticRect,
        t, nx, ny
    );

    CCollisionEvent* e = new CCollisionEvent(t, nx, ny, dx, dy, coO);
    return e;
}

bool CGameObject::isColliding(const RECT thisRect, const RECT otherRect) {
    //thisLeft <= otherRight <=> thisLeft - otherRight <= 0
    long left = thisRect.left - otherRect.right;
    //thisRight >= otherLeft <=> thisRight - otherLeft >= 0
    long right = thisRect.right - otherRect.left;
    //thisTop >= otherBottom <=> thisTop - otherBottom >=0
    long top = thisRect.top - otherRect.bottom;
    //thisBottom <= otherTop <=> thisBottom - otherTop <= 0
    long bottom = thisRect.bottom - otherRect.top;
    return (left < 0 && right > 0 && top < 0 && bottom > 0);
}

void CGameObject::Update(DWORD dt, vector<LPCGameObject>* coObjects) {

}

/*
 * Calculate all potential collisions given a list of objects
 * POST: List of collision events
 */
void CGameObject::CalcPotentialCollisions(
    DWORD dt, vector<LPCGameObject>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
    if (objDests == NULL)
        return;
    for (UINT i = 0; i < objDests->size(); i++)
    {

        LPCOLLISIONEVENT e = SweptAABBEx(dt, objDests->at(i));

        if (e->WasCollided() /*|| isColliding(this->getActiveRange(), objDests->at(i)->getActiveRange())*/)
        {

            coEvents.push_back(e);
            DebugOut(L"on collission with %d rect = (%d, %d, %d, %d)\n", i, objDests->at(i)->getActiveRange().left, objDests->at(i)->getActiveRange().right, objDests->at(i)->getActiveRange().top, objDests->at(i)->getActiveRange().bottom);
        }
        else
            delete e;
    }

    std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

/*
 * Find the nearest collision with a provided list of collision events -> find minimum time
 */
void CGameObject::FilterCollision(
    vector<LPCOLLISIONEVENT>& coEvents,
    LPCOLLISIONEVENT& colX,
    LPCOLLISIONEVENT& colY,
    int filterBlock,		// 1 = only filter block collisions, 0 = filter all collisions 
    int filterX,			// 1 = process events on X-axis, 0 = skip events on X 
    int filterY)
{
    float min_tx, min_ty;

    min_tx = 1.0f;
    min_ty = 1.0f;
    int min_ix = -1;
    int min_iy = -1;

    for (UINT i = 0; i < coEvents.size(); i++)
    {
        LPCOLLISIONEVENT c = coEvents[i];
        if (c->isDeleted) continue;
        if (c->obj->IsDeleted()) continue;
        if (filterBlock == 1 && !c->obj->IsBlocking())
        {
            continue;
        }
        if (c->t < min_tx && c->nx != 0 && filterX == 1) {
            min_tx = c->t; min_ix = i;
        }

        if (c->t < min_ty && c->ny != 0 && filterY == 1) {
            min_ty = c->t;  min_iy = i;
        }
    }

    if (min_ix >= 0) colX = coEvents[min_ix];
    if (min_iy >= 0) colY = coEvents[min_iy];
}