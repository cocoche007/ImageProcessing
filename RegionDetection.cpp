//------------------------------------------------------------------------------
//! @file RegionDetection.cpp
//! @brief Definition file of the CRegionDetection class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include "RegionDetection.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! CRegionDetection constructor for a given image
//!
//! @param imageIn The input image
//!
//! @return The created object
//------------------------------------------------------------------------------
CRegionDetection::CRegionDetection( QImage *imageIn)
{
    m_imageOrigin = imageIn;
    if ( m_imageOrigin )
    {
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);
        m_imageGray    = new CImageInt( m_imageOrigin->width(), m_imageOrigin->height());
    }
    
    createImageGray( m_imageOrigin, m_imageGray);

    if ( m_imageOrigin && m_imageTreated && m_imageGray )
        m_isValid = true;
    else
        m_isValid = false;
}

//------------------------------------------------------------------------------
//! Destructor
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
CRegionDetection::~CRegionDetection( void)
{
    delete m_imageTreated;
    delete m_imageGray;
}

//------------------------------------------------------------------------------
//! Get the treated image
//!
//! @param _
//!
//! @return A pointer on the treated image
//------------------------------------------------------------------------------
QImage* CRegionDetection::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Entry point for the region detection
//!
//! @param typeDetectionRegion The type of the region detection
//!
//! @return _
//------------------------------------------------------------------------------
void CRegionDetection::computeDetectionRegion( DETECTION_REGION_TYPE detectionRegionType)
{
    if ( m_isValid )
    {
        switch ( detectionRegionType )
        {
            case DETECTION_REGION_LINE :
                computeLine();
                break;

            case DETECTION_REGION_UNKNOWN :
            default :
                break;
        }
    }
}


//------------------------------------------------------------------------------
// Private Method(s):

//------------------------------------------------------------------------------
//! Create a grayscale (binary) image for a given image
//!
//! @param imageIn The input image
//! @param imageOut The output image
//!
//! @return _
//------------------------------------------------------------------------------
void CRegionDetection::createImageGray( QImage *imageIn, CImageInt *imageOut)
{
    int GOut;

    if ( imageIn && imageOut )
    {
        for ( int x = 0 ; x < imageIn->width() ; x++ )
        {
            for ( int y = 0 ; y < imageIn->height() ; y++ )
            {
                GOut = (  299 * qRed( imageIn->pixel( x, y))
                        + 587 * qGreen( imageIn->pixel( x, y))
                        + 114 * qBlue( imageIn->pixel( x, y)))
                       / 1000;

                if ( GOut < 128 )
                    (*imageOut)( x, y) = 0;
                else
                    (*imageOut)( x, y) = CIMAGEINT_MAX;
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Detect a line in the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CRegionDetection::computeLine( void)
{
    CImageInt *imageVote = NULL;
    int        aMin      = -m_imageOrigin->height();
    int        aMax      = 2 * m_imageOrigin->height() + 1;
    int        bMin      = -(2 * m_imageOrigin->height() + 1) * (m_imageOrigin->width() - 1);
    int        bMax      = m_imageOrigin->height() * m_imageOrigin->width() - 1;
    int        noVote    = 0;
    int        aWin;
    int        bWin;

    imageVote = new CImageInt( aMax-aMin+1, bMax-bMin+1);

    for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
    {
        for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
        {
            for ( int a = aMin ; a <= aMax ; a++ )
            {
                (*imageVote)(a-aMin, y - a * x - bMin)++;
            }
        }
    }

    for ( int a = aMin ; a <= aMax ; a++ )
    {
        for ( int b = bMin ; b <= bMax ; b++ )
        {
            if ( (*imageVote)( a-aMin, b-bMin) > noVote )
            {
                aWin = a;
                bWin = b;
            }
        }
    }

    CImage2QImage( imageVote, m_imageTreated);

    delete imageVote;
}

//------------------------------------------------------------------------------
//! Convert a CImageInt to a QImage
//!
//! @param imageIn The input image
//! @param imageOut The output image
//!
//! @return _
//------------------------------------------------------------------------------
void CRegionDetection::CImage2QImage( CImageInt *imageIn, QImage *imageOut)
{
    int GOut;

    if ( imageIn && imageOut )
    {
        for ( int xOut = 0 ; xOut < imageOut->width() ; xOut++ )
        {
            for ( int yOut = 0 ; yOut <  imageOut->height() ; yOut++ )
            {
                GOut = imageIn->get( xOut, yOut);
                imageOut->setPixel( xOut, yOut, qRgb( GOut, GOut, GOut));
            }
        }
    }
}
