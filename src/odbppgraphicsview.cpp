#include "odbppgraphicsview.h"

#include "symbolfactory.h"
#include "context.h"

extern Context ctx;

ODBPPGraphicsView::ODBPPGraphicsView(QWidget* parent): QGraphicsView(parent),
  m_profile(NULL)
{
  QGraphicsScene* scene = new ODBPPGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-800, -800, 1600, 1600);
  scene->setBackgroundBrush(ctx.bg_color);

  setScene(scene);

  setCacheMode(CacheBackground);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  scale(100, 100);
}

void ODBPPGraphicsView::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, -event->delta() / 240.0));
}

void ODBPPGraphicsView::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

  scale(scaleFactor, scaleFactor);
}

void ODBPPGraphicsView::loadProfile(QString step)
{
  QString path;
  path = QString("steps/%1/profile").arg(step.toLower());
  m_profile = new Profile(ctx.loader->absPath(path));

  QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
      255 - ctx.bg_color.blue(), 255);

  m_profile->setPen(QPen(color, 0));
  m_profile->setBrush(Qt::transparent);

  scene()->addItem(m_profile);
}

void ODBPPGraphicsView::setBackgroundColor(QColor color)
{
  scene()->setBackgroundBrush(color);

  if (m_profile) {
    QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
        255 - ctx.bg_color.blue(), 255);
    m_profile->setPen(QPen(color, 0));
    m_profile->setBrush(Qt::transparent);
  }
}