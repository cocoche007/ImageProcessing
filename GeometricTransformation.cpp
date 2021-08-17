//------------------------------------------------------------------------------
//! @file GeometricTransformation.cpp
//! @brief Definition file of the CGeometricTransformation class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include "qmath.h"
#include "GeometricTransformation.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! CGeometricTransformation constructor for a given image
//!
//! @param imageIn The input image
//!
//! @return The created object
//------------------------------------------------------------------------------
CGeometricTransformation::CGeometricTransformation( QImage *imageIn)
{
    m_imageOrigin  = imageIn;
    m_imageTreated = NULL;
}

//------------------------------------------------------------------------------
//! Destructor
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
CGeometricTransformation::~CGeometricTransformation( void)
{
    delete m_imageTreated;
}

//------------------------------------------------------------------------------
//! Get the treated image
//!
//! @param _
//!
//! @return A pointer on the treated image
//------------------------------------------------------------------------------
QImage* CGeometricTransformation::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Apply a rotation to the image
//!
//! @param rotationAngle The rotation angle in degrees
//!
//! @return _
//------------------------------------------------------------------------------
void CGeometricTransformation::computeRotation( int rotationAngle)
{
    qreal  radianAngle = rotationAngle * M_PI / 180;
    QPoint rotationCenter( m_imageOrigin->width() / 2, m_imageOrigin->height() / 2);
    int    R, G, B;
    int    xIn, yIn;
    int    xOut, yOut;
    int    xMin, xMax;
    int    yMin, yMax;

    xMin = yMin = 0;
    xMax = m_imageOrigin->width();
    yMax = m_imageOrigin->height();
    for ( xIn = 0 ; xIn < m_imageOrigin->width() ; xIn++ )
    {
        for ( yIn = 0 ; yIn < m_imageOrigin->height() ; yIn++ )
        {
            xOut = (int) (rotationCenter.x() + qCos( radianAngle) * (xIn - rotationCenter.x()) + qSin( radianAngle) * (yIn - rotationCenter.y()));
            yOut = (int) (rotationCenter.y() + qSin( radianAngle) * (xIn - rotationCenter.x()) + qCos( radianAngle) * (yIn - rotationCenter.y()));

            xMin = qMin( xOut, xMin);
            yMin = qMin( yOut, yMin);
            xMax = qMax( xOut, xMax);
            yMax = qMax( yOut, yMax);
        }
    }

    delete m_imageTreated;
    m_imageTreated = new QImage( xMax - xMin, yMax - yMin, QImage::Format_RGB32);

    for ( xOut = xMin ; xOut < xMax ; xOut++ )
    {
        for ( yOut = yMin ; yOut < yMax ; yOut++ )
        {
            xIn = (int) (rotationCenter.x() + qCos( radianAngle) * (xOut - rotationCenter.x()) + qSin( radianAngle) * (yOut - rotationCenter.y()));
            yIn = (int) (rotationCenter.y() - qSin( radianAngle) * (xOut - rotationCenter.x()) + qCos( radianAngle) * (yOut - rotationCenter.y()));

            if (    xIn >= 0 && xIn < m_imageOrigin->width()
                 && yIn >= 0 && yIn < m_imageOrigin->height() )
            {
                R = qRed(   m_imageOrigin->pixel( xIn, yIn));
                G = qGreen( m_imageOrigin->pixel( xIn, yIn));
                B = qBlue(  m_imageOrigin->pixel( xIn, yIn));

                m_imageTreated->setPixel( xOut - xMin, yOut - yMin, qRgb( R, G, B));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Apply a homotethie to the image
//!
//! @param scaleFactor The homothetie factor
//!
//! @return _
//------------------------------------------------------------------------------
void CGeometricTransformation::computeScale( int scaleFactor)
{
    qreal factor = (qreal) scaleFactor / 100;
    int   R, G, B;
    int   xIn, yIn;
    int   xOut, yOut;

    delete m_imageTreated;
    m_imageTreated = new QImage( (int) (m_imageOrigin->width() * factor), (int) (m_imageOrigin->height() * factor), QImage::Format_RGB32);

    for ( xOut = 0 ; xOut < m_imageTreated->width() ; xOut++ )
    {
        for ( yOut = 0 ; yOut <  m_imageTreated->height() ; yOut++ )
        {
            xIn = (int) (xOut / factor);
            yIn = (int) (yOut / factor);

            if (    xIn >= 0 && xIn < m_imageOrigin->width()
                 && yIn >= 0 && yIn < m_imageOrigin->height() )
            {
                R = qRed(   m_imageOrigin->pixel( xIn, yIn));
                G = qGreen( m_imageOrigin->pixel( xIn, yIn));
                B = qBlue(  m_imageOrigin->pixel( xIn, yIn));

                m_imageTreated->setPixel( xOut, yOut, qRgb( R, G, B));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Apply a shear to the image
//!
//! @param shearFactorX The shear factor by X
//! @param shearFactorY The shear factor by Y
//!
//! @return _
//------------------------------------------------------------------------------
void CGeometricTransformation::computeShear( int shearFactorX, int shearFactorY)
{
    qreal factorX = (qreal) shearFactorX / 100;
    qreal factorY = (qreal) shearFactorY / 100;
    int   R, G, B;
    int   xIn, yIn;

    delete m_imageTreated;
    m_imageTreated = new QImage( (int) (m_imageOrigin->width() + m_imageOrigin->height() * factorX), (int) (m_imageOrigin->height() + m_imageOrigin->width() * factorY), QImage::Format_RGB32);

    for ( int xOut = 0 ; xOut < m_imageTreated->width() ; xOut++ )
    {
        for ( int yOut = 0 ; yOut <  m_imageTreated->height() ; yOut++ )
        {
            xIn = (int) ((xOut - factorX * yOut) / ( 1 - factorX * factorY));
            yIn = (int) ((yOut - factorY * xOut) / ( 1 - factorX * factorY));

            if (    xIn >= 0 && xIn < m_imageOrigin->width()
                 && yIn >= 0 && yIn < m_imageOrigin->height() )
            {
                R = qRed(   m_imageOrigin->pixel( xIn, yIn));
                G = qGreen( m_imageOrigin->pixel( xIn, yIn));
                B = qBlue(  m_imageOrigin->pixel( xIn, yIn));

                m_imageTreated->setPixel( xOut, yOut, qRgb( R, G, B));
            }
        }
    }
}
