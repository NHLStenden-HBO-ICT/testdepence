#pragma once
#include "TerrainM.h"
#include "BitmapDrawer.h"
#include "TankCollection.h"
#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include <Content/SampleFpsTextRenderer.h>
#include <Content/Sample3DSceneRenderer.h>

// Renders Direct2D and 3D content on the screen.
namespace testdependence
{
	class testdepenceMain : public DX::IDeviceNotify
	{
	public:
		testdepenceMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~testdepenceMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();
		void CreateTanks();
		void MakePaden();
		void MakePaden(TerrainM wMap);
		void Rendertanks(BitmapDrawer& m_Drawer);

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();


		TerrainM mappa;

		TankCollection tankholder;

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}