#include "GameObject.h"

/*
 * SweptAABB for one static + one moving objects.
 */
void CGameObject::SweptAABB(RECT movingRect,
                            float dx, float dy,
                            RECT staticRect,
                            float &t, float &nx, float &ny) {

    float dx_entry, dx_exit, tx_entry, tx_exit;
    float dy_entry, dy_exit, ty_entry, ty_exit;

    float t_entry;
    float t_exit;

    t = -1.0f;			// no collision
    nx = ny = 0;

    //
    // Broad-phase test
    //

    float bl = dx > 0 ? movingRect.left : movingRect.left + dx;
    float bt = dy > 0 ? movingRect.top + dy : movingRect.top;
    float br = dx > 0 ? movingRect.right + dx : movingRect.right;
    float bb = dy > 0 ? movingRect.bottom : movingRect.bottom + dy;

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
        dx_exit = staticRect.left- movingRect.right;
    }


    if (dy > 0)
    {
        dy_entry = staticRect.bottom - movingRect.top;
        dy_exit = staticRect.top - movingRect.bottom;
    }
    else if (dy < 0)
    {
        dy_entry = movingRect.bottom - staticRect.top;
        dy_exit = movingRect.top - staticRect.bottom;
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


    if (  (tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

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
        dy > 0?ny = -1.0f:ny = 1.0f;
    }

}

/*
 * SweptAABB with two moving objects.
 */
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPCGameObject coO)
{
    float t, nx, ny;

    RECT movingRect = this->getBoundingBox();
    //Assume the other object is static.
    RECT staticRect = coO->getBoundingBox();

    // deal with moving object: m speed = original m speed - collide object speed
    Vec2 staticSpeed = coO->getSpeed();
    Vec2 staticDistance = {staticSpeed.x * dt, staticSpeed.y * dt};

    // (rdx, rdy) is RELATIVE movement distance/velocity
    Vec2 relativeDistance = {this->dx - staticDistance.x, this->dy - staticDistance.y};

    SweptAABB(
            movingRect,
            relativeDistance.x, relativeDistance.y,
            staticRect,
            t, nx, ny
    );

    return new CCollisionEvent(t, nx, ny, relativeDistance.x, relativeDistance.y, coO);
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

    return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

void CGameObject::Update(DWORD dt) {
    this->dt = dt;
    dx = Obj_speed.x*dt;
    dy = Obj_speed.y*dt;
}

/*
 * Calculate all potential collisions given a list of objects
 * POST: List of collision events
 */
void CGameObject::CalcPotentialCollisions(
        vector<LPCGameObject> *coObjects,
        vector<LPCOLLISIONEVENT> &coEvents)
{
    for (UINT i = 0; i < coObjects->size(); i++)
    {
        LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

        if (e->t > 0 && e->t <= 1.0f)
            coEvents.push_back(e);
        else
            delete e;
    }

    std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

/*
 * Find the nearest collision with a provided list of collision events -> find minimum time
 */
void CGameObject::FilterCollision(
        vector<LPCOLLISIONEVENT> &coEvents,
        vector<LPCOLLISIONEVENT> &coEventsResult,
        float &min_tx, float &min_ty,
        float &nx, float &ny, float &rdx, float &rdy)
{
    min_tx = 1.0f;
    min_ty = 1.0f;
    int min_ix = -1;
    int min_iy = -1;

    nx = 0.0f;
    ny = 0.0f;

    coEventsResult.clear();

    for (UINT i = 0; i < coEvents.size(); i++)
    {
        LPCOLLISIONEVENT c = coEvents[i];

        if (c->t < min_tx && c->nx != 0) {
            min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
        }

        if (c->t < min_ty  && c->ny != 0) {
            min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
        }
    }

    if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
    if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}