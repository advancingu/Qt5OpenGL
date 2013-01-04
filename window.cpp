#include "window.h"

#include "basicusagescene.h"

#include <QOpenGLContext>
#include <QTimer>

Window::Window(QScreen *screen) :
    QWindow(screen),
    mScene(new BasicUsageScene())
{
    setSurfaceType(OpenGLSurface);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(0);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);

    setFormat(format);
    create();

    mContext = new QOpenGLContext();
    mContext->setFormat(format);
    mContext->create();

    mScene->setContext(mContext);
    initializeGl();

    resize(QSize(800, 450));

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGl()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGl()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(16);
}

Window::~Window()
{
}

void Window::initializeGl()
{
    mContext->makeCurrent(this);
    mScene->initialize();
}

void Window::paintGl()
{
    mContext->makeCurrent(this);
    mScene->render();
    mContext->swapBuffers(this);
}

void Window::resizeGl()
{
    mContext->makeCurrent(this);
    mScene->resize(width(), height());
}

void Window::updateScene()
{
    mScene->update(0.0f);
    paintGl();
}
