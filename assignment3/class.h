#include<vector>

class Point{
//Point类表示平面上的点
public:
    Point(double _x=0.0,double _y=0.0):x(_x),y(_y){}

    double get_x() const;//获取横坐标
    double get_y() const;

    void write_x(double _x);//修改横坐标
    void write_y(double _y);

private:
    double x{};
    double y{};
};

class Shape{//图形类
protected:
    virtual bool is_valid_shape() const =0;//确认是否形成有效的图形(只考虑是否有顶点存在重合)
public:
    virtual double get_area() const =0;//求面积，纯虚函数
    virtual ~Shape() = default;
};

class Triangle:public Shape{
private:
    Point p1{},p2{},p3{};
    bool is_valid_shape() const override;
public:
    Triangle(Point _p1,Point _p2,Point _p3):p1(_p1),p2(_p2),p3(_p3){}
    Triangle():p1(Point()),p2(Point()),p3(Point()){}
    double get_area() const override;//求三角形面积
};
