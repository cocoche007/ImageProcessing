//------------------------------------------------------------------------------
//! @file MainWindow.cpp
//! @brief Fichier où la classe MainWindow est définie
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
#include "TreatedImageWindow.h"
#include "MainWindow.h"
#include "ColorModel.h"
#include "EdgeDetection.h"
#include "GeometricTransformation.h"
#include "Quantisation.h"
#include "RegionDetection.h"
#include "Sampling.h"


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) :

//------------------------------------------------------------------------------
//! Constructeur d'objet MainWindow
//!
//! @param parent : Le widget parent
//!
//! @return L'objet créé
//------------------------------------------------------------------------------
MainWindow::MainWindow( QWidget *parent)
    : QMainWindow( parent)
{
    QWidget     *centralArea                              = new QWidget;
    QMenu       *menuFile                                 = menuBar()->addMenu( tr( "&Fichier"));
    QMenu       *menuColorModel                           = menuBar()->addMenu( tr( "&Modele"));
    QMenu       *menuQuantisation                         = menuBar()->addMenu( tr( "&Quantification"));
    QMenu       *menuSampling                             = menuBar()->addMenu( tr( "&Echantillonnage"));
    QMenu       *menuGeometricTransformation              = menuBar()->addMenu( tr( "&Transfo Géo"));
    QMenu       *menuEdgeDetection                        = menuBar()->addMenu( tr( "&Détection Contour"));
    QMenu       *menuOpMorphoMaths                        = menuBar()->addMenu( tr( "&Op. Morphomathématiques"));
    QMenu       *menuDetectionRegion                      = menuBar()->addMenu( tr( "&Détection Région"));
    QMenu       *menuEdgeDetectionLaplacian               = NULL;
    QMenu       *menuEdgeDetectionDeriche                 = NULL;
    QAction     *actionOpen                               = new QAction( tr( "&Ouvrir"), this);
    QAction     *actionQuit                               = new QAction( tr( "&Quitter"), this);
    QAction     *actionDisplayY                           = new QAction( tr( "&Y (YUV)"), this);
    QAction     *actionDisplayU                           = new QAction( tr( "&U (YUV)"), this);
    QAction     *actionDisplayV                           = new QAction( tr( "&V (YUV)"), this);
    QAction     *actionQuantisationGray                   = new QAction( tr( "&Niveau de gris"), this);
    QAction     *actionQuantisationRGB                    = new QAction( tr( "&Couleur"), this);
    QAction     *actionFourierTransform                   = new QAction( tr( "&Transformée de Fourier"), this);
    QAction     *actionGeometricTransformationRotation    = new QAction( tr( "&Rotation"), this);
    QAction     *actionGeometricTransformationScale       = new QAction( tr( "&Homothétie"), this);
    QAction     *actionGeometricTransformationShear       = new QAction( tr( "&Cisaillement"), this);
    QAction     *actionEdgeDetectionSimple                = new QAction( tr( "&Naïf"), this);
    QAction     *actionEdgeDetectionRoberts               = new QAction( tr( "&Roberts"), this);
    QAction     *actionEdgeDetectionSobel                 = new QAction( tr( "&Sobel"), this);
    QAction     *actionEdgeDetectionPrewitt               = new QAction( tr( "&Prewitt"), this);
    QAction     *actionEdgeDetectionKirsch                = new QAction( tr( "&Kirsch"), this);
    QAction     *actionEdgeDetectionLaplacianConnexity4   = new QAction( tr( "&Connexité 4"), this);
    QAction     *actionEdgeDetectionLaplacianConnexity8   = new QAction( tr( "&Connexité 8"), this);
    QAction     *actionEdgeDetectionLaplacianDOG          = new QAction( tr( "&DOG"), this);
    QAction     *actionEdgeDetectionDericheSmooth         = new QAction( tr( "&Lissage"), this);
    QAction     *actionEdgeDetectionDericheDerivative     = new QAction( tr( "&Dérivée"), this);
    QAction     *actionEdgeDetectionDericheLaplacian      = new QAction( tr( "&Laplacien"), this);
    QAction     *actionOpMorphoMathsDilation              = new QAction( tr( "&Dilatation"), this);
    QAction     *actionOpMorphoMathsErosion               = new QAction( tr( "&Erosion"), this);
    QAction     *actionOpMorphoMathsOpening               = new QAction( tr( "&Ouverture"), this);
    QAction     *actionOpMorphoMathsClosing               = new QAction( tr( "&Fermeture"), this);
    QAction     *actionOpMorphoMathsInteriorGradient      = new QAction( tr( "&Contour intérieur"), this);
    QAction     *actionOpMorphoMathsExteriorGradient      = new QAction( tr( "&Contour extérieur"), this);
    QAction     *actionOpMorphoMathsMorphologicalGradient = new QAction( tr( "&Gradient morphologique"), this);
    QAction     *actionOpMorphoMathsHitOrMiss             = new QAction( tr( "&Tout ou rien"), this);
    QAction     *actionOpMorphoMathsThinning              = new QAction( tr( "&Amincissement"), this);
    QAction     *actionOpMorphoMathsSkeletonizing         = new QAction( tr( "&Squelettisation"), this);
    QAction     *actionRegionDetectionLine                = new QAction( tr( "&Droite"), this);
    QVBoxLayout *layout                                   = new QVBoxLayout;

    menuFile->addAction( actionOpen);
    menuFile->addAction( actionQuit);

    menuColorModel->addAction( actionDisplayY);
    menuColorModel->addAction( actionDisplayU);
    menuColorModel->addAction( actionDisplayV);

    menuQuantisation->addAction( actionQuantisationGray);
    menuQuantisation->addAction( actionQuantisationRGB);

    menuSampling->addAction( actionFourierTransform);

    menuGeometricTransformation->addAction( actionGeometricTransformationRotation);
    menuGeometricTransformation->addAction( actionGeometricTransformationScale);
    menuGeometricTransformation->addAction( actionGeometricTransformationShear);

    menuEdgeDetection->addAction( actionEdgeDetectionSimple);
    menuEdgeDetection->addAction( actionEdgeDetectionRoberts);
    menuEdgeDetection->addAction( actionEdgeDetectionSobel);
    menuEdgeDetection->addAction( actionEdgeDetectionPrewitt);
    menuEdgeDetection->addAction( actionEdgeDetectionKirsch);
    menuEdgeDetectionLaplacian = menuEdgeDetection->addMenu( tr( "&Laplacien"));
    menuEdgeDetectionLaplacian->addAction( actionEdgeDetectionLaplacianConnexity4);
    menuEdgeDetectionLaplacian->addAction( actionEdgeDetectionLaplacianConnexity8);
    menuEdgeDetectionDeriche = menuEdgeDetection->addMenu( tr( "&Deriche"));
    menuEdgeDetectionLaplacian->addAction( actionEdgeDetectionLaplacianDOG);
    menuEdgeDetectionDeriche->addAction( actionEdgeDetectionDericheSmooth);
    menuEdgeDetectionDeriche->addAction( actionEdgeDetectionDericheDerivative);
    menuEdgeDetectionDeriche->addAction( actionEdgeDetectionDericheLaplacian);

    menuOpMorphoMaths->addAction( actionOpMorphoMathsDilation);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsErosion);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsOpening);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsClosing);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsInteriorGradient);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsExteriorGradient);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsMorphologicalGradient);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsHitOrMiss);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsThinning);
    menuOpMorphoMaths->addAction( actionOpMorphoMathsSkeletonizing);

    menuDetectionRegion->addAction( actionRegionDetectionLine);

    connect( actionOpen, SIGNAL( triggered()), this, SLOT( openImage()));
    connect( actionQuit, SIGNAL( triggered()), qApp, SLOT( quit()));

    connect( actionDisplayY, SIGNAL( triggered()), this, SLOT( displayComponentY()));
    connect( actionDisplayU, SIGNAL( triggered()), this, SLOT( displayComponentU()));
    connect( actionDisplayV, SIGNAL( triggered()), this, SLOT( displayComponentV()));

    connect( actionQuantisationGray, SIGNAL( triggered()), this, SLOT( displayQuantisationGray()));
    connect( actionQuantisationRGB , SIGNAL( triggered()), this, SLOT( displayQuantisationRGB()));

    connect( actionFourierTransform, SIGNAL( triggered()), this, SLOT( displayFourierTransform()));

    connect( actionGeometricTransformationRotation, SIGNAL( triggered()), this, SLOT( displayRotation()));
    connect( actionGeometricTransformationScale   , SIGNAL( triggered()), this, SLOT( displayScale()));
    connect( actionGeometricTransformationShear   , SIGNAL( triggered()), this, SLOT( displayShear()));

    connect( actionEdgeDetectionSimple             , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionSimple()));
    connect( actionEdgeDetectionRoberts            , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionRoberts()));
    connect( actionEdgeDetectionSobel              , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionSobel()));
    connect( actionEdgeDetectionPrewitt            , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionPrewitt()));
    connect( actionEdgeDetectionKirsch             , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionKirsch()));
    connect( actionEdgeDetectionLaplacianConnexity4, SIGNAL( triggered()), this, SLOT( displayEdgeDetectionLaplacianConnexity4()));
    connect( actionEdgeDetectionLaplacianConnexity8, SIGNAL( triggered()), this, SLOT( displayEdgeDetectionLaplacianConnexity8()));
    connect( actionEdgeDetectionLaplacianDOG       , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionLaplacianDOG()));
    connect( actionEdgeDetectionDericheSmooth      , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionDericheSmooth()));
    connect( actionEdgeDetectionDericheDerivative  , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionDericheDerivative()));
    connect( actionEdgeDetectionDericheLaplacian   , SIGNAL( triggered()), this, SLOT( displayEdgeDetectionDericheLaplacian()));

    connect( actionOpMorphoMathsDilation             , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsDilation()));
    connect( actionOpMorphoMathsErosion              , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsErosion()));
    connect( actionOpMorphoMathsOpening              , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsOpening()));
    connect( actionOpMorphoMathsClosing              , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsClosing()));
    connect( actionOpMorphoMathsInteriorGradient     , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsInteriorGradient()));
    connect( actionOpMorphoMathsExteriorGradient     , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsExteriorGradient()));
    connect( actionOpMorphoMathsMorphologicalGradient, SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsMorphologicalGradient()));
    connect( actionOpMorphoMathsHitOrMiss            , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsHitOrMiss()));
    connect( actionOpMorphoMathsThinning             , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsThinning()));
    connect( actionOpMorphoMathsSkeletonizing        , SIGNAL( triggered()), this, SLOT( displayOpMorphoMathsSkeletonizing()));

    connect( actionRegionDetectionLine, SIGNAL( triggered()), this, SLOT( displayRegionDetectionLine()));

    layout->addWidget( &m_labelImage);
    centralArea->setLayout( layout);
    setCentralWidget( centralArea);
}

//------------------------------------------------------------------------------
//! Destructeur
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}


//------------------------------------------------------------------------------
// Fonction(s) Publique(s) Slot(s)

//------------------------------------------------------------------------------
//! Ouverture du fichier image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::openImage( void)
{
    m_imageFilename = QFileDialog::getOpenFileName( this, tr( "Ouvrir un fichier"), QString(), tr( "Images (*.png *.gif *.jpg *.jpeg *.bmp)"));

    m_imageOrigin.load( m_imageFilename);

    m_labelImage.setPixmap( QPixmap::fromImage( m_imageOrigin));
}

//------------------------------------------------------------------------------
//! Affichage de la composante Y de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentY( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_COLOR_MODEL_COMPONENT_Y, &m_imageOrigin);

    treatedImageWindow->display();
}

//------------------------------------------------------------------------------
//! Affichage de la composante U de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentU( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_COLOR_MODEL_COMPONENT_U, &m_imageOrigin);

    treatedImageWindow->display();
}

//------------------------------------------------------------------------------
//! Affichage de la composante V de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayComponentV( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_COLOR_MODEL_COMPONENT_V, &m_imageOrigin);

    treatedImageWindow->display();
}

//------------------------------------------------------------------------------
//! Affichage de la quantification en niveau de gris de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayQuantisationGray( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_QUANTISATION_GRAY, &m_imageOrigin);

    treatedImageWindow->displayQuantisationGray();
}

//------------------------------------------------------------------------------
//! Affichage de la quantification en couleur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayQuantisationRGB( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_QUANTISATION_RGB, &m_imageOrigin);

    treatedImageWindow->displayQuantisationRGB();
}

//------------------------------------------------------------------------------
//! Affichage de la Transformée de Fourier de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayFourierTransform( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_SAMPLING, &m_imageOrigin);

    treatedImageWindow->displayFourierTransform();
}

//------------------------------------------------------------------------------
//! Affichage de la rotation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayRotation( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_GEOMETRIC_TRANSFORMATION_ROTATION, &m_imageOrigin);

    treatedImageWindow->displayRotation();
}

//------------------------------------------------------------------------------
//! Affichage de l'homothétie de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayScale( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_GEOMETRIC_TRANSFORMATION_SCALE, &m_imageOrigin);

    treatedImageWindow->displayScale();
}

//------------------------------------------------------------------------------
//! Affichage du cisaillement de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayShear( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_GEOMETRIC_TRANSFORMATION_SHEAR, &m_imageOrigin);

    treatedImageWindow->displayShear();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours naïve de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionSimple( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_SIMPLE, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionSimple();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Roberts) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionRoberts( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_ROBERTS, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionRoberts();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Sobel) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionSobel( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_SOBEL, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionSobel();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Prewitt) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionPrewitt( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_PREWITT, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionPrewitt();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Kirsch) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionKirsch( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_KIRSCH, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionKirsch();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien Connexité 4)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianConnexity4( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_4, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianConnexity4();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien Connexité 8)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianConnexity8( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_LAPLACIAN_CONNEXITY_8, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianConnexity8();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Laplacien DOG) de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionLaplacianDOG( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_LAPLACIAN_DOG, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionLaplacianDOG();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Lissage)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheSmooth( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_DERICHE_SMOOTH, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheSmooth();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Dérivée)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheDerivative( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_DERICHE_DERIVATIVE, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheDerivative();
}

//------------------------------------------------------------------------------
//! Affichage de la détection de contours (Deriche Laplacien)
//! de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayEdgeDetectionDericheLaplacian( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_EDGE_DETECTION_DERICHE_LAPLACIAN, &m_imageOrigin);

    treatedImageWindow->displayEdgeDetectionDericheLaplacian();
}

//------------------------------------------------------------------------------
//! Affichage de la dilatation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsDilation( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_DILATION, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsDilation();
}

//------------------------------------------------------------------------------
//! Affichage de l'érosion de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsErosion( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_EROSION, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsErosion();
}

//------------------------------------------------------------------------------
//! Affichage de l'ouverture de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsOpening( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_OPENING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsOpening();
}

//------------------------------------------------------------------------------
//! Affichage de la fermeture de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsClosing( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_CLOSING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsClosing();
}

//------------------------------------------------------------------------------
//! Affichage du contour intérieur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsInteriorGradient( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_INTERIOR_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsInteriorGradient();
}

//------------------------------------------------------------------------------
//! Affichage du contour extérieur de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsExteriorGradient( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_EXTERIOR_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsExteriorGradient();
}

//------------------------------------------------------------------------------
//! Affichage du gradient morphologique de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsMorphologicalGradient( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_MORPHOLOGICAL_GRADIENT, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsMorphologicalGradient();
}

//------------------------------------------------------------------------------
//! Affichage du "Tout ou rien" de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsHitOrMiss( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_HIT_OR_MISS, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsHitOrMiss();
}

//------------------------------------------------------------------------------
//! Affichage de l'amincissement de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsThinning( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_THINNING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsThinning();
}

//------------------------------------------------------------------------------
//! Affichage de la squelettisation de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayOpMorphoMathsSkeletonizing( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_OP_MORPHO_MATHS_SKELETONIZING, &m_imageOrigin);

    treatedImageWindow->displayOpMorphoMathsSkeletonizing();
}

//------------------------------------------------------------------------------
//! Affichage de la détection d'une droite de l'image
//!
//! @param _
//!
//! @return _
//------------------------------------------------------------------------------
void MainWindow::displayRegionDetectionLine( void)
{
    CTreatedImageWindow *treatedImageWindow = new CTreatedImageWindow( PROCESSING_REGION_DETECTION_LINE, &m_imageOrigin);

    treatedImageWindow->displayRegionDetectionLine();
}
