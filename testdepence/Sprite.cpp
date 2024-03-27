#include "pch.h"
#include "Sprite.h"


#include <BitmapDrawer.h>

//using namespace mintest333;
//using namespace Microsoft::WRL;


Sprite::Sprite() {


}
Sprite::Sprite(Surface* a_Surface, unsigned int a_NumFrames) {


}
//use the filepath to directly load this file,
//us numframes for cell animation
Sprite::Sprite(std::wstring& filePath, unsigned int a_NumFrames, ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory) {

	testdependence::BitmapDrawer bitDrawer(d2dContext, wicFactory);
	d2dBitmap = bitDrawer.ReadAndSaveBitmap(filePath);
	//test size
	auto test = d2dBitmap->GetSize();
	int stop = 0;

	if (a_NumFrames > 2) {
		m_Width = 7;
		m_Height = 9;
		m_Pitch = 84;
		m_NumFrames = 12;
	}

	//if (a_NumFrames > 2) {
	//	LoadFrames(*d2dBitmap.Get(), a_NumFrames, d2dContext, wicFactory);
	//}
	//m_NumFrames = a_NumFrames;
	//todo based on frames make cell animation
}

void Sprite::Sprite::LoadFrames(ID2D1Bitmap& file, unsigned int a_NumFrames, ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory) {

	auto bitmapSize = file.GetSize();
	auto cellWidth = bitmapSize.width / a_NumFrames;

	auto cellHeight = bitmapSize.height;


	for (unsigned int i = 0; i < a_NumFrames; i++) {
		//Chat gpt was used for refactoring
		auto cellRect = D2D1::RectU(i * cellWidth, 0, (i + 1) * cellWidth, cellHeight);
		ComPtr<ID2D1Bitmap> cellBitmap;
		d2dContext->CreateBitmap(D2D1::SizeU(cellWidth, cellHeight), nullptr, 0, D2D1::BitmapProperties(d2dBitmap->GetPixelFormat()), &cellBitmap);
		cellBitmap->CopyFromBitmap(nullptr, d2dBitmap.Get(), &cellRect);
		//animation_cells.push_back(cellBitmap.Get());
	}

}

void Sprite::animationLooper() {
	m_CurrentFrame++;
	if (m_CurrentFrame >= m_NumFrames) {
		m_CurrentFrame = 0;
	}

}

//void set_Image(ID2D1Bitmap d2dBitmap);
Sprite::~Sprite() {

}

void Sprite::drawMK2(int a_X, int a_Y) {

}