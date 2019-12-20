#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

struct Color {
        int r,g,b;
};

Color colorPromedio (Mat pixels, int x, int y, int width, int height){

    int sumaR=0, sumaG=0, sumaB=0;

    for (int i=0; i<x+width; i++){

        for (int j=0; j<y+height; j++){
            int r,g,b;
            r = pixels.at<Vec3b>(i,j)[0];
            g = pixels.at<Vec3b>(i,j)[1];
            b = pixels.at<Vec3b>(i,j)[2];
            sumaR += r;
            sumaG += g;
            sumaB += b;
        }
    }

    int area = width*height;

    Color colorProm;
    colorProm.r = sumaR/area;
    colorProm.g = sumaG/area;
    colorProm.b = sumaB/area;

    return colorProm;
}

double distanciaPixs2Promedio (Mat pixels, int x, int y, int width, int height){
 
    Color colorProm=colorPromedio(pixels,x,y,width,height);
    //cout<<"color prom "<<colorPromedio(pixels,x,y,width,height).r<<'\n';
    int r,g,b;
    r = colorProm.r;
    g = colorProm.g;
    b = colorProm.b;

    double colorDist=0;
    for (int i=0; i<x+width; i++){

        for (int j=0; j<y+height; j++){

            int r_, g_, b_;
            r_ = pixels.at<Vec3b>(i,j)[0];
            g_ = pixels.at<Vec3b>(i,j)[1];
            b_ = pixels.at<Vec3b>(i,j)[2];
            colorDist += abs(r-r_);
            colorDist += abs(g-g_);
            colorDist += abs(b-b_);
        }
    }

    int area=width*height;
    return colorDist/(3*area);
}

class Nodo {
    public:
        int x, y, width, height;
        vector<Nodo*> hijos;
        Color color;
        
        Nodo();
        Nodo (Mat pixels, int x, int y,int width, int height, double distanciaPixs2PromedioMax)
                :x(x), y(y), width(width), height(height){
            //cout<<"x, y: "<<x<<" "<<y<<'\n';
            //cout<<"widht, heigth: "<<width<<" "<<height<<'\n';
            //cout<<"distabcia "<<distanciaPixs2Promedio(pixels,x,y,width,height)<<'\n';
            if ( width==2 || height==1 || distanciaPixs2Promedio(pixels,x,y,width,height) <= distanciaPixs2PromedioMax){
                color = colorPromedio(pixels,x,y,width,height);
                //cout<<" cal color de promedio R: "<<color.r<<'\n';
            }
            else{
                                //if(distanciaPixs2Promedio(pixels,x,y,width,height)<70){

                hijos.push_back(new Nodo(pixels,x,y,width/2,height/2,distanciaPixs2PromedioMax));
                hijos.push_back(new Nodo(pixels,x+width/2,y,width-width/2,height/2,distanciaPixs2PromedioMax));
                hijos.push_back(new Nodo(pixels,x,y+height/2,width/2,height-height/2,distanciaPixs2PromedioMax));
                hijos.push_back(new Nodo(pixels,x+width/2,y+height/2,width-width/2,height-height/2,distanciaPixs2PromedioMax));
                                //}
            }
        };

        bool esHoja (){
            return hijos.size() == 0;
        }

        Color getColor (int i, int j){
            if (esHoja()){
                return color;
            }
            else{
                if ( i < x+width/2 ){
                    if ( j < y+height/2 ){
                        return hijos[0]->getColor(i,j);
                    }
                    else{
                        return hijos[2]->getColor(i,j);
                    }
                }
                else{
                    if ( j < y+height/2 ){
                        return hijos[1]->getColor(i,j);
                    }
                    else{
                        return hijos[3]->getColor(i,j);
                    }
                }
            }
        }
};

int main( )
{


    Mat pixels = imread("sp.jpg", CV_LOAD_IMAGE_COLOR);

    //cout<<pixels.channels();

    int distanciaPixs2PromedioMax = 55;

    Nodo *quadtree = new Nodo(pixels, 0, 0, pixels.cols, pixels.rows, distanciaPixs2PromedioMax);
    
    //Color color = quadtree->getColor(500,0);
    //cout<<color.r<<" "<<color.g<<" "<<color.b<<'\n';

    Mat out(pixels.cols,pixels.rows,CV_8UC3, Scalar(0,0, 100));
    
    for (int i=0; i<pixels.rows; i++){
        for (int j=0; j<pixels.cols; j++){
            out.at<Vec3b>(i,j)[0] = quadtree->getColor(i,j).r;
            out.at<Vec3b>(i,j)[1] = quadtree->getColor(i,j).g;
            out.at<Vec3b>(i,j)[2] = quadtree->getColor(i,j).b;
        }
    }

    imwrite("spOut.jpg",out);

    return 0;
}