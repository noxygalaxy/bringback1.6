#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;

// This is my shit code :p laugh at it <3
struct OriginalState {
    CCPoint position;
    CCPoint scale;
    bool visible;
    CCSprite* originalSprite = nullptr;
    CCPoint anchorPoint;

    OriginalState() : position(CCPointZero), scale(CCPointZero), visible(false), anchorPoint(CCPoint(0.5f, 0.5f)) {}
    OriginalState(CCPoint pos, CCPoint scl, bool vis, CCSprite* sprite = nullptr, CCPoint anchor = CCPoint(0.5f, 0.5f)) 
        : position(pos), scale(scl), visible(vis), originalSprite(sprite), anchorPoint(anchor) {
        if (sprite) sprite->retain();
    }
    OriginalState(const OriginalState& other) 
        : position(other.position), scale(other.scale), visible(other.visible), 
          originalSprite(other.originalSprite), anchorPoint(other.anchorPoint) {
        if (originalSprite) originalSprite->retain();
    }
    ~OriginalState() {
        if (originalSprite) originalSprite->release();
    }
};

std::string getButtonSpriteName(bool isOldStyle, int quality) {
    std::string base = isOldStyle ? "bringback22-btn" : "bringback16-btn";
    std::string suffix;
    switch (quality) {
        case 2: // High quality
            suffix = "-uhd";
            break;
        case 1: // Medium quality
            suffix = "-hd";
            break;
        case 0: // Low quality
        default:
            suffix = "";
            break;
    }
    std::string spriteName = "noxygalaxy.bring_back_16/" + base + suffix + ".png";
    log::info("Attempting to load sprite: {}", spriteName);
    return spriteName;
}

// LevelInfoLayer modification
class $modify(OldStyleLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        bool isOldStyle = false;
        CCMenu* toggleMenu = nullptr;
        CCMenuItemSpriteExtra* toggleButton = nullptr;
        std::unordered_map<std::string, OriginalState> originalStates;
    };

    void storeOriginalState(CCNode* node, const std::string& id) {
        if (node) {
            m_fields->originalStates[id] = OriginalState(node->getPosition(), CCPoint(node->getScaleX(), node->getScaleY()), node->isVisible());
        }
    }

    void applyOldStyle() {
        bool hideCustomSongs = Mod::get()->getSettingValue<bool>("hide-custom-songs");

        if (hideCustomSongs) {
            if (auto widget = getChildByID("custom-songs-widget")) widget->setVisible(false);
        }

        if (auto widget = getChildByID("custom-songs-widget")) {
            widget->setScale(0.55);
            widget->setPosition(419.5, 187.0);
        }
        if (auto bar = getChildByID("practice-mode-bar")) {
            bar->setPosition(284.5, 22.0);
            bar->setScale(1.0);
            getChildByID("normal-mode-bar")->setPosition(284.5, 75.0);
            getChildByID("normal-mode-bar")->setScale(1.0);
        }
        if (auto percentage = getChildByID("practice-mode-percentage")) {
            percentage->setPosition(284.5, 22.0);
            percentage->setScale(0.55);
            getChildByID("normal-mode-percentage")->setPosition(284.5, 75.0);
            getChildByID("normal-mode-percentage")->setScale(0.55);
        }
        if (auto label = getChildByID("practice-mode-label")) {
            label->setPosition(284.5, 42.0);
            label->setScale(0.6);
            getChildByID("normal-mode-label")->setPosition(284.5, 95.0);
            getChildByID("normal-mode-label")->setScale(0.6);
        }
        if (auto coin = getChildByID("coin-icon-1")) {
            coin->setPositionY(168.0);
            getChildByID("coin-icon-2")->setPositionY(168.0);
            getChildByID("coin-icon-3")->setPositionY(168.0);
            getChildByID("difficulty-sprite")->setPositionY(198.0);
        } else {
            getChildByID("difficulty-sprite")->setPositionY(191.0);
        }
        if (auto icon = getChildByID("length-icon")) {
            icon->setPosition(155.5, 126.0);
            getChildByID("downloads-icon")->setPosition(262.5, 126.0);
            getChildByID("likes-icon")->setPosition(361.5, 126.0);
            getChildByID("orbs-icon")->setVisible(false);
        }
        if (auto label = getChildByID("length-label")) {
            label->setPosition(185.5, 125.0);
            label->setScale(0.6);
            getChildByID("exact-length-label")->setPosition(185.5, 115.0);
            getChildByID("exact-length-label")->setVisible(false);
            getChildByID("downloads-label")->setPosition(292.5, 125.0);
            getChildByID("downloads-label")->setScale(0.6);
            getChildByID("likes-label")->setPosition(391.5, 126.0);
            getChildByID("likes-label")->setScale(0.6);
            getChildByID("orbs-label")->setVisible(false);
        }
        if (auto menu = getChildByID("play-menu")) menu->setPositionY(138.0);
        if (auto label = getChildByID("title-label")) {
            label->setPositionY(288.0);
            label->setScale(1.15);
            getChildByID("creator-info-menu")->setPositionY(256.2);
            getChildByID("creator-info-menu")->setScale(1.1);
        }
    }

    void restoreOriginalStyle() {
        for (const auto& [id, state] : m_fields->originalStates) {
            if (auto node = getChildByID(id)) {
                node->setPosition(state.position);
                node->setScaleX(state.scale.x);
                node->setScaleY(state.scale.y);
                node->setVisible(state.visible);
            }
        }
    }

    void updateButtonSprite() {
        if (m_fields->toggleButton) {
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto newSprite = CCSprite::create(spriteName.c_str());
            if (!newSprite) {
                log::error("Failed to load sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                newSprite = CCSprite::create(spriteName.c_str());
            }
            if (newSprite) {
                m_fields->toggleButton->setNormalImage(newSprite);
            } else {
                log::error("Failed to load fallback sprite: {}", spriteName);
            }
        }
    }

    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_enabled", m_fields->isOldStyle);
        m_fields->isOldStyle ? applyOldStyle() : restoreOriginalStyle();
        updateButtonSprite();
    }

    bool init(GJGameLevel* level, bool p1) {
        if (!LevelInfoLayer::init(level, p1)) return false;

        bool shouldModify = Mod::get()->getSettingValue<bool>("change-levelinfolayer");
        const std::vector<std::string> ids = {
            "custom-songs-widget", "practice-mode-bar", "normal-mode-bar", "practice-mode-percentage",
            "normal-mode-percentage", "practice-mode-label", "normal-mode-label", "coin-icon-1",
            "coin-icon-2", "coin-icon-3", "difficulty-sprite", "length-icon", "downloads-icon",
            "likes-icon", "orbs-icon", "length-label", "exact-length-label", "downloads-label",
            "likes-label", "orbs-label", "play-menu", "title-label", "creator-info-menu"
        };

        for (const auto& id : ids) storeOriginalState(getChildByID(id), id);

        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_enabled", false);
            if (m_fields->isOldStyle) applyOldStyle();

            m_fields->toggleMenu = CCMenu::create();
            m_fields->toggleMenu->setID("bringback1.6-menu");
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto buttonSprite = CCSprite::create(spriteName.c_str());
            if (!buttonSprite) {
                log::error("Failed to load initial sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                buttonSprite = CCSprite::create(spriteName.c_str());
            }
            if (buttonSprite) {
                m_fields->toggleButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(OldStyleLevelInfoLayer::onToggle));
                m_fields->toggleButton->setID("bringback-btn");
                m_fields->toggleMenu->addChild(m_fields->toggleButton);
                m_fields->toggleMenu->setPosition(422.0, 295.0);
                addChild(m_fields->toggleMenu);
            } else {
                log::error("Failed to create toggle button with sprite: {}", spriteName);
            }
        } else {
            restoreOriginalStyle();
        }
        return true;
    }
};

// CreatorLayer modification
class $modify(OldStyleCreatorLayer, CreatorLayer) {
    struct Fields {
        bool isOldStyle = false;
        CCMenu* toggleMenu = nullptr;
        CCMenuItemSpriteExtra* toggleButton = nullptr;
        std::unordered_map<std::string, OriginalState> originalStates;
        bool statesStored = false;
    };

    void storeOriginalState(CCNode* node, const std::string& id) {
        if (node) m_fields->originalStates[id] = OriginalState(node->getPosition(), CCPoint(node->getScaleX(), node->getScaleY()), node->isVisible());
    }

    void storeInitialStates() {
        if (m_fields->statesStored) return;
        if (auto creatorMenu = getChildByID("creator-buttons-menu")) {
            const std::vector<std::string> ids = {
                "versus-button", "map-button", "daily-button", "weekly-button", "event-button",
                "gauntlets-button", "lists-button", "paths-button", "quests-button", "create-button",
                "saved-button", "scores-button", "featured-button", "map-packs-button", "search-button"
            };
            for (const auto& id : ids) storeOriginalState(creatorMenu->getChildByID(id), id);
        }
        m_fields->statesStored = true;
    }

    void applyOldStyle() {
        if (!m_fields->statesStored) storeInitialStates();
        if (auto creatorMenu = getChildByID("creator-buttons-menu")) {
            if (auto btn = creatorMenu->getChildByID("versus-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("map-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("daily-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("weekly-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("event-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("gauntlets-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("lists-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("paths-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("quests-button")) btn->setVisible(false);
            if (auto btn = creatorMenu->getChildByID("create-button")) btn->setPosition(135.8, 205.0);
            if (auto btn = creatorMenu->getChildByID("saved-button")) btn->setPosition(225.8, 205.0);
            if (auto btn = creatorMenu->getChildByID("scores-button")) btn->setPosition(315.8, 205.0);
            if (auto btn = creatorMenu->getChildByID("featured-button")) btn->setPosition(135.8, 105.0);
            if (auto btn = creatorMenu->getChildByID("map-packs-button")) btn->setPosition(225.8, 105.0);
            if (auto btn = creatorMenu->getChildByID("search-button")) btn->setPosition(315.8, 105.0);
        }
    }

    void restoreOriginalStyle() {
        if (auto creatorMenu = getChildByID("creator-buttons-menu")) {
            for (const auto& [id, state] : m_fields->originalStates) {
                if (auto node = creatorMenu->getChildByID(id)) {
                    node->setPosition(state.position);
                    node->setScaleX(state.scale.x);
                    node->setScaleY(state.scale.y);
                    node->setVisible(state.visible);
                }
            }
        }
    }

    void updateButtonSprite() {
        if (m_fields->toggleButton) {
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto newSprite = CCSprite::create(spriteName.c_str());
            if (!newSprite) {
                log::error("Failed to load sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                newSprite = CCSprite::create(spriteName.c_str());
            }
            if (newSprite) m_fields->toggleButton->setNormalImage(newSprite);
        }
    }

    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_in_creatorlayer", m_fields->isOldStyle);
        m_fields->isOldStyle ? applyOldStyle() : restoreOriginalStyle();
        updateButtonSprite();
    }

    bool init() {
        if (!CreatorLayer::init()) return false;
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-creatorlayer");

        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_in_creatorlayer", false);
            m_fields->toggleMenu = CCMenu::create();
            m_fields->toggleMenu->setID("bringback1.6-menu");
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto buttonSprite = CCSprite::create(spriteName.c_str());
            if (!buttonSprite) {
                log::error("Failed to load initial sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                buttonSprite = CCSprite::create(spriteName.c_str());
            }
            if (buttonSprite) {
                m_fields->toggleButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(OldStyleCreatorLayer::onToggle));
                m_fields->toggleButton->setID("bringback-btn");
                m_fields->toggleMenu->addChild(m_fields->toggleButton);
                m_fields->toggleMenu->setPosition(422.0, 295.0);
                addChild(m_fields->toggleMenu);
            }
        }
        this->scheduleOnce(schedule_selector(OldStyleCreatorLayer::onDelayedInit), 0.01f);
        return true;
    }

    void onDelayedInit(float dt) {
        storeInitialStates();
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-creatorlayer");
        if (shouldModify && m_fields->isOldStyle) applyOldStyle();
        else if (!shouldModify) restoreOriginalStyle();
    }
};

// EditorPauseLayer modification
class $modify(OldStyleEditorPauseLayer, EditorPauseLayer) {
    struct Fields {
        bool isOldStyle = false;
        CCMenu* toggleMenu = nullptr;
        CCMenuItemSpriteExtra* toggleButton = nullptr;
        std::unordered_map<std::string, OriginalState> originalStates;
        bool statesStored = false;
    };

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorPauseLayer::init(editorLayer)) return false;
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-editorpauselayer");

        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_in_editorpause", false);
            m_fields->toggleMenu = CCMenu::create();
            m_fields->toggleMenu->setID("bringback1.6-menu");
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto buttonSprite = CCSprite::create(spriteName.c_str());
            if (!buttonSprite) {
                log::error("Failed to load initial sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                buttonSprite = CCSprite::create(spriteName.c_str());
            }
            if (buttonSprite) {
                m_fields->toggleButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(OldStyleEditorPauseLayer::onToggle));
                m_fields->toggleButton->setID("bringback-btn");
                m_fields->toggleButton->setPositionX(-100.0);
                m_fields->toggleMenu->addChild(m_fields->toggleButton);
                auto winSize = CCDirector::sharedDirector()->getWinSize();
                m_fields->toggleMenu->setPosition(winSize.width - 50.0f, winSize.height - 25.0f);
                addChild(m_fields->toggleMenu, 100);
            }
            if (m_fields->isOldStyle) applyOldStyle();
        }
        return true;
    }

    void storeOriginalState(CCNode* node, const std::string& id) {
        if (node) m_fields->originalStates[id] = OriginalState(node->getPosition(), CCPoint(node->getScaleX(), node->getScaleY()), node->isVisible());
    }

    void storeInitialStates() {
        if (m_fields->statesStored) return;
        if (auto resumeMenu = getChildByID("resume-menu")) {
            const std::vector<std::string> ids = {"resume-button", "save-and-play-button", "save-and-exit-button", "exit-button", "save-button"};
            for (const auto& id : ids) storeOriginalState(resumeMenu->getChildByID(id), id);
        }
        m_fields->statesStored = true;
    }

    void applyOldStyle() {
        if (!m_fields->statesStored) storeInitialStates();
        if (auto resumeMenu = getChildByID("resume-menu")) {
            if (auto btn = resumeMenu->getChildByID("save-button")) btn->setVisible(false);
            if (auto btn = resumeMenu->getChildByID("resume-button")) btn->setPosition(98.0, 175.0);
            if (auto btn = resumeMenu->getChildByID("save-and-play-button")) btn->setPosition(98.0, 130.0);
            if (auto btn = resumeMenu->getChildByID("save-and-exit-button")) btn->setPosition(98.0, 85.0);
            if (auto btn = resumeMenu->getChildByID("exit-button")) btn->setPosition(98.0, 40.0);
        }
    }

    void restoreOriginalStyle() {
        if (auto resumeMenu = getChildByID("resume-menu")) {
            for (const auto& [id, state] : m_fields->originalStates) {
                if (auto node = resumeMenu->getChildByID(id)) {
                    node->setPosition(state.position);
                    node->setScaleX(state.scale.x);
                    node->setScaleY(state.scale.y);
                    node->setVisible(state.visible);
                }
            }
        }
    }

    void updateButtonSprite() {
        if (m_fields->toggleButton) {
            int quality = GameManager::sharedState()->getGameVariable("0033") ? 2 :
                         GameManager::sharedState()->getGameVariable("0032") ? 1 : 0;
            log::info("Quality level detected: {}", quality);
            std::string spriteName = getButtonSpriteName(m_fields->isOldStyle, quality);
            auto newSprite = CCSprite::create(spriteName.c_str());
            if (!newSprite) {
                log::error("Failed to load sprite: {}", spriteName);
                spriteName = m_fields->isOldStyle ? "noxygalaxy.bring_back_16/bringback22-btn.png" : "noxygalaxy.bring_back_16/bringback16-btn.png";
                newSprite = CCSprite::create(spriteName.c_str());
            }
            if (newSprite) m_fields->toggleButton->setNormalImage(newSprite);
        }
    }

    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_in_editorpause", m_fields->isOldStyle);
        m_fields->isOldStyle ? applyOldStyle() : restoreOriginalStyle();
        updateButtonSprite();
    }
};