#include <iostream>
#include <sc2api/sc2_api.h>

#include "TutorialApp.hpp"

int main(int argc, char* argv[])
{
    sc2::Coordinator* coordinator = new sc2::Coordinator();
    coordinator->LoadSettings(argc, argv);
    coordinator->SetRealtime(false);
    coordinator->SetWindowLocation(400, 200);

    TutorialApp::Bot* bot = new TutorialApp::Bot();
    coordinator->SetParticipants({
        sc2::CreateParticipant(sc2::Race::Terran, bot),
        sc2::CreateComputer(sc2::Race::Terran, sc2::Difficulty::Easy)
    });

    coordinator->LaunchStarcraft();
    coordinator->StartGame(sc2::kMapBelShirVestigeLE);

    while (coordinator->Update()) {
    }

    delete bot;
    delete coordinator;

    return 0;
}