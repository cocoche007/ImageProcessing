//------------------------------------------------------------------------------
//! @file TreatedImageWindow.h
//! @brief Header file of the CTreatedImageWindow class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __TREATED_IMAGE_WINDOW_H__
#define __TREATED_IMAGE_WINDOW_H__

//------------------------------------------------------------------------------
// Include(s) :

#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "ColorModel.h"
#include "EdgeDetection.h"
#include "GeometricTransformation.h"
#include "OpMorphoMaths.h"
#include "Quantisation.h"
#include "RegionDetection.h"
#include "Sampling.h"


//------------------------------------------------------------------------------
// Enumeration(s):

enum
{
    PROCESSING_UNKNOWN,
    PROCESSING_COLOR_MODEL_COMPONENT_Y,
    PROCESSING_COLOR_MODEL_COMPONENT_U,
    PROCESSING_COLOR_MODEL_COMPONENT_V,
    PROCESSING_QUANTISATION_GRAY,
    PROCESSING_QUANTISATION_RGB,
    PROCESSING_SAMPLING,
    PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION,
    PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE,
    PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR,
    PROCESSING_EDGE_DETECTION_SIMPLE,
    PROCESSING_EDGE_DETECTION_ROBERTS,
    PROCESSING_EDGE_DETECTION_SOBEL,
    PROCESSING_EDGE_DETECTION_PREWITT,
    PROCESSING_EDGE_DETECTION_KIRSCH,
    PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4,
    PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8,
    PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG,
    PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH,
    PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE,
    PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN,
    PROCESSING_OP_MORPHO_MATHS_DILATION,
    PROCESSING_OP_MORPHO_MATHS_EROSION,
    PROCESSING_OP_MORPHO_MATHS_OPENING,
    PROCESSING_OP_MORPHO_MATHS_CLOSING,
    PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT,
    PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT,
    PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT,
    PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS,
    PROCESSING_OP_MORPHO_MATHS_THINNING,
    PROCESSING_OP_MORPHO_MATHS_SKELETONIZING,
    PROCESSING_REGION_DETECTION_LINE
};


//------------------------------------------------------------------------------
// Classe(s) :

class CTreatedImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CTreatedImageWindow(int type, QImage *imageIn, QWidget *parent = nullptr);
    void display(void);
    void displayComponentY(void);
    void displayComponentU(void);
    void displayComponentV(void);
    void displayQuantisationGray(void);
    void displayQuantisationRGB(void);
    void displayFourierTransform(void);
    void displayRotation(void);
    void displayScale(void);
    void displayShear(void);
    void displayEdgeDetectionSimple(void);
    void displayEdgeDetectionRoberts(void);
    void displayEdgeDetectionSobel(void);
    void displayEdgeDetectionPrewitt(void);
    void displayEdgeDetectionKirsch(void);
    void displayEdgeDetectionLaplacianConnexity4(void);
    void displayEdgeDetectionLaplacianConnexity8(void);
    void displayEdgeDetectionLaplacianDOG(void);
    void displayEdgeDetectionDericheSmooth(void);
    void displayEdgeDetectionDericheDerivative(void);
    void displayEdgeDetectionDericheLaplacian(void);
    void displayOpMorphoMathsDilation(void);
    void displayOpMorphoMathsErosion(void);
    void displayOpMorphoMathsOpening(void);
    void displayOpMorphoMathsClosing(void);
    void displayOpMorphoMathsInteriorGradient(void);
    void displayOpMorphoMathsExteriorGradient(void);
    void displayOpMorphoMathsMorphologicalGradient(void);
    void displayOpMorphoMathsHitOrMiss(void);
    void displayOpMorphoMathsThinning(void);
    void displayOpMorphoMathsSkeletonizing(void);
    void displayRegionDetectionLine(void);

private:
    int m_processingType;

    QVBoxLayout *m_vboxLayout;
    QHBoxLayout *m_hboxLayout;
    QGridLayout *m_gridLayout;
    QLineEdit *  m_levelText;
    QSpinBox *   m_levelChoice;
    int          m_nParameters;
    QLabel *     m_parameterLabel1;
    QLabel *     m_parameterLabel2;
    QSpinBox *   m_parameterValue1;
    QSpinBox *   m_parameterValue2;
    QLabel *     m_labelLowerSpanSlider;
    QLabel *     m_labelUpperSpanSlider;
    QSlider *    m_thresholdMinSlider;
    QSlider *    m_thresholdMaxSlider;
    QCheckBox *  m_checkbox1;
    QLabel *     m_labelCheckbox1;
    QCheckBox *  m_checkbox2;
    QLabel *     m_labelCheckbox2;
    QLabel *     m_labelImage;
    QImage *     m_imageOrigin;
    QImage *     m_imageTreated;

    CColorModel *             m_colorModel;
    CQuantisation *           m_quantisation;
    CSampling *               m_sampling;
    CGeometricTransformation *m_geometricTransformation;
    CEdgeDetection *          m_edgeDetection;
    COpMorphoMaths *          m_opMorphoMaths;
    CRegionDetection *        m_regionDetection;

    int  m_quantisationLevel;
    int  m_rotationAngle;
    int  m_scaleFactor;
    int  m_shearFactorX;
    int  m_shearFactorY;
    bool m_isMonochrom;
    int  m_thresholdMin;
    int  m_thresholdMax;
    int  m_alphaDeriche;
    int  m_opMorphoMathsDimension;

    bool initColorModel(void);
    bool initQuantisation(void);
    bool initSampling(void);
    bool initGeometricTransformation(void);
    bool initEdgeDetection(void);
    bool initOpMorphoMaths(void);
    bool initRegionDetection(void);

signals:

public slots:
    void updateQuantisationLevel(int level);
    void updateAngleRotation(int angle);
    void updateScaleFactor(int factor);
    void updateShearFactorX(int factor);
    void updateShearFactorY(int factor);
    void updateIsMonochrome(int isMonochrom);
    void updateThresholdMin(int threshold);
    void updateThresholdMax(int threshold);
    void updateAlphaDeriche(int alpha);
    void updateOpMorphoMathsDimension(int dimension);
};

#endif // __TREATED_IMAGE_WINDOW_H__
