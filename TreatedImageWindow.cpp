//------------------------------------------------------------------------------
//! @file TreatedImageWindow.cpp
//! @brief Definition file of the CTreatedImageWindow class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <QMessageBox>

#include "TreatedImageWindow.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! CTreatedImageWindow constructor for a given image
//!
//! @param type The treatment type
//! @param imageIn The input image
//! @param parent The parent widget
//!
//! @return The created object
//------------------------------------------------------------------------------
CTreatedImageWindow::CTreatedImageWindow(int type, QImage *imageIn, QWidget *parent) : QWidget(parent)
{
    bool ret = false;

    if (imageIn != nullptr)
    {
        m_imageOrigin = imageIn;

        if (m_imageOrigin->width() && m_imageOrigin->height())
        {
            m_processingType = type;
            switch (m_processingType)
            {
                case PROCESSING_COLOR_MODEL_COMPONENT_Y:
                case PROCESSING_COLOR_MODEL_COMPONENT_U:
                case PROCESSING_COLOR_MODEL_COMPONENT_V:
                    ret = initColorModel();
                    break;

                case PROCESSING_QUANTISATION_GRAY:
                case PROCESSING_QUANTISATION_RGB:
                    ret = initQuantisation();
                    break;

                case PROCESSING_SAMPLING:
                    ret = initSampling();
                    break;

                case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION:
                case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE:
                case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR:
                    ret = initGeometricTransformation();
                    break;

                case PROCESSING_EDGE_DETECTION_SIMPLE:
                case PROCESSING_EDGE_DETECTION_ROBERTS:
                case PROCESSING_EDGE_DETECTION_SOBEL:
                case PROCESSING_EDGE_DETECTION_PREWITT:
                case PROCESSING_EDGE_DETECTION_KIRSCH:
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4:
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8:
                case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG:
                case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH:
                case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE:
                case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN:
                    ret = initEdgeDetection();
                    break;

                case PROCESSING_OP_MORPHO_MATHS_DILATION:
                case PROCESSING_OP_MORPHO_MATHS_EROSION:
                case PROCESSING_OP_MORPHO_MATHS_OPENING:
                case PROCESSING_OP_MORPHO_MATHS_CLOSING:
                case PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT:
                case PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT:
                case PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT:
                case PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS:
                case PROCESSING_OP_MORPHO_MATHS_THINNING:
                case PROCESSING_OP_MORPHO_MATHS_SKELETONIZING:
                    ret = initOpMorphoMaths();
                    break;

                case PROCESSING_REGION_DETECTION_LINE:
                    ret = initRegionDetection();
                    break;

                default:
                    break;
            }

            if (!ret)
                m_processingType = PROCESSING_UNKNOWN;
        }
        else
            QMessageBox::critical(this, tr(""), tr("Veuillez ouvrir une image"));
    }
    else
        QMessageBox::critical(this, tr(""), tr("Erreur d'allocation mémoire"));
}


//------------------------------------------------------------------------------
//! Display the treated image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::display(void)
{
    switch (m_processingType)
    {
        case PROCESSING_COLOR_MODEL_COMPONENT_Y:
            displayComponentY();
            break;

        case PROCESSING_COLOR_MODEL_COMPONENT_U:
            displayComponentU();
            break;

        case PROCESSING_COLOR_MODEL_COMPONENT_V:
            displayComponentV();
            break;

        case PROCESSING_QUANTISATION_GRAY:
            displayQuantisationGray();
            break;

        case PROCESSING_QUANTISATION_RGB:
            displayQuantisationRGB();
            break;

        case PROCESSING_SAMPLING:
            displayFourierTransform();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION:
            displayRotation();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE:
            displayScale();
            break;

        case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR:
            displayShear();
            break;

        case PROCESSING_EDGE_DETECTION_SIMPLE:
            displayEdgeDetectionSimple();
            break;

        case PROCESSING_EDGE_DETECTION_ROBERTS:
            displayEdgeDetectionRoberts();
            break;

        case PROCESSING_EDGE_DETECTION_SOBEL:
            displayEdgeDetectionSobel();
            break;

        case PROCESSING_EDGE_DETECTION_PREWITT:
            displayEdgeDetectionPrewitt();
            break;

        case PROCESSING_EDGE_DETECTION_KIRSCH:
            displayEdgeDetectionKirsch();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4:
            displayEdgeDetectionLaplacianConnexity4();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8:
            displayEdgeDetectionLaplacianConnexity8();
            break;

        case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG:
            displayEdgeDetectionLaplacianDOG();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH:
            displayEdgeDetectionDericheSmooth();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE:
            displayEdgeDetectionDericheDerivative();
            break;

        case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN:
            displayEdgeDetectionDericheLaplacian();
            break;

        case PROCESSING_OP_MORPHO_MATHS_DILATION:
            displayOpMorphoMathsDilation();
            break;

        case PROCESSING_OP_MORPHO_MATHS_EROSION:
            displayOpMorphoMathsErosion();
            break;

        case PROCESSING_OP_MORPHO_MATHS_OPENING:
            displayOpMorphoMathsOpening();
            break;

        case PROCESSING_OP_MORPHO_MATHS_CLOSING:
            displayOpMorphoMathsClosing();
            break;

        case PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT:
            displayOpMorphoMathsInteriorGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT:
            displayOpMorphoMathsExteriorGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT:
            displayOpMorphoMathsMorphologicalGradient();
            break;

        case PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS:
            displayOpMorphoMathsHitOrMiss();
            break;

        case PROCESSING_OP_MORPHO_MATHS_THINNING:
            displayOpMorphoMathsThinning();
            break;

        case PROCESSING_OP_MORPHO_MATHS_SKELETONIZING:
            displayOpMorphoMathsSkeletonizing();
            break;

        case PROCESSING_REGION_DETECTION_LINE:
            displayRegionDetectionLine();
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
//! Display the Y part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentY(void)
{
    if (m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_Y)
    {
        m_colorModel->computeComponentY();

        m_labelImage->setPixmap(QPixmap::fromImage(*m_colorModel->getImageTreated()));
        setWindowTitle(tr("Composante Y"));
    }
}


//------------------------------------------------------------------------------
//! Display the U part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentU(void)
{
    if (m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_U)
    {
        m_colorModel->computeComponentU();

        m_labelImage->setPixmap(QPixmap::fromImage(*m_colorModel->getImageTreated()));
        setWindowTitle(tr("Composante U"));
    }
}


//------------------------------------------------------------------------------
//! Display the V part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayComponentV(void)
{
    if (m_processingType == PROCESSING_COLOR_MODEL_COMPONENT_V)
    {
        m_colorModel->computeComponentV();

        m_labelImage->setPixmap(QPixmap::fromImage(*m_colorModel->getImageTreated()));
        setWindowTitle(tr("Composante V"));
    }
}


//------------------------------------------------------------------------------
//! Display the grayscale quantisation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayQuantisationGray(void)
{
    if (m_processingType == PROCESSING_QUANTISATION_GRAY)
    {
        m_quantisation->computeGrayQuantisation(m_quantisationLevel);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_quantisation->getImageTreated()));
        setWindowTitle(tr("Quantification Gris"));
    }
}


//------------------------------------------------------------------------------
//! Display the colored quantisation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayQuantisationRGB(void)
{
    if (m_processingType == PROCESSING_QUANTISATION_RGB)
    {
        m_quantisation->computeRGBQuantisation(m_quantisationLevel);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_quantisation->getImageTreated()));
        setWindowTitle(tr("Quantification RGB"));
    }
}


//------------------------------------------------------------------------------
//! Display the Fourier Transform of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayFourierTransform(void)
{
    if (m_processingType == PROCESSING_SAMPLING)
    {
        m_sampling->computeFourierTransform();

        m_labelImage->setPixmap(QPixmap::fromImage(*m_sampling->getImageTreated()));
        setWindowTitle(tr("Transformée de Fourier"));
    }
}


//------------------------------------------------------------------------------
//! Display the rotated image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayRotation(void)
{
    if (m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION)
    {
        m_geometricTransformation->computeRotation(m_rotationAngle);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_geometricTransformation->getImageTreated()));
        setWindowTitle(tr("Rotation"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a homothetie
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayScale(void)
{
    if (m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE)
    {
        m_geometricTransformation->computeScale(m_scaleFactor);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_geometricTransformation->getImageTreated()));
        setWindowTitle(tr("Homothétie"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a shear
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayShear(void)
{
    if (m_processingType == PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR)
    {
        m_geometricTransformation->computeShear(m_shearFactorX, m_shearFactorY);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_geometricTransformation->getImageTreated()));
        setWindowTitle(tr("Cisaillement"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a naive edge detection
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionSimple(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_SIMPLE)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_SIMPLE, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Naïf"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Roberts)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionRoberts(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_ROBERTS)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_ROBERTS, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Roberts"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Sobel)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionSobel(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_SOBEL)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_SOBEL, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Sobel"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Prewitt)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionPrewitt(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_PREWITT)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_PREWITT, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Prewitt"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Kirsch)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionKirsch(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_KIRSCH)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_KIRSCH, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Kirsch"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Laplacian with connectivity 4)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianConnexity4(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_LAPLACIAN_CONNEXITY_4, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Laplacian Connexité 4"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Laplacian with connectivity 8)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianConnexity8(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_LAPLACIAN_CONNEXITY_8, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Laplacian Connexité 8"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Laplacian DOG)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionLaplacianDOG(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG)
    {
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_LAPLACIAN_DOG, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Laplacian DOG"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Deriche smoothing filter)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheSmooth(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH)
    {
        m_edgeDetection->setAlphaDeriche((float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_DERICHE_SMOOTH, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Deriche Smooth"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Deriche derivative)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheDerivative(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE)
    {
        m_edgeDetection->setAlphaDeriche((float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_DERICHE_DERIVATIVE, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Deriche Dérivée"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after an edge detection (Deriche Laplacian)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayEdgeDetectionDericheLaplacian(void)
{
    if (m_processingType == PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN)
    {
        m_edgeDetection->setAlphaDeriche((float) m_alphaDeriche / 100);
        m_edgeDetection->computeEdgeDetection(EDGE_DETECTION_DERICHE_LAPLACIAN, m_thresholdMin, m_thresholdMax, m_isMonochrom);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_edgeDetection->getImageTreated()));
        setWindowTitle(tr("Détection Contours Deriche Laplacian"));
    }
}


//------------------------------------------------------------------------------
//! Display the dilated image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsDilation(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_DILATION)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_DILATION, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Dilatation"));
    }
}


//------------------------------------------------------------------------------
//! Display the eroded image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsErosion(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_EROSION)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_EROSION, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Erosion"));
    }
}


//------------------------------------------------------------------------------
//! Display the "opened" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsOpening(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_OPENING)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_OPENING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Ouverture"));
    }
}


//------------------------------------------------------------------------------
//! Display the "closed" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsClosing(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_CLOSING)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_CLOSING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Fermeture"));
    }
}


//------------------------------------------------------------------------------
//! Display the interior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsInteriorGradient(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_INTERIOR_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Contour intérieur"));
    }
}


//------------------------------------------------------------------------------
//! Display the exterior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsExteriorGradient(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_EXTERIOR_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Contour extérieur"));
    }
}


//------------------------------------------------------------------------------
//! Display the morphological gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsMorphologicalGradient(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_MORPHOLOGICAL_GRADIENT, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Gradient morphologique"));
    }
}


//------------------------------------------------------------------------------
//! Display the "hit or miss" of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsHitOrMiss(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_HIT_OR_MISS, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Tout ou rien"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a thinning transformation
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsThinning(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_THINNING)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_THINNING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Amincissement"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a skeletonization transformation
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayOpMorphoMathsSkeletonizing(void)
{
    if (m_processingType == PROCESSING_OP_MORPHO_MATHS_SKELETONIZING)
    {
        m_opMorphoMaths->computeOpMorphoMaths(OPMORPHOMATHS_SKELETONIZING, m_opMorphoMathsDimension);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_opMorphoMaths->getImageTreated()));
        setWindowTitle(tr("Squelettisation"));
    }
}


//------------------------------------------------------------------------------
//! Display the image after a line detection inside
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::displayRegionDetectionLine(void)
{
    if (m_processingType == PROCESSING_REGION_DETECTION_LINE)
    {
        m_regionDetection->computeDetectionRegion(DETECTION_REGION_LINE);

        m_labelImage->setPixmap(QPixmap::fromImage(*m_regionDetection->getImageTreated()));
        setWindowTitle(tr("Détection Droite"));
    }
}

//------------------------------------------------------------------------------
// Private Method(s):

//------------------------------------------------------------------------------
//! Initialization of the "Color Model" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initColorModel(void)
{
    bool ret = false;

    m_vboxLayout = new QVBoxLayout;
    m_labelImage = new QLabel(this);
    m_colorModel = new CColorModel(m_imageOrigin);

    if (m_vboxLayout && m_labelImage && m_colorModel)
    {
        ret = true;

        m_vboxLayout->addWidget(m_labelImage);
        setLayout(m_vboxLayout);
        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Quantisation" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initQuantisation(void)
{
    bool ret = false;

    m_vboxLayout        = new QVBoxLayout;
    m_hboxLayout        = new QHBoxLayout;
    m_labelImage        = new QLabel(this);
    m_levelText         = new QLineEdit(tr("Niveau Quantification :"));
    m_levelChoice       = new QSpinBox();
    m_quantisation      = new CQuantisation(m_imageOrigin);
    m_quantisationLevel = 1;

    if (m_vboxLayout && m_hboxLayout && m_labelImage && m_levelText && m_levelChoice && m_quantisation)
    {
        ret = true;

        m_levelText->setReadOnly(true);
        m_levelChoice->setRange(1, 8);
        m_levelChoice->setValue(m_quantisationLevel);

        connect(m_levelChoice, SIGNAL(valueChanged(int)), this, SLOT(updateQuantisationLevel(int)));

        m_hboxLayout->addWidget(m_levelText);
        m_hboxLayout->addWidget(m_levelChoice);
        m_vboxLayout->addLayout(m_hboxLayout);
        m_vboxLayout->addWidget(m_labelImage);
        setLayout(m_vboxLayout);
        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Sampling" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initSampling(void)
{
    bool ret = false;

    m_vboxLayout = new QVBoxLayout;
    m_labelImage = new QLabel(this);
    m_sampling   = new CSampling(m_imageOrigin);

    if (m_vboxLayout && m_labelImage && m_sampling)
    {
        ret = true;

        m_vboxLayout->addWidget(m_labelImage);
        setLayout(m_vboxLayout);
        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Geometric Transformation" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initGeometricTransformation(void)
{
    bool ret = false;

    m_hboxLayout              = new QHBoxLayout;
    m_vboxLayout              = new QVBoxLayout;
    m_gridLayout              = new QGridLayout;
    m_labelImage              = new QLabel(this);
    m_parameterLabel1         = new QLabel(this);
    m_parameterLabel2         = new QLabel(this);
    m_parameterValue1         = new QSpinBox();
    m_parameterValue2         = new QSpinBox();
    m_geometricTransformation = new CGeometricTransformation(m_imageOrigin);

    if (m_hboxLayout &&
        m_vboxLayout &&
        m_gridLayout &&
        m_labelImage &&
        m_parameterLabel1 &&
        m_parameterLabel2 &&
        m_parameterValue1 &&
        m_parameterValue2 &&
        m_geometricTransformation)
    {
        ret = true;

        switch (m_processingType)
        {
            case PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION:
                m_nParameters   = 1;
                m_rotationAngle = 0;

                m_parameterLabel1->setText(tr("Angle Rotation :"));
                m_parameterValue1->setRange(0, 360);
                m_parameterValue1->setValue(m_rotationAngle);

                connect(m_parameterValue1, SIGNAL(valueChanged(int)), this, SLOT(updateAngleRotation(int)));
                break;

            case PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE:
                m_nParameters = 1;
                m_scaleFactor = 100;
                m_parameterLabel1->setText(tr("Facteur Homothétie :"));
                m_parameterValue1->setRange(1, 200);
                m_parameterValue1->setValue(m_scaleFactor);

                connect(m_parameterValue1, SIGNAL(valueChanged(int)), this, SLOT(updateScaleFactor(int)));
                break;

            case PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR:
                m_nParameters  = 2;
                m_shearFactorX = 0;
                m_shearFactorY = 0;

                m_parameterLabel1->setText(tr("Facteur Cisaillement X"));
                m_parameterLabel2->setText(tr("Facteur Cisaillement Y"));
                m_parameterValue1->setRange(0, 100);
                m_parameterValue2->setRange(0, 100);
                m_parameterValue1->setValue(m_shearFactorX);
                m_parameterValue2->setValue(m_shearFactorY);

                connect(m_parameterValue1, SIGNAL(valueChanged(int)), this, SLOT(updateShearFactorX(int)));
                connect(m_parameterValue2, SIGNAL(valueChanged(int)), this, SLOT(updateShearFactorY(int)));
                break;

            default:
                m_nParameters = 0;
                break;
        }

        if (m_nParameters >= 1)
        {
            m_hboxLayout->addWidget(m_parameterLabel1);
            m_hboxLayout->addWidget(m_parameterValue1);
        }
        if (m_nParameters >= 2)
        {
            m_hboxLayout->addWidget(m_parameterLabel2);
            m_hboxLayout->addWidget(m_parameterValue2);
        }
        m_vboxLayout->addLayout(m_hboxLayout);
        m_vboxLayout->addWidget(m_labelImage);
        this->setLayout(m_vboxLayout);

        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Edge Detection" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initEdgeDetection(void)
{
    bool ret = false;

    m_hboxLayout           = new QHBoxLayout;
    m_vboxLayout           = new QVBoxLayout;
    m_gridLayout           = new QGridLayout;
    m_labelImage           = new QLabel(this);
    m_parameterValue2      = new QSpinBox();
    m_labelLowerSpanSlider = new QLabel("0");
    m_labelUpperSpanSlider = new QLabel("255");
    m_thresholdMinSlider   = new QSlider(Qt::Horizontal);
    m_thresholdMaxSlider   = new QSlider(Qt::Horizontal);
    m_checkbox1            = new QCheckBox();
    m_labelCheckbox1       = new QLabel(tr("MC"));
    m_checkbox2            = new QCheckBox();
    m_labelCheckbox2       = new QLabel(tr("Inv"));
    m_edgeDetection        = new CEdgeDetection(m_imageOrigin);

    if (m_hboxLayout &&
        m_vboxLayout &&
        m_gridLayout &&
        m_labelImage &&
        m_parameterValue2 &&
        m_edgeDetection)
    {
        ret = true;

        m_isMonochrom  = m_edgeDetection->isMonochrom();
        m_thresholdMin = m_edgeDetection->getThresholdMin();

        connect(m_checkbox1, SIGNAL(stateChanged(int)), this, SLOT(updateIsMonochrome(int)));
        connect(m_checkbox2, SIGNAL(stateChanged(int)), this, SLOT(updateIsAffichageInverse(int)));

        m_thresholdMinSlider->setMinimum(0);
        m_thresholdMinSlider->setMaximum(254);

        m_thresholdMaxSlider->setMinimum(1);
        m_thresholdMaxSlider->setMaximum(255);

        connect(m_thresholdMinSlider, SIGNAL(valueChanged(int)), this, SLOT(updateThresholdMin(int)));
        connect(m_thresholdMaxSlider, SIGNAL(valueChanged(int)), this, SLOT(updateThresholdMax(int)));

        m_thresholdMinSlider->setValue(0);
        m_thresholdMaxSlider->setValue(255);

        switch (m_processingType)
        {
            case PROCESSING_EDGE_DETECTION_SIMPLE:
            case PROCESSING_EDGE_DETECTION_ROBERTS:
            case PROCESSING_EDGE_DETECTION_SOBEL:
            case PROCESSING_EDGE_DETECTION_PREWITT:
            case PROCESSING_EDGE_DETECTION_KIRSCH:
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4:
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8:
            case PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG:
                m_nParameters = 1;
                break;

            case PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH:
            case PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE:
            case PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN:
                m_nParameters     = 2;
                m_alphaDeriche    = m_edgeDetection->getAlphaDeriche() * 100;
                m_parameterLabel2 = new QLabel(tr("Alpha :"));
                m_parameterValue2->setRange(0, 400);
                m_parameterValue2->setValue(m_alphaDeriche);
                connect(m_parameterValue2, SIGNAL(valueChanged(int)), this, SLOT(updateAlphaDeriche(int)));
                break;

            default:
                m_nParameters = 0;
                break;
        }

        if (m_nParameters >= 1)
        {
            m_hboxLayout->addWidget(m_labelCheckbox1);
            m_hboxLayout->addWidget(m_checkbox1);
            m_hboxLayout->addWidget(m_labelCheckbox2);
            m_hboxLayout->addWidget(m_checkbox2);
            m_hboxLayout->addWidget(m_labelLowerSpanSlider);
            m_hboxLayout->addWidget(m_thresholdMinSlider);
            m_hboxLayout->addWidget(m_thresholdMaxSlider);
            m_hboxLayout->addWidget(m_labelUpperSpanSlider);
        }
        if (m_nParameters >= 2)
        {
            m_hboxLayout->addWidget(m_parameterLabel2);
            m_hboxLayout->addWidget(m_parameterValue2);
        }
        m_vboxLayout->addLayout(m_hboxLayout);
        m_vboxLayout->addWidget(m_labelImage);
        this->setLayout(m_vboxLayout);

        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Morpho Mathematics" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initOpMorphoMaths(void)
{
    bool ret = false;

    m_hboxLayout      = new QHBoxLayout;
    m_vboxLayout      = new QVBoxLayout;
    m_gridLayout      = new QGridLayout;
    m_labelImage      = new QLabel(this);
    m_parameterLabel1 = new QLabel(tr("Dimension"));
    m_parameterValue1 = new QSpinBox();
    m_opMorphoMaths   = new COpMorphoMaths(m_imageOrigin);

    if (m_hboxLayout &&
        m_vboxLayout &&
        m_gridLayout &&
        m_labelImage &&
        m_parameterLabel1 &&
        m_parameterValue1 &&
        m_opMorphoMaths)
    {
        ret = true;

        m_opMorphoMathsDimension = m_opMorphoMaths->getDimension();

        m_parameterValue1->setRange(0, 100);
        m_parameterValue1->setValue(m_opMorphoMathsDimension);
        connect(m_parameterValue1, SIGNAL(valueChanged(int)), this, SLOT(updateOpMorphoMathsDimension(int)));

        m_hboxLayout->addWidget(m_parameterLabel1);
        m_hboxLayout->addWidget(m_parameterValue1);

        m_vboxLayout->addLayout(m_hboxLayout);
        m_vboxLayout->addWidget(m_labelImage);
        this->setLayout(m_vboxLayout);

        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
//! Initialization of the "Region Detection" treatment
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool CTreatedImageWindow::initRegionDetection(void)
{
    bool ret = false;

    m_vboxLayout      = new QVBoxLayout;
    m_labelImage      = new QLabel(this);
    m_regionDetection = new CRegionDetection(m_imageOrigin);

    if (m_vboxLayout && m_labelImage && m_regionDetection)
    {
        ret = true;

        m_vboxLayout->addWidget(m_labelImage);
        setLayout(m_vboxLayout);
        show();
    }

    return ret;
}


//------------------------------------------------------------------------------
// Public Slot Method(s):

//------------------------------------------------------------------------------
//! Update the quantisation level ("Quantification" treatment)
//!
//! @param level The quantisation level
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateQuantisationLevel(int level)
{
    m_quantisationLevel = level;

    display();
}


//------------------------------------------------------------------------------
//! Update the rotation angle ("Geometric Transformation" treatment)
//!
//! @param angle The rotation angle
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateAngleRotation(int angle)
{
    m_rotationAngle = angle;

    display();
}


//------------------------------------------------------------------------------
//! Update the homothetie factor ("Geometric Transformation" treatment)
//!
//! @param factor The homothetie factor
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateScaleFactor(int factor)
{
    m_scaleFactor = factor;

    display();
}


//------------------------------------------------------------------------------
//! Update the shear factor by X ("Geometric Transformation" treatment)
//!
//! @param factor The shear factor by X
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateShearFactorX(int factor)
{
    m_shearFactorX = factor;

    display();
}


//------------------------------------------------------------------------------
//! Update the shear factor by Y ("Geometric Transformation" treatment)
//!
//! @param factor The shear factor by Y
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateShearFactorY(int factor)
{
    m_shearFactorY = factor;

    display();
}


//------------------------------------------------------------------------------
//! Update the monochrom flag threshold ("Edge Detection" treatment)
//!
//! @param isMonochrom The monochrom flag
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateIsMonochrome(int isMonochrom)
{
    m_isMonochrom = isMonochrom;

    display();
}


//------------------------------------------------------------------------------
//! Update the minimum threshold ("Edge Detection" treatment)
//!
//! @param threshold The minimum threshold
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateThresholdMin(int threshold)
{
    m_thresholdMin = threshold;

    QString texte;
    texte = QString::number(threshold);
    m_labelLowerSpanSlider->setText(texte);

    if (threshold >= m_thresholdMax)
    {
        m_thresholdMaxSlider->setValue(threshold + 1);
    }

    display();
}


//------------------------------------------------------------------------------
//! Update the maximum threshold ("Edge Detection" treatment)
//!
//! @param threshold The maximum threshold
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateThresholdMax(int threshold)
{
    m_thresholdMax = threshold;

    QString texte;
    texte = QString::number(threshold);
    m_labelUpperSpanSlider->setText(texte);

    if (threshold <= m_thresholdMin)
    {
        m_thresholdMinSlider->setValue(threshold - 1);
    }

    display();
}


//------------------------------------------------------------------------------
//! Update the alpha value for Deriche ("Edge Detection" treatment)
//!
//! @param alpha The alpha value
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateAlphaDeriche(int alpha)
{
    m_alphaDeriche = alpha;

    display();
}


//------------------------------------------------------------------------------
//! Update the dimension ("Morpho Mathematics" treatment)
//!
//! @param dimension The dimension
//!
//! @return _
//------------------------------------------------------------------------------
void CTreatedImageWindow::updateOpMorphoMathsDimension(int dimension)
{
    m_opMorphoMathsDimension = dimension;

    display();
}
