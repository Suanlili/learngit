#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Manderbrot.h"
#include "../../bitmap/src/bitmap.h"

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		std::cerr << "Usage: " << argv[0]
				  << " filename ox oy dimension" << std::endl;
		exit(-1);
	}
	
	Window win(std::atof(argv[2]), std::atof(argv[3]), std::atof(argv[4]));
	double lpp = win.get_lpp();
	double dim = win.get_dimension();
	int width = win.get_width();
	int height = win.get_height();
	double ox = win.get_ox() - dim;
	double oy = win.get_oy() - dim / width * height;
	int N = 100;

	char *cache = new char[width * height * 3];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			int pos = width * j + i;
			int itn = 0;
			Manderbrot man(std::complex<double>{0.0, 0.0},
						   N,
						   std::complex<double>{x, y});
			while (!man.stop_criterion())
			{
				man.forward_step();
				itn = itn + 1;
				if (man.is_disconvergence())
					break;
			}
			/*
			//points that disconverge
		       	if (man.stop_criterion())
			{
				cache[pos * 3] = 255 - itn * 2.55;
				cache[pos * 3 + 1] = 255 - itn * 2.55;
				cache[pos * 3 + 2] = 255 - itn * 2.55;
			}
			//points that converge
			else
			{
				cache[pos * 3] = 0;
				cache[pos * 3 + 1] = 0;
				cache[pos * 3 + 2] = 0;
		       	}
			*/
			cache[pos * 3] = 255;
			cache[pos * 3 + 1] = (itn - 200 ) * (itn - 200)* (itn - 200)* (itn - 200)* (itn - 200)* (itn - 200) *0.03;
			cache[pos * 3 + 2] = (itn - 200 ) * (itn - 200)* (itn - 200)* (itn - 200)* (itn - 200)* (itn - 200) *0.1;
			
		}
	build_bmp(argv[1], width, height, cache);
	delete [] cache;
	return 0;
};
