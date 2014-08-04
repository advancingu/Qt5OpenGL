#include "basicusagescene.h"

#include "glassert.h"

#include <QObject>
#include <QOpenGLContext>

BasicUsageScene::BasicUsageScene()
    : mShaderProgram(),
      mVertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
      mVertexColorBuffer(QOpenGLBuffer::VertexBuffer)
{
}

void BasicUsageScene::initialize()
{
    prepareShaderProgram();
    prepareVertexBuffers();
}

void BasicUsageScene::update(float t)
{
    Q_UNUSED(t);
}

void BasicUsageScene::render()
{
    glAssert( glClear(GL_COLOR_BUFFER_BIT) );

    mShaderProgram.bind();
    mVAO.bind();

    glAssert( glDrawArrays(GL_TRIANGLES, 0, 3) );
}

void BasicUsageScene::resize(int width, int height)
{
    glAssert( glViewport(0, 0, width, height) );
}

void BasicUsageScene::prepareShaderProgram()
{
    if (!mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/phong.vert"))
    {
        qCritical() << "error";
    }
    if (!mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":shaders/phong.frag"))
    {
        qCritical() << "error";
    }
    if (!mShaderProgram.link())
    {
        qCritical() << "error";
    }
    glCheckError();
}

void BasicUsageScene::prepareVertexBuffers()
{
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    mVAO.create();
    mVAO.bind();

    mVertexPositionBuffer.create();
    mVertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVertexPositionBuffer.bind();
    mVertexPositionBuffer.allocate(positionData, 3 * 3 * sizeof(float));

    mVertexColorBuffer.create();
    mVertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVertexColorBuffer.bind();
    mVertexColorBuffer.allocate(colorData, 3 * 3 * sizeof(float));

    mShaderProgram.bind();

    mVertexPositionBuffer.bind();
    mShaderProgram.enableAttributeArray("vertexPosition");
    mShaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    mVertexColorBuffer.bind();
    mShaderProgram.enableAttributeArray("vertexColor");
    mShaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);
    glCheckError();
}
