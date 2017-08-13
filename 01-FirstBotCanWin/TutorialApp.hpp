#pragma once

#include <sc2api/sc2_api.h>

namespace TutorialApp
{
	class Bot : public sc2::Agent
	{
	public:
		virtual void OnGameStart() final;
		virtual void OnStep() final;
		virtual void OnUnitIdle(const sc2::Unit& unit) final;

		Bot();
		~Bot();

	private:
		bool TryBuildStructure(sc2::ABILITY_ID, sc2::UNIT_TYPEID unit_type = sc2::UNIT_TYPEID::TERRAN_SCV);
		bool TryBuildStructure(sc2::AbilityID, sc2::UnitTypeID, sc2::Tag);
		bool FindNearestMineralPatch(const sc2::Point2D& start, uint64_t& target);
		size_t CountUnitType(sc2::UNIT_TYPEID unit_type);
		size_t CountUnitType(const sc2::ObservationInterface*, sc2::UnitTypeID);

		bool TryBuildGas(sc2::AbilityID, sc2::UnitTypeID, sc2::Point2D);
		bool BuildRefinery();
		bool TryBuildBarracks();
		bool TryBuildSupplyDepot();
	};

	struct IsVespeneGeyser
	{
		bool operator()(const sc2::Unit& unit);
	};

	struct IsTownHall
	{
		bool operator()(const sc2::Unit& unit);
	};
};
