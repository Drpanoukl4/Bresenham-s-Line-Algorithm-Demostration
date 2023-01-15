#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

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

	struct vec2d 
	{

		float x;
		float y;

	};

	struct Polygon 
	{

		std::vector<vec2d> p;	//Transformed Points
		vec2d pos;				//Position of Shapes
		vec2d dpos;
		float angle; 			//Direction of Shape
		std::vector<vec2d> o;

	};

	std::vector<Polygon> vecShapes;

	void Bresenhams (int x0, int y0, int x1, int y1) 
	{	

		int dx = x1 - x0;
		int dy = y1 - y0;
		int incX = SGN(dx);
		int incY = SGN(dy);
		dx = ABS(dx);
		dy = ABS(dy);

		if (dy == 0)
		{
			// horizontal line
			for (int x = x0; x != x1 + incX; x += incX)
				Draw( x, y0 );
		}

		else if (dx == 0)
		{
			// vertical line
			for (int y = y0; y != y1 + incY; y += incY)
				Draw( x0, y );
		}
		else if (dx >= dy)
		{
			// more horizontal than vertical
			int slope = 2 * dy;
			int error = -dx;
			int errorInc = -2 * dx;
			int y = y0;

			for (int x = x0; x != x1 + incX; x += incX)
			{
				Draw( x, y );
				error += slope;

				if (error >= 0)
				{
					y += incY;
					error += errorInc;
				}
			}
		}
		else
		{
			// more vertical than horizontal
			int slope = 2 * dx;
			int error = -dy;
			int errorInc = -2 * dy;
			int x = x0;

			for (int y = y0; y != y1 + incY; y += incY)
			{
				Draw( x, y );
				error += slope;

				if (error >= 0)
				{
					x += incX;
					error += errorInc;
				}
			}
		}

		DrawString(5, 95, "Line From " + std::to_string(x0) + " ," + std::to_string(y0) + " To " + std::to_string(x1) + " ," + std::to_string(y1), olc::WHITE);
		DrawString(5, 110, "Angle of Line : "  + std::to_string( Angle(0, 0, 20, 40)) , olc::WHITE);

	}

	void BresenhamLine (int x0, int y0, int x1, int y1) 
	{	

		int dx = x1 - x0;
		int dy = y1 - y0;
		int incX = SGN(dx);
		int incY = SGN(dy);
		dx = ABS(dx);
		dy = ABS(dy);

		if (dy == 0)
		{
			// horizontal line
			for (int x = x0; x != x1 + incX; x += incX)
				Draw( x, y0 );
		}

		else if (dx == 0)
		{
			// vertical line
			for (int y = y0; y != y1 + incY; y += incY)
				Draw( x0, y );
		}
		else if (dx >= dy)
		{
			// more horizontal than vertical
			int slope = 2 * dy;
			int error = -dx;
			int errorInc = -2 * dx;
			int y = y0;

			for (int x = x0; x != x1 + incX; x += incX)
			{
				Draw( x, y );
				error += slope;

				if (error >= 0)
				{
					y += incY;
					error += errorInc;
				}
			}
		}
		else
		{
			// more vertical than horizontal
			int slope = 2 * dx;
			int error = -dy;
			int errorInc = -2 * dy;
			int x = x0;

			for (int y = y0; y != y1 + incY; y += incY)
			{
				Draw( x, y );
				error += slope;

				if (error >= 0)
				{
					x += incX;
					error += errorInc;
				}
			}
		}

	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		Polygon s1;
		float fTheta = 3.14159f * 2.0f / 3.0f;
		s1.pos = { 30, 60 };
		s1.angle = 0.0f;

		for(int i = 0; i < 3; i++){

			s1.o.push_back({10.0f * cosf(fTheta * i), 10.0f * sinf(fTheta * i) });
			s1.p.push_back({10.0f * cosf(fTheta * i), 10.0f * sinf(fTheta * i) });

		}

		vecShapes.push_back(s1);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::BLUE);

		if(GetKey(olc::Key::LEFT).bHeld) vecShapes[0].angle -= 2.0f * fElapsedTime;
		if(GetKey(olc::Key::RIGHT).bHeld) vecShapes[0].angle += 2.0f * fElapsedTime;
		if(GetKey(olc::Key::UP).bHeld) 
		{

			vecShapes[0].dpos.x += cosf(vecShapes[0].angle) * 1.5f * fElapsedTime;
			vecShapes[0].dpos.y += sinf(vecShapes[0].angle) * 1.5f * fElapsedTime;

		}

		vecShapes[0].pos.x += vecShapes[0].dpos.x;
		vecShapes[0].pos.y += vecShapes[0].dpos.y;

		for( auto &r : vecShapes )
		{

			for( int i = 0; i < r.o.size(); i ++ )
			{

				r.p[i] =
				{

					(r.o[i].x * cosf( r.angle )) - (r.o[i].y * sinf( r.angle )) + r.pos.x,
					(r.o[i].x * sinf( r.angle )) + (r.o[i].y * cosf( r.angle )) + r.pos.y,

				};

			}

		}

		for ( auto &r : vecShapes )
		{

			for(int i = 0; i < r.o.size(); i ++) 
			{

				BresenhamLine( r.p[i].x, r.p[i].y, r.p[ (i + 1) % r.p.size() ].x, r.p[ (i + 1) % r.p.size() ].y );

			}

		}

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
