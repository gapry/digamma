#pragma once

#include <sc2api/sc2_api.h>

namespace TutorialApp
{
    class Bot : public sc2::Agent
    {
    public:
		virtual void OnGameFullStart() final;
        virtual void OnGameStart() final;
		virtual void OnGameEnd() final;
        virtual void OnStep() final;
		virtual void OnUnitDestroyed(const sc2::Unit&) final;
		virtual void OnUnitCreated(const sc2::Unit&) final;
		virtual void OnUnitIdle(const sc2::Unit&) final;
		virtual void OnUpgradeCompleted(sc2::UpgradeID) final;
		virtual void OnBuildingConstructionComplete(const sc2::Unit&) final;
		virtual void OnNydusDetected() final;
		virtual void OnNuclearLaunchDetected() final;
		virtual void OnUnitEnterVision(const sc2::Unit&) final;
		virtual void OnError(const std::vector<sc2::ClientError>& client_errors, const std::vector<std::string>& protocol_errors = {}) final;

        Bot(int eo = 0);
        ~Bot();
	private:
		inline void dbgEventOrder(std::string);
		int eventOrder;
    };
};
