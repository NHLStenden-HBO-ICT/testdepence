#include "pch.h"
#include "Surface.h"

void NotifyUser(const char* s);
char Surface::s_Font[51][5][6];
bool Surface::fontInitialized = false;

// -----------------------------------------------------------
// True-color surface class implementation
// -----------------------------------------------------------

Surface::Surface(int a_Width, int a_Height) : m_Width(a_Width),
m_Height(a_Height),
m_Pitch(a_Width)
{
}

Surface::Surface(const char* a_File) {
	//a_file is the path
	//tijdelijke fix
	m_Width = 0;
	m_Height = 0;
	m_Pitch = 0;
}
//empty destructor
Surface::~Surface() {

}