//------------------------------------------------------------------------------
//! @file TreatedImageWindow.cpp
//! @brief Fichier où la classe CTreatedImageWindow est définie
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <QMessageBox>
#include "TreatedImageWindow.h"


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) :

//------------------------------------------------------------------------------
//! Constructeur d'objet CTreatedImageWindow pour une image donnée
//!
//! @param type : Le type de traitement
//! @param imageIn : L'image d'entrée
//! @param parent : Le widget parent
//!
//! @return L'objet créé
//------------------------------------------------------------------------------
CTreatedImageWindow::CTreatedImageWindow( int type, QImage *imageIn, QWidget *parent) :
    QWidget( parent)
{
    bool ret = false;

    if ( imageIn != NULL )
    {
        m_imageOrigin = imageIn;

        if ( m_imageOrigin->width() && m_imageOrigin->height() )
        {
            m_processingType = type;
            switch ( m_processingType )
            {
                case PROCESSING_COLOR_MODEL_COMPONENT_Y :
                case PROCESSING_COLOR_MODEL_COMPONENT_U :
                case PROCESSING_COLOR_MODEL_COMPONENT_V :
                    ret = initColorModel();
                    break;

                case PROCESSING_QUANTISATION_GRAY :
                case PROCESSING_QUANTISATION_RGB :
                    ret = initQuantisation();
                    break;

                case PROCESSING_SAMPLING :
                    ret = initSampling();
                    break;

                case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION :
                case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE :
                case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR :
                    ret = initGeometricTransformation();
                    break;

                case PROCESSING_EDGE_DETECTION_SIMPLE :
                case PROCESSING_EDGE_DETECTION_ROBERTS :
                case PROCESSING_EDGE_DETECTION_SOBEL :
                case PROCESSING_EDGE_DETECTION_PREWITT :
                case PROCESSING_EDGE_DETECTION_KIRSCH :
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4 :
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8 :
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG :
                case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH :
                case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE :
                case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN :
                    ret = initEdgeDetection();
                    break;

                case PROCESSING_OP_MORPHO_MATHS_DILATION :
                case PROCESSING_OP_MORPHO_MATHS_EROSION :
                case PROCESSING_OP_MORPHO_MATHS_OPENING :
                case PROCESSING_OP_MORPHO_MATHS_CLOSING :
                case PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT :
                case PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT :
                case PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT :
                case PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS :
                case PROCESSING_OP_MORPHO_MATHS_THINNING :
                case PROCESSING_OP_MORPHO_MATHS_SKELETONIZING :
                    ret = initOpMorphoMaths();
                    break;

                case PROCESSING_REGION_DETECTION_LINE :
                    ret = initRegionDetection();
                    break;

                default :
                    break;
            }

            if ( !ret )
                m_processingType = PROCESSING_UNKNOWN;
        }
        else
            QMessageBox::critical( this, tr( ""), tr( "Veuillez ouvrir une image"));
    }
    else
        QMessageBox::critical( this, tr( ""), tr( "Erreur d'allocation mémoire"));
}

//------------------------------------------------------------------------------
//! Affichage d'entrée
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::display( void)
{
    switch ( m_processingType )
    {
        case PROCESSING_COLOR_MODEL_COMPONENT_Y :
            displayComponentY();
            break;

        case PROCESSING_COLOR_MODEL_COMPONENT_U :
            displayComponentU();
            break;

        case PROCESSING_COLOR_MODEL_COMPONENT_V :
            displayComponentV();
            break;

        case PROCESSING_QUANTISATION_GRAY :
            displayQuantisationGray();
            break;

        case PROCESSING_QUANTISATION_RGB :
            displayQuantisationRGB();
            break;

        case PROCESSING_SAMPLING :
            displayFourierTransform();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION :
            displayRotation();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE :
            displayScale();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR :
            displayShear();
            break;

        case PROCESSING_EDGE_DETECTION_SIMPLE :
            displayEdgeDetectionSimple();
            break;

        case PROCESSING_EDGE_DETECTION_ROBERTS :
            displayEdgeDetectionRoberts();
            break;

        case PROCESSING_EDGE_DETECTION_SOBEL :
            displayEdgeDetectionSobel();
            break;

        case PROCESSING_EDGE_DETECTION_PREWITT :
            displayEdgeDetectionPrewitt();
            break;

        case PROCESSING_EDGE_DETECTION_KIRSCH :
            displayEdgeDetectionKirsch();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4 :
            displayEdgeDetectionLaplacianConnexity4();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8 :
            displayEdgeDetectionLaplacianConnexity8();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG :
            displayEdgeDetectionLaplacianDOG();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH :
            displayEdgeDetectionDericheSmooth();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE :
            displayEdgeDetectionDericheDerivative();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN :
            displayEdgeDetectionDericheLaplacian();
            break;

        case PROCESSING_OP_MORPHO_MATHS_DILATION :
            displayOpMorphoMathsDilation();
            break;

        case PROCESSING_OP_MORPHO_MATHS_EROSION :
            displayOpMorphoMathsErosion();
            break;

        case PROCESSING_OP_MORPHO_MATHS_OPENING :
            displayOpMorphoMathsOpening();
            break;

        case PROCESSING_OP_MORPHO_MATHS_CLOSING :
            displayOpMorphoMathsClosing();
            break;

        case PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT :
            displayOpMorphoMathsInteriorGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT :
            displayOpMorphoMathsExteriorGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT :
            displayOpMorphoMathsMorphologicalGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS :
            displayOpMorphoMathsHitOrMiss();
            break;

        case PROCESSING_OP_MORPHO_MATHS_THINNING :
            displayOpMorphoMathsThinning();
            break;

        case PROCESSING_OP_MORPHO_MATHS_SKELETONIZING :
            displayOpMorphoMathsSkeletonizing();
            break;

        case PROCESSING_REGION_DETECTION_LINE :
            displayRegionDetectionLine();
            break;

        default :
            break;
    }
}

//------------------------------------------------------------------------------
//! Affichage de la composante Y de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentY( void)
{
    if ( m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_Y )
    {
        m_colorModel->computeComponentY();

        m_labelImage->setPixmap( QPixmap::fromImage( *m_colorModel->getImageTreated()));
        setWindowTitle( tr( "Composante Y"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la composante U de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentU( void)
{
    if ( m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_U )
    {
        m_colorModel->computeComponentU();

        m_labelImage->setPixmap( QPixmap::fromImage( *m_colorModel->getImageTreated()));
        setWindowTitle( tr( "Composante U"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la composante V de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentV( void)
{
    if ( m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_V )
    {
        m_colorModel->computeComponentV();

        m_labelImage->setPixmap( QPixmap::fromImage( *m_colorModel->getImageTreated()));
        setWindowTitle( tr( "Composante V"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la quantification en niveau de gris de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayQuantisationGray( void)
{
    if ( m_processingType == PROCESSING_QUANTISATION_GRAY )
    {
        m_quantisation->computeGrayQuantisation( m_quantisationLevel);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_quantisation->getImageTreated()));
        setWindowTitle( tr( "Quantification Gris"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la quantification en couleur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayQuantisationRGB( void)
{
    if ( m_processingType == PROCESSING_QUANTISATION_RGB )
    {
        m_quantisation->computeRGBQuantisation( m_quantisationLevel);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_quantisation->getImageTreated()));
        setWindowTitle( tr( "Quantification RGB"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la Transformée de Fourier de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayFourierTransform( void)
{
    if ( m_processingType == PROCESSING_SAMPLING )
    {
        m_sampling->computeFourierTransform();

        m_labelImage->setPixmap( QPixmap::fromImage( *m_sampling->getImageTreated()));
        setWindowTitle( tr( "Transformée de Fourier"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la rotation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayRotation( void)
{
    if ( m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION )
    {
        m_geometricTransformation->computeRotation( m_rotationAngle);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_geometricTransformation->getImageTreated()));
        setWindowTitle( tr( "Rotation"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de l'homothétie de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayScale( void)
{
    if ( m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE )
    {
        m_geometricTransformation->computeScale( m_scaleFactor);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_geometricTransformation->getImageTreated()));
        setWindowTitle( tr( "Homothétie"));
    }
}

//------------------------------------------------------------------------------
//! Affichage du cisaillement de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayShear( void)
{
    if ( m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR )
    {
        m_geometricTransformation->computeShear( m_shearFactorX, m_shearFactorY);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_geometricTransformation->getImageTreated()));
        setWindowTitle( tr( "Cisaillement"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours naïve de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionSimple( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_SIMPLE )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_SIMPLE, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Naïf"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Roberts) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionRoberts( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_ROBERTS )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_ROBERTS, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Roberts"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Sobel) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionSobel( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_SOBEL )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_SOBEL, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Sobel"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Prewitt) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionPrewitt( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_PREWITT )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_PREWITT, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Prewitt"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Kirsch) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionKirsch( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_KIRSCH )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_KIRSCH, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Kirsch"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien Connexité 4)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianConnexity4( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4 )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_LAPLACIAN_CONNEXITY_4, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Laplacian Connexité 4"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien Connexité 8)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianConnexity8( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8 )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_LAPLACIAN_CONNEXITY_8, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Laplacian Connexité 8"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien DOG) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianDOG( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG )
    {
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_LAPLACIAN_DOG, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Laplacian DOG"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Lissage)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheSmooth( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH )
    {
        m_edgeDetection->setAlphaDeriche( (float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_DERICHE_SMOOTH, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Deriche Smooth"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Dérivée)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheDerivative( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE )
    {
        m_edgeDetection->setAlphaDeriche( (float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_DERICHE_DERIVATIVE, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Deriche Dérivée"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Laplacien)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheLaplacian( void)
{
    if ( m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN )
    {
        m_edgeDetection->setAlphaDeriche( (float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection( EDGE_DETECTION_DERICHE_LAPLACIAN, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_edgeDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Contours Deriche Laplacian"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la dilatation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsDilation( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_DILATION )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_DILATION, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Dilatation"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de l'érosion de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsErosion( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_EROSION )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_EROSION, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Erosion"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de l'ouverture de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsOpening( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_OPENING )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_OPENING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Ouverture"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la fermeture de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsClosing( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_CLOSING )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_CLOSING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Fermeture"));
    }
}

//------------------------------------------------------------------------------
//! Affichage du contour intérieur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsInteriorGradient( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_INTERIOR_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Contour intérieur"));
    }
}

//------------------------------------------------------------------------------
//! Affichage du contour extérieur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsExteriorGradient( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_EXTERIOR_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Contour extérieur"));
    }
}

//------------------------------------------------------------------------------
//! Affichage du gradient morphologique de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsMorphologicalGradient( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_MORPHOLOGICAL_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Gradient morphologique"));
    }
}

//------------------------------------------------------------------------------
//! Affichage du "Tout ou rien" de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsHitOrMiss( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_HIT_OR_MISS, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Tout ou rien"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de l'amincissement de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsThinning( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_THINNING )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_THINNING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Amincissement"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la squelettisation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsSkeletonizing( void)
{
    if ( m_processingType == PROCESSING_OP_MORPHO_MATHS_SKELETONIZING )
    {
        m_opMorphoMaths->computeOpMorphoMaths( OPMORPHOMATHS_SKELETONIZING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_opMorphoMaths->getImageTreated()));
        setWindowTitle( tr( "Squelettisation"));
    }
}

//------------------------------------------------------------------------------
//! Affichage de la détection d'une droite de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayRegionDetectionLine( void)
{
    if ( m_processingType == PROCESSING_REGION_DETECTION_LINE )
    {
        m_regionDetection->computeDetectionRegion( DETECTION_REGION_LINE);

        m_labelImage->setPixmap( QPixmap::fromImage( *m_regionDetection->getImageTreated()));
        setWindowTitle( tr( "Détection Droite"));
    }
}

//------------------------------------------------------------------------------
// Fonction Privée(s) :

//------------------------------------------------------------------------------
//! Initialisation du traitement "Modèle de couleur"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initColorModel( void)
{
    bool ret = false;

    m_vboxLayout = new QVBoxLayout;
    m_labelImage = new QLabel( this);
    m_colorModel = new CColorModel( m_imageOrigin);

    if ( m_vboxLayout && m_labelImage && m_colorModel )
    {
        ret = true;

        m_vboxLayout->addWidget( m_labelImage);
        setLayout( m_vboxLayout);
        show();
    }

   return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Quantification"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initQuantisation( void)
{
    bool ret = false;

    m_vboxLayout        = new QVBoxLayout;
    m_hboxLayout        = new QHBoxLayout;
    m_labelImage        = new QLabel( this);
    m_levelText         = new QLineEdit( tr( "Niveau Quantification :"));
    m_levelChoice       = new QSpinBox();
    m_quantisation      = new CQuantisation( m_imageOrigin);
    m_quantisationLevel = 1;

    if ( m_vboxLayout && m_hboxLayout && m_labelImage && m_levelText && m_levelChoice && m_quantisation )
    {
        ret = true;

        m_levelText->setReadOnly( true);
        m_levelChoice->setRange( 1, 8);
        m_levelChoice->setValue( m_quantisationLevel);

        connect( m_levelChoice, SIGNAL( valueChanged(int)), this, SLOT( updateQuantisationLevel( int)));

        m_hboxLayout->addWidget( m_levelText);
        m_hboxLayout->addWidget( m_levelChoice);
        m_vboxLayout->addLayout( m_hboxLayout);
        m_vboxLayout->addWidget( m_labelImage);
        setLayout( m_vboxLayout);
        show();
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Echantillonnage"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initSampling( void)
{
    bool ret = false;

    m_vboxLayout = new QVBoxLayout;
    m_labelImage = new QLabel( this);
    m_sampling   = new CSampling( m_imageOrigin);

    if ( m_vboxLayout && m_labelImage && m_sampling )
    {
        ret = true;

        m_vboxLayout->addWidget( m_labelImage);
        setLayout( m_vboxLayout);
        show();
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Transformation Géométrique"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initGeometricTransformation( void)
{
    bool ret = false;

    m_hboxLayout              = new QHBoxLayout;
    m_vboxLayout              = new QVBoxLayout;
    m_gridLayout              = new QGridLayout;
    m_labelImage              = new QLabel( this);
    m_parameterLabel1         = new QLabel( this);
    m_parameterLabel2         = new QLabel( this);
    m_parameterValue1         = new QSpinBox();
    m_parameterValue2         = new QSpinBox();
    m_geometricTransformation = new CGeometricTransformation( m_imageOrigin);

    if (    m_hboxLayout      && m_vboxLayout      && m_gridLayout       && m_labelImage
         && m_parameterLabel1 && m_parameterLabel2 && m_parameterValue1 && m_parameterValue2
         && m_geometricTransformation )
    {
        ret = true;

        switch ( m_processingType )
        {
            case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION :
                m_nParameters = 1;
                m_rotationAngle    = 0;

                m_parameterLabel1->setText( tr( "Angle Rotation :"));
                m_parameterValue1->setRange( 0, 360);
                m_parameterValue1->setValue( m_rotationAngle);

                connect( m_parameterValue1, SIGNAL( valueChanged(int)), this, SLOT( updateAngleRotation( int)));
                break;

            case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE :
                m_nParameters  = 1;
                m_scaleFactor = 100;
                m_parameterLabel1->setText( tr( "Facteur Homothétie :"));
                m_parameterValue1->setRange( 1, 200);
                m_parameterValue1->setValue( m_scaleFactor);

                connect( m_parameterValue1, SIGNAL( valueChanged(int)), this, SLOT( updateScaleFactor( int)));
                break;

            case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR :
                m_nParameters     = 2;
                m_shearFactorX = 0;
                m_shearFactorY = 0;

                m_parameterLabel1->setText( tr( "Facteur Cisaillement X"));
                m_parameterLabel2->setText( tr( "Facteur Cisaillement Y"));
                m_parameterValue1->setRange( 0, 100);
                m_parameterValue2->setRange( 0, 100);
                m_parameterValue1->setValue( m_shearFactorX);
                m_parameterValue2->setValue( m_shearFactorY);

                connect( m_parameterValue1, SIGNAL( valueChanged(int)), this, SLOT( updateShearFactorX( int)));
                connect( m_parameterValue2, SIGNAL( valueChanged(int)), this, SLOT( updateShearFactorY( int)));
                break;

            default :
                m_nParameters = 0;
                break;
        }

        if ( m_nParameters >= 1 )
        {
            m_hboxLayout->addWidget( m_parameterLabel1);
            m_hboxLayout->addWidget( m_parameterValue1);
        }
        if ( m_nParameters >= 2 )
        {
            m_hboxLayout->addWidget( m_parameterLabel2);
            m_hboxLayout->addWidget( m_parameterValue2);
        }
        m_vboxLayout->addLayout( m_hboxLayout);
        m_vboxLayout->addWidget( m_labelImage);
        this->setLayout( m_vboxLayout);

        show();
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Détection de contours"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initEdgeDetection( void)
{
    bool ret = false;

    m_hboxLayout           = new QHBoxLayout;
    m_vboxLayout           = new QVBoxLayout;
    m_gridLayout           = new QGridLayout;
    m_labelImage           = new QLabel( this);
    m_parameterValue2      = new QSpinBox();
    m_labelLowerSpanSlider = new QLabel( "0");
    m_labelUpperSpanSlider = new QLabel( "255");
    m_spanSlider           = new QxtSpanSlider( Qt::Horizontal);
    m_checkbox1            = new QCheckBox();
    m_labelCheckbox1       = new QLabel( tr( "MC"));
    m_checkbox2            = new QCheckBox();
    m_labelCheckbox2       = new QLabel( tr( "Inv"));
    m_edgeDetection        = new CEdgeDetection( m_imageOrigin);

    if (    m_hboxLayout && m_vboxLayout && m_gridLayout && m_labelImage && m_parameterValue2
         && m_edgeDetection )
    {
        ret = true;

        m_isMonochrom  = m_edgeDetection->isMonochrom();
        m_thresholdMin = m_edgeDetection->getThresholdMin();

        connect( m_checkbox1, SIGNAL( stateChanged(int)), this, SLOT( updateIsMonochrome( int)));
        connect( m_checkbox2, SIGNAL( stateChanged(int)), this, SLOT( updateIsAffichageInverse( int)));

        m_spanSlider->setRange( 0, 255);
        m_spanSlider->setLowerValue( 0);
        m_spanSlider->setUpperValue( 255);
        connect( m_spanSlider, SIGNAL( lowerValueChanged( int)), this, SLOT( updateThresholdMin( int)));
        connect( m_spanSlider, SIGNAL( upperValueChanged( int)), this, SLOT( updateThresholdMax( int)));

        switch ( m_processingType )
        {
            case PROCESSING_EDGE_DETECTION_SIMPLE :
            case PROCESSING_EDGE_DETECTION_ROBERTS :
            case PROCESSING_EDGE_DETECTION_SOBEL :
            case PROCESSING_EDGE_DETECTION_PREWITT :
            case PROCESSING_EDGE_DETECTION_KIRSCH :
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4 :
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8 :
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG :
                m_nParameters = 1;
                break;

            case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH :
            case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE :
            case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN :
                m_nParameters = 2;
                m_alphaDeriche = m_edgeDetection->getAlphaDeriche() * 100;
                m_parameterLabel2 = new QLabel( tr( "Alpha :"));
                m_parameterValue2->setRange( 0, 400);
                m_parameterValue2->setValue( m_alphaDeriche);
                connect( m_parameterValue2, SIGNAL( valueChanged(int)), this, SLOT( updateAlphaDeriche( int)));
                break;

            default :
                m_nParameters = 0;
                break;
        }

        if ( m_nParameters >= 1 )
        {
            m_hboxLayout->addWidget( m_labelCheckbox1);
            m_hboxLayout->addWidget( m_checkbox1);
            m_hboxLayout->addWidget( m_labelCheckbox2);
            m_hboxLayout->addWidget( m_checkbox2);
            m_hboxLayout->addWidget( m_labelLowerSpanSlider);
            m_hboxLayout->addWidget( m_spanSlider);
            m_hboxLayout->addWidget( m_labelUpperSpanSlider);
        }
        if ( m_nParameters >= 2 )
        {
            m_hboxLayout->addWidget( m_parameterLabel2);
            m_hboxLayout->addWidget( m_parameterValue2);
        }
        m_vboxLayout->addLayout( m_hboxLayout);
        m_vboxLayout->addWidget( m_labelImage);
        this->setLayout( m_vboxLayout);

        show();
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Opérateur Morpho-Mathématiques"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initOpMorphoMaths( void)
{
    bool ret = false;

    m_hboxLayout      = new QHBoxLayout;
    m_vboxLayout      = new QVBoxLayout;
    m_gridLayout      = new QGridLayout;
    m_labelImage      = new QLabel( this);
    m_parameterLabel1 = new QLabel( tr( "Dimension"));
    m_parameterValue1 = new QSpinBox();
    m_opMorphoMaths   = new COpMorphoMaths( m_imageOrigin);

    if (    m_hboxLayout      && m_vboxLayout       && m_gridLayout       && m_labelImage
         && m_parameterLabel1 && m_parameterValue1 && m_opMorphoMaths )
    {
        ret = true;

        m_opMorphoMathsDimension = m_opMorphoMaths->getDimension();

        m_parameterValue1->setRange( 0, 100);
        m_parameterValue1->setValue( m_opMorphoMathsDimension);
        connect( m_parameterValue1, SIGNAL( valueChanged(int)), this, SLOT( updateOpMorphoMathsDimension( int)));

        m_hboxLayout->addWidget( m_parameterLabel1);
        m_hboxLayout->addWidget( m_parameterValue1);

        m_vboxLayout->addLayout( m_hboxLayout);
        m_vboxLayout->addWidget( m_labelImage);
        this->setLayout( m_vboxLayout);

        show();
    }

    return ret;
}

//------------------------------------------------------------------------------
//! Initialisation du traitement "Détection de régions"
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initRegionDetection( void)
{
    bool ret = false;

    m_vboxLayout      = new QVBoxLayout;
    m_labelImage      = new QLabel( this);
    m_regionDetection = new CRegionDetection( m_imageOrigin);

    if ( m_vboxLayout && m_labelImage && m_regionDetection )
    {
        ret = true;

        m_vboxLayout->addWidget( m_labelImage);
        setLayout( m_vboxLayout);
        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//  Fonction(s) Publique(s) Slot :

//------------------------------------------------------------------------------
//! Mise à jour du niveau de quantification (Traitement "Quantification")
//!
//! @param level : Le niveau de quantification
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateQuantisationLevel( int level)
{
    m_quantisationLevel = level;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour de l'angle de rotation (Traitement "Transformation Géométrique")
//!
//! @param angle : L'angle de rotation
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateAngleRotation( int angle)
{
    m_rotationAngle = angle;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du facteur d'homothétie (Traitement "Transformation Géométrique")
//!
//! @param factor : Le facteur d'homothétie
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateScaleFactor( int factor)
{
    m_scaleFactor = factor;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du facteur de cisaillement en X (Traitement
//! "Transformation Géométrique")
//!
//! @param factor : Le facteur de cisaillement en X
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateShearFactorX( int factor)
{
    m_shearFactorX = factor;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du facteur de cisaillement en Y (Traitement
//! "Transformation Géométrique")
//!
//! @param factor : Le facteur de cisaillement en Y
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateShearFactorY( int factor)
{
    m_shearFactorY = factor;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du facteur de cisaillement en X (Traitement
//! "Transformation Géométrique")
//!
//! @param isMonochrom : Le facteur de cisaillement en X
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateIsMonochrome( int isMonochrom)
{
    m_isMonochrom = isMonochrom;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du seuil minimum (Traitement "Détection de contours")
//!
//! @param threshold : Le seuil
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateThresholdMin( int threshold)
{
    m_thresholdMin = threshold;

    QString texte;
    texte = QString::number( threshold);
    m_labelLowerSpanSlider->setText( texte);

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du seuil maximum (Traitement "Détection de contours")
//!
//! @param threshold : Le seuil
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateThresholdMax( int threshold)
{
    m_thresholdMax = threshold;

    QString texte;
    texte = QString::number( threshold);
    m_labelUpperSpanSlider->setText( texte);

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour du alpha de Deriche (Traitement "Détection de contours")
//!
//! @param alpha : La valeur alpha
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateAlphaDeriche( int alpha)
{
    m_alphaDeriche = alpha;

    display();
}

//------------------------------------------------------------------------------
//! Mise à jour de la dimension (Traitement "Opérateur Morpho-Mathématique")
//!
//! @param v : La dimension
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateOpMorphoMathsDimension( int dimension)
{
    m_opMorphoMathsDimension = dimension;

    display();
}
