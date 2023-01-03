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

		//Removing Floats
		//if we compare -0.5f with 0 is lithe bit faster than 0 with 0.5f
		//them going to erase floats
		//slope and errors are float we are going to convert it to integers

		int y = y0;

		int dx = x1 - x0;
		int dy = y1 - y0;
		float slope = 2 * dy;

		float error = -dx;
		float errorInc = -2 * dx;

		for(int x = x0; x <= x1; x++) {

			Draw( x, y );
			error += slope;

			if(error >= 0.0f) 
			{

				y ++;
				error += errorInc;

			}

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
