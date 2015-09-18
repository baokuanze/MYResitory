#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    //调试
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -400.0f)); //设置重力加速度、默认为100
    auto layer = HelloWorld::create();
    layer->setphyworld(scene->getPhysicsWorld()); //将创建的物理世界传递到子层中
    Size visibleSize=Director::getInstance()->getVisibleSize();        //线宽为1
    auto body=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,1);
    body->setGravityEnable(true);
    auto edgeNode=Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(body);
    scene->addChild(edgeNode);
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EventListenerTouchOneByOne *one=EventListenerTouchOneByOne::create();
    one->onTouchBegan=[this](Touch *touch, Event *unused_event){
        log("onTouchBegan");
        return true;
    };
    one->onTouchEnded=[this](Touch *touch, Event *unused_event){
        log("onTouchEnded");
        addNewSpriteAtPosition(touch->getLocation());
    
    };
    auto dispather=Director::getInstance()->getEventDispatcher();
    dispather->addEventListenerWithSceneGraphPriority(one, this);
    
    
    auto contactListener=EventListenerPhysicsContact::create();
    contactListener->onContactBegin=[this](const PhysicsContact &contact){
        log("contact");
        return true;
    };
    //分开时调用的 设置物理世界中各种物体碰撞的监听对象
    contactListener->onContactSeperate=[this](PhysicsContact &contact){
        auto node1=contact.getShapeA()->getBody()->getNode();
        auto node2=contact.getShapeA()->getBody()->getNode();
        log("seprated");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
 
    return true;
}


void HelloWorld:: addNewSpriteAtPosition(Point p){
    auto sprite=Sprite::create("CloseNormal.png");
    sprite->setTag(1);
    auto body=PhysicsBody::createCircle(sprite->getContentSize().width/2);
    body->setCategoryBitmask(1);
    body->setCollisionBitmask(1);//决定了 能否发生碰撞
    body->setContactTestBitmask(1);
    sprite->setPhysicsBody(body);
    sprite->setPosition(p);
    this->addChild(sprite);
}
void HelloWorld::onEnter(){
    Layer::onEnter();
};

void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
