/* vokoscreen - A desktop recorder
 * Copyright (C) 2011-2013 Volker Kohaupt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "regionselection.h" 
#include <QCoreApplication>
#include <QToolTip>
#include <QMouseEvent>

using namespace std;

// Double Buffering
//http://books.google.de/books?id=T373zcyFfvoC&pg=PA168&lpg=PA168&dq=qt+double+buffering&source=bl&ots=Wavv6fM_7D&sig=eOilngWo3WQzrrRPcoP4oOycWbE&hl=de&sa=X&ei=_hgAUoKNIcjwsgaiiIHgCw&ved=0CDEQ6AEwAA#v=onepage&q=qt%20double%20buffering&f=false

/**
 * int x : 
 * int y :
 * int width :
 * int height :
 * int framewidth :
 */
regionselection::regionselection( int x, int y, int width, int height, int framewidth )
{
  (void)framewidth;
  handlePressed = NoHandle;
  handleUnderMouse = NoHandle;
  painter =  new QPainter();

  
  
QToolTip::showText ( QPoint( 300, 300 ), "Aber Hallo", this );
  
  
  setGeometry( x, y, width, height );
  setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip );

  if( QX11Info::isCompositingManagerRunning() )
    setAttribute( Qt::WA_TranslucentBackground, true );
  
  setMouseTracking( true );
  
  qDebug() << "width:" << width << "height:" << height;
  
  borderLeft = 20;
  borderTop = 20;
  borderRight = 40;
  borderBottom = 20;
 
  // Von außen bis Mitte blauer Rahmen
  // Breite blauer Rahmen
  frameWidth = 4;
  
  radius = 20;

  penWidth = 2;
  penHalf = penWidth / 2;
 
  // Framelock
  lockFrame( false );
}


regionselection::~regionselection()
{
}


void regionselection::resizeEvent( QResizeEvent * event )
{
 (void)event;
 //qDebug() << "resizeEvent";
}


void regionselection::HandleTopLeft()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );
  
  QRectF rectangle = QRectF( borderLeft - radius + penHalf, borderTop - radius + penHalf, 2 * radius, 2 * radius );
  int startAngle = 0 * 16;
  int spanAngle = 270 * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );

  // Begin Pfeil zeichnen
  double h = 2 * radius / 3;
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( borderLeft - frameWidth / 2 , borderTop - frameWidth / 2 );
  painterPath->lineTo( borderLeft - h + penHalf, borderTop - h + penHalf );
  painterPath->lineTo( borderLeft - h + penHalf + 7, borderTop - h + penHalf + 3 );
  painterPath->lineTo( borderLeft - h + penHalf + 3, borderTop - h + penHalf + 7 );
  painterPath->lineTo( borderLeft - h + penHalf, borderTop - h + penHalf );
  painter->drawPath( *painterPath );
}


void regionselection::HandleTopMiddle()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );
  
  QRectF rectangle = QRectF( ( width() - borderLeft - borderRight ) / 2 + borderLeft - radius, borderTop - radius + penHalf, 2 * radius, 2 * radius );
  int startAngle = 0 * 16;
  int spanAngle = 180 * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );
  painter->setPen( QPen( arrow, 2 ) );
  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( ( width() - borderLeft - borderRight ) / 2 + borderLeft, borderTop );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + borderLeft, borderTop - radius + penWidth + 1 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + borderLeft - 3, borderTop - radius + 7 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + borderLeft + 3, borderTop - radius + 7 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + borderLeft, borderTop -radius + penWidth + 1 );
  painter->drawPath( *painterPath );
}


void regionselection::HandleTopRight()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );

  QRectF rectangle = QRectF( width() - borderRight - radius - penHalf, borderTop - radius + penHalf, 2 * radius, 2 * radius );
  int startAngle = 180 * 16;
  int spanAngle =  -270  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );

  // Begin Pfeil zeichnen
  double h = 2 * radius / 3;
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( width() - borderRight + frameWidth / 2  , borderTop - frameWidth / 2 );
  painterPath->lineTo( width() - borderRight + h - penWidth / 2, borderTop - h + penWidth / 2 );
  painterPath->lineTo( width() - borderRight + h - 7           , borderTop - h + 3 );
  painterPath->lineTo( width() - borderRight + h - 3           , borderTop - h + 7 );
  painterPath->lineTo( width() - borderRight + h - penWidth    , borderTop - h + penWidth );  
  
  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::HandleRightMiddle()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );
  
  QRectF rectangle = QRectF( width() - borderRight - radius - penHalf, ( height() - borderTop - borderBottom ) / 2 + borderTop - radius,  2 * radius, 2 * radius );
  int startAngle = 90 * 16;
  int spanAngle =  -180  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle ); 
  
   // Begin Pfeil zeichnen
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( width() - borderRight + frameWidth / 2       , ( ( height() - borderTop - borderBottom ) / 2 + borderTop ) );
  painterPath->lineTo( width() - borderRight + radius - penWidth - 1, ( ( height() - borderTop - borderBottom ) / 2 + borderTop ) );
  painterPath->lineTo( width() - borderRight + radius - penWidth - 7, ( ( height() - borderTop - borderBottom ) / 2 + borderTop + 3 ) );
  painterPath->lineTo( width() - borderRight + radius - penWidth - 7, ( ( height() - borderTop - borderBottom ) / 2 + borderTop - 3 ) );
  painterPath->lineTo( width() - borderRight + radius - penWidth - 1, ( ( height() - borderTop - borderBottom ) / 2 + borderTop ) );

  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::HandleBottomRight()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );
  
  QRectF rectangle = QRectF( width() - borderRight - radius - penHalf, height() - borderBottom - radius - penHalf, 2 * radius, 2 * radius );
  int startAngle = 90 * 16;
  int spanAngle =  -270  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );
  
  // Begin Pfeil zeichnen
  double h = 2 * radius / 3;
  
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( width() - borderRight + frameWidth / 2  , height() - borderBottom + frameWidth / 2 );
  painterPath->lineTo( width() - borderRight + h - penWidth / 2, height() - borderBottom + h - penWidth / 2 );
  painterPath->lineTo( width() - borderRight + h - 7           , height() - borderBottom + h - 3 );
  painterPath->lineTo( width() - borderRight + h - 3           , height() - borderBottom + h - 7 );
  painterPath->lineTo( width() - borderRight + h - penWidth / 2, height() - borderBottom + h - penWidth / 2);
  
  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::HandleBottomMiddle()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );

  QRectF rectangle = QRectF( ( width() - borderLeft - borderRight ) / 2, height() - borderBottom - radius - penHalf, 2 * radius, 2 * radius );
  int startAngle = 0 * 16;
  int spanAngle =  -180  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );
  
  // Begin Pfeil zeichnen
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( ( width() - borderLeft - borderRight ) / 2 + radius, height() - borderBottom );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + radius, height() - borderBottom + radius - penWidth - 1 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + radius - 3, height() - borderBottom + radius - penWidth - 7 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + radius + 3, height() - borderBottom + radius - penWidth - 7 );
  painterPath->lineTo( ( width() - borderLeft - borderRight ) / 2 + radius, height() - borderBottom + radius - penWidth - 1 );
  
  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::HandleBottomLeft()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );

  QRectF rectangle = QRectF( borderLeft - radius + penHalf, height() - borderBottom - radius - penHalf, 2 * radius, 2 * radius );
  int startAngle = 90 * 16;
  int spanAngle =  270  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );

  // Begin Pfeil zeichnen
  painter->setPen( QPen( arrow, 2 ) );

  double h = 2 * radius / 3;

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( borderLeft - frameWidth / 2, height() - borderBottom + frameWidth / 2 );
  painterPath->lineTo( borderLeft - h + penHalf,  height() - borderBottom + h - penHalf );
  painterPath->lineTo( borderLeft - h + 3, height() - borderBottom + h - 7 );
  painterPath->lineTo( borderLeft - h + 7, height() - borderBottom + h - 3 );
  painterPath->lineTo( borderLeft - h + penHalf,  height() - borderBottom + h - penHalf );
  
  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::HandleLeftMiddle()
{
  QColor color, arrow;
  
  if ( isFrameLocked() )
  {
    color = Qt::red;
    arrow = Qt::red;
  }
  else
  {
    color = Qt::green;
    arrow = Qt::black;
  }
  
  QBrush brush( color, Qt::SolidPattern );
  painter->setBrush( brush );
  painter->setPen( QPen( Qt::black, penWidth ) );

  QRectF rectangle = QRectF( borderLeft - radius + penHalf, ( height() - borderTop - borderBottom ) / 2 + borderTop - radius, 2 * radius, 2 * radius );
  int startAngle = 90 * 16;
  int spanAngle =  180  * 16;
  painter->drawPie( rectangle, startAngle, spanAngle );
  
  // Begin Pfeil zeichnen
  painter->setPen( QPen( arrow, 2 ) );

  QPainterPath * painterPath = new QPainterPath();
  painterPath->moveTo( borderLeft - frameWidth / 2, ( height() - borderTop - borderBottom ) / 2 + borderTop );
  painterPath->lineTo( penWidth + 1, ( height() - borderTop - borderBottom ) / 2 + borderTop );
  painterPath->lineTo( penHalf + 7,  ( height() - borderTop - borderBottom ) / 2 + borderTop + 3 );
  painterPath->lineTo( penHalf + 7,  ( height() - borderTop - borderBottom ) / 2 + borderTop - 3 );
  painterPath->lineTo( penWidth + 1, ( height() - borderTop - borderBottom ) / 2 + borderTop );
  
  painterPath->setFillRule( Qt::OddEvenFill );
  
  painter->drawPath( *painterPath );
  // End Pfeil zeichnen
}


void regionselection::paintEvent( QPaintEvent *event ) 
{
  (void)event;
  QRegion regionWidget(  0, 
                         0, 
                         width(),
                         height(), 
                         QRegion::Rectangle );
/*  
  // Region Handle TopLeft
  QRegion handleTopLeftRectangle( 0, 0, borderLeft + radius + 4, borderTop + radius+4, QRegion::Rectangle );
  QRegion handleTopLeftCircle( borderLeft - radius - penHalf, borderTop - radius-penHalf, 2 * radius + penWidth+1, 2 * radius + penWidth+1, QRegion::Ellipse );
  QRegion handleTopLeftSmallRectangle( borderLeft, borderTop, radius, radius, QRegion::Rectangle );
  QRegion test123 = handleTopLeftRectangle.subtract( handleTopLeftCircle  );
  //QRegion test234 = test123.intersected ( handleTopLeftSmallRectangle );
  
  // Region bettween TopLeft and TopMiddle
  QRegion betweenTopLeftAndTopMiddle( borderLeft + radius + 2,
			              0,
			              width() / 2 - borderLeft - 2 * radius - 3,
			              borderTop - frameWidth / 2 );
  
  // Region record
  QRegion regionRecord( borderLeft + frameWidth / 2, 
                        borderTop + frameWidth / 2, 
                        width() - borderLeft - borderRight - frameWidth,
                        height() - borderTop - borderBottom - frameWidth, 
                        QRegion::Rectangle );
  
  
  QRegion r15 = regionWidget.subtract( regionRecord );

  //r15 = r15.subtract( handleTopLeftCircle );
  //r15 = test123.united( handleTopLeftSmallRectangle );
  //r15 = r15.subtract( test123 );
  
  setMask( r15 );
*/  
  painter->begin( this );
  painter->setRenderHints( QPainter::Antialiasing, true );

  HandleTopLeft();
  HandleTopMiddle();
  HandleTopRight();
  HandleRightMiddle();
  HandleBottomRight();
  HandleBottomMiddle();
  HandleBottomLeft();
  HandleLeftMiddle();

/*  
  // Kreis in der Mitte
  painter.drawEllipse ( width()/2 - radius, height()/2 - radius, 2 * radius, 2 * radius );

*/  
  // Blue Frame
  painter->setPen( QPen( Qt::blue, frameWidth ) );
  
  // Left Line
  painter->drawLine( borderLeft, borderTop, borderLeft, height() - borderBottom );
  
  // Top Line
  painter->drawLine( borderLeft, borderTop, width() - borderRight, borderTop );
  
  // Right Line
  painter->drawLine( width() - borderRight, borderTop, width() - borderRight, height() - borderBottom );
  
  // Bottome Line
  painter->drawLine( borderLeft, height() - borderBottom, width() - borderRight, height() - borderBottom );

  painter->end();
  
  event->accept();  
  
}


void regionselection::lockFrame( bool status )
{
    frameLocked = status;
    qDebug() << "[vokoscreen][Regional selection] Frame locked:" << status;
    qDebug();
    handlingFrameLock();
}


bool regionselection::isFrameLocked()
{
    return frameLocked;
}


int regionselection::getX()
{
  return this->x() + borderLeft + frameWidth / 2; 
}


int regionselection::getY()
{
  return  this->y() + borderTop + frameWidth / 2;
}


int regionselection::getHeight()
{
  return this->height() - borderTop - borderBottom - frameWidth; 
}


int regionselection::getWidth()
{
  return this->width() - borderLeft - borderRight - frameWidth; 
}


void regionselection::handlingFrameLock()
{
  repaint();
}


/*! MouseMove fuer das bewegen des Fensters und Ränder
\param event QMouseEvent Mouse Event
*/
void regionselection::mouseMoveEvent( QMouseEvent *event )
{
  if ( isFrameLocked() )
    return;
   
  switch ( handlePressed )
  {
    case NoHandle    :                            break;
    case TopLeft     : moveTopLeft( event );      break;
    case TopMiddle   : moveTopMiddle( event );    break;
    case TopRight    : moveTopRight( event );     break;
    case RightMiddle : moveRightMiddle( event );  break;
    case BottomRight : moveBottomRight( event );  break;
    case BottomMiddle: moveBottomMiddle( event ); break;
    case BottomLeft  : moveBottomLeft( event );   break;
    case LeftMiddle  :    break;
    case Middle      :    break;
    return;
  }
 
  if ( ( event->x() > ( borderLeft - radius ) ) and
       ( event->x() < ( borderLeft + radius ) ) and 
       ( event->y() > ( borderTop - radius  ) ) and 
       ( event->y() < ( borderTop + radius) ) )
  {
    setCursor( Qt::SizeFDiagCursor );  
    handleUnderMouse = TopLeft;
    return;
  }

  if ( ( event->x() > ( width() - borderLeft - borderRight ) / 2 + borderLeft - radius ) and
       ( event->x() < ( width() - borderLeft - borderRight ) / 2 + borderLeft + radius ) and
       ( event->y() > borderTop - radius ) and
       ( event->y() < borderTop ) )
  {
    setCursor( Qt::SizeVerCursor );  
    handleUnderMouse = TopMiddle;
    return;
  }

  if ( ( event->x() > width() - borderRight - radius ) and 
       ( event->x() < width() - borderRight + radius ) and
       ( event->y() > borderTop - radius ) and
       ( event->y() < borderTop + radius ) )
  {
    setCursor( Qt::SizeBDiagCursor  );
    handleUnderMouse = TopRight;
    return;
  }
  
  if ( ( event->x() > width() - borderRight ) and
       ( event->x() < width() - borderRight + radius ) and
       ( event->y() > ( ( height() - borderTop - borderBottom ) / 2 + borderTop - radius ) ) and
       ( event->y() < ( ( height() - borderTop - borderBottom ) / 2 + borderTop + radius ) ) )
  {
    setCursor( Qt::SizeHorCursor );
    handleUnderMouse = RightMiddle;
    return;
  }

  if ( ( event->x() > width() - borderRight - radius ) and
       ( event->x() < width() - borderRight + radius ) and
       ( event->y() > height() - borderBottom - radius ) and
       ( event->y() < height() - borderBottom + radius ) )
  {
     setCursor( Qt::SizeFDiagCursor );
     handleUnderMouse = BottomRight;
     return;
  }

  if ( ( event->x() > ( width() - borderLeft - borderRight ) / 2 + borderLeft - radius ) and 
       ( event->x() < ( width() - borderLeft - borderRight ) / 2 + borderLeft + radius ) and 
       ( event->y() < height() ) and 
       ( event->y() > height() - radius ) )
  {
    setCursor( Qt::SizeVerCursor );
    handleUnderMouse = BottomMiddle;
    return;
  }
  
  if ( ( event->x() > ( borderLeft - radius ) ) and
       ( event->x() < ( borderLeft + radius ) ) and
       ( event->y() > ( height() - borderBottom - radius ) ) and
       ( event->y() < height() ) )
  {
    setCursor( Qt::SizeBDiagCursor );
    handleUnderMouse = BottomLeft;
    return;
  }
  
  handleUnderMouse = NoHandle;
  
  unsetCursor();

  event->accept();

/*    
    if (  event->buttons() & Qt::LeftButton )
    {
        move( event->globalPos() - m_dragPosition );
        event->accept();
    }
  
*/ 
}

void regionselection::moveTopLeft( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalX = event->globalX();
  int mouseGlobalY = event->globalY();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetWidth = geometry().width();
  int widgetHeight = geometry().height();
  
  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalY >= widgetY + widgetHeight - 200 )
    mouseGlobalY = widgetY + widgetHeight - 200;

  if ( mouseGlobalX >= widgetX + widgetWidth - 200 )
    mouseGlobalX = widgetX + widgetWidth - 200;
  
  // Maximale Größe begrenzen
  if ( mouseGlobalY - currentMouseLocalY < 0 )
    mouseGlobalY = widgetY + currentMouseLocalY;
    
  if ( mouseGlobalX - currentMouseLocalX < 0 )  
    mouseGlobalX = widgetX + currentMouseLocalX;
  
  // Neue Geometry des Dialogfenster setzen
  this->setGeometry( mouseGlobalX - currentMouseLocalX,
		     mouseGlobalY - currentMouseLocalY, 
		     widgetWidth + ( widgetX - mouseGlobalX + currentMouseLocalX ),
		     widgetHeight + ( widgetY - mouseGlobalY + currentMouseLocalY ) );
  
  event->accept();
}


void regionselection::moveTopMiddle( QMouseEvent *event )
{
  // Globale Mauskoordinaten 
  int mouseGlobalY = event->globalY();
  
  // Alte Globale Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetWidth = geometry().width();
  int widgetHeight = geometry().height();

  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalY >= widgetY + widgetHeight - 200 )
    mouseGlobalY = widgetY + widgetHeight - 200;

  // Maximale Größe begrenzen
  if ( mouseGlobalY - currentMouseLocalY < 0 )
    mouseGlobalY = widgetY + currentMouseLocalY;
  
  // Neue Geometry des HauptWidget setzen
  this->setGeometry( widgetX,
		     mouseGlobalY - currentMouseLocalY,
		     widgetWidth,
		     widgetHeight + ( widgetY - mouseGlobalY + currentMouseLocalY ) );
}


void regionselection::moveTopRight( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalX = event->globalX();
  int mouseGlobalY = event->globalY();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetHeight = geometry().height();
  int widgetWidth = geometry().width();

  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalX <= widgetX + 200 )
    mouseGlobalX = widgetX + 200;
  
  if ( mouseGlobalY >= widgetY + widgetHeight - 200 )
    mouseGlobalY = widgetY + widgetHeight - 200;

  // Maximale Größe begrenzen
  if ( mouseGlobalY - currentMouseLocalY < 0 )
    mouseGlobalY = widgetY + currentMouseLocalY;

 
  
  QDesktopWidget *desk = QApplication::desktop();
  qDebug() <<  desk->screenGeometry().width() - widgetX - widgetWidth;
  if ( ( mouseGlobalX + ( desk->screenGeometry().width() - widgetX - widgetWidth )*-1 ) > desk->screenGeometry().width() )
  {
    qDebug() << "111111111111111111111111";
    mouseGlobalX = mouseGlobalX + ( desk->screenGeometry().width() - widgetX - widgetWidth ) * -1;
    
  }
  
  
  // Neue Geometry des Fenster setzen
  this->setGeometry( widgetX,
		     mouseGlobalY - currentMouseLocalY,
		     currentWidgetWidth + ( mouseGlobalX - ( widgetX + currentMouseLocalX ) ),
     		     widgetHeight  + ( widgetY - mouseGlobalY + currentMouseLocalY ) );
  
  //event->accept();
}


void regionselection::moveRightMiddle( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalX = event->globalX();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetHeight = geometry().height();
  
  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalX <= widgetX + 200 )
    mouseGlobalX = widgetX + 200;
  
  this->setGeometry( widgetX,
		     widgetY,
		     currentWidgetWidth + ( mouseGlobalX - ( widgetX + currentMouseLocalX ) ),
		     widgetHeight );
}


void regionselection::moveBottomRight( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalX = event->globalX();
  int mouseGlobalY = event->globalY();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
 
  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalX <= widgetX + 200 )
    mouseGlobalX = widgetX + 200;
  
  if ( mouseGlobalY <= widgetY + 200 )
    mouseGlobalY = widgetY +  200;
  
  this->setGeometry( widgetX,
		     widgetY,
		     currentWidgetWidth + ( mouseGlobalX - ( widgetX + currentMouseLocalX ) ),
		     currentWidgetHeight + ( mouseGlobalY - ( widgetY + currentMouseLocalY ) ) );
}


void regionselection::moveBottomMiddle( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalY = event->globalY();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetWidth = geometry().width();

  if ( mouseGlobalY <= widgetY + 200 )
    mouseGlobalY = widgetY +  200;
  
  this->setGeometry( widgetX,
		     widgetY,
     		     widgetWidth,
		     currentWidgetHeight + ( mouseGlobalY - ( widgetY + currentMouseLocalY ) ) );
}


void regionselection::moveBottomLeft( QMouseEvent *event )
{
  // Globale Mauskoordinaten
  int mouseGlobalX = event->globalX();
  int mouseGlobalY = event->globalY();
  
  // Alte Widget Koordinaten
  int widgetX = geometry().x();
  int widgetY = geometry().y();
  int widgetWidth = geometry().width();

  // Minimale Größe des Widget begrenzen
  if ( mouseGlobalY <= widgetY + 200 )
    mouseGlobalY = widgetY + 200;

  if ( mouseGlobalX >= widgetX + widgetWidth - 200 )
    mouseGlobalX = widgetX + widgetWidth - 200;
  
  if ( mouseGlobalX - currentMouseLocalX < 0 )  
    mouseGlobalX = widgetX + currentMouseLocalX;
  
  
  this->setGeometry( mouseGlobalX - currentMouseLocalX,
		     widgetY,
     		     widgetWidth + ( widgetX - mouseGlobalX + currentMouseLocalX ),
		     currentWidgetHeight + ( mouseGlobalY - ( widgetY + currentMouseLocalY ) ) );
}


void regionselection::mousePressEvent( QMouseEvent *event )
{
  // Position bei klick im Fenster festhalten
  currentMouseLocalX = event->x();
  currentMouseLocalY = event->y();

  currentWidgetWidth = geometry().width();
  currentWidgetHeight = geometry().height();
  
  switch ( handleUnderMouse )
  {
    case NoHandle    : handlePressed = NoHandle;     break;
    case TopLeft     : handlePressed = TopLeft;      break;
    case TopMiddle   : handlePressed = TopMiddle;    break;
    case TopRight    : handlePressed = TopRight;     break;
    case RightMiddle : handlePressed = RightMiddle;  break;
    case BottomRight : handlePressed = BottomRight;  break;
    case BottomMiddle: handlePressed = BottomMiddle; break;
    case BottomLeft  : handlePressed = BottomLeft;   break;
    case LeftMiddle  : handlePressed = LeftMiddle;   break;
    case Middle      : handlePressed = Middle;       break;
  }
  
  event->accept();  
}

void regionselection::mouseReleaseEvent( QMouseEvent * event )
{
  (void)event;
  handlePressed = NoHandle;
  event->accept();  
}
