#pragma once
#include "gdal/ogrsf_frmts.h"
#include "osgDB/ReadFile"


//!
//! ����shapeת3Dtile��ں�����������������Զ�ת��shape�ļ�
//!
//! shape�ļ�������·��
//! ת����3Dtile�ļ���·��
//! �߶�
//! ����true:�ɹ�	false:ʧ��
//!
bool ShapTo3Dtiles(const char* filename, const char* dest, const char* height);

//!
//! ��ȡ����ת���Ľ���
//!
//! ����ֵ������ǰת���Ľ���ֵ��1-100��
//!
int GetProgressData();

