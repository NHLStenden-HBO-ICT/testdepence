#pragma once
#include <pch.h>
#include <string>
#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"
#include <wincodec.h>
#include <Common/DirectXHelper.h>
using namespace Microsoft::WRL;

namespace testdependence {



    class BitmapDrawer
    {
    public:
        BitmapDrawer(ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory)
            : m_d2dContext(d2dContext), m_wicFactory(wicFactory)
        {
        }
        void DrawBitmap(ComPtr<ID2D1Bitmap> bitmap, const D2D1_RECT_F& destinationRect)
        {
            //ComPtr<IWICBitmapDecoder> decoder;
            //DX::ThrowIfFailed(m_wicFactory->CreateDecoderFromFilename(
            //    filePath.c_str(),
            //    nullptr,
            //    GENERIC_READ,
            //    WICDecodeMetadataCacheOnDemand,
            //    decoder.GetAddressOf()));

            //ComPtr<IWICBitmapFrameDecode> frame;
            //DX::ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

            //ComPtr<IWICFormatConverter> formatConverter;
            //DX::ThrowIfFailed(m_wicFactory->CreateFormatConverter(formatConverter.GetAddressOf()));

            //DX::ThrowIfFailed(formatConverter->Initialize(
            //    frame.Get(),
            //    GUID_WICPixelFormat32bppPBGRA,
            //    WICBitmapDitherTypeNone,
            //    nullptr,
            //    0.f,
            //    WICBitmapPaletteTypeMedianCut));

            //ComPtr<ID2D1Bitmap> d2dBitmap;
            //DX::ThrowIfFailed(m_d2dContext->CreateBitmapFromWicBitmap(
            //    formatConverter.Get(),
            //    d2dBitmap.GetAddressOf()));

            m_d2dContext->DrawBitmap(bitmap.Get(), destinationRect);
        }
        void DrawBitmap(const std::wstring& filePath, const D2D1_RECT_F& destinationRect)
        {
            ComPtr<IWICBitmapDecoder> decoder;
            DX::ThrowIfFailed(m_wicFactory->CreateDecoderFromFilename(
                filePath.c_str(),
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnDemand,
                decoder.GetAddressOf()));

            ComPtr<IWICBitmapFrameDecode> frame;
            DX::ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

            ComPtr<IWICFormatConverter> formatConverter;
            DX::ThrowIfFailed(m_wicFactory->CreateFormatConverter(formatConverter.GetAddressOf()));

            DX::ThrowIfFailed(formatConverter->Initialize(
                frame.Get(),
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.f,
                WICBitmapPaletteTypeMedianCut));

            ComPtr<ID2D1Bitmap> d2dBitmap;
            DX::ThrowIfFailed(m_d2dContext->CreateBitmapFromWicBitmap(
                formatConverter.Get(),
                d2dBitmap.GetAddressOf()));

            m_d2dContext->DrawBitmap(d2dBitmap.Get(), destinationRect);
        }
        ComPtr<ID2D1Bitmap> ReadAndSaveBitmap(std::wstring& filePath)
        {
            ComPtr<IWICBitmapDecoder> decoder;
            DX::ThrowIfFailed(m_wicFactory->CreateDecoderFromFilename(
                filePath.c_str(),
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnDemand,
                decoder.GetAddressOf()));

            ComPtr<IWICBitmapFrameDecode> frame;
            DX::ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

            ComPtr<IWICFormatConverter> formatConverter;
            DX::ThrowIfFailed(m_wicFactory->CreateFormatConverter(formatConverter.GetAddressOf()));

            DX::ThrowIfFailed(formatConverter->Initialize(
                frame.Get(),
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.f,
                WICBitmapPaletteTypeMedianCut));

            ComPtr<ID2D1Bitmap> d2dBitmap;
            DX::ThrowIfFailed(m_d2dContext->CreateBitmapFromWicBitmap(
                formatConverter.Get(),
                d2dBitmap.GetAddressOf()));
            //D2D1_RECT_F rec = d2dBitmap.Get();
                //return d2dBitmap.Get();
            //m_d2dContext->DrawBitmap(d2dBitmap.Get(), destinationRect);
            //return d2dBitmap;
            return d2dBitmap;
        }

    private:
        Microsoft::WRL::ComPtr<ID2D1DeviceContext2> m_d2dContext;
        Microsoft::WRL::ComPtr<IWICImagingFactory2> m_wicFactory;
    };
}