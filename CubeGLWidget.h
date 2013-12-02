/** File:		CubeGLWidget.h
 ** Author:		Dongli Zhang
 ** Contact:	dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __CUBEGLWIDGET_H__
#define __CUBEGLWIDGET_H__

#include <QtOpenGL/QGLWidget>
#include <GL\glut.h>
#include <QtGui>

class CubeGLWidget : public QGLWidget
{
	Q_OBJECT

private:
	int spinStatus;
	float spinSpeed;

	GLfloat vertex[24];
	GLfloat color[24];
	GLint index[24];

	float xRot;
	float yRot;
	int ox;
	int oy;
	int buttonState;
	float xRotLength;
	float yRotLength;

public:
	CubeGLWidget(QWidget *parent = 0);
	void setSpinStatus(int status);
	void setSpinSpeed(float speed);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void timerEvent(QTimerEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif
