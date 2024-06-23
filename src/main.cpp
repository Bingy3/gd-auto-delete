#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/binding/GameLevelManager.hpp>

static bool auto_delete = true;

class $modify(lil, LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) { return false; }

		auto menu = CCMenu::create();

		auto button = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Disable auto delete"),
			this,
			menu_selector(lil::toggleAutoDelete)
		);

		menu->setID("auto-delete-menu");
		button->setID("toggle-auto-delete-button");

		button->setPosition(310.0f, 160.0f);
		menu->setScale(0.520f);
		menu->setPosition(-220.0f, -50.0f);

		menu->addChild(button);

		this->addChild(menu);

		this->updateSpriteState();

		return true;
	}

	void onBack(cocos2d::CCObject*sender) {
		LevelInfoLayer::onBack(sender);
		if (auto_delete) { GameLevelManager::get()->deleteLevel(this->m_level); }
	}

	void toggleAutoDelete(CCObject*) {
		auto_delete = !auto_delete;
		this->updateSpriteState();
	} 

	void updateSpriteState() {
		CCMenuItemSpriteExtra* button = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("auto-delete-menu")->getChildByID("toggle-auto-delete-button"));
		if (auto_delete)
			button->setSprite(ButtonSprite::create("Disable auto delete"));
		else
			button->setSprite(ButtonSprite::create("Enable auto delete"));
	}
};