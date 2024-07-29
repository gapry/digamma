#include <agent/agent.hpp>
#include <log/log.hpp>
#include <iostream>

void Digamma::agent::OnGameStart() {
  log_info(__FUNCSIG__);
}

void Digamma::agent::OnStep() {
  log_info(__FUNCSIG__);
}

void Digamma::agent::OnUnitIdle(const sc2::Unit& unit) {
}

bool Digamma::agent::TryBuildGas(sc2::AbilityID  build_ability,
                                 sc2::UnitTypeID worker_type,
                                 sc2::Point2D    base_location) {
  return false;
}

bool Digamma::agent::BuildRefinery() {
  return false;
}

bool Digamma::agent::TryBuildBarracks() {
  return false;
}

bool Digamma::agent::TryBuildSupplyDepot() {
  return false;
}

bool Digamma::agent::TryBuildStructure(sc2::AbilityID  ability_type_for_structure,
                                       sc2::UnitTypeID unit_type,
                                       sc2::Tag        location_tag) {
  return false;
}

bool Digamma::agent::TryBuildStructure(sc2::ABILITY_ID ability_type_for_structure, sc2::UNIT_TYPEID unit_type) {
  return true;
}

bool Digamma::agent::FindNearestMineralPatch(const sc2::Point2D& start, uint64_t& target) {
  return true;
}

size_t Digamma::agent::CountUnitType(const sc2::ObservationInterface* observation, sc2::UnitTypeID unit_type) {
  return 0;
}

size_t Digamma::agent::CountUnitType(sc2::UNIT_TYPEID unit_type) {
  return 0;
}

bool Digamma::IsTownHall::operator()(const sc2::Unit& unit) {
  switch (unit.unit_type.ToType()) {
    case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER: return true;
    case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return true;
    case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
    case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
    default: return false;
  }
}

bool Digamma::IsVespeneGeyser::operator()(const sc2::Unit& unit) {
  switch (unit.unit_type.ToType()) {
    case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
    case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
    case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
    default: return false;
  }
}

Digamma::agent::agent() {
}

Digamma::agent::~agent() {
}