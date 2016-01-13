//
//  LocalController.cpp
//  IF
//
//  Created by zhaohf on 13-8-30.
//
//

#include "LocalController.h"
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "../Ext/CCDevice.h"
//#include "support/user_default/CCUserDefault.h"
//#include "TypeDefinition.h"
//#include "CCCommonUtils.h"
//#include "GlobalData.h"

USING_NS_CC;
USING_NS_CC_EXT;

const std::string localPath = "local/";
const std::string xmlFile = "database.local.xml";
const std::string iniFile = "text_zh_CN.ini";

LocalController* LocalController::m_LocalController = NULL;

LocalController::LocalController():m_objINIFileParser(NULL),m_objXMLParser(NULL),m_lang("")
{

}

LocalController::~LocalController()
{
    purgeData();
}

LocalController* LocalController::shared()
{
    if (!m_LocalController) {
        m_LocalController = new LocalController();
        m_LocalController->updatePath = CCFileUtils::sharedFileUtils()->getWritablePath();
        m_LocalController->init();
    }
    return m_LocalController;
}

std::string LocalController::getLanguageFileNameBasedOnUserSystem()
{

}

std::string LocalController::getLanguageFileName()
{
//    if (m_lang != "") {
//        return m_lang;
//    }
//    std::string preferredLanguage = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_PREFERRED_LANGUAGE,"");
//    std::string fileName="";
//    if(preferredLanguage==""){
//        // tao.yu 第一版只开放英文
////        fileName = getLanguageFileNameBasedOnUserSystem();
//        fileName = "en";
//    }else{
//        fileName=preferredLanguage;
//    }
//
//    bool fileExist = CCFileUtils::sharedFileUtils()->isFileExist("local/text/text_"+fileName+".ini");
//    
//    if (!fileExist)
//    {
//        fileName = "en";
//    }
//    
//    m_lang = fileName;
//
//    if (preferredLanguage != fileName) {
//        CCUserDefault::sharedUserDefault()->setStringForKey(KEY_PREFERRED_LANGUAGE, fileName);
//        CCUserDefault::sharedUserDefault()->setStringForKey("current-version-code","");
//        CCUserDefault::sharedUserDefault()->flush();
//    }
//    
//    return fileName;
}

void LocalController::init() {
    purgeData();
    
//    std::string languageFileName = getLanguageFileName();
//    std::string local2 = localPath + "text/text_" + languageFileName + ".ini";
//    m_objINIFileParser = CCINIParser::parseWithFile(local2.c_str(),local2.c_str());
//    
    bool test_xml = false;
    if (false == test_xml)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        const char* XMLS[1] = {
            
            "item_goods.xml",

        };
        m_objXMLParser = new CCRapidXMLParser();
        for (int i = 0; i < 1; i++)
        {
            std::string filePath = FileUtils::getInstance()->fullPathForFilename(XMLS[i]);
            CCLOG("android m_objXMLParser: %s", filePath.c_str());
            m_objXMLParser->initWithFile(filePath.c_str());
        }
#else
        m_objXMLParser = CCRapidXMLParser::parseWithFileAndLocalDir("", "xml");
#endif
    }
    else
    {
        std::string local1 = localPath + xmlFile;
        m_objXMLParser = CCRapidXMLParser::parseWithFile(local1.c_str(), local1.c_str());
        
        auto reset_by_single_xml = [this](const char* xml_path, const char* group_id) {
            
            auto parser = CCRapidXMLParser::parseWithFile(xml_path, xml_path);
            CCDictionary* new_group = parser->getGroupByKey(group_id);
            m_objXMLParser->getDictGroup()->setObject(new_group, group_id);
            for (auto k : *new_group->allKeys()) {
                std::string key = ((__String*)k)->_string;
                auto new_item = parser->getObjectByKey(key);
                m_objXMLParser->getDictItem()->setObject(new_item, key);
            }
            CC_SAFE_RELEASE_NULL(parser);
        };
        reset_by_single_xml("local/xml/item_ab.xml", "ab");
        reset_by_single_xml("local/xml/item_achievement.xml", "achievement");
        reset_by_single_xml("local/xml/item_activity_panel.xml", "activity_panel");
        reset_by_single_xml("local/xml/item_alliancescience.xml", "alliancescience");
        reset_by_single_xml("local/xml/item_allianceshop.xml", "allianceshop");
        reset_by_single_xml("local/xml/item_arms.xml", "arms");
        reset_by_single_xml("local/xml/item_building.xml", "building");
        reset_by_single_xml("local/xml/item_changeLanguage.xml", "changeLanguage");
        reset_by_single_xml("local/xml/item_daily_quest.xml", "daily_quest");
        reset_by_single_xml("local/xml/item_equipment.xml", "equipment");
        reset_by_single_xml("local/xml/item_explore.xml", "explore");
        reset_by_single_xml("local/xml/item_field_monster.xml", "field_monster");
        reset_by_single_xml("local/xml/item_general.xml", "general");
        reset_by_single_xml("local/xml/item_gift.xml", "gift");
        reset_by_single_xml("local/xml/item_goods.xml", "goods");
        reset_by_single_xml("local/xml/item_grade.xml", "grade");
        reset_by_single_xml("local/xml/item_guide.xml", "guide");
        reset_by_single_xml("local/xml/item_help_link.xml", "help_link");
        reset_by_single_xml("local/xml/item_house.xml", "house");
        reset_by_single_xml("local/xml/item_howtoplay.xml", "howtoplay");
        reset_by_single_xml("local/xml/item_lordDetails.xml", "lordDetails");
        reset_by_single_xml("local/xml/item_medal.xml", "medal");
        reset_by_single_xml("local/xml/item_office.xml", "office");
        reset_by_single_xml("local/xml/item_position_unlock.xml", "position_unlock");
        reset_by_single_xml("local/xml/item_position.xml", "position");
        reset_by_single_xml("local/xml/item_quest.xml", "quest");
        reset_by_single_xml("local/xml/item_rank.xml", "rank");
        reset_by_single_xml("local/xml/item_resource2.xml", "resource2");
        reset_by_single_xml("local/xml/item_reward.xml", "reward");
        reset_by_single_xml("local/xml/item_role.xml", "role");
        reset_by_single_xml("local/xml/item_science.xml", "science");
        reset_by_single_xml("local/xml/item_score.xml", "score");
        reset_by_single_xml("local/xml/item_sk.xml", "sk");
        reset_by_single_xml("local/xml/item_status.xml", "status");
        reset_by_single_xml("local/xml/item_territory_effect.xml", "territory_effect");
        reset_by_single_xml("local/xml/item_territory.xml", "territory");
        reset_by_single_xml("local/xml/item_time_gift.xml", "time_gift");
        reset_by_single_xml("local/xml/item_trial.xml", "trial");
        reset_by_single_xml("local/xml/item_vip.xml", "vip");
        reset_by_single_xml("local/xml/item_wonder.xml", "wonder");
        reset_by_single_xml("local/xml/item_worldcastle.xml", "worldcastle");
        reset_by_single_xml("local/xml/loading_tips.xml", "loading_tips");
        reset_by_single_xml("local/xml/titan.xml", "titan");
    }
}

CCRapidXMLParser* LocalController::DBXMLManager()
{
    CCAssert(m_objXMLParser != NULL, "Must init before use the XML!");
    return m_objXMLParser;
    
//    {
//        //  从全局索引表中读取对象的属性
//        CCDictionary * pDictT = pXmlParser->getObjectByKey("1010101");
//        CCString *sValue = (CCString *)pDictT->objectForKey("x");
//        CCLOG("x = %s",sValue->m_sString.c_str());
    
        
//        pDictT = pXmlParser->getObjectByKey("929001");
//        sValue = (CCString *)pDictT->objectForKey("iso_x");
//        CCLOG("iso_x = %s",sValue->m_sString.c_str());
//        
//        pDictT = pXmlParser->getObjectByKey("10");
//        sValue = (CCString *)pDictT->objectForKey("rewardItem");
//        CCLOG("rewardItem = %s",sValue->m_sString.c_str());
//        
//        //  从分组索引表中读取对象的属性
//        CCDictionary * pGroupDict = pXmlParser->getGroupByKey("Item");
//        
//        CCDictionary * pDictItem = (CCDictionary *)pGroupDict->objectForKey("330005");
//        
//        sValue = (CCString *)pDictItem->objectForKey("cash_cost");
//        CCLOG("cash_cost = %s",sValue->m_sString.c_str());
        
//    }
    
}
CCINIParser* LocalController::TextINIManager()
{
    //TODO 根据手机语言取得不同ini文件
    CCAssert(m_objINIFileParser != NULL, "Must init before use the INI!");
    return m_objINIFileParser;
}

void LocalController::purgeData() {
//    CC_SAFE_RELEASE_NULL(m_objINIFileParser);
    CC_SAFE_RELEASE_NULL(m_objXMLParser);
}
