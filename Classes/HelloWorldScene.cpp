#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // シーンを作成します。
    auto scene = Scene::create();
    
    // 緑から青にグラデーションする
    auto bg = LayerGradient::create(Color4B(194, 50, 194, 255), Color4B(255, 255, 255, 255));
    // シーンを追加します。
    scene->addChild(bg);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    

    // return the scene
    return scene;
}

void HelloWorld::update( float frame )
{
    log("だるい");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    this->schedule(schedule_selector(HelloWorld::update), 5.0f);
    
    // イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create(); // シングルタッチ
    // イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    // タッチ開始
    listener->onTouchBegan = [](Touch* touch, Event* event){
        // タッチ開始時の処理を書く
        Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
        log("X:%f、Y:%fをタッチしました", touchPoint.x, touchPoint.y);
        
        //log("開始");
        return true;
    };
    // タッチ中
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // タッチ中の処理を書く
        log("動かし中");
    };
    
    // タッチ終了
    listener->onTouchEnded = [](Touch* touch, Event* event){
        // タッチ終了時の処理を書く
         log("おわり！");
    };
    // タッチキャンセル
    listener->onTouchCancelled = [](Touch* touch, Event* event){
        // タッチキャンセル時の処理を書く
    };
    // イベントリスナーを登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                       this);
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
