#pragma once
#include <CheatCompile.h>

#include <Surface.h>

using namespace Microsoft::WRL;

class Sprite
{


public:
    // Sprite flags
    enum
    {
        FLARE = (1 << 0),
        OPFLARE = (1 << 1),
        FLASH = (1 << 4),
        DISABLED = (1 << 6),
        GMUL = (1 << 7),
        BLACKFLARE = (1 << 8),
        BRIGHTEST = (1 << 9),
        RFLARE = (1 << 12),
        GFLARE = (1 << 13),
        NOCLIP = (1 << 14)
    };

    // Structors
    //the sprite animation will be hard to reprogram but i am sure thigns will.......
    Sprite();
    Sprite(Surface* a_Surface, unsigned int a_NumFrames);
    Sprite(std::wstring& filePath, unsigned int a_NumFrames, ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory);
    ~Sprite();
    // Methods
    //the surface is the screen

    //the draw call will be replaced and done in the render method
    //void draw(Surface* a_Target, int a_X, int a_Y);
    void drawMK2(int a_X, int a_Y);
    void set_Image(ID2D1Bitmap d2dBitmap);
    void draw_scaled(int a_X, int a_Y, int a_Width, int a_Height, Surface* a_Target);
    void set_flags(unsigned int a_Flags) { m_Flags = a_Flags; }
    void set_frame(unsigned int a_Index) { m_CurrentFrame = a_Index; }
    unsigned int get_flags() const { return m_Flags; }
    int get_width() { return m_Width; }
    int get_height() { return m_Height; }
    //pixel gone
    //Pixel* get_buffer() { return m_Surface->get_buffer(); }
    unsigned int frames() { return m_NumFrames; }
    Surface* get_surface() { return m_Surface; }
    ComPtr<ID2D1Bitmap> d2dBitmap;
    //std::vector<ComPtr<ID2D1Bitmap>> animation_cells;
    unsigned int m_CurrentFrame;
    void initialize_start_data();
    void animationLooper();

private:
    // Attributes
    //std::vector<ID2D1Bitmap*> animation_cells;
    int m_Width, m_Height, m_Pitch;
    unsigned int m_NumFrames;
    //unsigned int m_CurrentFrame;
    unsigned int m_Flags;
    unsigned int** m_Start;
    Surface* m_Surface;

    void LoadFrames(ID2D1Bitmap& file, unsigned int a_NumFrames, ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory);
    //ComPtr<ID2D1Bitmap> d2dBitmap;

};

