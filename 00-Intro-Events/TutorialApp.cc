#include <iostream>
#include "TutorialApp.hpp"

void TutorialApp::Bot::OnGameFullStart()
{
    this->dbgEventOrder("OnGameFullStart");
}

void TutorialApp::Bot::OnGameStart()
{
    this->dbgEventOrder("OnGameStart");
}

void TutorialApp::Bot::OnGameEnd()
{
    this->dbgEventOrder("OnGameEnd");
}

void TutorialApp::Bot::OnStep()
{
    //this->dbgEventOrder("Onstep");
    /*
	std::cout << Observation()->GetGameLoop() << std::endl;
    std::cout << "[dbg]: minerals: " << Observation()->GetMinerals() << std::endl;
    std::cout << "[dbg]: vespene: " << Observation()->GetVespene() << std::endl;
    */
}

void TutorialApp::Bot::OnUnitDestroyed(const sc2::Unit& unit)
{
    this->dbgEventOrder("OnUnitDestroyed");
}

void TutorialApp::Bot::OnUnitCreated(const sc2::Unit& unit)
{
    this->dbgEventOrder("OnUnitCreated");
    
    std::cout << "[dbg] diplay_type: " << unit.display_type << std::endl;
    std::cout << "[dbg] alliance: " << unit.alliance << std::endl;
    std::cout << "[dbg] cloaked: " << unit.Cloaked << std::endl;
    std::cout << "[dbg] tag: " << unit.tag << std::endl;    
}

void TutorialApp::Bot::OnUnitIdle(const sc2::Unit& unit)
{
    this->dbgEventOrder("OnUnitIdle");
}

void TutorialApp::Bot::OnUpgradeCompleted(sc2::UpgradeID upgrade)
{
    this->dbgEventOrder("OnUpgradeCompleted");
}

void TutorialApp::Bot::OnBuildingConstructionComplete(const sc2::Unit& unit)
{
    this->dbgEventOrder("OnBuildingConstructionComplete");
}

void TutorialApp::Bot::OnNydusDetected()
{
    this->dbgEventOrder("OnNydusDetected");
}

void TutorialApp::Bot::OnNuclearLaunchDetected()
{
    this->dbgEventOrder("OnNuclearLaunchDetected");
}

void TutorialApp::Bot::OnUnitEnterVision(const sc2::Unit& unit)
{
    this->dbgEventOrder("OnUnitEnterVision");
}

void TutorialApp::Bot::OnError(const std::vector<sc2::ClientError>& client_errors, const std::vector<std::string>& protocol_errors)
{
    this->dbgEventOrder("OnError");
}

inline void TutorialApp::Bot::dbgEventOrder(std::string eventName)
{
    std::cout << "[dbg] Invoke " << eventName <<" Event" << std::endl;
    std::cout << "[dbg] eventOder: " << this->eventOrder++ << std::endl;
}

TutorialApp::Bot::Bot(int eo): eventOrder(eo)
{
    std::cout << "[dbg] Inoke Bot Constructor" << std::endl;
}

TutorialApp::Bot::~Bot()
{
	std::cout << "[dbg]: Inoke Bot Destructor" << std::endl;
}