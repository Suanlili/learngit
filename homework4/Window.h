class Window
{
 private:
  Point2d origin = {0.0, 0.0};
  double dimension=5.0;
  int height =1080;
  int width = 1920;
 public:
  Window(){}
  Window(double _ox, double _oyy, double _d){
    origin.x=_ox;
    origin.y=_oy;
}
