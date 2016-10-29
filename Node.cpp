#include "StdAfx.h"
#include "Node.h"
Node::Node(){
	//初始化你要用的对象
	float x=0.0;
	float y=0.0;
	float z=0.0;
	//float YuanXin_X=0.0;
	//float YuanXin_Y=0.0;
	int Num=0;
}
void Node::operator=(Node &n)
{
	Num=n.Num;
	x=n.x;
	y=n.y;
	z=n.z;
}
