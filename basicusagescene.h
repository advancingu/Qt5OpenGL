#ifndef BASICUSAGESCENE_H
#define BASICUSAGESCENE_H

#include "abstractscene.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class BasicUsageScene : public AbstractScene
{
public:
    BasicUsageScene();

    virtual void initialize();
    virtual void update(float t);
    virtual void render();
    virtual void resize(int width, int height);

private:
    QOpenGLShaderProgram mShaderProgram;
    QOpenGLVertexArrayObject mVAO;
    QOpenGLBuffer mVertexPositionBuffer;
    QOpenGLBuffer mVertexColorBuffer;

    void prepareShaderProgram();
    void prepareVertexBuffers();
};

#endif // BASICUSAGESCENE_H
