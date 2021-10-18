#include <iostream>
#include <vector>
#include <cmath>

#include "./opengl.h"
#include "maze.cpp"
#pragma once

using namespace std;

typedef std::vector<std::vector<char>> Map;
typedef std::vector<char> Row;

class Board {
   public:
    Board(int, int);
    bool isValid(int, int, char);
    void setPositionBoard(int x, int y, char id);
    void loadTexture(const char *, int);
    void draw();

   private:
    int posP[2] = {};
    int posE[2] = {};
    Map map;

    void respawnPointGenerator();
    bool isOccupied(int, int, char);
    void readJPEG(const char *, unsigned char **, int *, int *);
};

Board::Board(int height, int width) {
    Maze maze;
    Row row = Row(width - 1);

    srand(time(0));
    for (int i = 0; i < height - 2; ++i) map.push_back(row);

    maze.maze(map);
    respawnPointGenerator();
    maze.showMaze(map);
}

void Board::respawnPointGenerator() {
    int i = map.size() - 2;
    int j = 1;
    map[i][j] = 'E';
    bool connected = false;

    while (!connected) {
        if (map[i - 1][j] == ' ' || map[i][j + 1] == ' ')
            connected = true;
        else if (map[i][j] == 'W')
            map[i][j] = ' ';
        i--;
    }

    connected = false;
    i = 1;
    j = map.size() - 2;
    map[i][j] = 'P';

    while (!connected) {
        if (map[i + 1][j] == ' ' || map[i][j - 1] == ' ')
            connected = true;
        else if (map[i][j] == 'W')
            map[i][j] = ' ';
        i++;
    }
}

bool Board::isValid(int x, int y, char id) {
    if ((map[x][y] == ' ' || map[x][y] == 'P' || map[x][y] == 'E') && !isOccupied(x, y, id)) {
        if (id == 'P') cout << "MAP ..> " << map[x][y] << " Coord: " << x << " " << y << endl;
        if ((map[x][y] == 'P' && id == 'E') || (map[x][y] == 'E' && id == 'P')) {  // Winner is Enemy
            cout << "Winner is " << id << endl;
        }
        return true;
    } else {
        return false;
    }
}

void Board::setPositionBoard(int x, int y, char id) {
    if (id == 'P') {
        posP[0] = x;
        posP[1] = y;
    } else if (id == 'E') {
        posE[0] = x;
        posE[1] = y;
    }
}

bool Board::isOccupied(int x, int y, char id) {
    if (id == 'P')
        return x == this->posE[0] && y == this->posE[1];
    else
        return x == this->posP[0] && y == this->posP[1];
}

void Board::draw() {
    int translationX = -(int)round(WIDTH / 2);   // WIDTH <--> COLUMNS
    int translationY = -(int)round(HEIGHT / 2);  // HEIGHT <--> ROWS

    int vertex[8][3] = {
        {0, 1, 0},   // a
        {0, 1, -1},  // b
        {0, 0, -1},  // c
        {0, 0, 0},   // d
        {1, 0, 0},   // e
        {1, 1, 0},   // f
        {1, 0, -1},  // g
        {1, 1, -1}   // h
    };

    for (int i = 0; i < map.size(); i++) {         //
        for (int j = 0; j < map[i].size(); j++) {  //
            if (map[i][j] == ' ') continue;
            switch (map[i][j]) {
                case 'W':
                    glColor3f(0.8, 0.8, 0.8);
                    break;
                case 'E':
                    glColor3f(0.66, 0, 0);
                    break;
                case 'P':
                    glColor3f(0.294, 0.325, 0.125);
                    break;
            }
            // lower quadrilater
            glBegin(GL_QUADS);
            glVertex3i((i + vertex[1][0]) * DISTANCE_UNIT + translationX, (j + vertex[1][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
            glVertex3i((i + vertex[2][0]) * DISTANCE_UNIT + translationX, (j + vertex[2][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
            glVertex3i((i + vertex[6][0]) * DISTANCE_UNIT + translationX, (j + vertex[6][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
            glVertex3i((i + vertex[7][0]) * DISTANCE_UNIT + translationX, (j + vertex[7][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
            glEnd();

            if (map[i][j] == 'W') {
                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3i((i + vertex[3][0]) * DISTANCE_UNIT + translationX, (j + vertex[3][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
                glVertex3i((i + vertex[0][0]) * DISTANCE_UNIT + translationX, (j + vertex[0][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
                glVertex3i((i + vertex[5][0]) * DISTANCE_UNIT + translationX, (j + vertex[5][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
                glVertex3i((i + vertex[4][0]) * DISTANCE_UNIT + translationX, (j + vertex[4][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
                glEnd();

                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3i((i + vertex[3][0]) * DISTANCE_UNIT + translationX, (j + vertex[3][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
                glVertex3i((i + vertex[0][0]) * DISTANCE_UNIT + translationX, (j + vertex[0][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
                glVertex3i((i + vertex[1][0]) * DISTANCE_UNIT + translationX, (j + vertex[1][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
                glVertex3i((i + vertex[2][0]) * DISTANCE_UNIT + translationX, (j + vertex[2][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
                glEnd();

                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3i((i + vertex[3][0]) * DISTANCE_UNIT + translationX, (j + vertex[3][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
                glVertex3i((i + vertex[2][0]) * DISTANCE_UNIT + translationX, (j + vertex[2][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
                glVertex3i((i + vertex[6][0]) * DISTANCE_UNIT + translationX, (j + vertex[6][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
                glVertex3i((i + vertex[5][0]) * DISTANCE_UNIT + translationX, (j + vertex[5][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
                glEnd();

                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3i((i + vertex[5][0]) * DISTANCE_UNIT + translationX, (j + vertex[5][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
                glVertex3i((i + vertex[6][0]) * DISTANCE_UNIT + translationX, (j + vertex[6][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
                glVertex3i((i + vertex[7][0]) * DISTANCE_UNIT + translationX, (j + vertex[7][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
                glVertex3i((i + vertex[4][0]) * DISTANCE_UNIT + translationX, (j + vertex[4][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
                glEnd();

                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3i((i + vertex[0][0]) * DISTANCE_UNIT + translationX, (j + vertex[0][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
                glVertex3i((i + vertex[1][0]) * DISTANCE_UNIT + translationX, (j + vertex[1][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
                glVertex3i((i + vertex[7][0]) * DISTANCE_UNIT + translationX, (j + vertex[7][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
                glVertex3i((i + vertex[4][0]) * DISTANCE_UNIT + translationX, (j + vertex[4][1]) * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
                glEnd();
            }
        }
    }
}

void Board::readJPEG(const char *filename, unsigned char **image, int *width, int *height) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    unsigned char **buffer;
    int i, j;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    if ((infile = fopen(filename, "rb")) == NULL) {
        printf("Unable to open file %s\n", filename);
        exit(1);
    }

    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_calc_output_dimensions(&cinfo);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;

    *image = (unsigned char *)malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components);

    buffer = (unsigned char **)malloc(1 * sizeof(unsigned char **));
    buffer[0] = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);

    i = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        for (j = 0; j < cinfo.output_width * cinfo.output_components; j++) {
            (*image)[i] = buffer[0][j];
            i++;
        }
    }

    free(buffer);
    jpeg_finish_decompress(&cinfo);
}

void Board::loadTexture(const char *filename, int dim) {
    unsigned char *buffer;
    unsigned char *buffer2;
    int width, height;
    long i, j;
    long k, h;

    readJPEG(filename, &buffer, &width, &height);

    buffer2 = (unsigned char *)malloc(dim * dim * 3);

    //-- The texture pattern is subsampled so that its dimensions become dim x dim --
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++) {
            k = i * height / dim;
            h = j * width / dim;

            buffer2[3 * (i * dim + j)] = buffer[3 * (k * width + h)];
            buffer2[3 * (i * dim + j) + 1] = buffer[3 * (k * width + h) + 1];
            buffer2[3 * (i * dim + j) + 2] = buffer[3 * (k * width + h) + 2];
        }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dim, dim, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer2);

    free(buffer);
    free(buffer2);
}
