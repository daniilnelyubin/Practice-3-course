#include <gtest/gtest.h>
#include "computerVision.hpp"

const double EPS = 5.0;

TEST(structTest, imageRead) {
  EXPECT_THROW(imageRead("kjsdfljs"), std::invalid_argument);
}

TEST(structTest, imageRead2) {
  EXPECT_NO_FATAL_FAILURE(
          imageRead("/home/daniilka/CLionProjects/Grains_2/1233.JPG"));
}

TEST(structTest, imageRead3) {
  EXPECT_THROW(
          imageRead("/home/daniilka/CLionProjects/Grains_2/1233.jpg"),
                    std::invalid_argument);
}

TEST(structTest, imageRead4) {
  EXPECT_THROW(
          imageRead("/home/daniilka/CLionProjects/Grains_2/"),std::exception);
}

TEST(laplacianTest, test1) {
  Mat kernel = (Mat_<float>(5, 5) <<
                                  0, 0, 0, 0, 0,
          0, 255, 255, 255, 0,
          0, 255, 255, 255, 0,
          0, 255, 255, 255, 0,
          0, 0, 0, 0, 0);
  Mat image = laplacian(kernel);

  EXPECT_GT (image.at<double>(3, 3) + EPS, 0.0);

}

TEST(laplacianTest, test2) {
  Mat kernel = (Mat_<float>(5, 5) <<
                                  255, 255, 255, 255, 255,
          255, 0, 0, 0, 255,
          255, 0, 0, 0, 255,
          255, 0, 0, 0, 255,
          255, 255, 255, 255, 255);

  Mat image = laplacian(kernel);

  EXPECT_GT (0.0 + EPS, image.at<double>(3, 3));
}

TEST(erodeTest, test1) {
  Mat kernel = (Mat_<float>(5, 5) <<
          255, 255, 255, 255, 255,
          255, 0, 0, 0, 255,
          255, 0, 100, 0, 255,
          255, 0, 0, 0, 255,
          255, 255, 255, 255, 255);
  Mat lap = laplacian(kernel);
  Mat image = erode(kernel, lap);

  EXPECT_GT (0.0 + EPS, image.at<double>(3, 3));
}

TEST(erodeTest, test2) {
  Mat kernel = (Mat_<float>(5, 5) <<
          255, 255, 255, 255, 255,
          255, 255, 255, 255, 255,
          255, 255, 255, 255, 255,
          255, 255, 255, 255, 255,
          255, 255, 255, 255, 255);
  Mat lap = laplacian(kernel);
  Mat image = erode(kernel, lap);


  EXPECT_GT (0.0 + EPS, image.at<double>(3, 3));
}

TEST(erodeTest, test3) {
  Mat kernel = (Mat_<float>(5, 5) <<
          0, 0, 0, 0, 0,
          0, 0, 255, 0, 0,
          0, 255, 255, 255, 0,
          0, 0, 255, 0, 0,
          0, 0, 0, 0, 0);
  Mat lap = laplacian(kernel);
  Mat image = erode(kernel, lap);



  EXPECT_GT (0.0 + EPS, image.at<double>(3, 3));
}

TEST(erodeTest, test4) {
  Mat
  kernel = (Mat_<float>(6, 6) <<
          255, 255, 255, 255, 255, 255,
          255, 0, 0, 0, 255, 255,
          255, 0, 0, 0, 255, 255,
          255, 0, 0, 0, 255, 255,
          255, 255, 255, 255, 255, 255,
          255, 255, 255, 255, 255, 255);
  Mat lap = laplacian(kernel);
  Mat image = erode(kernel, lap);

  EXPECT_GT (0.0 + EPS, image.at<double>(3, 3));
}

TEST(markerTest, centerTest1) {
  Mat img = imread("rice.png");
  Mat hsv;
  cvtColor(img, hsv, CV_BGR2HSV);

  vector<Mat> channels;
  split(hsv, channels);
  Mat sharp = channels[2];

  Mat imgLaplacian = laplacian(sharp);
  imgLaplacian = laplacian(imgLaplacian);



  channels[2].convertTo(sharp, CV_32F);

  Mat subPlans = sharp - imgLaplacian;
  subPlans = erode(subPlans, imgLaplacian);



  Mat sureFigure, unknown;
  Mat markers = getMarkers(subPlans, sureFigure, unknown);

  EXPECT_EQ(0, unknown.at<double>(30, 60));
  EXPECT_GT(0, unknown.at<double>(25, 5)-EPS);
}
TEST(markerTest, centerTest2) {
  Mat img = imread("rice.png");
  Mat hsv;
  cvtColor(img, hsv, CV_BGR2HSV);

  vector<Mat> channels;
  split(hsv, channels);
  Mat sharp = channels[2];

  Mat imgLaplacian = laplacian(sharp);
  imgLaplacian = laplacian(imgLaplacian);



  channels[2].convertTo(sharp, CV_32F);

  Mat subPlans = sharp - imgLaplacian;
  subPlans = erode(subPlans, imgLaplacian);



  Mat sureFigure, unknown;
  Mat markers = getMarkers(subPlans, sureFigure, unknown);

  EXPECT_EQ(0, unknown.at<double>(100, 60));

}
TEST(markerTest, grainTest1) {
  Mat img = imread("rice.png");
  Mat hsv;
  cvtColor(img, hsv, CV_BGR2HSV);

  vector<Mat> channels;
  split(hsv, channels);
  Mat sharp = channels[2];

  Mat imgLaplacian = laplacian(sharp);
  imgLaplacian = laplacian(imgLaplacian);



  channels[2].convertTo(sharp, CV_32F);

  Mat subPlans = sharp - imgLaplacian;
  subPlans = erode(subPlans, imgLaplacian);



  Mat sureFigure, unknown;
  Mat markers = getMarkers(subPlans, sureFigure, unknown);


  EXPECT_GT(0, unknown.at<double>(25, 5)-EPS);

}
TEST(markerTest, grainTest2) {
  Mat img = imread("rice.png");
  Mat hsv;
  cvtColor(img, hsv, CV_BGR2HSV);

  vector<Mat> channels;
  split(hsv, channels);
  Mat sharp = channels[2];

  Mat imgLaplacian = laplacian(sharp);
  imgLaplacian = laplacian(imgLaplacian);



  channels[2].convertTo(sharp, CV_32F);

  Mat subPlans = sharp - imgLaplacian;
  subPlans = erode(subPlans, imgLaplacian);



  Mat sureFigure, unknown;
  Mat markers = getMarkers(subPlans, sureFigure, unknown);


  EXPECT_GT(0, unknown.at<double>(120, 5)-EPS);

}
TEST(getFileListTest, listTest1) {
  std::string path = "dfjakl";
  EXPECT_THROW(getFileList(path),std::invalid_argument);
}
TEST(getFileListTest, listTest2) {
  std::string path = "..";
  EXPECT_NO_THROW(getFileList(path));
}
TEST(getFileListTest, listTest3) {
  std::string path = ".";
  EXPECT_NO_THROW(getFileList(path));
}
TEST(getFileListTest, listTest4) {
  std::string path = "/home/daniilka/CLionProjects/Grains_2/Photo/";
  EXPECT_NO_THROW(getFileList(path));
}
