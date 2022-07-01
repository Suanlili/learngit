#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Manderbrot.h"
#include "../../bitmap/src/bitmap.h"
//水平有限T_T，这里定义了两个全局变量，用于每次迭代调整zoom的位置。
double o_x, o_y;

/*这里对老师的manderbrot.cpp中的main函数做了一些修改，使其每次执行可以进行一次调整。
调整使得zoom的位置位于边界附近。
*/
int generate(char* bmpname, double oox, double ooy, double indim)
{

	
	Window win(oox, ooy, indim);
	double lpp = win.get_lpp();
	double dim = win.get_dimension();
	int width = win.get_width();
	int height = win.get_height();
	double ox = win.get_ox() - dim;
	double oy = win.get_oy() - dim / width * height;
	int N = 500;

	char *cache = new char[width * height * 3];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
		  int bdryn = 0;
		  int flagn = rand() % 500;
		  int prtflag = 0;
		  
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			int pos = width * j + i;
			int itn = 0;  //我在这里加入了一个计数器，用来记录迭代的次数。再次迭代时会初始化。
			Manderbrot man(std::complex<double>{0.0, 0.0},
						   N,
						   std::complex<double>{x, y});
			while (!man.stop_criterion())
			{
				man.forward_step();
				itn++;
				if (man.is_disconvergence())
					break;
			}
			//以下是更改的颜色参数。
			cache[pos * 3] = 255;
			cache[pos * 3 + 1] = itn * itn * itn * 0.03;
			cache[pos * 3 + 2] = itn * itn * itn * 0.1;
			
			if(bdryn < 500 && itn >= N - 50 && prtflag == 0){
			  if(bdryn == flagn){
			    o_x = x;
			    o_y = y;
			  }
			  bdryn++;
			  prtflag = 1;
			  }
			
		}
	build_bmp(bmpname, width, height, cache);
	delete [] cache;
	return 0;
};

int main(int argc, char *argv[]){
  //初始输入无需命名文件，但要给出坐标和初始dimension。
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0]
				  << "ox oy dimension" << std::endl;
		exit(-1);
	}
	int i;
	o_x = std::atof(argv[1]);
	o_y = std::atof(argv[2]);
	double dim = std::atof(argv[3]);
	char name[9] = "run0.bmp";   //每次运行创建一个名为run_.bmp的文件，空格处为第几次放大。
	for (i = 0; i < 10; i++){
	  generate(name, o_x, o_y, dim);
	  name[3]++;
	  dim /= 4 ;                 //每次放大4倍。（考虑到电脑性能T_T)
	  std::cout<<"OUtput"<<std::endl;
	}
}
