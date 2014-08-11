//
//  ClashUnit.cpp
//  MerryMe
//
//  Created by youn seok park on 2014. 7. 4..
//
//

#include "ClashUnit.h"
#include "MMSpriteResourceManager.h"
#include "gamedefs.h"
#include "ClashBoard.h"

#define CLASHUNIT_MOVESPEED     0.1
//static int farmCropOffsetTable[][]={};

//static int posAdjustTable[6][2]={{0,0},{0,0},{0,6},{0,24},{0,36},{0,24}};


ClashUnit::ClashUnit() {
    
}

bool ClashUnit::init(ClashBoard *board) {
    
    if(SFActor::init(0) == false)
        return false;
    
    this->m_pBoard = board;
    this->setReadyToMerge(false);

    return true;
}

ClashUnit::~ClashUnit() {
    
    CCLog("[INFO]::ClashUnit::~ClashUnit() called!");
    
	//CC_SAFE_RELEASE_NULL(this->m_arrRenderSpriteList);
}

ClashUnit *ClashUnit::create(ClashBoard *board) {
    
    ClashUnit *unit = new ClashUnit();
    unit->init(board);
    unit->autorelease();
    
    return unit;
}

bool ClashUnit::bindToParent(cocos2d::CCNode *parentNode) {
    
    this->getBaseSprite()->removeFromParent();
    parentNode->addChild(this->getBaseSprite());
    
    return true;
}

bool ClashUnit::unbindFromParent() {
    
    this->getBaseSprite()->removeFromParent();
    return SFActor::unbindFromParent();
}

void ClashUnit::updatePosition(CCPoint pos,int zorder) {
    
    this->getBaseSprite()->setZOrder(zorder);
    this->getBaseSprite()->setPosition(ccp(pos.x,pos.y));
}

void ClashUnit::updateUnitType(int major, int minor) {

    this->m_nMajorUnitType = major;
    this->m_nMinorUnitType = minor;
}

void ClashUnit::setMasterUnit(ClashUnit *unit) {
    
    this->m_pMasterUnit = unit;
}

ClashUnit *ClashUnit::getMasterUnit() {
    
    return this->m_pMasterUnit;
}

int ClashUnit::getMajorUnitType() {
    
    return this->m_nMajorUnitType;
}

int ClashUnit::getMinorUnitType() {
    
    return this->m_nMinorUnitType;
}

void ClashUnit::setMoveInfo(unsigned int blockNumToMove,int moveDir) {
    
    this->m_nBlockNumToMove = blockNumToMove;
    this->m_nMoveDir = moveDir;
}

void ClashUnit::startMoving() {

    this->getSpriteByID(CLASHUNIT_SPRITE_UNIT)->stopAllActions();

    int nMoveNum;
    
    if(this->m_nBlockNumToMove <= 0)
        return;

    if(this->m_pMasterUnit != NULL) {
        nMoveNum = this->m_nBlockNumToMove-1;
    } else {
        nMoveNum = this->m_nBlockNumToMove;
    }
    
    CCPoint ptTargetOffset;
    if(this->m_nMoveDir == CLASHUNIT_DIR_LEFT)
        ptTargetOffset = ccp(-nMoveNum*(CLASHUNIT_SPRITE_WIDTH+CLASHBOARD_MARGIN_WIDTH*2),0);
    else if(this->m_nMoveDir == CLASHUNIT_DIR_RIGHT)
        ptTargetOffset = ccp(nMoveNum*(CLASHUNIT_SPRITE_WIDTH+CLASHBOARD_MARGIN_WIDTH*2),0);
    else if(this->m_nMoveDir == CLASHUNIT_DIR_TOP)
        ptTargetOffset = ccp(0,nMoveNum*(CLASHUNIT_SPRITE_HEIGHT+CLASHBOARD_MARGIN_HEIGHT*2));
    else
        ptTargetOffset = ccp(0,-nMoveNum*(CLASHUNIT_SPRITE_HEIGHT+CLASHBOARD_MARGIN_HEIGHT*2));
    
    this->doActionOfMoveBy(this->m_pBoard, CLASHUNIT_SPRITE_UNIT, ptTargetOffset, 0, CLASHUNIT_MOVESPEED*nMoveNum, true);
}

bool ClashUnit::buildUI() {
    
    CCSprite *sprite = MM_SRMGR->createSprite(MMFACTORYTYPE_SHOP, "shop_farmcrop_water.png", false);
    this->setBaseSprite(sprite,CLASHUNIT_SPRITE_UNIT);
    
    return true;
}

void ClashUnit::notifySlaveUnitReached(ClashUnit *slaveUnit) {
    
    if(this->getMajorUnitType() == MAJOR_UNITTYPE_MYUNIT) {
        
    } else if(this->getMajorUnitType() == MAJOR_UNITTYPE_ENERMY) {
        
    } else if(this->getMajorUnitType() == MAJOR_UNITTYPE_RESOURCE) {
        
    }
    //int unitLevel = slaveUnit->getMinorUnitType();
}

void ClashUnit::notifyMergeComplete(ClashUnit *slaveUnit) {
    
}
