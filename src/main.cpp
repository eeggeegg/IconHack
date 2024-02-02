
#include <Geode/Geode.hpp>

#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GJGarageLayer.hpp>



using namespace geode::prelude;

CCSprite* box;
bool iconhack = false;

class IconHack {
	public:
		void icon_toggle(CCObject*);
};


void IconHack::icon_toggle(CCObject* xanii) {
	if (iconhack){
		iconhack = false;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOff_001.png"));
	}
	else {
		iconhack = true;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOn_001.png"));
	}
	Mod::get()->setSavedValue<bool>("is-enabled", iconhack);
}


class $modify(GJGarageLayer) {


	void refreshIcons() {
		selectTab(IconType::Cube);
	}

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




