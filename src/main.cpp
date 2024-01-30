
#include <Geode/Geode.hpp>

#include <Geode/modify/GameManager.hpp>


using namespace geode::prelude;


class $modify(GameManager) {

	bool isIconUnlocked(int p0, IconType p1) {

		return true;
	}

	bool isColorUnlocked(int p0, UnlockType p1) {

		return true;
	}
};
