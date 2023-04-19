#ifndef SRC_AFFINE_H_
#define SRC_AFFINE_H_

#include <math.h>

typedef struct {
  double x;
  double y;
  double z;
} translated_cooord;

void AbduzhalilTransformations(double *ArrayOfVertexes, double *NewArray,
                               int ArrayLength, double ZoomScale, double angleX,
                               double angleY, double angleZ,
                               translated_cooord coord);

#endif  // SRC_AFFINE_H_
