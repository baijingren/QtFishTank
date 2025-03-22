//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_CAMERA_H
#define QTFISHTANK_CAMERA_H


class Camera {
private:
	int position[4], lookAt[4];
public:
	void setLookAt(int x, int y, int z);
	void setPosition(int x, int y, int z);
};


#endif//QTFISHTANK_CAMERA_H
