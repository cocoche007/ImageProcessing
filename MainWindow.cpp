//------------------------------------------------------------------------------
//! @file MainWindow.cpp
//! @brief Definition file of the MainWindow class
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

#include "ColorModel.h"
#include "EdgeDetection.h"
#include "GeometricTransformation.h"
#include "MainWindow.h"
#include "Quantisation.h"
#include "RegionDetection.h"
#include "Sampling.h"
#include "TreatedImageWindow.h"


//------------------------------------------------------------------------------
// Public Method(s):

//------------------------------------------------------------------------------
//! MainWindow constructor
//!
//! @param parent The parent widget
//!
//! @return The created object
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *    centralArea                              = new QWidget;
    QMenu *      menuFile                                 = menuBar()->addMenu(tr("&Fichier"));
    QMenu *      menuColorModel                           = menuBar()->addMenu(tr("&Modele"));
    QMenu *      menuQuantisation                         = menuBar()->addMenu(tr("&Quantification"));
    QMenu *      menuSampling                             = menuBar()->addMenu(tr("&Echantillonnage"));
    QMenu *      menuGeometricTransformation              = menuBar()->addMenu(tr("&Transfo Géo"));
    QMenu *      menuEdgeDetection                        = menuBar()->addMenu(tr("&Détection Contour"));
    QMenu *      menuOpMorphoMaths                        = menuBar()->addMenu(tr("&Op. Morphomathématiques"));
    QMenu *      menuDetectionRegion                      = menuBar()->addMenu(tr("&Détection Région"));
    QMenu *      menuEdgeDetectionLaplacian               = NULL;
    QMenu *      menuEdgeDetectionDeriche                 = NULL;
    QAction *    actionOpen                               = new QAction(tr("&Ouvrir"), this);
    QAction *    actionQuit                               = new QAction(tr("&Quitter"), this);
    QAction *    actionDisplayY                           = new QAction(tr("&Y (YUV)"), this);
    QAction *    actionDisplayU                           = new QAction(tr("&U (YUV)"), this);
    QAction *    actionDisplayV                           = new QAction(tr("&V (YUV)"), this);
    QAction *    actionQuantisationGray                   = new QAction(tr("&Niveau de gris"), this);
    QAction *    actionQuantisationRGB                    = new QAction(tr("&Couleur"), this);
    QAction *    actionFourierTransform                   = new QAction(tr("&Transformée de Fourier"), this);
    QAction *    actionGeometricTransformationRotation    = new QAction(tr("&Rotation"), this);
    QAction *    actionGeometricTransformationScale       = new QAction(tr("&Homothétie"), this);
    QAction *    actionGeometricTransformationShear       = new QAction(tr("&Cisaillement"), this);
    QAction *    actionEdgeDetectionSimple                = new QAction(tr("&Naïf"), this);
    QAction *    actionEdgeDetectionRoberts               = new QAction(tr("&Roberts"), this);
    QAction *    actionEdgeDetectionSobel                 = new QAction(tr("&Sobel"), this);
    QAction *    actionEdgeDetectionPrewitt               = new QAction(tr("&Prewitt"), this);
    QAction *    actionEdgeDetectionKirsch                = new QAction(tr("&Kirsch"), this);
    QAction *    actionEdgeDetectionLaplacianConnexity4   = new QAction(tr("&Connexité 4"), this);
    QAction *    actionEdgeDetectionLaplacianConnexity8   = new QAction(tr("&Connexité 8"), this);
    QAction *    actionEdgeDetectionLaplacianDOG          = new QAction(tr("&DOG"), this);
    QAction *    actionEdgeDetectionDericheSmooth         = new QAction(tr("&Lissage"), this);
    QAction *    actionEdgeDetectionDericheDerivative     = new QAction(tr("&Dérivée"), this);
    QAction *    actionEdgeDetectionDericheLaplacian      = new QAction(tr("&Laplacien"), this);
    QAction *    actionOpMorphoMathsDilation              = new QAction(tr("&Dilatation"), this);
    QAction *    actionOpMorphoMathsErosion               = new QAction(tr("&Erosion"), this);
    QAction *    actionOpMorphoMathsOpening               = new QAction(tr("&Ouverture"), this);
    QAction *    actionOpMorphoMathsClosing               = new QAction(tr("&Fermeture"), this);
    QAction *    actionOpMorphoMathsInteriorGradient      = new QAction(tr("&Contour intérieur"), this);
    QAction *    actionOpMorphoMathsExteriorGradient      = new QAction(tr("&Contour extérieur"), this);
    QAction *    actionOpMorphoMathsMorphologicalGradient = new QAction(tr("&Gradient morphologique"), this);
    QAction *    actionOpMorphoMathsHitOrMiss             = new QAction(tr("&Tout ou rien"), this);
    QAction *    actionOpMorphoMathsThinning              = new QAction(tr("&Amincissement"), this);
    QAction *    actionOpMorphoMathsSkeletonizing         = new QAction(tr("&Squelettisation"), this);
    QAction *    actionRegionDetectionLine                = new QAction(tr("&Droite"), this);
    QVBoxLayout *layout                                   = new QVBoxLayout;

    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);

    menuColorModel->addAction(actionDisplayY);
    menuColorModel->addAction(actionDisplayU);
    menuColorModel->addAction(actionDisplayV);

    menuQuantisation->addAction(actionQuantisationGray);
    menuQuantisation->addAction(actionQuantisationRGB);

    menuSampling->addAction(actionFourierTransform);

    menuGeometricTransformation->addAction(actionGeometricTransformationRotation);
    menuGeometricTransformation->addAction(actionGeometricTransformationScale);
    menuGeometricTransformation->addAction(actionGeometricTransformationShear);

    menuEdgeDetection->addAction(actionEdgeDetectionSimple);
    menuEdgeDetection->addAction(actionEdgeDetectionRoberts);
    menuEdgeDetection->addAction(actionEdgeDetectionSobel);
    menuEdgeDetection->addAction(actionEdgeDetectionPrewitt);
    menuEdgeDetection->addAction(actionEdgeDetectionKirsch);
    menuEdgeDetectionLaplacian = menuEdgeDetection->addMenu(tr("&Laplacien"));
    menuEdgeDetectionLaplacian->addAction(actionEdgeDetectionLaplacianConnexity4);
    menuEdgeDetectionLaplacian->addAction(actionEdgeDetectionLaplacianConnexity8);
    menuEdgeDetectionDeriche = menuEdgeDetection->addMenu(tr("&Deriche"));
    menuEdgeDetectionLaplacian->addAction(actionEdgeDetectionLaplacianDOG);
    menuEdgeDetectionDeriche->addAction(actionEdgeDetectionDericheSmooth);
    menuEdgeDetectionDeriche->addAction(actionEdgeDetectionDericheDerivative);
    menuEdgeDetectionDeriche->addAction(actionEdgeDetectionDericheLaplacian);

    menuOpMorphoMaths->addAction(actionOpMorphoMathsDilation);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsErosion);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsOpening);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsClosing);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsInteriorGradient);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsExteriorGradient);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsMorphologicalGradient);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsHitOrMiss);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsThinning);
    menuOpMorphoMaths->addAction(actionOpMorphoMathsSkeletonizing);

    menuDetectionRegion->addAction(actionRegionDetectionLine);

    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(actionDisplayY, SIGNAL(triggered()), this, SLOT(displayComponentY()));
    connect(actionDisplayU, SIGNAL(triggered()), this, SLOT(displayComponentU()));
    connect(actionDisplayV, SIGNAL(triggered()), this, SLOT(displayComponentV()));

    connect(actionQuantisationGray, SIGNAL(triggered()), this, SLOT(displayQuantisationGray()));
    connect(actionQuantisationRGB, SIGNAL(triggered()), this, SLOT(displayQuantisationRGB()));

    connect(actionFourierTransform, SIGNAL(triggered()), this, SLOT(displayFourierTransform()));

    connect(actionGeometricTransformationRotation, SIGNAL(triggered()), this, SLOT(displayRotation()));
    connect(actionGeometricTransformationScale, SIGNAL(triggered()), this, SLOT(displayScale()));
    connect(actionGeometricTransformationShear, SIGNAL(triggered()), this, SLOT(displayShear()));

    connect(actionEdgeDetectionSimple, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionSimple()));
    connect(actionEdgeDetectionRoberts, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionRoberts()));
    connect(actionEdgeDetectionSobel, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionSobel()));
    connect(actionEdgeDetectionPrewitt, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionPrewitt()));
    connect(actionEdgeDetectionKirsch, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionKirsch()));
    connect(actionEdgeDetectionLaplacianConnexity4, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionLaplacianConnexity4()));
    connect(actionEdgeDetectionLaplacianConnexity8, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionLaplacianConnexity8()));
    connect(actionEdgeDetectionLaplacianDOG, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionLaplacianDOG()));
    connect(actionEdgeDetectionDericheSmooth, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionDericheSmooth()));
    connect(actionEdgeDetectionDericheDerivative, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionDericheDerivative()));
    connect(actionEdgeDetectionDericheLaplacian, SIGNAL(triggered()), this, SLOT(displayEdgeDetectionDericheLaplacian()));

    connect(actionOpMorphoMathsDilation, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsDilation()));
    connect(actionOpMorphoMathsErosion, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsErosion()));
    connect(actionOpMorphoMathsOpening, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsOpening()));
    connect(actionOpMorphoMathsClosing, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsClosing()));
    connect(actionOpMorphoMathsInteriorGradient, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsInteriorGradient()));
    connect(actionOpMorphoMathsExteriorGradient, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsExteriorGradient()));
    connect(actionOpMorphoMathsMorphologicalGradient, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsMorphologicalGradient()));
    connect(actionOpMorphoMathsHitOrMiss, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsHitOrMiss()));
    connect(actionOpMorphoMathsThinning, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsThinning()));
    connect(actionOpMorphoMathsSkeletonizing, SIGNAL(triggered()), this, SLOT(displayOpMorphoMathsSkeletonizing()));

    connect(actionRegionDetectionLine, SIGNAL(triggered()), this, SLOT(displayRegionDetectionLine()));

    layout->addWidget(&m_labelImage);
    centralArea->setLayout(layout);
    setCentralWidget(centralArea);
}


//------------------------------------------------------------------------------
//! Destructor
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}


//------------------------------------------------------------------------------
// Public Slot Method(s)

//------------------------------------------------------------------------------
//! Open the image file
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::openImage(void)
{
    m_imageFilename = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QString(), tr("Images (*.png *.gif *.jpg *.jpeg *.bmp)"));

    m_imageOrigin.load(m_imageFilename);

    m_labelImage.setPixmap(QPixmap::fromImage(m_imageOrigin));
}


//------------------------------------------------------------------------------
//! Display the Y part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentY(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_COLOR_MODEL_COMPONENT_Y, &m_imageOrigin);

    treatedImageWindow->display();
}


//------------------------------------------------------------------------------
//! Display the U part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentU(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_COLOR_MODEL_COMPONENT_U, &m_imageOrigin);

    treatedImageWindow->display();
}


//------------------------------------------------------------------------------
//! Display the V part of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentV(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_COLOR_MODEL_COMPONENT_V, &m_imageOrigin);

    treatedImageWindow->display();
}


//------------------------------------------------------------------------------
//! Display the grayscale quantisation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayQuantisationGray(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_QUANTISATION_GRAY, &m_imageOrigin);

    treatedImageWindow->displayQuantisationGray();
}


//------------------------------------------------------------------------------
//! Display the colored quantisation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayQuantisationRGB(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_QUANTISATION_RGB, &m_imageOrigin);

    treatedImageWindow->displayQuantisationRGB();
}


//------------------------------------------------------------------------------
//! Display the Fourier transformation of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayFourierTransform(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_SAMPLING, &m_imageOrigin);

    treatedImageWindow->displayFourierTransform();
}


//------------------------------------------------------------------------------
//! Display the rotated the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayRotation(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION, &m_imageOrigin);

    treatedImageWindow->displayRotation();
}


//------------------------------------------------------------------------------
//! Display the resulted by homothetie of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayScale(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE, &m_imageOrigin);

    treatedImageWindow->displayScale();
}


//------------------------------------------------------------------------------
//! Display the resulted by shear of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayShear(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR, &m_imageOrigin);

    treatedImageWindow->displayShear();
}


//------------------------------------------------------------------------------
//! Display the resulted by naive edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionSimple(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_SIMPLE, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionSimple();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Roberts" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionRoberts(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_ROBERTS, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionRoberts();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Sobel" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionSobel(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_SOBEL, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionSobel();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Prewitt" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionPrewitt(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_PREWITT, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionPrewitt();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Kirsch" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionKirsch(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_KIRSCH, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionKirsch();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Laplacian with connectivity 4" edge detection of
//! the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianConnexity4(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianConnexity4();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Laplacian with connectivity 8" edge detection of
//! the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianConnexity8(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianConnexity8();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Laplacian DOG" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianDOG(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianDOG();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Derich smoothing filter" edge detection of the
//! image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheSmooth(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheSmooth();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Derivated Deriche" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheDerivative(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheDerivative();
}


//------------------------------------------------------------------------------
//! Display the resulted by "Laplacian Deriche" edge detection of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheLaplacian(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheLaplacian();
}


//------------------------------------------------------------------------------
//! Display the resulted dilated image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsDilation(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_DILATION, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsDilation();
}


//------------------------------------------------------------------------------
//! Display the resulted eroded image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsErosion(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_EROSION, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsErosion();
}


//------------------------------------------------------------------------------
//! Display the resulted "opened" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsOpening(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_OPENING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsOpening();
}


//------------------------------------------------------------------------------
//! Display the resulted "closed" image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsClosing(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_CLOSING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsClosing();
}


//------------------------------------------------------------------------------
//! Display the resulted interior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsInteriorGradient(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsInteriorGradient();
}


//------------------------------------------------------------------------------
//! Display the resulted exterior gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsExteriorGradient(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsExteriorGradient();
}


//------------------------------------------------------------------------------
//! Display the resulted morphological gradient of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsMorphologicalGradient(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsMorphologicalGradient();
}


//------------------------------------------------------------------------------
//! Display the resulted "hit or miss" of the image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsHitOrMiss(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsHitOrMiss();
}


//------------------------------------------------------------------------------
//! Display the resulted thinned image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsThinning(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_THINNING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsThinning();
}


//------------------------------------------------------------------------------
//! Display the resulted skeletonized image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsSkeletonizing(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_OP_MORPHO_MATHS_SKELETONIZING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsSkeletonizing();
}


//------------------------------------------------------------------------------
//! Display the resulted image after a line detection
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayRegionDetectionLine(void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow(PROCESSING_REGION_DETECTION_LINE, &m_imageOrigin);

    treatedImageWindow->displayRegionDetectionLine();
}
