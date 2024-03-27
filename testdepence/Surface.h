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

