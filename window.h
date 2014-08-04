#ifndef WINDOW_H
#define WINDOW_H

#include "abstractscene.h"

#include <QWindow>

class QOpenGLContext;

class Window : public QWindow
{
    Q_OBJECT
public:
    explicit Window(QScreen *screen = 0);
    ~Window();
    
signals:
    
public slots:

protected slots:
    void resizeGl();
    void paintGl();
    void updateScene();

private:
    void printContextInfos();

    QOpenGLContext *mContext;
    QScopedPointer<AbstractScene> mScene;
    
    void initializeGl();
};

#endif // WINDOW_H
