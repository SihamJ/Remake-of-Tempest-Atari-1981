// #include "../headers/Triangle.hpp"

// Triangle::Triangle(){}

// Triangle::Triangle(int height, int width){
//     this->height = height;
//     this->width = width;
// }

// Triangle::~Triangle(){}

// std::array<Line, 2> Triangle::getMedians(){
//     return this->medians;
// }

// void Triangle::setMedians(std::array<Line, 2> medians){
//     this->medians = medians;
// }

// void Triangle::findMedians(int width){
//     Point mid_1 = Point( width/2 - abs(this->points.at(2).get_x() - this->points.at(0).get_x()) / 2, this->points.at(2).get_y() + abs( this->points.at(0).get_y() - this->points.at(2).get_y()) / 2);
//     Point mid_2 = Point( width/2 + abs(this->points.at(2).get_x() - this->points.at(1).get_x() ) / 2, this->points.at(2).get_y() + abs( this->points.at(1).get_y() - this->points.at(2).get_y() ) / 2);
//     Point mid_3 = Point( width/2, this->points.at(0).get_y());
//     this->medians[0].set_line(this->points.at(0), mid_2);
//     this->medians[1].set_line(this->points.at(1), mid_1);
// }

// void Triangle::Build() {
//     // Base du triangle
//     this->points.push_back(Point(width/2 - this->width/2, height/2 + this->height/2));
//     this->points.push_back(Point(width/2 + this->width/2, height/2 + this->height/2));

//     // Point supérieur
//     this->points.push_back(Point(width/2, height/2 - this->height/2));
// }



