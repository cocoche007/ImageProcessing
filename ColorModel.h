//------------------------------------------------------------------------------
//! @file ColorModel.h
//! @brief Header file of the CColorModel class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef __COLOR_MODEL_H__
#define __COLOR_MODEL_H__

//------------------------------------------------------------------------------
// Include(s):

#include <QImage>


//------------------------------------------------------------------------------
// Classe(s):

class CColorModel
{
public :
    CColorModel( QImage *imageIn);
    ~CColorModel();

    QImage *getImageTreated( void);
    void    computeComponentY( void);
    void    computeComponentU( void);
    void    computeComponentV( void);

private :
    QImage *m_imageOrigin;
    QImage *m_imageTreated;
};

#endif // __COLOR_MODEL_H__
