#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//ERROR
//#define ABS(_x) ((_x) >= 0 ? : -( _x ))
//#define SGN(_x) ((_x) > 0 ?  -1 : \
				((_x) > 0 ?  1 : 0))

#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))

#define SGN(_x) ((_x) < 0 ? -1 : \
		                 ((_x) > 0 ? 1 : 0))

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "BRESENHAMS";
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

		int incX = SGN(dx);
		int incY = SGN(dy);

		float slope = 2 * ABS(dy);

		float error = -ABS(dx);
		float errorInc = -2 * ABS(dx);

		for(int x = x0; x != x1 + incX; x += incX) {

			Draw( x, y );
			error += slope;

			if(error >= 0.0f) 
			{

				y += incY;
				error += errorInc;

			}

		}

		DrawString(5, 95, "Line From " + std::to_string(x0) + " ," + std::to_string(y0) + " To " + std::to_string(x1) + " ," + std::to_string(y1), olc::WHITE);
		DrawString(5, 110, "Angle of Line : "  + std::to_string( Angle(0, 0, 20, 40)) , olc::WHITE);

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

	float Angle (int x0, int y0, int x1, int y1) 
	{

		float fpi = 3.14159f;

		float Fangle = atan2( y1 - y0 , x1 - x0  ) * 180 / fpi;

		return Fangle;

	}

};

int main()
{
	Example demo;
	if (demo.Construct(216, 140, 4, 4))
		demo.Start();

	return 0;
}
