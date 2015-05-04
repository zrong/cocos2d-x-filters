#include "VisibleRect.h"

Rect VisibleRect::s_visibleRect;
Size VisibleRect::_sSize;

void VisibleRect::lazyInit()
{
    if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
    {
        Director* director = Director::getInstance();
        GLView* pGLView = director->getOpenGLView();
        s_visibleRect.origin = pGLView->getVisibleOrigin();
        s_visibleRect.size = pGLView->getVisibleSize();
        _sSize = director->getWinSize();
    }
}

Rect VisibleRect::getVisibleRect()
{
    lazyInit();
    return Rect(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

Size VisibleRect::getWinSize()
{
    lazyInit();
    return Size(_sSize.width, _sSize.height);
}

Point VisibleRect::left()
{
    lazyInit();
    return Point(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::left(const float &ox, const float &oy)
{
    Point ccp = left();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::right()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::right(const float &ox, const float &oy)
{
    Point ccp = right();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::top()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::top(const float &ox, const float &oy)
{
    Point ccp = top();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::bottom()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

Point VisibleRect::bottom(const float &ox, const float &oy)
{
    Point ccp = bottom();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::center()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::center(const float &ox, const float &oy)
{
    Point ccp = center();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::leftTop()
{
    lazyInit();
    return Point(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::leftTop(const float &ox, const float &oy)
{
    Point ccp = leftTop();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::rightTop()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::rightTop(const float &ox, const float &oy)
{
    Point ccp = rightTop();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

Point VisibleRect::leftBottom(const float &ox, const float &oy)
{
    Point ccp = leftBottom();
    return Point(ccp.x + ox, ccp.y + oy);
}

Point VisibleRect::rightBottom()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}

Point VisibleRect::rightBottom(const float &ox, const float &oy)
{
    Point ccp = rightBottom();
    return Point(ccp.x + ox, ccp.y + oy);
}