#include "StdAfx.h"
#include "element.h"
element::element()
{
	int qd;
	int zd;
	//int unit;//1,2,3,4,5,6分别代表x向y向z向杆件及xy面xz面yz面剪刀撑
	float xs;
	float ys;
	float zs;
	float xe;
	float ye;
	float ze;
}
void element::operator=(element &n)
{
	qd=n.qd;
	zd=n.zd;
	xs=n.xs;
	ys=n.ys;
	zs=n.zs;
	xe=n.xe;
	ye=n.ye;
	ze=n.ze;
}
