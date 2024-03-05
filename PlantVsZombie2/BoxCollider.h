#pragma once
#include"CoreMinimal.h"



//碰撞器（高性能要求，慎用）
class BoxCollider :public Component
{

	Vector size = Vector(0,0);
	string type = "Default";
	COLORREF color = RED;

	set<BoxCollider*>boxes;
	vector<Object*>aims;
	bool bOpen = true;

	bool CollisionJudge(BoxCollider* another)
	{
		Vector pos = GetWorldPosition();
		Vector pos_a = another->GetWorldPosition();
		return (pos.x<pos_a.x + another->GetSize().x && pos.x + size.x>pos_a.x
			&& pos.y<pos_a.y + another->GetSize().y && pos.y + size.y>pos_a.y);
	}

	void PrintInfo()
	{
		if (!boxes.empty()) {
			cout << "Collisions Of The " << GetType() << " in " << GetWorldPosition() << ":  ";
			int num = 0;
			for (auto it = boxes.begin(); it != boxes.end(); ++it)
			{
				cout << (*it)->GetType() << " "; num++;
			}
			cout << "  --------  " << num << endl;
		}
	}


public:
	BoxCollider(Vector s = Vector(0, 0)) :size(s) { GameColliders.insert(this); }
	virtual ~BoxCollider() { GameColliders.erase(this); }
	virtual void Update(){;}
	
	const vector<Object*>& GetCollisions(string t)
	{
		aims.clear();
		if (!boxes.empty()) {
			for (auto it = boxes.begin(); it != boxes.end(); ++it)
			{
				if ((*it)->GetType() == t)aims.push_back((*it)->owner);
			}
		}
		return aims;
	}

	bool IsUnderCursor();
	
	void DrawDebugLine(int thickness = 1)
	{
		if (size.x > 0 && size.y > 0) {
			float l = GetWorldPosition().x, t = GetWorldPosition().y;
			float r = l + size.x, b = t + size.y;
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, thickness);
			setlinecolor(color);
			rectangle((int)l, (int)t, (int)r, (int)b);
		}
	}

	const string& GetType() { return type; }
	void SetType(string t) { type = t; }
	const Vector& GetSize() { return size; }
	void SetSize(Vector s) { size.x = s.x, size.y = s.y; }
	void SetColor(COLORREF col) { color = col; }
	void SetOpen(bool open) { bOpen = open; }
	bool GetOpen() { return bOpen; }

	void Clear() { boxes.clear(); }
	void Insert(BoxCollider* another) { if (bOpen && another->GetOpen() && boxes.find(another) == boxes.end() 
		&& CollisionJudge(another))boxes.insert(another); }


};














//// 定义一个四叉树节点
//class QuadTreeNode {
//public:
//	Vector center;
//	Vector size;
//	vector<BoxCollider*> colliders;
//	QuadTreeNode* children[4];
//
//	QuadTreeNode(Vector c, Vector s) : center(c), size(s) {
//		for (int i = 0; i < 4; ++i) {
//			children[i] = nullptr;
//		}
//	}
//};

//// 碰撞体类优化
//class BoxCollider : public Component {
//private:
//	Vector size;
//	string type;
//	COLORREF color;
//	vector<BoxCollider*> boxes;
//	QuadTreeNode* quadTreeRoot;
//
//	// 碰撞体积判断
//	bool BoundingBoxCheck(BoxCollider* another) {
//		// 碰撞体积判断逻辑
//	}
//
//	// 在四叉树中插入碰撞体
//	void InsertIntoQuadTree(BoxCollider* collider) {
//		// 将碰撞体插入四叉树中的逻辑
//	}
//
//public:
//	BoxCollider(Vector s = Vector(0, 0)) : size(s) {
//		GameColliders.insert(this);
//		quadTreeRoot = new QuadTreeNode(Vector(0, 0), Vector(1000, 1000)); // 初始化四叉树根节点
//	}
//
//	virtual ~BoxCollider() {
//		GameColliders.erase(this);
//		// 释放四叉树节点的内存
//	}
//
//	void Refresh() {
//		// 清空四叉树
//		// 重新构建四叉树
//		for (auto it = GameColliders.begin(); it != GameColliders.end(); ++it) {
//			if ((*it) != this && BoundingBoxCheck(*it)) {
//				InsertIntoQuadTree(*it);
//			}
//		}
//	}
//
//	// 其他方法保持不变
//};



struct Point {
	float x, y;
};

struct Rect {
	float x, y, w, h;

	bool contains(Point point) {
		return (point.x >= x - w / 2 && point.x < x + w / 2 && point.y >= y - h / 2 && point.y < y + h / 2);
	}

	bool intersects(Rect range) {
		return !(range.x - range.w / 2 > x + w / 2 || range.x + range.w / 2 < x - w / 2
			|| range.y - range.h / 2 > y + h / 2 || range.y + range.h / 2 < y - h / 2);
	}
};

class QuadTree {
private:
	Rect boundary;
	int capacity;
	vector<Point> points;
	bool divided;
	QuadTree* northeast;
	QuadTree* northwest;
	QuadTree* southeast;
	QuadTree* southwest;

public:
	QuadTree(Rect boundary, int capacity) : boundary(boundary), capacity(capacity), divided(false) {}

	bool insert(Point point) {
		if (!boundary.contains(point)) 
			return false;

		if (points.size() < capacity) {
			points.push_back(point);
			return true;
		}
		else {
			if (!divided) subdivide();

			if (northeast->insert(point) || northwest->insert(point) || southeast->insert(point) || southwest->insert(point)) 
				return true;
			
		}

		return false;
	}

	bool checkCollision(Rect rect) {
		if (!boundary.intersects(rect))return false;
		

		for (Point p : points)
			if (rect.contains(p)) return true;

		if (divided) {
			if (northeast->checkCollision(rect) || northwest->checkCollision(rect) 
				|| southeast->checkCollision(rect) || southwest->checkCollision(rect)) 			
				return true;
		}

		return false;
	}

	void subdivide() {
		float x = boundary.x;
		float y = boundary.y;
		float w = boundary.w / 2;
		float h = boundary.h / 2;

		Rect ne = { x + w / 2, y - h / 2, w, h };
		northeast = new QuadTree(ne, capacity);

		Rect nw = { x - w / 2, y - h / 2, w, h };
		northwest = new QuadTree(nw, capacity);

		Rect se = { x + w / 2, y + h / 2, w, h };
		southeast = new QuadTree(se, capacity);

		Rect sw = { x - w / 2, y + h / 2, w, h };
		southwest = new QuadTree(sw, capacity);

		divided = true;
	}
};