/** File:		MainWidget.cpp
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

#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	cubeCanvas = new CubeGLWidget(this);

	check = new QCheckBox("Spin");
	check->setFixedSize(50,30);
	check->setChecked(true);

	slider = new QSlider(Qt::Horizontal);
	slider->setRange(1, 20);

	bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(check);
	bottomLayout->addWidget(slider);

	layout = new QVBoxLayout();
	layout->addWidget(cubeCanvas);
	layout->addLayout(bottomLayout);
	setLayout(layout);

	this->resize(650, 700);
	this->setFixedSize(this->width(),this->height());

	QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
	QObject::connect(check, SIGNAL(stateChanged(int)), this, SLOT(checkChanged(int)));
}

void MainWidget::sliderChanged(int value)
{
	cubeCanvas->setSpinSpeed((float)value);
}

void MainWidget::checkChanged(int value)
{
	if(value == Qt::Checked)
	{
		cubeCanvas->setSpinStatus(1);
	}

	if(value == Qt::Unchecked)
	{
		cubeCanvas->setSpinStatus(0);
	}
}
