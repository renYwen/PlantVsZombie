#include "Renderer.h"
#include "Camera.h"
#include "GameStatics.h"
#include "Resources.h"

extern bool cmp(SpriteRenderer* a, SpriteRenderer* b)
{
	if (a->GetLayer() == b->GetLayer())
		return a < b;
	else
		return a->GetLayer() < b->GetLayer();
}

extern set<SpriteRenderer*, decltype(&cmp)> GameRenders(cmp);



void SpriteRenderer::Render()
{
	if (sprite.image) {
		Vector pos = (bIsUI ? GetLocalPosition() : GetWorldPosition() - MainCamera->GetWorldPosition())
			+ sprite.delta;

		if (bEn) {
			putimage(pos.x, pos.y, &en, SRCPAINT);
			putimage(pos.x, pos.y, sprite.image, SRCAND);
			return;
		}

		HDC dstDC = GetImageHDC(NULL);
		HDC srcDC; int w, h;
		if (transform.rotation == 0) {
			srcDC = GetImageHDC(sprite.image);
			w = sprite.image->getwidth();
			h = sprite.image->getheight();
		}
		else {
			srcDC = GetImageHDC(&copy_);
			w = copy_.getwidth();
			h = copy_.getheight();
		}

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, transparency, AC_SRC_ALPHA };
		if (sprite.flag == 1) {
			w /= sprite.column, h /= sprite.row;
			int i = sprite.index / sprite.column;
			int j = sprite.index % sprite.column;
			AlphaBlend(dstDC, int(pos.x), int(pos.y), w, h, srcDC, j * w, i * h, w, h, bf);
		}
		else {
			if (sprite_.isUsed)
				AlphaBlend(dstDC, int(pos.x), int(pos.y), sprite_.aimSize.x, sprite_.aimSize.y,
					srcDC, sprite_.aimLoc.x, sprite_.aimLoc.y, sprite_.aimSize.x, sprite_.aimSize.y, bf);
			else
				AlphaBlend(dstDC, int(pos.x), int(pos.y), w, h, srcDC, 0, 0, w, h, bf);
		}
	}
}


IMAGE SpriteRenderer::RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor)
{
	radian = -radian;														// ���� y �ᷭת����ת�Ƕ���Ҫ�为
	float fSin = (float)sin(radian), fCos = (float)cos(radian);				// �洢���Ǻ���ֵ
	float fNSin = (float)sin(-radian), fNCos = (float)cos(-radian);
	int left = 0, top = 0, right = 0, bottom = 0;							// ��ת��ͼ�񶥵�
	int w = pImg->getwidth(), h = pImg->getheight();
	DWORD* pBuf = GetImageBuffer(pImg);
	POINT points[4] = { {0, 0}, {w, 0}, {0, h}, {w, h} };					// �洢ͼ�񶥵�
	for (int j = 0; j < 4; j++)												// ��תͼ�񶥵㣬������ת���ͼ��߽�
	{
		points[j] = {
			(int)(points[j].x * fCos - points[j].y * fSin),
			(int)(points[j].x * fSin + points[j].y * fCos)
		};
		if (points[j].x < points[left].x)	left = j;
		if (points[j].y > points[top].y)	top = j;
		if (points[j].x > points[right].x)	right = j;
		if (points[j].y < points[bottom].y)	bottom = j;
	}

	int nw = points[right].x - points[left].x;								// ��ת���ͼ��ߴ�
	int nh = points[top].y - points[bottom].y;
	int nSize = nw * nh;
	int offset_x = points[left].x < 0 ? points[left].x : 0;					// ��ת��ͼ�񳬳���һ���޵�λ�ƣ��ݴ˵���ͼ��λ�ã�
	int offset_y = points[bottom].y < 0 ? points[bottom].y : 0;

	IMAGE img(nw, nh);
	DWORD* pNewBuf = GetImageBuffer(&img);
	if (bkcolor != BLACK)													// ����ͼ�񱳾�ɫ
		for (int i = 0; i < nSize; i++)
			pNewBuf[i] = BGR(bkcolor);

	for (int i = offset_x, ni = 0; ni < nw; i++, ni++)						// i ����ӳ��ԭͼ�����꣬ni ���ڶ�λ��ת��ͼ������
	{
		for (int j = offset_y, nj = 0; nj < nh; j++, nj++)
		{
			int nx = (int)(i * fNCos - j * fNSin);							// ����ת���ͼ��������ԭͼ������ӳ��
			int ny = (int)(i * fNSin + j * fNCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)						// ��Ŀ��ӳ����ԭͼ��Χ�ڣ��򿽱�ɫֵ
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
		}
	}

	return img;
}


void SpriteRenderer::SetScale(Vector scale, string name)
{
	if (!copy)copy = new IMAGE;
	else {
		delete copy; copy = new IMAGE;
		loadimage(copy, ResourcePool.FindPath(name).c_str(), scale.x, scale.y);
		sprite.image = copy;
	}
}

void SpriteRenderer::Load(string name)
{
	sprite.image = ResourcePool.Fetch(name);
}

StaticMesh::StaticMesh()
{
	renderer = GameStatics::ConstructComponent<SpriteRenderer>(Vector(0,0));
	renderer->SetAttachment(root);
}
