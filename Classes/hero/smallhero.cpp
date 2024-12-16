#include "smallhero.h"

smallHero* smallHero::initSmall()
{
    smallHero* smallmy = smallHero::create();
    smallmy->picturename = "./hero/smallHero.png";
    smallmy->picturenum = 1;
    smallmy->heroAnimation(smallmy->picturename, smallmy->picturenum, smallmy, speed, -1);
    return smallmy;
}

void smallHero::moveByMouse_R(Hero* myHero) {
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this, myHero](Event* event) { // ʹ�ò����б��� this �� myHero
        auto mouseEvent = static_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
        {
            auto location = mouseEvent->getLocationInView();
            // ���������һ��ֹͣ���ж����ĵ��ã��Է�ֹ������ͻ
            myHero->runAction(MoveTo::create(1.0f, location));
        }
    };

    // ȷ���¼��ַ�������ȷ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, myHero);
}