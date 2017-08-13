#include <iostream>
#include "TutorialApp.hpp"

void TutorialApp::Bot::OnGameStart() {}

void TutorialApp::Bot::OnStep()
{
    if (this->TryBuildSupplyDepot()) return;
    if (this->TryBuildBarracks()) return;
    if (this->BuildRefinery()) return;
}

void TutorialApp::Bot::OnUnitIdle(const sc2::Unit& unit)
{
    switch (unit.unit_type.ToType()) {
    case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER: {
        Actions()->UnitCommand(unit, sc2::ABILITY_ID::TRAIN_SCV);
        break;
    }

    case sc2::UNIT_TYPEID::TERRAN_SCV: {
        uint64_t mineral_target;
        if (!this->FindNearestMineralPatch(unit.pos, mineral_target)) break;
        Actions()->UnitCommand(unit, sc2::ABILITY_ID::SMART, mineral_target);

        break;
    }

    case sc2::UNIT_TYPEID::TERRAN_BARRACKS: {
        Actions()->UnitCommand(unit, sc2::ABILITY_ID::TRAIN_MARINE);
        Actions()->UnitCommand(unit, sc2::ABILITY_ID::TRAIN_REAPER);
        break;
    }

    case sc2::UNIT_TYPEID::TERRAN_MARINE: {
        const sc2::ObservationInterface* observation = Observation();
        const sc2::GameInfo& game_info = Observation()->GetGameInfo();

        if (CountUnitType(observation, sc2::UNIT_TYPEID::TERRAN_MARINE) >= 15) {
            Actions()->UnitCommand(unit, sc2::ABILITY_ID::ATTACK_ATTACK, game_info.enemy_start_locations.front());
        }

        break;
    }

    default: break;
    }
}

bool TutorialApp::Bot::TryBuildGas(sc2::AbilityID build_ability, sc2::UnitTypeID worker_type, sc2::Point2D base_location)
{
    const sc2::ObservationInterface* observation = Observation();
    sc2::Units geysers = observation->GetUnits(sc2::Unit::Alliance::Neutral, IsVespeneGeyser());

    float minimum_distance = 15.0f;
    sc2::Tag closestGeyster = 0;
    for (const auto& geyser : geysers) {
        float current_distance = sc2::Distance2D(base_location, geyser.pos);
        if (current_distance < minimum_distance) {
            if (Query()->Placement(build_ability, geyser.pos)) {
                minimum_distance = current_distance;
                closestGeyster = geyser.tag;
            }
        }
    }

    if (0 == closestGeyster) return false;

    return this->TryBuildStructure(build_ability, worker_type, closestGeyster);
}

bool TutorialApp::Bot::BuildRefinery()
{
    const sc2::ObservationInterface* observation = Observation();
    sc2::Units bases = observation->GetUnits(sc2::Unit::Alliance::Self, IsTownHall());

    if (CountUnitType(observation, sc2::UNIT_TYPEID::TERRAN_REFINERY) >= observation->GetUnits(sc2::Unit::Alliance::Self, IsTownHall()).size() * 2) {
        return false;
    }

    for (const auto& base : bases) {
        if (base.assigned_harvesters >= base.ideal_harvesters) {
            if (1 == base.build_progress) {
                if (TryBuildGas(sc2::ABILITY_ID::BUILD_REFINERY, sc2::UNIT_TYPEID::TERRAN_SCV, base.pos)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool TutorialApp::Bot::TryBuildBarracks()
{
    const sc2::ObservationInterface* observation = Observation();

    if (this->CountUnitType(sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT) < 1) {
        return false;
    }

    if (this->CountUnitType(sc2::UNIT_TYPEID::TERRAN_BARRACKS) > 7) {
        return false;
    }

    return this->TryBuildStructure(sc2::ABILITY_ID::BUILD_BARRACKS);
}

bool TutorialApp::Bot::TryBuildSupplyDepot()
{
    const sc2::ObservationInterface* observation = Observation();

    if (observation->GetFoodUsed() <= observation->GetFoodCap() - 7) return false;

    return TryBuildStructure(sc2::ABILITY_ID::BUILD_SUPPLYDEPOT);
}

bool TutorialApp::Bot::TryBuildStructure(sc2::AbilityID ability_type_for_structure, sc2::UnitTypeID unit_type, sc2::Tag location_tag)
{
    const sc2::ObservationInterface* observation = Observation();
    sc2::Units workers = observation->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(unit_type));
    const sc2::Unit* target = observation->GetUnit(location_tag);

    if (workers.empty()) return false;

    for (const auto& worker : workers) {
        for (const auto& order : worker.orders) {
            if (order.ability_id == ability_type_for_structure) return false;
        }
    }

    const sc2::Unit& unit = sc2::GetRandomEntry(workers);

    if (Query()->Placement(ability_type_for_structure, target->pos)) {
        Actions()->UnitCommand(unit.tag, ability_type_for_structure, location_tag);
        return true;
    }

    return false;
}

bool TutorialApp::Bot::TryBuildStructure(sc2::ABILITY_ID ability_type_for_structure, sc2::UNIT_TYPEID unit_type)
{
    const sc2::ObservationInterface* observation = Observation();

    sc2::Unit unit_to_build;
    sc2::Units units = observation->GetUnits(sc2::Unit::Alliance::Self);
    for (const auto& unit : units) {
        for (const auto& order : unit.orders) {
            if (order.ability_id == ability_type_for_structure) {
                return false;
            }
        }

        if (unit.unit_type == unit_type) unit_to_build = unit;
    }

    float rx = sc2::GetRandomScalar();
    float ry = sc2::GetRandomScalar();

    Actions()->UnitCommand(
        unit_to_build,
        ability_type_for_structure,
        sc2::Point2D(unit_to_build.pos.x + rx * 20.0f, unit_to_build.pos.y + ry * 20.0f)
    );

    return true;
}

bool TutorialApp::Bot::FindNearestMineralPatch(const sc2::Point2D& start, uint64_t& target)
{
    sc2::Units units = Observation()->GetUnits(sc2::Unit::Alliance::Neutral);
    float distance = std::numeric_limits<float>::max();
    for (const auto& u : units) {
        if (u.unit_type == sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD) {
            float d = sc2::DistanceSquared2D(u.pos, start);
            if (d < distance) {
                distance = d;
                target = u.tag;
            }
        }
    }

    if (distance == std::numeric_limits<float>::max()) return false;

    return true;
}

size_t TutorialApp::Bot::CountUnitType(const sc2::ObservationInterface* observation, sc2::UnitTypeID unit_type)
{
    return observation->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(unit_type)).size();
}

size_t TutorialApp::Bot::CountUnitType(sc2::UNIT_TYPEID unit_type)
{
    return Observation()->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(unit_type)).size();
}

bool TutorialApp::IsTownHall::operator()(const sc2::Unit& unit)
{
    switch (unit.unit_type.ToType()) {
    case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER: return true;
    case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return true;
    case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
    case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
    default: return false;
    }
}

bool TutorialApp::IsVespeneGeyser::operator()(const sc2::Unit& unit)
{
    switch (unit.unit_type.ToType()) {
    case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
    case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
    case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
    default: return false;
    }
}

TutorialApp::Bot::Bot() {}

TutorialApp::Bot::~Bot() {}