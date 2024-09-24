#pragma once

#include "afxwin.h"

class DisplayHelper
{
public:
	DisplayHelper(int w, int h, CStatic* pic_item, bool paint_to_pic_item = false)
		: hdc(NULL), bitmap(NULL), zoomx(1), zoomy(1), pic(NULL), picdc(NULL), paint2Pic(paint_to_pic_item)
	{
		pic_item->GetClientRect(picRect);
		if (picRect.Width() <= 0 || picRect.Height() <= 0)
			return;

		zoomx = (double)picRect.Width() / w;
		zoomy = (double)picRect.Height() / h;

		picdc = pic_item->GetDC();
		if (!picdc) return;

		// create the new memory DC for painting
		HDC pichdc = picdc->GetSafeHdc();
	    hdc = CreateCompatibleDC(pichdc);
		bitmap = CreateCompatibleBitmap(pichdc, picRect.Width(),
			picRect.Height());

		// replace with new created bitmap
		HBITMAP prevBitmap = (HBITMAP)SelectObject(hdc, bitmap);
		if (prevBitmap)
			DeleteObject(prevBitmap);

		// white background
		FillRect(hdc, &picRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		pic = pic_item;
	}

	~DisplayHelper()
	{
		if (pic)
		{
			// refresh the ui
			if (paint2Pic) {
				HBITMAP prev = pic->SetBitmap(bitmap);
				if (prev) {
					DeleteObject(prev);
				}
			}
			else {
				HDC pichdc = picdc->GetSafeHdc();
				BitBlt(pichdc, picRect.left, picRect.top, picRect.Width(), picRect.Height(),
					hdc, 0, 0, SRCCOPY);
				pic->ReleaseDC(picdc);
			}
		}

		if (hdc) {
			// release hdc
			DeleteObject(hdc);
		}

		if (bitmap && !paint2Pic) {
			// release bitmap
			DeleteObject(bitmap);
		}
	}

	HDC hdc;
	HBITMAP bitmap;
	double zoomx;
	double zoomy;

	CStatic* pic;
	CDC* picdc;
	CRect picRect;
	bool paint2Pic;
};
