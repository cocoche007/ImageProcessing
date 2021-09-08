//------------------------------------------------------------------------------
//! @file Sampling.h
//! @brief Header file of the CSampling class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef SAMPLING_HEADER
#define SAMPLING_HEADER

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>

#include "../../Commun/Image/cimage.h"


//------------------------------------------------------------------------------
// Classe(s) :

class CSampling
{
public:
    CSampling(QImage *imageIn);
    ~CSampling(void);

    QImage *getImageTreated(void);
    void    computeFourierTransform(void);

private:
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // SAMPLING_HEADER
