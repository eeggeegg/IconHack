
#include <Geode/Geode.hpp>

#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include <iostream>
#include <random>

using namespace geode::prelude;

CCSprite* box;
bool iconhack = false;


class IconHack {
	public:
		void icon_toggle(CCObject*);
		void randomize_icons(CCObject*);
		void recursive_seticon(int, IconType);


};


void IconHack::icon_toggle(CCObject*) {
	if (iconhack){
		iconhack = false;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOff_001.png"));
	}
	else {
		iconhack = true;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOn_001.png"));
	}

	auto garagelayer = as<GJGarageLayer*>(as<CCNode*>(CCDirector::get()->getRunningScene())->getChildren()->objectAtIndex(0));




	Mod::get()->setSavedValue<bool>("is-enabled", iconhack);
}


int generateRandomNumber(int min, int max) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(min, max);

    return distr(eng);
}



void IconHack::recursive_seticon(int id, IconType type) {

	auto gm = GameManager::sharedState();

	auto setid = generateRandomNumber(1, 484);

	if(gm->isIconUnlocked(setid, type)) {
		gm->setPlayerFrame(setid);
	} else {
		recursive_seticon(id, type);
	}

}


void IconHack::randomize_icons(CCObject* sender) {
	
	log::info("Randomize");

	auto gm = GameManager::sharedState();






	gm->setPlayerFrame(generateRandomNumber(1, 484));

	gm->setPlayerShip(generateRandomNumber(1, 169));
	gm->setPlayerBall(generateRandomNumber(1, 118));
	gm->setPlayerBird(generateRandomNumber(1, 149));
	gm->setPlayerDart(generateRandomNumber(1, 96));
	gm->setPlayerRobot(generateRandomNumber(1, 68));
	gm->setPlayerSpider(generateRandomNumber(1, 69));
	gm->setPlayerSwing(generateRandomNumber(1, 43));
	gm->setPlayerJetpack(generateRandomNumber(1, 5));

	gm->setPlayerColor(generateRandomNumber(1, 104));
	gm->setPlayerColor2(generateRandomNumber(1, 104));
	gm->setPlayerColor3(generateRandomNumber(1, 104));

	auto garagelayer = as<GJGarageLayer*>(as<CCNode*>(CCDirector::get()->getRunningScene())->getChildren()->objectAtIndex(0));
	auto colorpage = as<CharacterColorPage*>(garagelayer->getChildByID("CharacterColorPage"));



	garagelayer->updatePlayerColors();

	garagelayer->onPaint(nullptr);

	colorpage->onClose(nullptr);

}


class $modify(CharacterColorPage) {
	
	bool init() {
		bool result = CharacterColorPage::init();

		this->setID("CharacterColorPage");



		CCSprite* randomize_box;

		randomize_box = ButtonSprite::create("Randomize!");

		auto menu = CCMenu::create();

		auto randomize_btn = CCMenuItemSpriteExtra::create(randomize_box, this, menu_selector(IconHack::randomize_icons));


		addChild(menu);
		menu->addChild(randomize_btn);
		randomize_box->setScale(0.5);
		menu->setPosition({305, 293});


		return result;
	}


};

class $modify(GJGarageLayer) {



	bool init() {

		iconhack = Mod::get()->getSavedValue<bool>("is-enabled", true);


		bool result = GJGarageLayer::init();
		auto director = CCDirector::sharedDirector();
		auto size = director->getWinSize(); 

		CCLabelBMFont* label = CCLabelBMFont::create("Icon Hack", "bigFont.fnt");
		if (iconhack){
			box = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		}
		else {
			box = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		}


		auto button = CCMenuItemSpriteExtra::create(box, this, menu_selector(IconHack::icon_toggle)); // this shows its in the garagelayer, (current layer)


		auto menu = CCMenu::create();

		menu->setPosition({size.width/2 - 12,size.height/2});
		menu->setScale(0.6f);
		menu->addChild(button);

		label->setScale(0.45f);
		label->setPosition({menu->getPositionX() + 165.0f, menu->getPositionY() + 64.5f});;

		if (iconhack){
			box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOn_001.png"));
		}
		else {
			box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOff_001.png"));
		}



		addChild(menu);
		addChild(label);
		return result;
	}
};






class $modify(GameManager) {

	bool isIconUnlocked(int iconID, IconType type) {
		bool result = GameManager::isIconUnlocked(iconID, type);
		if (iconhack) {
			return true;
		}
		return result;
	}

	bool isColorUnlocked(int p0, UnlockType p1) {


		bool result = GameManager::isColorUnlocked(p0, p1);
		if (iconhack) {
			return true;
		}
		return result;
	}
};
