#pragma once
class Surface
{


    enum
    {
        OWNER = 1
    };

public:
    // constructor / destructor
    //wist je dat het nu 2 uur snachts is 
    //ik had gewoon meoten gaymeeeen!!
    //alles met pixel mag weg
    //Surface(int a_Width, int a_Height, int a_Pitch);
    Surface(int a_Width, int a_Height);
    //this one is for images
    Surface(const char* a_File);
    ~Surface();
    // member data access
    //Pixel* get_buffer() { return m_Buffer; }
    //void set_buffer(Pixel* a_Buffer) { m_Buffer = a_Buffer; }
    int get_width() { return m_Width; }
    int get_height() { return m_Height; }
    int get_pitch() { return m_Pitch; }
    void set_pitch(int a_Pitch) { m_Pitch = a_Pitch; }
    // Special operations
    void init_charset();
    void set_char(int c, const char* c1, const char* c2, const char* c3, const char* c4, const char* c5);
    //void centre(const char* a_String, int y1, Pixel color);
    //void print(const char* a_String, int x1, int y1, Pixel color);
    //void clear(Pixel a_Color);
    //void line(float x1, float y1, float x2, float y2, Pixel color);
    //void line(vec2 start, vec2 end, Pixel color);
    //void plot(int x, int y, Pixel c);
    void load_image(const char* a_File);
    void copy_to(Surface* a_Dst, int a_X, int a_Y);
    void blend_copy_to(Surface* a_Dst, int a_X, int a_Y);
    void scale_color(unsigned int a_Scale);
    //de boxes zijn niet meer relevant
    //void box(int x1, int y1, int x2, int y2, Pixel color);
    //void bar(int x1, int y1, int x2, int y2, Pixel color);
    void resize(Surface* a_Orig);

private:
    // Attributes
    //Pixel* m_Buffer;
    int m_Width, m_Height;
    int m_Pitch;
    //int m_Flags;
    // Static attributes for the builtin font
    static char s_Font[51][5][6];
    static bool fontInitialized;
    //int s_Transl[256];

};

