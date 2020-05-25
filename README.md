# shpTo3dtiles

shp转3dtiles工具。

shapefile => 3dtile,  convert shape file to 3dtiles.

## 命令行：
shpto3dtile [FLAGS] [OPTIONS] --input <FILE> --output <FILE> --height

### 示例：
ShapeTo3Dtile.exe --sourceDirectory F:\test\ShapeData\building.shp --targetDirectory F:\test\dest --buildingHeight 10

### 参数说明：


  -i		--input <FILE> 
	
  -o		--output <FILE> （需要指定存在的目录!）
  
  --height	指定shapefile的高度字段 (转shapefile时，必须参数)

#### 命令行参数详解：

--sourceDirectory 存放shapefile的目录。

--targetDirectory 转换后3Dtile文件的存放目录。

--buildingHeight  指定shapefile中的高度属性字段。

### 数据说明：

目前仅支持 shapefile 的面数据，可用于建筑物轮廓批量生成 3dtile。

仅支持WGS84坐标系的矢量数据。

# About author

我们立志于做专业的三维大数据应用平台，目前平台后端相关数据转换这块的功能刚做出来，代码如有纰漏，请不吝赐教。

"# ShapTo3Dtile" 
