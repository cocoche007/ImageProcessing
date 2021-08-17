//------------------------------------------------------------------------------
//! @file Quantisation.cpp
//! @brief Definition file of the CQuantisation class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include "Quantisation.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! CQuantisation constructor for a given image
//!
//! @param imageIn The input image
//!
//! @return The created object
//------------------------------------------------------------------------------
CQuantisation::CQuantisation( QImage *imageIn)
{
    m_imageOrigin = imageIn;
    m_imageTreated = NULL;
}

//------------------------------------------------------------------------------
//! Destructor
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
CQuantisation::~CQuantisation( void)
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
QImage* CQuantisation::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Compute the grayscale quantisated image
//!
//! @param quantisationLevel The quantisation level
//!
//! @return _
//------------------------------------------------------------------------------
void CQuantisation::computeGrayQuantisation( int quantisationLevel)
{
    int pas = 256 >> quantisationLevel;
    int G;

    if ( m_imageOrigin )
    {
        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);

        if ( m_imageTreated )
        {
            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    G = (   299 * qRed( m_imageOrigin->pixel( x, y))
                          + 587 * qGreen( m_imageOrigin->pixel( x, y))
                          + 114 * qBlue( m_imageOrigin->pixel( x, y)))
                        / 1000;

                    G = ((G / pas * 2 + 1) * pas) / 2;

                   m_imageTreated->setPixel( x, y, qRgb( G, G, G));
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Compute the colored quantisated image
//!
//! @param quantisationLevel The quantisation level
//!
//! @return _
//------------------------------------------------------------------------------
void CQuantisation::computeRGBQuantisation( int quantisationLevel)
{
    int pas = 256 >> quantisationLevel;
    int R;
    int G;
    int B;

    if ( m_imageOrigin )
    {
        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);

        if ( m_imageTreated )
        {
            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    R = ((qRed( m_imageOrigin->pixel( x, y)   / pas * 2 + 1) * pas)) / 2;
                    G = ((qGreen( m_imageOrigin->pixel( x, y) / pas * 2 + 1) * pas)) / 2;
                    B = ((qBlue( m_imageOrigin->pixel( x, y)  / pas * 2 + 1) * pas)) / 2;

                    m_imageTreated->setPixel( x, y, qRgb( R, G, B));
                }
            }
        }
    }
}
