//------------------------------------------------------------------------------
//! @file Quantisation.cpp
//! @brief Fichier où la classe CQuantisation est définie
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include "Quantisation.h"


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) :

//------------------------------------------------------------------------------
//! Constructeur d'objet CQuantisation pour une image donnée
//!
//! @param imageIn : L'image d'entrée
//!
//! @return L'objet créé
//------------------------------------------------------------------------------
CQuantisation::CQuantisation( QImage *imageIn)
{
    m_imageOrigin = imageIn;
    m_imageTreated = NULL;
}

//------------------------------------------------------------------------------
//! Destructeur
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
//! Retourne l'image traitée
//!
//! @param _
//!
//! @return Le pointeur sur l'image traitée
//------------------------------------------------------------------------------
QImage* CQuantisation::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Calcul de l'image quantifiée en niveau de gris
//!
//! @param quantisationLevel : Le niveau de quantification
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
//! Calcul de l'image quantifiée en couleur
//!
//! @param quantisationLevel : Le niveau de quantification
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
