#include "abdujaffine.h"

void AbduzhalilTransformations(double *ArrayOfVertexes, double *NewArray,
                               int ArrayLength, double ZoomScale, double angleX,
                               double angleY, double angleZ,
                               translated_cooord coord) {
  for (unsigned int i = 0; i < (ArrayLength * 3); i += 3) {
    double tempX = ArrayOfVertexes[i];
    double tempY = ArrayOfVertexes[i + 1];
    double tempZ = ArrayOfVertexes[i + 2];
    NewArray[i] =
        ZoomScale * (cos(angleZ) * (tempX * cos(angleY) + tempZ * sin(angleY)) -
                     sin(angleZ) * (tempX * sin(angleX) * sin(angleY) +
                                    tempY * cos(angleX) -
                                    tempZ * sin(angleX) * cos(angleY))) +
        coord.x;
    NewArray[i + 1] =
        ZoomScale *
            (cos(angleZ) *
                 (tempX * sin(angleX) * sin(angleY) + tempY * cos(angleX) -
                  tempZ * sin(angleX) * cos(angleY)) +
             sin(angleZ) * (tempX * cos(angleY) + tempZ * sin(angleY))) +
        coord.y;
    NewArray[i + 2] =
        ZoomScale *
            (cos(angleX) * (tempZ * cos(angleX) * cos(angleY) -
                            tempX * sin(angleY) + tempY * sin(angleX))) +
        coord.z;
  }
}