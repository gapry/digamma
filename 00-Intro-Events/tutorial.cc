#include <iostream>
#include <sc2api/sc2_api.h>

#include "TutorialApp.hpp"

int main(int argc, char* argv[]) 
{
    sc2::Coordinator* coordinator = new sc2::Coordinator();
    coordinator->LoadSettings(argc, argv);

    TutorialApp::Bot* bot = new TutorialApp::Bot();
    coordinator->SetParticipants({
        sc2::CreateParticipant(sc2::Race::Terran, bot),
        sc2::CreateComputer(sc2::Race::Zerg)
    });

    coordinator->LaunchStarcraft();

    const char* fetchMap = sc2::kMapBelShirVestigeLE;
    coordinator->StartGame(fetchMap);
    
    while (coordinator->Update()) {
    }

    delete bot;
    delete coordinator;
   
    return 0;
}