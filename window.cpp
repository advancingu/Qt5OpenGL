#include "window.h"

#include "basicusagescene.h"

#include <iostream>
#include <QOpenGLContext>
#include <QTimer>

static void infoGL()
{
    const GLubyte *str;
    std::cout << "OpenGL infos with gl functions" << std::endl;
    str = glGetString(GL_RENDERER);
    std::cout << "Renderer : " << str << std::endl;
    str = glGetString(GL_VENDOR);
    std::cout << "Vendor : " << str << std::endl;
    str = glGetString(GL_VERSION);
    std::cout << "OpenGL Version : " << str << std::endl;
    str = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL Version : " << str << std::endl;
}

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

    printContextInfos();
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

void Window::printContextInfos()
{
    if(!mContext->isValid())
        std::cerr << "The OpenGL context is invalid!" << std::endl;

    mContext->makeCurrent(this);

    std::cout << "Window format version is: "
              << format().majorVersion() << "."
              << format().minorVersion() << std::endl;

    std::cout << "Context format version is: "
              << mContext->format().majorVersion()
              << "." << mContext->format().minorVersion() << std::endl;
    infoGL();
}

void Window::initializeGl()
{
    mContext->makeCurrent(this);
    mScene->initialize();
}

void Window::paintGl()
{
    if( !isExposed() ) return;
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
