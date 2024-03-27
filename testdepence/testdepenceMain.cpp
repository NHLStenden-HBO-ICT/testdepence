#include "pch.h"
#include "testdepenceMain.h"
#include "Common\DirectXHelper.h"
#include <BitmapDrawer.h>
#include <AssetPathN.h>
#include <TerrainM.h>
#include <PathFinder.h>


using namespace testdependence;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

static std::unique_ptr<Sprite> Red_Tank_Sprite;
static std::unique_ptr<Sprite> Blue_Tank_Sprite;
static std::unique_ptr<Sprite> BetterTank;
static std::unique_ptr<Sprite> SuperTank;
static std::unique_ptr<Sprite> rocketSprite;

std::wstring Better_TankFilePath = std::wstring(L"assets/bigtank.png");
std::wstring Blue_TankFilePath = std::wstring(L"assets/Tank_Blue_Proj2.png");
std::wstring Red_TankFilePath = std::wstring(L"assets/RotatedBigtankRed.png");
std::wstring Super_TankFilePath = std::wstring(L"assets/better.png");
std::wstring SuperRocketPath = std::wstring(L"assets.missle.tga");


// Loads and initializes application assets when the application is loaded.
testdepenceMain::testdepenceMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: Replace this with your app's content initialization.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(m_deviceResources));

	m_fpsTextRenderer = std::unique_ptr<SampleFpsTextRenderer>(new SampleFpsTextRenderer(m_deviceResources));

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	//Make blue Tank sprite
	Blue_Tank_Sprite = std::make_unique<Sprite>(Blue_TankFilePath, 12, m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	//std::make_unique<Sprite>(Blue_TankFilePath, 1, m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	//Make red tank sprite
	Red_Tank_Sprite = std::make_unique<Sprite>(Red_TankFilePath, 12, m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	BetterTank = std::make_unique<Sprite>(Better_TankFilePath, 12, m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	SuperTank = std::make_unique<Sprite>(Super_TankFilePath, 12, m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	//number to round down
	CreateTanks();
}

testdepenceMain::~testdepenceMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void testdepenceMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}
//stack size is too big
void testdepenceMain::CreateTanks() {

	//create the object for the tank collection
	tankholder = TankCollection(vec2(7, 9));
	tankholder.Init(vec2(17, 19), 3, 1000, 1, *BetterTank, *Red_Tank_Sprite, Sprite());
	tankholder.CreateCustomTank(vec2(30, 25), 3, 1000, 1, *BetterTank, Sprite(), vec2(30, 30));
	tankholder.CreateCustomTank(vec2(100, 100),30, 100, 1, *SuperTank, Sprite(), vec2(50, 50));
	tankholder.CreateCustomTank(vec2(30, 25), 3, 1000, 1, *BetterTank, Sprite(), vec2(15, 15));
	//reduce the stack size
	mappa = TerrainM(m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());

	MakePaden();
};
//create and calculate paths for both lists
void testdepenceMain::MakePaden() {
	PathFinder pad = PathFinder(mappa);
	//pak de paden
	std::vector<std::reference_wrapper<Tank>> t(tankholder.bluetanks.begin(), tankholder.bluetanks.end());
	//pad.getPath(t);
	pad.getPath(tankholder.bluetanks);
	pad.getPath(tankholder.redTanks);

}
//create and calculate paths for both lists
void testdepenceMain::MakePaden(TerrainM wMap) {
	PathFinder pad = PathFinder(wMap);
	//pak de paden
	pad.getPath(tankholder.bluetanks);
	pad.getPath(tankholder.redTanks);

}


// Updates the application state once per frame.
void testdepenceMain::Update() 
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		m_sceneRenderer->Update(m_timer);
		m_fpsTextRenderer->Update(m_timer);
		tankholder.TankTicks();
	});
}
/*
// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool testdepenceMain::Render() 
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_sceneRenderer->Render();
	m_fpsTextRenderer->Render();

	return true;
}
*/
// Notifies renderers that device resources need to be released.
void testdepenceMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void testdepenceMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

bool testdepenceMain::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		//mappa2 = TerrainM(m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();
	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView* const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_sceneRenderer->Render();
	m_fpsTextRenderer->Render();
	//ID2D1DeviceContext m_d2dContext = m_deviceResources->GetD2DDeviceContext();
	// Clear the render target.
	m_deviceResources->GetD2DDeviceContext()->BeginDraw();
	//m_deviceResources->GetD2DDeviceContext()->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
	BitmapDrawer m_bitmapDrawer = BitmapDrawer(m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());

	std::wstring folderName = AssetPath().GetAssetsFolderPath();
	int stopper = 10;
	//auto padName = folderName + "ball.png";

	//std::wstring padName = folderName + L"\\256.jpg";
	// Draw the bitmap.
	//m_bitmapDrawer.DrawBitmap(padName, D2D1::RectF(0.f, 0.f, 100.f, 100.f));

	//TerrainM mappa = TerrainM(m_deviceResources->GetD2DDeviceContext(), m_deviceResources->GetWicImagingFactory());
	const int rows = mappa.tiles.size();
	const int cols = mappa.tiles.at(0).size(); // Assuming all rows have the same number of columns
	const float spriteSize = mappa.sprite_size;
	const float gridWidth = cols * spriteSize;
	const float gridHeight = rows * spriteSize;

	//m_bitmapDrawer.DrawBitmap(mappa.tile_mountains2->d2dBitmap, D2D1::RectF(500, 500, 500 + spriteSize, 500 + spriteSize));

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			// Calculate the top-left position of the sprite in the grid
			//this is the 1 to alot conversion
			float left = col * spriteSize;
			float top = row * spriteSize;
			//crash below
			m_bitmapDrawer.DrawBitmap(mappa.tiles.at(row).at(col).Pic->d2dBitmap, D2D1::RectF(left, top, left + spriteSize, top + spriteSize));
		}
	}
	Rendertanks(m_bitmapDrawer);
	m_deviceResources->GetD2DDeviceContext()->EndDraw();

	// Present the swap chain.
	//DX::ThrowIfFailed(m_swapChain->Present(1, 0));

	return true;
}


void testdepenceMain::Rendertanks(BitmapDrawer& m_drawer) {

	//m_Drawer.DrawBitmap(mappa.tiles.at(row).at(col).Pic->d2dBitmap, D2D1::RectF(left, top, left + spriteSize, top + spriteSize));


	for (Tank& tank : tankholder.redTanks) {
		//m_drawer.DrawBitmap(tank.tank_sprite->d2dBitmap, D2D1::RectF(tank.position.x, tank.position.y, tank.position.x + 7, tank.position.y + 9));
		m_drawer.DrawBitmap(tank.tank_sprite->d2dBitmap, D2D1::RectF(tank.position.x, tank.position.y, tank.position.x + tank.size.x, tank.position.y + tank.size.y));

	}
	for (Tank& tank : tankholder.bluetanks) {
		m_drawer.DrawBitmap(tank.tank_sprite->d2dBitmap, D2D1::RectF(tank.position.x, tank.position.y, tank.position.x + tank.size.x, tank.position.y + tank.size.y));
	}

}

