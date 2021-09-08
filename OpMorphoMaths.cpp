//------------------------------------------------------------------------------
//! @file OpMorphoMaths.cpp
//! @brief Definition file of the COpMorphoMaths class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include "OpMorphoMaths.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! COpMorphoMaths constructor for a given image
//!
//! @param imageIn The input image
//!
//! @return The created object
//------------------------------------------------------------------------------
COpMorphoMaths::COpMorphoMaths(QImage *imageIn)
{
    m_imageOrigin = imageIn;
    if (m_imageOrigin)
    {
        m_imageTreated = new QImage(m_imageOrigin->size(), QImage::Format_RGB32);
        m_imageGray    = new CImageInt(m_imageOrigin->width(), m_imageOrigin->height());
    }

    createImageGray(m_imageOrigin, m_imageGray);

    if (m_imageOrigin && m_imageTreated && m_imageGray)
        m_isValid = true;
    else
        m_isValid = false;

    m_dimension = 0;
}


//------------------------------------------------------------------------------
//! Destructor
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
COpMorphoMaths::~COpMorphoMaths()
{
    delete m_imageTreated;
    delete m_imageGray;
    delete m_neighborhood;
}


//------------------------------------------------------------------------------
//! Get the treated image
//!
//! @param _
//!
//! @return A pointer on the treated image
//------------------------------------------------------------------------------
QImage *COpMorphoMaths::getImageTreated(void)
{
    return m_imageTreated;
}


//------------------------------------------------------------------------------
//! Get the dimension of the neighborhood
//!
//! @param _
//!
//! @return The dimension
//------------------------------------------------------------------------------
int COpMorphoMaths::getDimension(void)
{
    return m_dimension;
}


//------------------------------------------------------------------------------
//! Start method for the MorphoMaths operations
//!
//! @param operationType The operation type
//! @param dimension The neighborhood dimension
//! @param neighborhoodType The neighborhood type
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeOpMorphoMaths(OPMORPHOMATHS_TYPE operationType, int dimension, int neighborhoodType)
{
    m_dimension        = dimension;
    m_neighborhoodType = neighborhoodType;

    initNeighborhood();

    if (m_isValid)
    {
        switch (operationType)
        {
            case OPMORPHOMATHS_DILATION:
                computeDilation();
                break;

            case OPMORPHOMATHS_EROSION:
                computeErosion();
                break;

            case OPMORPHOMATHS_OPENING:
                computeOpening();
                break;

            case OPMORPHOMATHS_CLOSING:
                computeClosing();
                break;

            case OPMORPHOMATHS_INTERIOR_GRADIENT:
                computeInteriorGradient();
                break;

            case OPMORPHOMATHS_EXTERIOR_GRADIENT:
                computeExteriorGradient();
                break;

            case OPMORPHOMATHS_MORPHOLOGICAL_GRADIENT:
                computeMorphologicalGradient();
                break;

            case OPMORPHOMATHS_HIT_OR_MISS:
                computeHitOrMiss();
                break;

            case OPMORPHOMATHS_THINNING:
                computeThinning();
                break;

            case OPMORPHOMATHS_SKELETONIZING:
                computeSkeletonizing();
                break;

            case OPMORPHOMATHS_UNKNOWN:
            default:
                break;
        }
    }
}


//------------------------------------------------------------------------------
// Private Method(s):

//------------------------------------------------------------------------------
//! Create a grayscale image (binary) for a given image
//!
//! @param imageIn The input image
//! @param imageOut The output image
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::createImageGray(QImage *imageIn, CImageInt *imageOut)
{
    int GOut;

    if (imageIn && imageOut)
    {
        for (int x = 0; x < imageIn->width(); x++)
        {
            for (int y = 0; y < imageIn->height(); y++)
            {
                GOut = (299 * qRed(imageIn->pixel(x, y)) +
                        587 * qGreen(imageIn->pixel(x, y)) +
                        114 * qBlue(imageIn->pixel(x, y))) /
                       1000;

                if (GOut < 128)
                    (*imageOut)(x, y) = 0;
                else
                    (*imageOut)(x, y) = CIMAGEINT_MAX;
            }
        }
    }
}


//------------------------------------------------------------------------------
//! Initialize the neighborhood depending on the type (see the
//! computeOpMorphoMaths method)
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::initNeighborhood(void)
{
    m_neighborhood = new CImageInt(m_dimension * 2 + 1, m_dimension * 2 + 1);

    if (m_neighborhood)
    {
        switch (m_neighborhoodType)
        {
            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4:
                for (int x = 0; x < m_neighborhood->getWidth(); x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                for (int y = 0; y < m_neighborhood->getHeight(); y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_8:
                for (int x = 0; x < m_neighborhood->getWidth(); x++)
                    for (int y = 0; y < m_neighborhood->getHeight(); y++)
                        (*m_neighborhood)(x, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_VERTICAL:
                for (int y = 0; y < m_neighborhood->getHeight(); y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_HORIZONTAL:
                for (int x = 0; x < m_neighborhood->getWidth(); x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_UP:
                for (int x = 0; x < m_neighborhood->getWidth(); x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                for (int y = 0; y <= m_dimension; y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_DOWN:
                for (int x = 0; x < m_neighborhood->getWidth(); x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                for (int y = m_dimension + 1; y < m_neighborhood->getHeight(); y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_LEFT:
                for (int x = 0; x <= m_dimension; x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                for (int y = 0; y < m_neighborhood->getHeight(); y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_CONNEXITY_4_RIGHT:
                for (int x = m_dimension + 1; x < m_neighborhood->getWidth(); x++)
                    (*m_neighborhood)(x, m_dimension) = CIMAGEINT_MAX;
                for (int y = 0; y < m_neighborhood->getHeight(); y++)
                    (*m_neighborhood)(m_dimension, y) = CIMAGEINT_MAX;
                break;

            case OPMORPHOMATHS_NEIGHBORHOOD_UNKNOWN:
            default:
                break;
        }
    }
}


//------------------------------------------------------------------------------
//! Compute the dilated image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeDilation(void)
{
    CImageInt *dilateImage = nullptr;

    dilateImage = m_imageGray->opDilation(m_neighborhood);
    CImage2QImage(dilateImage, m_imageTreated);

    delete dilateImage;
}


//------------------------------------------------------------------------------
//! Compute the eroded image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeErosion(void)
{
    CImageInt *erodedImage = nullptr;

    erodedImage = m_imageGray->opErosion(m_neighborhood);
    CImage2QImage(erodedImage, m_imageTreated);

    delete erodedImage;
}


//------------------------------------------------------------------------------
//! Compute the "opened" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeOpening(void)
{
    CImageInt *erodedImage = nullptr;
    CImageInt *dilateImage = nullptr;

    erodedImage = m_imageGray->opErosion(m_neighborhood);
    if (erodedImage)
        dilateImage = erodedImage->opDilation(m_neighborhood);
    CImage2QImage(dilateImage, m_imageTreated);

    delete erodedImage;
    delete dilateImage;
}


//------------------------------------------------------------------------------
//! Compute the "closed" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeClosing(void)
{
    CImageInt *dilateImage = nullptr;
    CImageInt *erodedImage = nullptr;

    dilateImage = m_imageGray->opDilation(m_neighborhood);
    if (dilateImage)
        erodedImage = dilateImage->opErosion(m_neighborhood);
    CImage2QImage(erodedImage, m_imageTreated);

    delete dilateImage;
    delete erodedImage;
}


//------------------------------------------------------------------------------
//! Compute the interior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeInteriorGradient(void)
{
    CImageInt *erodedImage        = nullptr;
    CImageInt *complementaryImage = nullptr;

    erodedImage = m_imageGray->opErosion(m_neighborhood);
    if (erodedImage)
        complementaryImage = m_imageGray->opComplementary(erodedImage);
    CImage2QImage(complementaryImage, m_imageTreated);

    delete erodedImage;
    delete complementaryImage;
}


//------------------------------------------------------------------------------
//! Compute the exterior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeExteriorGradient(void)
{
    CImageInt *dilateImage        = nullptr;
    CImageInt *complementaryImage = nullptr;

    dilateImage = m_imageGray->opDilation(m_neighborhood);
    if (dilateImage)
        complementaryImage = dilateImage->opComplementary(m_imageGray);
    CImage2QImage(complementaryImage, m_imageTreated);

    delete dilateImage;
    delete complementaryImage;
}


//------------------------------------------------------------------------------
//! Compute the morphological gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeMorphologicalGradient(void)
{
    CImageInt *dilateImage        = nullptr;
    CImageInt *erodedImage        = nullptr;
    CImageInt *complementaryImage = nullptr;

    dilateImage = m_imageGray->opDilation(m_neighborhood);
    erodedImage = m_imageGray->opErosion(m_neighborhood);
    if (dilateImage)
        complementaryImage = dilateImage->opComplementary(erodedImage);
    CImage2QImage(complementaryImage, m_imageTreated);

    delete dilateImage;
    delete erodedImage;
    delete complementaryImage;
}


//------------------------------------------------------------------------------
//! Compute the "hit or miss" transformation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeHitOrMiss(void)
{
    CImageInt *erodedImage1                   = nullptr;
    CImageInt *erodedImage2                   = nullptr;
    CImageInt *negativeImage                  = nullptr;
    CImageInt *intersectionImage              = nullptr;
    CImageInt *localComplementaryNeighborhood = nullptr;

    erodedImage1  = m_imageGray->opErosion(m_neighborhood);
    negativeImage = m_imageGray->opNegative();
    if (negativeImage)
    {
        localComplementaryNeighborhood = m_neighborhood->opLocalComplementary();

        if (localComplementaryNeighborhood)
            erodedImage2 = negativeImage->opErosion(localComplementaryNeighborhood);
    }
    if (erodedImage1)
        intersectionImage = erodedImage1->opIntersection(erodedImage2);

    CImage2QImage(intersectionImage, m_imageTreated);

    delete erodedImage1;
    delete erodedImage2;
    delete negativeImage;
    delete intersectionImage;
    delete localComplementaryNeighborhood;
}


//------------------------------------------------------------------------------
//! Compute the thinness image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
bool COpMorphoMaths::computeThinning(void)
{
    CImageInt * thinImage = new CImageInt(m_imageGray->getWidth(), m_imageGray->getHeight(), m_imageGray);
    CImageBool *passImage = new CImageBool(m_imageGray->getWidth(), m_imageGray->getHeight());
    bool        ret       = false;
    int         nNeighbors;
    int         nTransitions;
    bool        conditionConnection;
    int         v0, v1, v2, v3, v4, v5, v6, v7;

    if (thinImage && passImage)
    {
        for (int i = 0; i < m_dimension; i++)
        {
            for (int noPass = 1; noPass <= 2; noPass++)
            {
                passImage->reset();

                for (int x = 0; x < thinImage->getWidth(); x++)
                {
                    for (int y = 0; y < thinImage->getHeight(); y++)
                    {
                        if (thinImage->get(x, y) != 0)
                        {
                            v0 = ((thinImage->get(x, y + 1) == 0) ? 0 : 1);
                            v1 = ((thinImage->get(x + 1, y + 1) == 0) ? 0 : 1);
                            v2 = ((thinImage->get(x + 1, y) == 0) ? 0 : 1);
                            v3 = ((thinImage->get(x + 1, y - 1) == 0) ? 0 : 1);
                            v4 = ((thinImage->get(x, y - 1) == 0) ? 0 : 1);
                            v5 = ((thinImage->get(x - 1, y - 1) == 0) ? 0 : 1);
                            v6 = ((thinImage->get(x - 1, y) == 0) ? 0 : 1);
                            v7 = ((thinImage->get(x - 1, y + 1) == 0) ? 0 : 1);

                            if (noPass == 1)
                                conditionConnection = (!v0 || !v2 || !v4) && (!v2 || !v4 || !v6);
                            else
                                conditionConnection = (!v0 || !v2 || !v6) && (!v0 || !v4 || !v6);

                            nTransitions = 0;
                            if (v0 && !v1)
                                nTransitions++;
                            if (v1 && !v2)
                                nTransitions++;
                            if (v2 && !v3)
                                nTransitions++;
                            if (v3 && !v4)
                                nTransitions++;
                            if (v4 && !v5)
                                nTransitions++;
                            if (v5 && !v6)
                                nTransitions++;
                            if (v6 && !v7)
                                nTransitions++;
                            if (v7 && !v0)
                                nTransitions++;

                            nNeighbors = v0 + v1 + v2 + v3 + v4 + v5 + v6 + v7;

                            if ((nNeighbors >= 2) &&
                                (nNeighbors <= 6) &&
                                (nTransitions == 1) &&
                                conditionConnection)
                            {
                                (*passImage)(x, y) = true;
                                ret                = true;
                            }
                        }
                    }
                }

                for (int x = 0; x < thinImage->getWidth(); x++)
                {
                    for (int y = 0; y < thinImage->getHeight(); y++)
                    {
                        if (passImage->get(x, y))
                            (*thinImage)(x, y) = 0;
                    }
                }
            }
        }
    }

    CImage2QImage(thinImage, m_imageTreated);

    delete thinImage;
    delete passImage;

    return ret;
}


//------------------------------------------------------------------------------
//! Compute the skeletonized image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::computeSkeletonizing(void)
{
    bool thinning;

    m_dimension = 1;

    do
    {
        thinning = computeThinning();
        createImageGray(m_imageTreated, m_imageGray);
    } while (thinning);
}


//------------------------------------------------------------------------------
//! Convert a CImageInt to a QImage
//!
//! @param imageIn The input image
//! @param imageOut The output image
//!
//! @return _
//------------------------------------------------------------------------------
void COpMorphoMaths::CImage2QImage(CImageInt *imageIn, QImage *imageOut)
{
    int GOut;

    if (imageIn && imageOut)
    {
        for (int xOut = 0; xOut < imageOut->width(); xOut++)
        {
            for (int yOut = 0; yOut < imageOut->height(); yOut++)
            {
                GOut = imageIn->get(xOut, yOut);
                imageOut->setPixel(xOut, yOut, qRgb(GOut, GOut, GOut));
            }
        }
    }
}
