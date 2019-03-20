
#include <gtest/gtest.h>

#include "computerVision.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  int code = RUN_ALL_TESTS();
  std::string dirName = "/home/daniilka/CLionProjects/Grains_2/Photo/";
  std::vector<std::string> files= getFileList(dirName);

  ofstream myfile;
  myfile.open ("res.csv");
  for (int i = 0; i < files.size(); ++i) {
    vector<double> length;
    vector<double> width;
    vector<double> area;
    Mat image = imread(string(dirName+files.at(i)));
//    int count = mainAlg(image, length, width, area);

//    myfile << i-2<<","<<count << "\n";



  }

  myfile.close();

  return 0;
}
