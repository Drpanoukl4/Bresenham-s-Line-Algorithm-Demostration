#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "BRESENHAMS";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::BLUE);

		Bresenhams(0, 0, 20, 40);

		return true;
	}

	void Bresenhams (int x0, int y0, int x1, int y1) 
	{

		float slope = float(y1 - y0) / float(x1 - x0);

		for(int x = x0; x <= x1; x++) {

			float y = slope * (x - x0) + y0;

			Draw( x, y );

		}

	}

};


int main()
{
	Example demo;
	if (demo.Construct(166, 140, 4, 4))
		demo.Start();

	return 0;
}
