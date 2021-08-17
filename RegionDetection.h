//------------------------------------------------------------------------------
//! @file RegionDetection.h
//! @brief Header file of the CRegionDetection class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __REGION_DETECTION_H__
#define __REGION_DETECTION_H__

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>

#include "../../Commun/Image/cimage.h"


//------------------------------------------------------------------------------
// Enumeration(s):

enum DETECTION_REGION_TYPE
{
    DETECTION_REGION_UNKNOWN,
    DETECTION_REGION_LINE
};


//------------------------------------------------------------------------------
// Classe(s) :

class CRegionDetection
{
public:
    CRegionDetection(QImage *imageIn = NULL);
    ~CRegionDetection(void);

    QImage *getImageTreated(void);
    void    computeDetectionRegion(DETECTION_REGION_TYPE detectionRegionType);

private:
    QImage *   m_imageOrigin;
    QImage *   m_imageTreated;
    CImageInt *m_imageGray;
    bool       m_isValid;

    void createImageGray(QImage *imageIn, CImageInt *imageOut);
    void computeLine(void);
    void CImage2QImage(CImageInt *imageIn, QImage *imageOut);
};

#endif // __REGION_DETECTION_H__
