//------------------------------------------------------------------------------
//! @file GeometricTransformation.h
//! @brief Header file of the CGeometricTransformation class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef GEOMETRIC_TRANSFORMATION_HEADER
#define GEOMETRIC_TRANSFORMATION_HEADER

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>


//------------------------------------------------------------------------------
// Classe(s) :

class CGeometricTransformation
{
public:
    CGeometricTransformation(QImage *imageIn);
    ~CGeometricTransformation();

    QImage *getImageTreated(void);
    void    computeRotation(int rotationAngle);
    void    computeScale(int scaleFactor);
    void    computeShear(int shearFactorX, int shearFactorY);

private:
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // GEOMETRIC_TRANSFORMATION_HEADER
