/** File:		CubeGLWidget.cpp
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

#include "CubeGLWidget.h"

CubeGLWidget::CubeGLWidget(QWidget *parent)
	: QGLWidget(parent)
{
	this->setMinimumSize(600, 600);

	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	setFocusPolicy(Qt::StrongFocus);

	GLfloat temp_vertex[24] = {-8.0f, -8.0f, 8.0f, 
							8.0f, -8.0f, 8.0f,
							8.0f, 8.0f, 8.0f, 
							-8.0f, 8.0f, 8.0f,
							-8.0f, -8.0f, -8.0f, 
							8.0f, -8.0f, -8.0f,
							8.0f, 8.0f, -8.0f, 
							-8.0f, 8.0f, -8.0f};

	GLfloat temp_color[24] = {0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f,
							0.0f, 1.0f, 0.0f,
							0.0f, 1.0f, 1.0f,
							1.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 1.0f,
							1.0f, 1.0f, 0.0f,
							1.0f, 1.0f, 1.0f};

	GLint temp_index[24] = {0, 1, 2, 3,
							1, 5, 6, 2,
							5, 4, 7, 6,
							4, 0, 3, 7,
							3, 2, 6, 7,
							4, 5, 1, 0};

	memcpy((void *)vertex, (void *)temp_vertex, sizeof(GLfloat)*24);
	memcpy((void *)color, (void *)temp_color, sizeof(GLfloat)*24);
	memcpy((void *)index, (void *)temp_index, sizeof(GLint)*24);

	spinStatus = 1;
	spinSpeed = 4.0f;
}

void CubeGLWidget::setSpinStatus(int status)
{
	this->spinStatus = status;
}

void CubeGLWidget::setSpinSpeed(float speed)
{
	this->spinSpeed = speed;
}

void CubeGLWidget::initializeGL()
{
	xRot = 0.0f;
	yRot = 0.0f;
	xRotLength = 0.0f;
	yRotLength = 0.0f;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, vertex);

	startTimer(30);
}

void CubeGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (float)width/height, 0.001, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -38.0f);
}

void CubeGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glPushMatrix();

	if(buttonState == 1)
	{
		xRot += (xRotLength-xRot)*0.1f;
		yRot += (yRotLength-yRot)*0.1f;
	}
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index);

	glPopMatrix();
}

void CubeGLWidget::timerEvent(QTimerEvent *event)
{
	if(spinStatus == 1)
	{
		yRot += spinSpeed;
		updateGL();
	}
}

void CubeGLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		int x = event->x();
		int y = event->y();

		buttonState = 1;

		ox = x; 
		oy = y;
	}
}

void CubeGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		int x = event->x();
		int y = event->y();

		buttonState = 0;

		ox = x; 
		oy = y;
	}
}

void CubeGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		int x = event->x();
		int y = event->y();

		float dx, dy;
		dx = (float)(x - ox);
		dy = (float)(y - oy);

		if (buttonState == 1) 
		{
			xRotLength += dy / 5.0f;
			yRotLength += dx / 5.0f;
		}

		ox = x; 
		oy = y;

		updateGL();
	}
}
