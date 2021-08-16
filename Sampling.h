//------------------------------------------------------------------------------
//! @file Sampling.h
//! @brief Header du fichier Sampling.cpp
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __SAMPLING_H__
#define __SAMPLING_H__

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>
#include "../../Commun/Image/cimage.h"


//------------------------------------------------------------------------------
// Classe(s) :

class CSampling
{
public :
    CSampling( QImage *imageIn);
    ~CSampling( void);

    QImage *getImageTreated( void);
    void    computeFourierTransform( void);
    
private :
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // __SAMPLING_H__
