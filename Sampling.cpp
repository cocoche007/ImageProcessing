//------------------------------------------------------------------------------
//! @file Sampling.cpp
//! @brief Fichier o� la classe CSampling est d�finie
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <QLibrary>
#include "Sampling.h"
//#include "../../Commun/Maths/qrealfourier/include/qfouriertransformer.h"
//#include "../../Commun/Maths/fftw/fftw3.h"


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) :

//------------------------------------------------------------------------------
//! Constructeur d'objet CSampling pour une image donn�e
//!
//! @param imageIn : L'image d'entr�e
//!
//! @return L'objet cr��
//------------------------------------------------------------------------------
CSampling::CSampling( QImage *imageIn)
{
    m_imageOrigin  = imageIn;
    m_imageTreated = NULL;
}

//------------------------------------------------------------------------------
//! Destructeur
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
CSampling::~CSampling()
{
    delete m_imageTreated;
}

//------------------------------------------------------------------------------
//! Retourne l'image trait�e
//!
//! @param _
//!
//! @return Le pointeur sur l'image trait�e
//------------------------------------------------------------------------------
QImage* CSampling::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Calcul de la transform�e de fourier de l'image
//!
//! @param _
//!
//! @return Le pointeur sur l'image trait�e
//------------------------------------------------------------------------------
void CSampling::computeFourierTransform( void)
{
#ifdef TO_DO
    float     *ligneIn    = NULL;
    float     *ligneOut   = NULL;
    CImageInt *imageFloat = NULL;
    //QLibrary  *libFFTW    = NULL;
    int        widthIn    = 0;
    int        heightIn   = 0;
    int        G;

    if ( m_imageOrigin )
    {
        widthIn  = m_imageOrigin->width();
        heightIn = m_imageOrigin->height();

        //fftw_complex in[5], out[5];

        delete m_imageTreated;
        m_imageTreated = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);
        ligneIn        = new float[qMax( widthIn, heightIn)];
        ligneOut       = new float[qMax( widthIn, heightIn)];
        //libFFTW        = new QLibrary( "fftw3");
        imageFloat     = new CImageInt( widthIn, heightIn);

        if ( m_imageTreated && ligneIn && ligneOut && imageFloat /*&& libFFTW*/ )
        {
            for ( int x = 0 ; x < widthIn ; x++ )
            {
                for ( int y = 0 ; y < heightIn ; y++ )
                {
                    G = (   299 * qRed( m_imageOrigin->pixel( x, y))
                          + 587 * qGreen( m_imageOrigin->pixel( x, y))
                          + 114 * qBlue( m_imageOrigin->pixel( x, y)))
                        / 1000;
                    (*imageFloat)( x, y) = G;
                }
            }

            (*imageFloat)( 0, 0) = 0;
            (*imageFloat)( 0, 1) = 1;
            (*imageFloat)( 0, 2) = 2;
            (*imageFloat)( 0, 3) = 3;
            (*imageFloat)( 0, 4) = 4;
            (*imageFloat)( 0, 5) = 5;
            (*imageFloat)( 0, 6) = 6;
            (*imageFloat)( 0, 7) = 7;
            widthIn = 8;

            for ( int y = 0 ; y < heightIn ; y++ )
            {
                for ( int x = 0 ; x < widthIn ; x++ )
                    ligneIn[x] = (*imageFloat)( x, y);
                //fourierTransformer->forwardTransform( ligneIn, ligneOut);
                for ( int x = 0 ; x < widthIn ; x++ )
                     (*imageFloat)( x, y) = ligneOut[x];
            }

            int Gmax = 0;
            for ( int x = 0 ; x < widthIn ; x++ )
            {
                for ( int y = 0 ; y < heightIn ; y++ )
                {
                    G = qAbs( (int) (*imageFloat)( x, y));

                    if ( G > Gmax )
                        Gmax = G;
                }
            }

            for ( int x = 0 ; x < widthIn ; x++ )
            {
                for ( int y = 0 ; y < heightIn ; y++ )
                {
                     (*imageFloat)( x, y) = qAbs( (int) (*imageFloat)( x, y)) * 256 / Gmax;
                }
            }

            for ( int x = 0 ; x < widthIn ; x++ )
            {
                for ( int y = 0 ; y < heightIn ; y++ )
                {
                    G = qAbs( (int) (*imageFloat)( x, y)) * 256 / Gmax;
                    G = qAbs( (int) (*imageFloat)( x, y));

                    m_imageTreated->setPixel( x, y, qRgb( G, G, G));
                }
            }
        }

        delete ligneIn;
        delete ligneOut;
        delete imageFloat;
    }
#endif
}
