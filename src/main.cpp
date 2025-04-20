#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;

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

std::string getButtonSpriteName(bool isOldStyle) {
    return isOldStyle ? "bringback22-btn.png"_spr : "bringback16-btn.png"_spr;
}

// LevelInfoLayer modification
class $modify(OldStyleLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        bool isOldStyle = false;
        CCMenuItemToggler* toggleButton = nullptr;
        std::unordered_map<std::string, OriginalState> originalStates;
    };

    void storeOriginalState(CCNode* node, const std::string& id) {
        if (node) {
            m_fields->originalStates[id] = OriginalState(node->getPosition(), CCPoint(node->getScaleX(), node->getScaleY()), node->isVisible());
        }
    }

    void applyOldStyle() {
        bool hideCustomSongs = Mod::get()->getSettingValue<bool>("hide-custom-songs");

        if (auto widget = getChildByID("custom-songs-widget")) {
            if (hideCustomSongs) widget->setVisible(false);
            widget->setScale(0.55);
            widget->setPosition(419.5, 187.0);
        }

        if (auto practiceBar = getChildByID("practice-mode-bar")) {
            if (auto normalBar = getChildByID("normal-mode-bar")) {
                practiceBar->setPosition(284.5, 22.0);
                practiceBar->setScale(1.0);
                normalBar->setPosition(284.5, 75.0);
                normalBar->setScale(1.0);
            }
        }

        if (auto practicePercent = getChildByID("practice-mode-percentage")) {
            if (auto normalPercent = getChildByID("normal-mode-percentage")) {
                practicePercent->setPosition(284.5, 22.0);
                practicePercent->setScale(0.55);
                normalPercent->setPosition(284.5, 75.0);
                normalPercent->setScale(0.55);
            }
        }

        if (auto practiceLabel = getChildByID("practice-mode-label")) {
            if (auto normalLabel = getChildByID("normal-mode-label")) {
                practiceLabel->setPosition(284.5, 42.0);
                practiceLabel->setScale(0.6);
                normalLabel->setPosition(284.5, 95.0);
                normalLabel->setScale(0.6);
            }
        }

        CCNode* coin1 = getChildByID("coin-icon-1");
        CCNode* coin2 = getChildByID("coin-icon-2");
        CCNode* coin3 = getChildByID("coin-icon-3");
        CCNode* difficulty = getChildByID("difficulty-sprite");
        CCNode* moreDifficulties = getChildByID("uproxide.more_difficulties/more-difficulties-spr");
        if (coin1 && coin2 && coin3 && difficulty) {
            coin1->setPositionY(161.0);
            coin2->setPositionY(161.0);
            coin3->setPositionY(161.0);
            difficulty->setPositionY(171.0);
        }
        if (coin1 && difficulty) {
            coin1->setPositionY(161.0);
            difficulty->setPositionY(171.0);
        }
        if (coin1 && coin2 && difficulty) {
            coin1->setPositionY(161.0);
            coin2->setPositionY(161.0);
            difficulty->setPositionY(171.0);
        } else if (difficulty) {
            difficulty->setPositionY(171.0);
        }

        if (coin1 && coin2 && coin3 && moreDifficulties) {
            coin1->setPositionY(161.0);
            coin2->setPositionY(161.0);
            coin3->setPositionY(161.0);
            moreDifficulties->setPositionY(204.5);
        }
        if (coin1 && moreDifficulties) {
            coin1->setPositionY(161.0);
            moreDifficulties->setPositionY(204.5);
        }
        if (coin1 && coin2 && moreDifficulties) {
            coin1->setPositionY(161.0);
            coin2->setPositionY(161.0);
            moreDifficulties->setPositionY(204.5);
        } else if (moreDifficulties) {
            moreDifficulties->setPositionY(171.0);
        }

        if (auto lengthIcon = getChildByID("length-icon")) {
            if (auto downloadsIcon = getChildByID("downloads-icon")) {
                if (auto likesIcon = getChildByID("likes-icon")) {
                    if (auto orbsIcon = getChildByID("orbs-icon")) {
                        lengthIcon->setPosition(155.5, 126.0);
                        downloadsIcon->setPosition(262.5, 126.0);
                        likesIcon->setPosition(361.5, 126.0);
                        orbsIcon->setVisible(false);
                    }
                }
            }
        }

        if (auto lengthLabel = getChildByID("length-label")) {
            if (auto exactLengthLabel = getChildByID("exact-length-label")) {
                if (auto downloadsLabel = getChildByID("downloads-label")) {
                    if (auto likesLabel = getChildByID("likes-label")) {
                        if (auto orbsLabel = getChildByID("orbs-label")) {
                            lengthLabel->setPosition(185.5, 125.0);
                            lengthLabel->setScale(0.6);
                            exactLengthLabel->setPosition(185.5, 115.0);
                            exactLengthLabel->setVisible(false);
                            downloadsLabel->setPosition(292.5, 125.0);
                            downloadsLabel->setScale(0.6);
                            likesLabel->setPosition(391.5, 126.0);
                            likesLabel->setScale(0.6);
                            orbsLabel->setVisible(false);
                        }
                    }
                }
            }
        }

        if (auto playMenu = getChildByID("play-menu")) playMenu->setPositionY(138.0);

        if (auto titleLabel = getChildByID("title-label")) {
            if (auto creatorMenu = getChildByID("creator-info-menu")) {
                titleLabel->setPositionY(288.0);
                titleLabel->setScale(1.15);
                creatorMenu->setPositionY(250.2);
                creatorMenu->setScale(1.1);
            }
        }

        if (auto copyIndicator = getChildByID("copy-indicator")) {
            copyIndicator->setPositionY(258.0);
        }

        if (auto highObjectIndicator = getChildByID("high-object-indicator")) {
            highObjectIndicator->setPositionY(258.0);
        }

        CCNode* starsLabel = getChildByID("stars-label");
        CCNode* starsIcon = getChildByID("stars-icon");
        if (starsLabel && starsIcon) {
            starsLabel->setPositionY(172.0);
            starsIcon->setPositionY(172.0);
            if (difficulty) difficulty->setPositionY(211.0);
            if (moreDifficulties) moreDifficulties->setPositionY(211.0);
        }
        if (coin1 && coin2 && coin3 && starsLabel && starsIcon) {
            coin1->setPositionY(156.5);
            coin2->setPositionY(156.5);
            coin3->setPositionY(156.5);
            starsLabel->setPositionY(172.0);
            starsIcon->setPositionY(172.0);
            if (difficulty) difficulty->setPositionY(205.0);
            if (moreDifficulties) moreDifficulties->setPositionY(205.0);
        }
        if (coin1 && starsLabel && starsIcon) {
            coin1->setPositionY(156.5);
            starsLabel->setPositionY(172.0);
            starsIcon->setPositionY(172.0);
            if (difficulty) difficulty->setPositionY(205.0);
            if (moreDifficulties) moreDifficulties->setPositionY(205.0);
        }
        if (coin1 && coin2 && starsLabel && starsIcon) {
            coin1->setPositionY(156.5);
            coin2->setPositionY(156.5);
            starsLabel->setPositionY(172.0);
            starsIcon->setPositionY(172.0);
            if (difficulty) difficulty->setPositionY(205.0);
            if (moreDifficulties) moreDifficulties->setPositionY(205.0);
        }

        CCNode* bestTimeLabel = getChildByID("best-time-label");
        if (bestTimeLabel) {
            bestTimeLabel->setPositionY(100.0);
            bestTimeLabel->setScale(0.85);
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

    bool init(GJGameLevel* level, bool p1) {
        if (!LevelInfoLayer::init(level, p1)) return false;
    
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-levelinfolayer");
        const std::vector<std::string> ids = {
            "custom-songs-widget", "practice-mode-bar", "normal-mode-bar", "practice-mode-percentage",
            "normal-mode-percentage", "practice-mode-label", "normal-mode-label", "coin-icon-1",
            "coin-icon-2", "coin-icon-3", "difficulty-sprite", "length-icon", "downloads-icon",
            "likes-icon", "orbs-icon", "length-label", "exact-length-label", "downloads-label",
            "likes-label", "orbs-label", "play-menu", "title-label", "creator-info-menu",
            "copy-indicator", "high-object-indicator", "stars-label", "stars-icon",
            "uproxide.more_difficulties/more-difficulties-spr", "best-time-label"
        };
    
        for (const auto& id : ids) storeOriginalState(getChildByID(id), id);
    
        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_enabled", false);
    
            auto node = getChildByID("left-side-menu");
            if (!node || !dynamic_cast<CCMenu*>(node)) return true;
            auto menu = static_cast<CCMenu*>(node);
    
            auto offSprite = CCSprite::create("bringback16-btn.png"_spr);
            auto onSprite = CCSprite::create("bringback22-btn.png"_spr);
    
            if (!offSprite || !onSprite) {
                log::error("Failed to create toggle sprites: offSprite={}, onSprite={}", 
                    offSprite ? "loaded" : "null", onSprite ? "loaded" : "null");
                return true;
            }
    
            m_fields->toggleButton = CCMenuItemToggler::create(
                offSprite,
                onSprite,
                this,
                menu_selector(OldStyleLevelInfoLayer::onToggle)
            );
            m_fields->toggleButton->setID("bringback-btn");
            m_fields->toggleButton->toggle(m_fields->isOldStyle);
            menu->addChild(m_fields->toggleButton);
            menu->updateLayout();
    
            if (m_fields->isOldStyle) applyOldStyle();
        }
        return true;
    }
    
    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_enabled", m_fields->isOldStyle);
        if (m_fields->isOldStyle) {
            applyOldStyle();
        } else {
            restoreOriginalStyle();
        }
    }
};

// CreatorLayer modification
class $modify(OldStyleCreatorLayer, CreatorLayer) {
    struct Fields {
        bool isOldStyle = false;
        CCMenuItemToggler* toggleButton = nullptr;
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

    bool init() {
        if (!CreatorLayer::init()) return false;
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-creatorlayer");

        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_in_creatorlayer", false);

            auto menu = getChildByID("top-right-menu");
            if (!menu || !menu->getChildByID("vault-button")) return true;
            auto referenceBtn = menu->getChildByID("vault-button");

            auto offSprite = CCSprite::create("bringback16-btn.png"_spr);
            auto onSprite = CCSprite::create("bringback22-btn.png"_spr);

            if (!offSprite || !onSprite) {
                log::error("Failed to create toggle sprites: offSprite={}, onSprite={}", 
                    offSprite ? "loaded" : "null", onSprite ? "loaded" : "null");
                return true;
            }

            m_fields->toggleButton = CCMenuItemToggler::create(
                offSprite,
                onSprite,
                this,
                menu_selector(OldStyleCreatorLayer::onToggle)
            );
            m_fields->toggleButton->setID("bringback-btn");
            m_fields->toggleButton->toggle(m_fields->isOldStyle);
            m_fields->toggleButton->setPosition(referenceBtn->getPosition() - CCPoint{50.f, 0.f});
            menu->addChild(m_fields->toggleButton);
            menu->updateLayout();

            if (m_fields->isOldStyle) applyOldStyle();
        }
        this->scheduleOnce(schedule_selector(OldStyleCreatorLayer::onDelayedInit), 0.01f);
        return true;
    }

    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_in_creatorlayer", m_fields->isOldStyle);
        if (m_fields->isOldStyle) {
            applyOldStyle();
        } else {
            restoreOriginalStyle();
        }
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
        CCMenuItemToggler* toggleButton = nullptr;
        std::unordered_map<std::string, OriginalState> originalStates;
        bool statesStored = false;
    };

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorPauseLayer::init(editorLayer)) return false;
        bool shouldModify = Mod::get()->getSettingValue<bool>("change-editorpauselayer");

        if (shouldModify) {
            m_fields->isOldStyle = Mod::get()->getSavedValue<bool>("old_style_in_editorpause", false);

            auto menu = getChildByID("guidelines-menu");
            if (!menu || !menu->getChildByID("guidelines-enable-toggle")) return true;
            auto referenceBtn = menu->getChildByID("guidelines-enable-toggle");

            auto offSprite = CCSprite::create("bringback16-btn.png"_spr);
            auto onSprite = CCSprite::create("bringback22-btn.png"_spr);

            if (!offSprite || !onSprite) {
                log::error("Failed to create toggle sprites: offSprite={}, onSprite={}", 
                offSprite ? "loaded" : "null", onSprite ? "loaded" : "null");
                return true;
            }

            m_fields->toggleButton = CCMenuItemToggler::create(
                offSprite,
                onSprite,
                this,
                menu_selector(OldStyleEditorPauseLayer::onToggle)
            );
            m_fields->toggleButton->setID("bringback-btn");
            m_fields->toggleButton->toggle(m_fields->isOldStyle);
            m_fields->toggleButton->setPosition(referenceBtn->getPosition() + CCPoint{50.f, 0.f});
            menu->addChild(m_fields->toggleButton);
            menu->updateLayout();

            if (m_fields->isOldStyle) applyOldStyle();
        }
        return true;
    }

    void onToggle(CCObject* sender) {
        m_fields->isOldStyle = !m_fields->isOldStyle;
        Mod::get()->setSavedValue("old_style_in_editorpause", m_fields->isOldStyle);
        if (m_fields->isOldStyle) {
            applyOldStyle();
        } else {
            restoreOriginalStyle();
        }
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
};