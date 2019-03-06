#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


const double PIXEL_SIZE = 0.265;

int watershed(std::string path, std::vector<double> &length,
              std::vector<double> &width, std::vector<double> &area) {

    Mat resultImage = imread(path.c_str());
    Mat hsv;

    cvtColor(resultImage, hsv, CV_BGR2HSV);
    vector<Mat> channels;
    split(hsv, channels);

    Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
    Mat imgLaplacian;

    Mat sharp = channels[1];
    filter2D(sharp, imgLaplacian, CV_32F, kernel);
        channels[1].convertTo(sharp, CV_32F);

    Mat subPlans = sharp - imgLaplacian;
    subPlans.convertTo(subPlans, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    blur(subPlans, subPlans, Size(3, 3));

    int erodeSz = 4;
    Mat structuringElement = cv::getStructuringElement(MORPH_ELLIPSE,
                                                Size(2 * erodeSz + 1,
                                                         2 * erodeSz + 1),
                                                Point(erodeSz, erodeSz));

    erode(subPlans, subPlans, structuringElement);
    dilate(subPlans, subPlans, structuringElement);
    bitwise_not(subPlans, subPlans);

    threshold(subPlans, subPlans, 40, 255,
                  CV_THRESH_BINARY | CV_THRESH_OTSU);

    Mat opening;
    Mat kernel_1(3, 3, CV_8U, Scalar(1));
    morphologyEx(subPlans, opening, MORPH_OPEN, kernel_1,
                     Point(-1, -1), 1);

    Mat sure_bg;
    dilate(opening, sure_bg, kernel_1, Point(-1, -1), 3);

    Mat distTransform;
    distanceTransform(opening, distTransform, CV_DIST_L2, 5);

    Mat sureFigure;
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(distTransform, &minVal, &maxVal, &minLoc, &maxLoc);
    threshold(distTransform, sureFigure, 0, 255, 0);

    distTransform = distTransform / maxVal;

    Mat unknown, sureFigure1;
    sureFigure.convertTo(sureFigure1, CV_8UC1);
    subtract(sure_bg, sureFigure1, unknown);

    int compCount = 0;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    sureFigure.convertTo(sureFigure, CV_32SC1, 1.0);

    findContours(sureFigure, contours, hierarchy, RETR_CCOMP,
                     CHAIN_APPROX_SIMPLE);

    if (contours.empty()) return -1;

    Mat markers = Mat::zeros(sureFigure.rows, sureFigure.cols, CV_32SC1);


    for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
        drawContours(markers, contours, index, Scalar::all(compCount + 1),
                         -1, 8, hierarchy, INT_MAX);
    markers = markers + 1;

    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            unsigned char &v = unknown.at<unsigned char>(i, j);
            if (v == 255) {
                markers.at<int>(i, j) = 0;

            }
        }
    }

    watershed(resultImage, markers);

    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            int index = markers.at<int>(i, j);
            if (index == -1)
                resultImage.at<Vec3b>(i, j) = Vec3b(0, 255, 0);

        }
    }

    int quantity = 0;

    for (unsigned int i = 0; i < contours.size(); i = i + 2) {
        RotatedRect rect = minAreaRect(contours[i]);
        putText(resultImage, to_string(quantity + 1), rect.center,
                    FONT_ITALIC, 2, Scalar(0, 0, 255), 1);
        length.push_back(rect.size.height * PIXEL_SIZE);
        width.push_back(rect.size.width * PIXEL_SIZE);
        area.push_back(contourArea(contours[i]) * PIXEL_SIZE * PIXEL_SIZE);
        quantity++;
    }

    imwrite("result.png", resultImage);
    return quantity;
}

int main() {

    vector <double> length;
    vector<double> width;
    vector<double> area;
    int count = watershed(string("1392.jpg"), length, width, area);
    cout<<count<<"\n";
    for (int i = 0; i < length.size(); ++i) {
        cout<< length[i]<<" "<<width[i]<<" area: "<<area[i]<<"\n";
    }
    return 0;
}
