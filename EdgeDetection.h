//------------------------------------------------------------------------------
//! @file EdgeDetection.h
//! @brief Header file of the CEdgeDetection class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef EDGE_DETECTION_HEADER
#define EDGE_DETECTION_HEADER

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>

#include "../../Commun/Image/cimage.h"


//------------------------------------------------------------------------------
// Enumeration(s) :

enum
{
    EDGE_DETECTION_UNKNOWN,
    EDGE_DETECTION_SIMPLE,
    EDGE_DETECTION_ROBERTS,
    EDGE_DETECTION_SOBEL,
    EDGE_DETECTION_PREWITT,
    EDGE_DETECTION_KIRSCH,
    EDGE_DETECTION_LAPLACIAN_CONNECTEDNESS_4,
    EDGE_DETECTION_LAPLACIAN_CONNECTEDNESS_8,
    EDGE_DETECTION_LAPLACIAN_DOG,
    EDGE_DETECTION_DERICHE_SMOOTH,
    EDGE_DETECTION_DERICHE_DERIVATIVE,
    EDGE_DETECTION_DERICHE_LAPLACIAN
};


//------------------------------------------------------------------------------
// Classe(s) :

class CEdgeDetection
{
public:
    CEdgeDetection(QImage *imageIn);
    ~CEdgeDetection(void);

    QImage *getImageTreated(void);
    bool    isMonochrom(void);
    int     getThresholdMin(void);
    int     getThresholdMax(void);
    float   getAlphaDeriche(void);
    void    setThresholdMin(int threshold);
    void    setThresholdMax(int threshold);
    void    setAlphaDeriche(float alpha);
    void    computeEdgeDetection(int detectionType, int thresholdMin, int thresholdMax, int isMonochrom);

private:
    QImage *   m_imageOrigin;
    QImage *   m_imageTreated;
    CImageInt *m_imageGray;
    CImageInt *m_edgeDetectionImage;
    bool       m_isValid;
    int        m_detectionType;
    int        m_thresholdMin;
    int        m_thresholdMax;
    float      m_alphaDeriche;
    bool       m_isMonochrom;

    void createImageGray(QImage *imageIn, CImageInt *imageOut);
    int  convolution(CImageInt *imageIn, int x, int y, const int matrix[3][3], int quotient);
    bool thresholding(CImageInt *imageIn, QImage *imageOut, bool isMonochrom, int thresholdMin, int thresholdMax);
    void computeEdgeDetectionSimple(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionRoberts(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionSobel(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionPrewitt(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionKirsch(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionLaplacianConnectedness4(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionLaplacianConnectedness8(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionLaplacianDOG(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionDericheSmooth(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionDericheDerivative(CImageInt *imageIn, CImageInt *imageOut);
    void computeEdgeDetectionDericheLaplacian(CImageInt *imageIn, CImageInt *imageOut);
};

#endif // EDGE_DETECTION_HEADER
