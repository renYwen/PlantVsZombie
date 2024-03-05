#include "UserInterface.h"
#include "Controller.h"
#include "Renderer.h"
#include "GameStatics.h"
#include "Camera.h"


extern set<Widget*>GamePainters{};

extern set<UserInterface*>GameUIs{};

extern vector<UserInterface*>GameUIs_{};


map<string, COLORREF>Characters::TextColorMap = 
{ {"$0",WHITE}/*��ɫ*/,{"$1",RGB(245, 245, 245)}/*�̰�ɫ*/,
	{"$2",LIGHTGRAY}/*ǳ��ɫ*/,{"$3",DARKGRAY}/*���ɫ*/, {"$4",BLACK}/*��ɫ*/,
	{"$5",GREEN}/*����ɫ*/,{"$6",LIGHTGREEN}/*��ɫ*/, {"$7",YELLOW}/*��ɫ*/,
	{"$8",RGB(255, 165, 0)}/*��ɫ*/,{"$9",LIGHTRED}/*ǳ��ɫ*/, {"$a",RED}/*���ɫ*/,
	{"$b",LIGHTMAGENTA}/*��ɫ*/,{"$c",MAGENTA}/*Ʒ��ɫ*/, {"$d",RGB(148, 0, 211)}/*��ɫ*/,
	{"$e",BLUE}/*����ɫ*/,{"$f",LIGHTBLUE}/*����ɫ*/, {"$g",LIGHTCYAN}/*����ɫ*/,
	{"$h",CYAN}/*��ɫ*/,{"$i",BROWN}/*��ɫ*/
};



void Widget::ShowInfoBox()
{
	if (IsUnderCursor() && bInfoBox) {
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL);
		setfillcolor(RGB(255, 247, 213));

		Vector pos = MainController->GetCursorScreenPosition() + Vector(-15, 15);
		fillrectangle(pos.x, pos.y, pos.x + InfoText.GetWidth(), pos.y + InfoText.GetHeight());
		InfoText.PrintText(pos, 1);
	}
}





bool Widget::IsUnderCursor()
{
	float x = MainController->GetCursorScreenPosition().x;
	float y = MainController->GetCursorScreenPosition().y;
	Vector loc = GetAbsoluteLocation();
	if (x<size.x + loc.x && x> loc.x && y<size.y + loc.y && y> loc.y)
	{
		return true;
	}
	return false;
}




Image::Image()
{
	ima = GameStatics::ConstructComponent<SpriteRenderer>(Vector(0,0));
	ima->SetUI(true);
	ui = new IMAGE;
	ima->SetImage(ui);
}

Image::~Image()
{
	GameComponents_.push_back(static_cast<Component*>(ima));
	delete ui;
}

void Image::Update()
{
	Widget::Update(); ima->SetPosition(GetAbsoluteLocation());
}

void Image::SetVisibility(bool visible)
{
	bVisibiliy = visible;
	if (visible) { GameRenders.insert(ima); ima->SetPosition(GetAbsoluteLocation());}
	else GameRenders.erase(ima);
}

void Image::LoadPicture(string path, Vector si)
{
	Vector temp = (si == Vector(0, 0) ? GetSize() : si);
	this->path = path;
	ima->Load(path, temp.x, temp.y); ima->SetLayer(layer);
}

void Image::LoadPicture(string path, string path_en, Vector si)
{
	Vector temp = (si == Vector(0, 0) ? GetSize() : si);
	ima->Load(path, path_en,temp.x, temp.y); ima->SetLayer(layer);
}


void Image::SetLayer(int lay)
{
	layer = lay;  if(ima)ima->SetLayer(layer);
}

BYTE Image::GetTrans()
{
	return ima->GetTransparency();
}

void Image::SetTrans(int tran)
{
	if (ima)ima->SetTransparency(tran);
}

void Image::SetPicSize(Vector si)
{
	ima->SetFixSize(si);
}

void Image::SetPicLoc(Vector loc)
{
	ima->SetFixLoc(loc);
}

void Image::SetScale(Vector scale)
{
	delete ui;
	ui = new IMAGE;
	ima->SetImage(ui);
	ima->Load(this->path, scale.x, scale.y);
}

void Image::SetRotation(float rot)
{
	ima->SetRotation(rot);
}

void Image::AddRotation(float rot)
{
	ima->AddRotation(rot);
}

float Image::GetRotation()
{
	return ima->GetLocalRotation();
}

bool Image::IsCursorOn()
{
	return bVisibiliy && IsUnderCursor();
}







Button::Button()
{
	normal.image = new IMAGE;
	hover.image = new IMAGE;
	click.image = new IMAGE;
}

Button::~Button()
{
	delete normal.image;
	delete hover.image;
	delete click.image;
}

void Button::Update()
{
	Image::Update();
	if (IsCursorClicked())ima->SetSprite(click);
	else if (IsCursorOn())ima->SetSprite(hover);
	else ima->SetSprite(normal);

	if (IsCursorClicked())clickFlag = 1;
	else if (clickFlag == 1) clickFlag = 2 - MainController->GetCursorMessage().lbutton;
	else clickFlag = 0;
}

void Button::LoadPicture(string path, Vector si)
{
	Vector temp = (si == Vector(0, 0) ? GetSize() : si);
	ima->SetLayer(layer);
	loadimage(normal.image, LPCTSTR(path.c_str()), temp.x, temp.y);
}

void Button::LoadHoverPicture(string path, Vector si)
{
	Vector temp = (si == Vector(0, 0) ? GetSize() : si); 
	loadimage(hover.image, LPCTSTR(path.c_str()), temp.x, temp.y);
}

void Button::LoadClickPicture(string path, Vector si)
{
	Vector temp = (si == Vector(0, 0) ? GetSize() : si); 
	loadimage(click.image, LPCTSTR(path.c_str()), temp.x, temp.y);
}

bool Button::IsCursorClicked()
{
	return bVisibiliy && IsUnderCursor() && MainController->GetCursorMessage().lbutton;
}

bool Button::IsCursorUp()
{
	return bVisibiliy && clickFlag == 2;
}


