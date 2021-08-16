//------------------------------------------------------------------------------
//! @file GeometricTransformation.h
//! @brief Header du fichier GeometricTransformation.cpp
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __GEOMETRIC_TRANSFORMATION_H__
#define __GEOMETRIC_TRANSFORMATION_H__

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>


//------------------------------------------------------------------------------
// Classe(s) :

class CGeometricTransformation
{
public :
    CGeometricTransformation( QImage *imageIn);
    ~CGeometricTransformation();

    QImage *getImageTreated( void);
    void    computeRotation( int rotationAngle);
    void    computeScale( int scaleFactor);
    void    computeShear( int shearFactorX, int shearFactorY);

private :
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // __GEOMETRIC_TRANSFORMATION_H__
