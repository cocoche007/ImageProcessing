//------------------------------------------------------------------------------
//! @file ColorModel.cpp
//! @brief Definition file of the CColorModel class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s):

#include "ColorModel.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! CColorModel constructor for a given image
//!
//! @param imageIn The input image
//!
//! @return The created object
//------------------------------------------------------------------------------
CColorModel::CColorModel( QImage *imageIn)
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
CColorModel::~CColorModel( void)
{
    delete m_imageTreated;
}

//------------------------------------------------------------------------------
//! Return the treated image
//!
//! @param _
//!
//! @return A pointer on the treated image
//------------------------------------------------------------------------------
QImage* CColorModel::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Compute the Y part or the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CColorModel::computeComponentY( void)
{
    int Y;

    if ( m_imageOrigin )
    {
        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);

        if ( m_imageTreated != NULL )
        {
            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    Y = (   299 * qRed(   m_imageOrigin->pixel( x, y))
                          + 587 * qGreen( m_imageOrigin->pixel( x, y))
                          + 114 * qBlue( m_imageOrigin->pixel( x, y)))
                        / 1000;
                    m_imageTreated->setPixel( x, y, qRgb( Y, Y, Y));
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Compute the U part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CColorModel::computeComponentU( void)
{
    int U;

    if ( m_imageOrigin )
    {
        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);

        if ( m_imageTreated != NULL )
        {
            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    U = (   436 * qBlue( m_imageOrigin->pixel( x, y))
                          - 147 * qRed( m_imageOrigin->pixel( x, y))
                          - 289 * qGreen( m_imageOrigin->pixel( x, y)))
                         / 1000;
                    U = (U + 111) * 115 / 100;

                    if ( U > 255 )
                        U = 255;
                    if ( U < 0 )
                        U = 0;

                    m_imageTreated->setPixel( x, y, qRgb( U, U, U));
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Compute the V part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CColorModel::computeComponentV( void)
{
    int V;

    if ( m_imageOrigin )
    {
        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);
        if ( m_imageTreated != NULL )
        {
            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    V = (   615 * qRed( m_imageOrigin->pixel( x, y))
                          - 515 * qGreen( m_imageOrigin->pixel( x, y))
                          - 100 * qBlue( m_imageOrigin->pixel( x, y)))
                        / 1000;

                    V = (V + 157) * 81 / 100;

                    if ( V > 255 )
                        V = 255;
                    if ( V < 0 )
                        V = 0;

                    m_imageTreated->setPixel( x, y, qRgb( V, V, V));
                }
            }
        }
    }
}
