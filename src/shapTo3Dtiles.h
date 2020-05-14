#pragma once
#include "gdal/ogrsf_frmts.h"
#include "osgDB/ReadFile"


//!
//! 调用shape转3Dtile入口函数，根据输入参数自动转换shape文件
//!
//! shape文件的完整路径
//! 转换后3Dtile文件的路径
//! 高度
//! 返回true:成功	false:失败
//!
bool ShapTo3Dtiles(const char* filename, const char* dest, const char* height);

//!
//! 获取程序转换的进度
//!
//! 返回值：程序当前转换的进度值（1-100）
//!
int GetProgressData();

