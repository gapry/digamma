#include <sc2api/sc2_api.h>
#include <agent/agent.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
  sc2::Coordinator* coordinator = new sc2::Coordinator();
  coordinator->LoadSettings(argc, argv);
  coordinator->SetRealtime(false);
  coordinator->SetWindowLocation(400, 200);

  Digamma::agent* bot = new Digamma::agent();
  coordinator->SetParticipants({
    sc2::CreateParticipant(sc2::Race::Terran, bot), //
    sc2::CreateComputer(sc2::Race::Terran,          //
                        sc2::Difficulty::Easy)      //
  });                                               //

  coordinator->LaunchStarcraft();
  coordinator->StartGame(argv[1]);

  while (coordinator->Update()) {
  }

  delete bot;
  delete coordinator;
  return 0;
}