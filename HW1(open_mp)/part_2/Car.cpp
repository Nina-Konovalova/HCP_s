#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>

// include omp header file here

#define RGB_COMPONENT_COLOR 255

using namespace std;
struct PPMPixel {
    int red;
    int green;
    int blue;
};

typedef struct{
    int x, y, all;
    PPMPixel * data;
} PPMImage;

void readPPM(const char *filename, PPMImage& img){
    std::ifstream file (filename);
    if (file){
        std::string s;
        int rgb_comp_color;
        file >> s;
        if (s!="P3") {std::cout<< "error in format"<<std::endl; exit(9);}
        file >> img.x >>img.y;
        file >>rgb_comp_color;
        img.all = img.x*img.y;
        std::cout << s << std::endl;
        std::cout << "x=" << img.x << " y=" << img.y << " all=" <<img.all << std::endl;
        img.data = new PPMPixel[img.all];
        for (int i=0; i<img.all; i++){
            file >> img.data[i].red >>img.data[i].green >> img.data[i].blue;
        }

    }else{
        std::cout << "the file:" << filename << "was not found" << std::endl;
    }
    file.close();
}

void writePPM(const char *filename, PPMImage & img){
    std::ofstream file (filename, std::ofstream::out);
    file << "P3"<<std::endl;
    file << img.x << " " << img.y << " "<< std::endl;
    file << RGB_COMPONENT_COLOR << std::endl;

    for(int i=0; i<img.all; i++){
        file << img.data[i].red << " " << img.data[i].green << " " << img.data[i].blue << (((i+1)%img.x ==0)? "\n" : " ");
    }
    file.close();
}

void shiftPPM(PPMImage & img) {
	PPMImage new_image;
	new_image.data = new PPMPixel[img.all];
	 
	int delta = 1;
#pragma omp parallel for collapse(2) num_threads(2)
	for (int i = 0; i < img.x-1; i++) {
		for (int j = 0; j < img.y; j++) {
			new_image.data[i+1+j*img.x].green = img.data[i+j*img.x].green; //green color
			new_image.data[i+1+j*img.x].red = img.data[i+j*img.x].red; //red color
			new_image.data[i+1+j*img.x].blue = img.data[i+j*img.x].blue; //blue color
		}
	}
#pragma omp parallel for num_threads(2)
        for (int i = 0; i < img.y; i++) {
		new_image.data[i*img.x].green = img.data[img.x-1+i*img.x].green;
		new_image.data[i*img.x].red = img.data[img.x - 1+i*img.x].red;
		new_image.data[i*img.x].blue = img.data[img.x -1+i*img.x].blue;
	}
//rewrite img
#pragma omp parallel for num_threads(2)
        for (int i = 0; i<img.all; i++){
		img.data[i].green = new_image.data[i].green;
		img.data[i].red = new_image.data[i].red;
		img.data[i].blue = new_image.data[i].blue;
	}

}

int main(int argc, char *argv[]){
    PPMImage image;
    readPPM("car.ppm", image);
    
    double start = omp_get_wtime();
#pragma omp parallel shared (image) num_threads(2)
    
    shiftPPM(image);
    double end = omp_get_wtime();
    writePPM("new_car.ppm", image);
    cout << "Time: " << end - start << endl;
    return 0;}
