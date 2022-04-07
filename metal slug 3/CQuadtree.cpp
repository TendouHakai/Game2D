#include "CQuadtree.h"

void CQuadtree::setRootNode(unordered_map<int, LPCGameObject> GameObjects, int w, int h)
{
	int i = 0;
	if (w > h)
		i = w;
	else i = h;
	this->rootNode = new CQuadnode(0, i, i, 0, GameObjects, true);
}

void CQuadtree::Build(CQuadnode* Node)
{
    if (CCamera::GetInstance()->GetCamSize().x >= Node->getWidth() && CCamera::GetInstance()->GetCamSize().y <= Node->getHeight() && Node->Objects.size() > 0)
    {
        Node->lt = new CQuadnode(Node->ltx, Node->lty, Node->ltx + abs(Node->rbx - Node->ltx) / 2, Node->rby + abs(Node->lty - Node->rby) / 2, Node->Objects, false);
        Node->rt = new CQuadnode(Node->ltx + abs(Node->rbx - Node->ltx) / 2, Node->lty, Node->rbx, Node->rby + abs(Node->lty - Node->rby) / 2, Node->Objects, false);
        Node->rb = new CQuadnode(Node->ltx + abs(Node->rbx - Node->ltx) / 2, Node->rby + abs(Node->lty - Node->rby) / 2, Node->rbx, Node->rby, Node->Objects, false);
        Node->lb = new CQuadnode(Node->ltx, Node->rby + abs(Node->lty - Node->rby) / 2, Node->ltx + abs(Node->rbx - Node->ltx) / 2, Node->rby, Node->Objects, false);
        Node->Objects.clear();
        Build(Node->lt);
        Build(Node->rt);
        Build(Node->rb);
        Build(Node->lb);
    }
    else
    {
        return;
    }
    
}

void CQuadtree::getListGameObjectInCamera(CQuadnode* Node)
{
    if (Node->lt == NULL)
    {
        if (CGraphic::GetInstance()->Collision(CCamera::GetInstance()->getBoundingBox(), Node->getBoudingBox()))
        {
            for (auto x : Node->Objects)
            {
                if(listGameObjectInCamera.size()==0)
                    listGameObjectInCamera.insert(x);
                else
                {
                    for (auto y : listGameObjectInCamera)
                        if (x.first == y.first)
                            continue;
                }
                /*unordered_map<int, LPCGameObject>::const_iterator got = listGameObjectInCamera.find(x.first);
                if (got == listGameObjectInCamera.end())
                    listGameObjectInCamera.insert(x);*/
                listGameObjectInCamera.insert(x);
                DebugOut(L"Object %d\n", x.first);
            }
        }
    }
    else
    {
        if (CGraphic::GetInstance()->Collision(CCamera::GetInstance()->getBoundingBox(), Node->lt->getBoudingBox()))
            getListGameObjectInCamera(Node->lt);
        if (CGraphic::GetInstance()->Collision(CCamera::GetInstance()->getBoundingBox(), Node->rt->getBoudingBox()))
            getListGameObjectInCamera(Node->rt);
        if (CGraphic::GetInstance()->Collision(CCamera::GetInstance()->getBoundingBox(), Node->rb->getBoudingBox()))
            getListGameObjectInCamera(Node->rb);
        if (CGraphic::GetInstance()->Collision(CCamera::GetInstance()->getBoundingBox(), Node->lb->getBoudingBox()))
            getListGameObjectInCamera(Node->lb);
    }
}
