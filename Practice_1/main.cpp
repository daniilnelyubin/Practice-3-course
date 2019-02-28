#include <iostream>
#include <fstream>

void get_from_file(const std::string &name, int *arr) {
    std::string line;

    std::ifstream in(name);
    int i = 0;
    if (in.is_open()) {

        while (getline(in, line)) {
            for (int j = 0; j < line.size(); ++j) {
                arr[i][j] = arr[i];
            }
            i++;
        }
    }
    in.close();
}


int main() {
    int W = 0;
    int H = 0;
    int X = 0;
    int Y = 0;
    int D = 0;
    std::cin >> W >> H >> X >> Y >> D;
    char* field[H][W];
    get_from_file("1.txt",field);

}