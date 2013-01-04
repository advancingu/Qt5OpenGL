#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

class QOpenGLContext;

class AbstractScene
{
public:
    AbstractScene() {}

    void setContext(QOpenGLContext *context) { mContext = context; }
    QOpenGLContext* context() const { return mContext; }

    virtual void initialize() = 0;

    virtual void update(float t) = 0;

    virtual void render() = 0;

    virtual void resize(int width, int height) = 0;

protected:
    QOpenGLContext *mContext;
};

#endif // ABSTRACTSCENE_H
