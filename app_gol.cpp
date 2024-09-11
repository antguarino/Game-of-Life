#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <unordered_set>

using namespace std;


void runGame(const bool grid[3][3], const int& time) {
    cv::Mat canvas = cv::Mat::zeros(300, 300, CV_8UC3);
    cv::Size frameSize(3000, 3000);
    cv::Mat frameCanvas;

    cv::VideoWriter writer;
    writer.open("game_of_life_simulation.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 24, frameSize, true);

    // Initialize the canvas with the starting grid
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (grid[y][x]) {
                canvas.at<cv::Vec3b>(canvas.rows / 2 - 1 + y, canvas.cols / 2 - 1 + x) = cv::Vec3b(255, 255, 255);
            }
        }
    }

    cv::resize(canvas, frameCanvas, frameSize);
    writer.write(frameCanvas);

    cv::Mat newCanvas = cv::Mat::zeros(300, 300, CV_8UC3);

    int live_neighbors;

    for (int runtime = 0; runtime < time * 24; runtime++) {
        for (int y = 1; y < canvas.rows - 1; y++) {
            for (int x = 1; x < canvas.cols - 1; x++) {
                live_neighbors = 0;

                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        if (j == 0 && i == 0) continue;
                        if (canvas.at<cv::Vec3b>(y + j, x + i) == cv::Vec3b(255, 255, 255)) {
                            live_neighbors++;
                        }
                    }
                }

                /* Rules (From Wikipedia)
                1.) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
                2.) Any live cell with two or three live neighbours lives on to the next generation.
                3.) Any live cell with more than three live neighbours dies, as if by overpopulation.
                4.) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                */

                if (canvas.at<cv::Vec3b>(y, x) == cv::Vec3b(255, 255, 255)) {
                    if (live_neighbors == 2 || live_neighbors == 3) {
                        newCanvas.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
                    } else {
                        newCanvas.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
                    }
                } else {
                    if (live_neighbors == 3) {
                        newCanvas.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
                    } else {
                        newCanvas.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
                    }
                }
            }
        }

        canvas = newCanvas.clone();
        newCanvas = cv::Mat::zeros(300, 300, CV_8UC3);
        cv::resize(canvas, frameCanvas, frameSize);
        writer.write(frameCanvas);
    }

    writer.release();
}

int main() {
    cout << "Game of Life" << endl;
    bool grid[3][3] = {{false, true, true}, {false, false, true}, {true, true, true}};
    runGame(grid, 20);

    return 0;
}
