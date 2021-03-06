//------------------------------------------------------------------------------
//! @file OpMorphoMaths.h
//! @brief Header file of the MainWindow class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

#ifndef MAIN_WINDOW_HEADER
#define MAIN_WINDOW_HEADER

//------------------------------------------------------------------------------
// Include(s) :

#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QString>


//------------------------------------------------------------------------------
// Classe(s) :

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void openImage(void);
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
    void displayEdgeDetectionLaplacianConnectedness4(void);
    void displayEdgeDetectionLaplacianConnectedness8(void);
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
    QString m_imageFilename;
    QLabel  m_labelImage;
    QImage  m_imageOrigin;
};

#endif // MAIN_WINDOW_HEADER
