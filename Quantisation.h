//------------------------------------------------------------------------------
//! @file Quantisation.h
//! @brief Header file of the CQuantisation class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __QUANTISATION_H__
#define __QUANTISATION_H__

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>


//------------------------------------------------------------------------------
// Classe(s) :

class CQuantisation
{
public :
    CQuantisation( QImage *imageIn);
    ~CQuantisation();

    QImage *getImageTreated( void);
    void    computeGrayQuantisation( int quantisationLevel);
    void    computeRGBQuantisation( int quantisationLevel);
    
private :
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // __QUANTISATION_H__
