//------------------------------------------------------------------------------
//! @file EdgeDetection.cpp
//! @brief Fichier où la classe CEdgeDetection est définie
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <qmath.h>
#include "EdgeDetection.h"


//------------------------------------------------------------------------------
// Variable(s) Constante(s) :

const int sobelMatrix1[3][3]            = { { 1,  2,  1}, { 0, 0,  0}, {-1, -2, -1} };
const int sobelMatrix2[3][3]            = { {-1,  0,  1}, {-2, 0,  2}, {-1,  0,  1} };
const int prewittMatrix1[3][3]          = { { 1,  1,  1}, { 0, 0,  0}, {-1, -1, -1} };
const int prewittMatrix2[3][3]          = { { 1,  1,  0}, { 1, 0, -1}, { 0, -1, -1} };
const int prewittMatrix3[3][3]          = { { 1,  0, -1}, { 1, 0, -1}, { 1,  0, -1} };
const int prewittMatrix4[3][3]          = { { 0, -1, -1}, { 1, 0, -1}, { 1,  1,  0} };
const int kirschMatrix1[3][3]           = { { 5,  5,  5}, {-3, 0, -3}, {-3, -3, -3} };
const int kirschMatrix2[3][3]           = { { 5,  5, -3}, { 5, 0, -3}, {-3, -3, -3} };
const int kirschMatrix3[3][3]           = { { 5, -3, -3}, { 5, 0, -3}, { 5, -3, -3} };
const int kirschMatrix4[3][3]           = { {-3, -3, -3}, { 5, 0, -3}, { 5,  5, -3} };
const int kirschMatrix5[3][3]           = { {-3, -3, -3}, {-3, 0, -3}, { 5,  5,  5} };
const int kirschMatrix6[3][3]           = { {-3, -3, -3}, {-3, 0,  5}, {-3,  5,  5} };
const int kirschMatrix7[3][3]           = { {-3, -3,  5}, {-3, 0,  5}, {-3, -3,  5} };
const int kirschMatrix8[3][3]           = { {-3,  5,  5}, {-3, 0,  5}, {-3, -3, -3} };
const int laplaceConnexityMatrix4[3][3] = { { 0, -1,  0}, {-1, 4, -1}, { 0, -1,  0} };
const int laplaceConnexityMatrix8[3][3] = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };
const int noyauGaussien3x3[3][3]        = { { 1,  1,  1}, { 1, 8,  1}, { 1,  1,  1} };


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) :

//------------------------------------------------------------------------------
//! Constructeur d'objet CEdgeDetection pour une image donnée
//!
//! @param imageIn : L'image d'entrée
//!
//! @return L'objet créé
//------------------------------------------------------------------------------
CEdgeDetection::CEdgeDetection( QImage *imageIn)
{
    m_imageOrigin = imageIn;
    if ( m_imageOrigin )
    {
        m_imageTreated       = new QImage( m_imageOrigin->size(), QImage::Format_RGB32);
        m_imageGray          = new CImageInt( m_imageOrigin->width(), m_imageOrigin->height());
        m_edgeDetectionImage = new CImageInt( m_imageOrigin->width(), m_imageOrigin->height());
    }
    m_detectionType = EDGE_DETECTION_UNKNOWN;
    m_isMonochrom   = false;
    m_thresholdMin  = 0;
    m_alphaDeriche  = 0;

    createImageGray( m_imageOrigin, m_imageGray);

    if ( m_imageOrigin && m_imageTreated && m_imageGray && m_edgeDetectionImage )
        m_isValid = true;
    else
        m_isValid = false;
}

//------------------------------------------------------------------------------
//! Destructeur
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
CEdgeDetection::~CEdgeDetection()
{
    delete m_imageTreated;
    delete m_imageGray;
    delete m_edgeDetectionImage;
}

//------------------------------------------------------------------------------
//! Retourne l'image traitée
//!
//! @param _
//!
//! @return Le pointeur sur l'image traitée
//------------------------------------------------------------------------------
QImage* CEdgeDetection::getImageTreated( void)
{
    return m_imageTreated;
}

//------------------------------------------------------------------------------
//! Retourne si le traitement est en monochrome ou non
//!
//! @param _
//!
//! @return true ou false
//------------------------------------------------------------------------------
bool CEdgeDetection::isMonochrom( void)
{
    return m_isMonochrom;
}

//------------------------------------------------------------------------------
//! Retourne le seuil minimum
//!
//! @param _
//!
//! @return Le seuil minimum
//------------------------------------------------------------------------------
int CEdgeDetection::getThresholdMin( void)
{
    return m_thresholdMin;
}

//------------------------------------------------------------------------------
//! Retourne le seuil maximum
//!
//! @param _
//!
//! @return Le seuil maximum
//------------------------------------------------------------------------------
int CEdgeDetection::getThresholdMax( void)
{
    return m_thresholdMax;
}

//------------------------------------------------------------------------------
//! Retourne la valeur alpha pour le lissage de Deriche
//!
//! @param _
//!
//! @return La valeur alpha
//------------------------------------------------------------------------------
float CEdgeDetection::getAlphaDeriche( void)
{
    return m_alphaDeriche;
}

//------------------------------------------------------------------------------
//! Affecte le seuil minimum
//!
//! @param Le seuil à affecter
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::setThresholdMin( int threshold)
{
    m_thresholdMin = threshold;
}

//------------------------------------------------------------------------------
//! Affecte le seuil maximum
//!
//! @param Le seuil à affecter
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::setThresholdMax( int threshold)
{
    m_thresholdMax = threshold;
}

//------------------------------------------------------------------------------
//! Affecte la valeur alpha pour le lissage de Deriche
//!
//! @param La valeur alpha à affecter
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::setAlphaDeriche( float alpha)
{
    if ( m_alphaDeriche != alpha )
    {
        m_alphaDeriche  = alpha;
        m_detectionType = EDGE_DETECTION_UNKNOWN;
    }
}

//------------------------------------------------------------------------------
//! Fonction d'entrée pour les détections de contour
//!
//! @param detectionType : Le type de détection
//! @param thresholdMin : Le seuil minimum
//! @param thresholdMax : Le seuil maximum
//! @param isMonochrom : Indication de traitement monochrome ou non
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetection( int detectionType, int thresholdMin, int thresholdMax, int isMonochrom)
{
    m_isMonochrom  = isMonochrom;
    m_thresholdMin = thresholdMin;
    m_thresholdMax = thresholdMax;

    if ( m_isValid )
    {
        if ( m_detectionType != detectionType )
        {
            m_detectionType = detectionType;
            switch ( detectionType )
            {
                case EDGE_DETECTION_SIMPLE :
                    computeEdgeDetectionSimple( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_ROBERTS :
                    computeEdgeDetectionRoberts( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_SOBEL :
                    computeEdgeDetectionSobel( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_PREWITT :
                    computeEdgeDetectionPrewitt( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_KIRSCH :
                    computeEdgeDetectionKirsch( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_LAPLACIAN_CONNEXITY_4 :
                    computeEdgeDetectionLaplacianConnexity4( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_LAPLACIAN_CONNEXITY_8 :
                    computeEdgeDetectionLaplacianConnexity8( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_LAPLACIAN_DOG :
                    computeEdgeDetectionLaplacianDOG( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_DERICHE_SMOOTH :
                    computeEdgeDetectionDericheSmooth( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_DERICHE_DERIVATIVE :
                    computeEdgeDetectionDericheDerivative( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_DERICHE_LAPLACIAN :
                    computeEdgeDetectionDericheLaplacian( m_imageGray, m_edgeDetectionImage);
                    break;

                case EDGE_DETECTION_UNKNOWN :
                default :
                    break;
            }
        }

        thresholding( m_edgeDetectionImage, m_imageTreated, m_isMonochrom, m_thresholdMin, m_thresholdMax);
    }
}


//------------------------------------------------------------------------------
// Fonction(s) Privée(s) :

//------------------------------------------------------------------------------
//! Création d'une image en niveau de gris (binaire) pour une image donnée
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::createImageGray( QImage *imageIn, CImageInt *imageOut)
{
    if ( imageIn && imageOut )
    {
        for ( int x = 0 ; x < imageIn->width() ; x++ )
        {
            for ( int y = 0 ; y < imageIn->height() ; y++ )
            {
                (*imageOut)( x, y) = (  299 * qRed( imageIn->pixel( x, y))
                                      + 587 * qGreen( imageIn->pixel( x, y))
                                      + 114 * qBlue( imageIn->pixel( x, y)))
                                     / 1000;
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de la convolution en un point de l'image pour une matrice[3][3]
//!
//! @param imageIn : L'image d'entrée
//! @param x : La coordonnée x du point considérée
//! @param y : La coordonnée y du point considérée
//! @param matrix : La matrice de convolution
//! @param quotient : Le quotient de "normalisation"
//!
//! @return _
//------------------------------------------------------------------------------
int CEdgeDetection::convolution( CImageInt *imageIn, int x, int y, const int matrix[3][3], int quotient)
{
   int ret = 0;

   if ( imageIn && matrix )
   {
       ret =   matrix[0][0] * imageIn->get( x-1, y-1)
             + matrix[0][1] * imageIn->get( x-1, y  )
             + matrix[0][2] * imageIn->get( x-1, y+1)
             + matrix[1][0] * imageIn->get( x  , y-1)
             + matrix[1][1] * imageIn->get( x  , y  )
             + matrix[1][2] * imageIn->get( x  , y+1)
             + matrix[2][0] * imageIn->get( x+1, y-1)
             + matrix[2][1] * imageIn->get( x+1, y  )
             + matrix[2][2] * imageIn->get( x+1, y+1);

       if ( quotient )
           ret /= quotient;
   }

   return ret;
}

//------------------------------------------------------------------------------
//! Seuillage d'une image
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//! @param isMonochrom : Indication de traitement monochrome ou non
//! @param thresholdMin : Le seuil minimum
//! @param thresholdMax : Le seuil maximum
//!
//! @return true si OK
//! @return false sinon
//------------------------------------------------------------------------------
bool CEdgeDetection::thresholding( CImageInt *imageIn, QImage *imageOut, bool isMonochrom, int thresholdMin, int thresholdMax)
{
    bool ret = false;
    int  GOut;

    if ( imageIn && imageOut )
    {
        if ( imageIn->getMax() )
        {
            ret = true;

            for ( int xOut = 0 ; xOut < imageOut->width() ; xOut++ )
            {
                for ( int yOut = 0 ; yOut < imageOut->height() ; yOut++ )
                {
                    GOut = imageIn->get( xOut, yOut) * 255 / imageIn->getMax();

                    if ( GOut < thresholdMin )
                        GOut = 0;
                    else if ( GOut < thresholdMax )
                    {
                        if (    (imageIn->get( xOut-1, yOut-1) < thresholdMax)
                             && (imageIn->get( xOut  , yOut-1) < thresholdMax)
                             && (imageIn->get( xOut+1, yOut-1) < thresholdMax)
                             && (imageIn->get( xOut-1, yOut  ) < thresholdMax)
                             && (imageIn->get( xOut+1, yOut  ) < thresholdMax)
                             && (imageIn->get( xOut-1, yOut+1) < thresholdMax)
                             && (imageIn->get( xOut  , yOut+1) < thresholdMax)
                             && (imageIn->get( xOut+1, yOut+1) < thresholdMax) )
                            GOut = 0;
                    }

                    if ( isMonochrom && GOut )
                        GOut = 255;

                    imageOut->setPixel( xOut, yOut, qRgb( GOut, GOut, GOut));
                }
            }
        }
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour naïf
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionSimple( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1, K2;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() ; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() ; y++ )
            {
                K1 = imageIn->get( x, y) - imageIn->get( x-1, y);
                K2 = imageIn->get( x, y) - imageIn->get( x  , y-1);

                (*imageOut)( x, y) = qSqrt( K1*K1 + K2*K2);

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Roberts)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionRoberts( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1, K2;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = imageIn->get( x  , y+1) - imageIn->get( x+1, y);
                K2 = imageIn->get( x+1, y+1) - imageIn->get( x  , y);

                (*imageOut)( x, y) = qSqrt( K1*K1 + K2*K2);

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Sobel)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionSobel( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1, K2;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = convolution( imageIn, x, y, sobelMatrix1, 4);
                K2 = convolution( imageIn, x, y, sobelMatrix2, 4);

                (*imageOut)( x, y) = qSqrt( K1*K1 + K2*K2);

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Prewitt)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionPrewitt( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1, K2, K3, K4;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = convolution( imageIn, x, y, prewittMatrix1, 3);
                K2 = convolution( imageIn, x, y, prewittMatrix2, 3);
                K3 = convolution( imageIn, x, y, prewittMatrix3, 3);
                K4 = convolution( imageIn, x, y, prewittMatrix4, 3);

                (*imageOut)( x, y) = qMax( qAbs( K1), qAbs( K2));
                (*imageOut)( x, y) = qMax( qAbs( K3), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K4), imageOut->get( x, y));

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Kirsch)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionKirsch( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1, K2, K3, K4, K5, K6, K7, K8;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = convolution( imageIn, x, y, kirschMatrix1, 15);
                K2 = convolution( imageIn, x, y, kirschMatrix2, 15);
                K3 = convolution( imageIn, x, y, kirschMatrix3, 15);
                K4 = convolution( imageIn, x, y, kirschMatrix4, 15);
                K5 = convolution( imageIn, x, y, kirschMatrix5, 15);
                K6 = convolution( imageIn, x, y, kirschMatrix6, 15);
                K7 = convolution( imageIn, x, y, kirschMatrix7, 15);
                K8 = convolution( imageIn, x, y, kirschMatrix8, 15);

                (*imageOut)( x, y) = qMax( qAbs( K1), qAbs( K2));
                (*imageOut)( x, y) = qMax( qAbs( K3), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K4), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K5), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K6), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K7), imageOut->get( x, y));
                (*imageOut)( x, y) = qMax( qAbs( K8), imageOut->get( x, y));

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Laplacien Connexité 4)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionLaplacianConnexity4( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = convolution( imageIn, x, y, laplaceConnexityMatrix4, 4);

                (*imageOut)( x, y) = qAbs( K1);

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Laplacien Connexité 8)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionLaplacianConnexity8( CImageInt *imageIn, CImageInt *imageOut)
{
    int K1;

    if ( imageIn && imageOut )
    {
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {
                K1 = convolution( imageIn, x, y, laplaceConnexityMatrix8, 8);

                (*imageOut)( x, y) = qAbs( K1);

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
    }
}

//------------------------------------------------------------------------------
//! Calcul de détection de contour (Laplacien DOG)
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionLaplacianDOG( CImageInt *imageIn, CImageInt *imageOut)
{

    if ( imageIn && imageOut )
    {
#ifdef TO_DO
        imageOut->setMax( 0);
        for ( int x = 1 ; x < m_imageOrigin->width() - 1; x++ )
        {
            for ( int y = 1 ; y < m_imageOrigin->height() - 1; y++ )
            {

                if ( imageOut->getMax() < imageOut->get( x, y) )
                    imageOut->setMax( imageOut->get( x, y));
            }
        }
#endif
    }
}

//------------------------------------------------------------------------------
//! Calcul de lissage de Deriche
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionDericheSmooth( CImageInt *imageIn, CImageInt *imageOut)
{
    CImageFloat *imageY1 = NULL;
    CImageFloat *imageY2 = NULL;
    CImageFloat *imageR  = NULL;
    float        k;
    float        a1, a2, a3, a4;
    float        a5, a6, a7, a8;
    float        b1, b2;
    float        c1, c2;

    if ( imageIn && imageOut )
    {
        imageY1 = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageY2 = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageR  = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());

        if ( imageY1 && imageY2 && imageR )
        {
            imageOut->setMax( 0);

            if ( 1 + 2*m_alphaDeriche*qExp( -m_alphaDeriche) - qExp( -2*m_alphaDeriche) )
                k = ((1 - qExp( -m_alphaDeriche))*(1 - qExp( -m_alphaDeriche))) / (1 + 2*m_alphaDeriche*qExp( -m_alphaDeriche) - qExp( -2*m_alphaDeriche));
            else
                k = 0;

            a1 = k;
            a2 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche - 1);
            a3 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche + 1);
            a4 = -k * qExp( -2*m_alphaDeriche);

            a5 = k;
            a6 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche - 1);
            a7 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche + 1);
            a8 = -k * qExp( -2*m_alphaDeriche);

            b1 = 2*qExp( -m_alphaDeriche);
            b2 = -qExp( -2*m_alphaDeriche);

            c1 = 1;
            c2 = 1;

            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageY1)( x, y) = a1*m_imageGray->get( x, y) + a2*m_imageGray->get( x, y-1) + b1*imageY1->get( x, y-1) + b2*imageY1->get( x, y-2);

                for ( int y = m_imageOrigin->height() - 1 ; y >= 0 ; y-- )
                    (*imageY2)( x, y) = a3*m_imageGray->get( x, y+1) + a4*m_imageGray->get( x, y+2) + b1*imageY2->get( x, y+1) + b2*imageY2->get( x, y+2);

                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageR)( x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
            {
                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageY1)( x, y) = a5*imageR->get( x, y) + a6*imageR->get( x-1, y) + b1*imageY1->get( x-1, y) + b2*imageY1->get( x-2, y);

                for ( int x = m_imageOrigin->width() - 1 ; x >= 0 ; x-- )
                    (*imageY2)( x, y) = a7*imageR->get( x+1, y) + a8*imageR->get( x+2, y) + b1*imageY2->get( x+1, y) + b2*imageY2->get( x+2, y);

                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                {
                    (*imageOut)(x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
                    if ( imageOut->getMax() < imageOut->get( x, y) )
                        imageOut->setMax( imageOut->get( x, y));
                }
            }
        }

        delete imageY1;
        delete imageY2;
        delete imageR;
    }
}

//------------------------------------------------------------------------------
//! Calcul de Deriche dérivée
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionDericheDerivative( CImageInt *imageIn, CImageInt *imageOut)
{
    CImageFloat *imageY1          = NULL;
    CImageFloat *imageY2          = NULL;
    CImageFloat *imageR           = NULL;
    CImageFloat *imageDerivativeX = NULL;
    CImageFloat *imageDerivativeY = NULL;
    float        k;
    float        a1, a2, a3, a4;
    float        a5, a6, a7, a8;
    float        b1, b2;
    float        c1, c2;

    if ( imageIn && imageOut )
    {
        imageY1          = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageY2          = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageR           = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageDerivativeX = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageDerivativeY = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());

        if ( imageY1 && imageY2 && imageR && imageDerivativeX && imageDerivativeY )
        {
            imageOut->setMax( 0);

            // Calcul de l'image dérivée selon x
            if ( 1 + 2*m_alphaDeriche*qExp( -m_alphaDeriche) - qExp( -2*m_alphaDeriche) )
                k = ((1 - qExp( -m_alphaDeriche))*(1 - qExp( -m_alphaDeriche))) / (1 + 2*m_alphaDeriche*qExp( -m_alphaDeriche) - qExp( -2*m_alphaDeriche));
            else
                k = 0;

            a1 = 0;
            a2 = 1;
            a3 = -1;
            a4 = 0;

            a5 = k;
            a6 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche - 1);
            a7 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche + 1);
            a8 = -k * qExp( -2*m_alphaDeriche);

            b1 = 2*qExp( -m_alphaDeriche);
            b2 = -qExp( -2*m_alphaDeriche);

            c1 = -(1-qExp(-m_alphaDeriche)) * (1-qExp(-m_alphaDeriche));
            c2 = 1;

            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageY1)( x, y) = a1*m_imageGray->get( x, y) + a2*m_imageGray->get( x, y-1) + b1*imageY1->get( x, y-1) + b2*imageY1->get( x, y-2);

                for ( int y = m_imageOrigin->height() - 1 ; y >= 0 ; y-- )
                    (*imageY2)( x, y) = a3*m_imageGray->get( x, y+1) + a4*m_imageGray->get( x, y+2) + b1*imageY2->get( x, y+1) + b2*imageY2->get( x, y+2);

                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageR)( x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
            {
                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageY1)( x, y) = a5*imageR->get( x, y) + a6*imageR->get( x-1, y) + b1*imageY1->get( x-1, y) + b2*imageY1->get( x-2, y);

                for ( int x = m_imageOrigin->width() - 1 ; x >= 0 ; x-- )
                    (*imageY2)( x, y) = a7*imageR->get( x+1, y) + a8*imageR->get( x+2, y) + b1*imageY2->get( x+1, y) + b2*imageY2->get( x+2, y);

                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageDerivativeX)(x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            // Calcul de l'image dérivée selon y
            a1 = k;
            a2 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche - 1);
            a3 = k * qExp( -m_alphaDeriche) * (m_alphaDeriche + 1);
            a4 = -k * qExp( -2*m_alphaDeriche);

            a5 = 0;
            a6 = 1;
            a7 = -1;
            a8 = 0;

            b1 = 2*qExp( -m_alphaDeriche);
            b2 = -qExp( -2*m_alphaDeriche);

            c1 = 1;
            c2 = -(1-qExp(-m_alphaDeriche)) * (1-qExp(-m_alphaDeriche));

            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageY1)( x, y) = a1*m_imageGray->get( x, y) + a2*m_imageGray->get( x, y-1) + b1*imageY1->get( x, y-1) + b2*imageY1->get( x, y-2);

                for ( int y = m_imageOrigin->height() - 1 ; y >= 0 ; y-- )
                    (*imageY2)( x, y) = a3*m_imageGray->get( x, y+1) + a4*m_imageGray->get( x, y+2) + b1*imageY2->get( x, y+1) + b2*imageY2->get( x, y+2);

                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageR)( x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
            {
                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageY1)( x, y) = a5*imageR->get( x, y) + a6*imageR->get( x-1, y) + b1*imageY1->get( x-1, y) + b2*imageY1->get( x-2, y);

                for ( int x = m_imageOrigin->width() - 1 ; x >= 0 ; x-- )
                    (*imageY2)( x, y) = a7*imageR->get( x+1, y) + a8*imageR->get( x+2, y) + b1*imageY2->get( x+1, y) + b2*imageY2->get( x+2, y);

                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageDerivativeY)(x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }


            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    (*imageOut)(x, y) = qSqrt( (imageDerivativeX->get( x, y) * imageDerivativeX->get( x, y)) + (imageDerivativeY->get( x, y) * imageDerivativeY->get( x, y)));
                    if ( imageOut->getMax() < imageOut->get( x, y) )
                        imageOut->setMax( imageOut->get( x, y));

                }
            }
        }

        delete imageY1;
        delete imageY2;
        delete imageR;
        delete imageDerivativeX;
        delete imageDerivativeY;
    }
 }

//------------------------------------------------------------------------------
//! Calcul de lissage de Deriche Laplacien
//!
//! @param imageIn : L'image d'entrée
//! @param imageOut : L'image de sortie
//!
//! @return _
//------------------------------------------------------------------------------
void CEdgeDetection::computeEdgeDetectionDericheLaplacian( CImageInt *imageIn, CImageInt *imageOut)
{
#ifdef TO_DO
    CImageFloat *imageY1         = NULL;
    CImageFloat *imageY2         = NULL;
    CImageFloat *imageR          = NULL;
    CImageFloat *imageLaplacian1 = NULL;
    CImageFloat *imageLaplacian2 = NULL;
    float        k;
    float        a1, a2, a3, a4;
    float        a5, a6, a7, a8;
    float        b1, b2;
    float        c1, c2;

    if ( imageIn && imageOut )
    {
        imageY1         = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageY2         = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageR          = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageLaplacian1 = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());
        imageLaplacian2 = new CImageFloat( m_imageTreated->width(), m_imageTreated->height());

        if ( imageY1 && imageY2 && imageR && imageLaplacian1 && imageLaplacian2 )
        {
            imageOut->setMax( 0);

            // Calcul de l'image Laplacien 1
            if ( 2*m_alphaDeriche*qExp( -m_alphaDeriche) )
                k = (1 - qExp( -2*m_alphaDeriche)) / (2*m_alphaDeriche*qExp( -m_alphaDeriche));
            else
                k = 0;

            a1 = 1;
            a2 = 0;
            a3 = qExp( -m_alphaDeriche);
            a4 = 0;

            a5 = 1;
            a6 = 0;
            a7 = qExp( -m_alphaDeriche);
            a8 = 0;

            b1 = qExp( -m_alphaDeriche);
            b2 = 0;

            c1 = 1;
            c2 = 1;

            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageY1)( x, y) = a1*m_imageGray->get( x, y) + a2*m_imageGray->get( x, y-1) + b1*imageY1->get( x, y-1) + b2*imageY1->get( x, y-2);

                for ( int y = m_imageOrigin->height() - 1 ; y >= 0 ; y-- )
                    (*imageY2)( x, y) = a3*m_imageGray->get( x, y+1) + a4*m_imageGray->get( x, y+2) + b1*imageY2->get( x, y+1) + b2*imageY2->get( x, y+2);

                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageR)( x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
            {
                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageY1)( x, y) = a5*imageR->get( x, y) + a6*imageR->get( x-1, y) + b1*imageY1->get( x-1, y) + b2*imageY1->get( x-2, y);

                for ( int x = m_imageOrigin->width() - 1 ; x >= 0 ; x-- )
                    (*imageY2)( x, y) = a7*imageR->get( x+1, y) + a8*imageR->get( x+2, y) + b1*imageY2->get( x+1, y) + b2*imageY2->get( x+2, y);

                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageLaplacian1)(x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            // Calcul de l'image Laplacien 2
            /*
            a1 = 0;
            a2 = 1;
            a3 = 1;
            a4 = 0;

            a5 = 0;
            a6 = 1;
            a7 = 1;
            a8 = 0;

            b1 = 2*qExp( -m_alphaDeriche);
            b2 = -qExp( -2*m_alphaDeriche);

            c1 = (1 - qExp( -2*m_alphaDeriche)) / 2;
            c2 = (1 - qExp( -2*m_alphaDeriche)) / 2;

            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageY1)( x, y) = a1*m_imageGray->get( x, y) + a2*m_imageGray->get( x, y-1) + b1*imageY1->get( x, y-1) + b2*imageY1->get( x, y-2);

                for ( int y = m_imageOrigin->height() - 1 ; y >= 0 ; y-- )
                    (*imageY2)( x, y) = a3*m_imageGray->get( x, y+1) + a4*m_imageGray->get( x, y+2) + b1*imageY2->get( x, y+1) + b2*imageY2->get( x, y+2);

                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                    (*imageR)( x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }

            for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
            {
                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageY1)( x, y) = a5*imageR->get( x, y) + a6*imageR->get( x-1, y) + b1*imageY1->get( x-1, y) + b2*imageY1->get( x-2, y);

                for ( int x = m_imageOrigin->width() - 1 ; x >= 0 ; x-- )
                    (*imageY2)( x, y) = a7*imageR->get( x+1, y) + a8*imageR->get( x+2, y) + b1*imageY2->get( x+1, y) + b2*imageY2->get( x+2, y);

                for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
                    (*imageLaplacian2)(x, y) = c1 * (imageY1->get( x, y) + imageY2->get( x, y));
            }
            */


            for ( int x = 0 ; x < m_imageOrigin->width() ; x++ )
            {
                for ( int y = 0 ; y < m_imageOrigin->height() ; y++ )
                {
                    (*imageOut)( x, y) = qAbs( imageLaplacian1->get( x, y));
                    if ( imageOut->getMax() < imageOut->get( x, y) )
                        imageOut->setMax( imageOut->get( x, y));
                }
            }
        }

        delete imageY1;
        delete imageY2;
        delete imageR;
        delete imageLaplacian1;
        delete imageLaplacian2;
    }
#endif
}
