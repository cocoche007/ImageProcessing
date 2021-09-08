//------------------------------------------------------------------------------
//! @file OpMorphoMaths.h
//! @brief Header file of the COpMorphoMaths class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef OP_MORPHO_MATHS_HEADER
#define OP_MORPHO_MATHS_HEADER

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>

#include "../../Commun/Image/cimage.h"


//------------------------------------------------------------------------------
// Enumeration(s):

enum OPMORPHOMATHS_TYPE
{
    OPMORPHOMATHS_UNKNOWN,
    OPMORPHOMATHS_DILATION,
    OPMORPHOMATHS_EROSION,
    OPMORPHOMATHS_OPENING,
    OPMORPHOMATHS_CLOSING,
    OPMORPHOMATHS_INTERIOR_GRADIENT,
    OPMORPHOMATHS_EXTERIOR_GRADIENT,
    OPMORPHOMATHS_MORPHOLOGICAL_GRADIENT,
    OPMORPHOMATHS_HIT_OR_MISS,
    OPMORPHOMATHS_THINNING,
    OPMORPHOMATHS_SKELETONIZING
};

enum OPMORPHOMATHS_NEIGHBORHOOD_TYPE
{
    OPMORPHOMATHS_NEIGHBORHOOD_UNKNOWN,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_8,
    OPMORPHOMATHS_NEIGHBORHOOD_VERTICAL,
    OPMORPHOMATHS_NEIGHBORHOOD_HORIZONTAL,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_UP,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_DOWN,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_LEFT,
    OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_RIGHT
};


//------------------------------------------------------------------------------
// Classe(s) :

class COpMorphoMaths
{
public:
    COpMorphoMaths(QImage *imageIn);
    ~COpMorphoMaths(void);

    QImage *getImageTreated(void);
    int     getDimension(void);
    void    computeOpMorphoMaths(OPMORPHOMATHS_TYPE OperationType, int dimension, int neighborhoodType = OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_8);

private:
    QImage *   m_imageOrigin;
    QImage *   m_imageTreated;
    CImageInt *m_imageGray;
    CImageInt *m_neighborhood;
    bool       m_isValid;
    int        m_dimension;
    int        m_neighborhoodType;

    void createImageGray(QImage *imageIn, CImageInt *imageOut);
    void initNeighborhood(void);
    void computeDilation(void);
    void computeErosion(void);
    void computeOpening(void);
    void computeClosing(void);
    void computeInteriorGradient(void);
    void computeExteriorGradient(void);
    void computeMorphologicalGradient(void);
    void computeHitOrMiss(void);
    bool computeThinning(void);
    void computeSkeletonizing(void);
    void CImage2QImage(CImageInt *imageIn, QImage *imageOut);
};

#endif // OP_MORPHO_MATHS_HEADER
