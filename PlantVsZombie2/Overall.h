/* variable����Ϸȫ�ֱ����� */


#pragma once

#include<set>
#include<vector>
#include<map>
#include<stack>

#define WIN_WIDTH 800
#define WIN_HIGHT 600

#define DELTA_TIME 0.01f

#define ROW_WIDTH 80
#define COLUMN_HIGHT 100

/* ������Ҫָ��ĳһֵ����ַ�����в��Ҳ�ɾ�����������Բ��ҿ����ϴ�
��ʹ������set�洢��������ɾʱ�临�Ӷȶ�ΪO��logN�� */

//��Ϸ����ʵ��
extern std::set<class Object*>GameObjects;

//��Ϸ���ʵ��
extern std::set<class Component*>GameComponents;


/* ����ֻ��Ҫ�������Դ洢������ɾ������ʹ��vector�洢��
����ʱ�临�Ӷ�ΪO��1������ʱ�临�Ӷ�ΪO��N�� */

//��Ϸ����ɾ������
extern std::vector<class Object*>GameObjects_;

//��Ϸ���ɾ������
extern std::vector<class Component*>GameComponents_;


/* ������Ҫ�ϸ������Ա��ڰ��ղ㼶��Ⱦ���Ҳ㼶��ȫ�����ظ���
���ԱȽ�ʱ���������ֵַ��Ϊ�㼶��ͬʱ�ıȽϣ���ʹ��set�洢��
���β���ɾ��ʱʱ�临�Ӷ�ΪO��logN������Ⱦʱ��ʱ�临�Ӷ�Ϊ0��N��*/

//��Ϸ��Ⱦ���
extern bool cmp(class SpriteRenderer*a,class SpriteRenderer*b);
extern std::set<class SpriteRenderer*,decltype(&cmp)>GameRenders;

//��Ϸ���ֻ�ͼ���
extern std::set<class Widget*>GamePainters;


//��Ϸ��ײ���(ÿ�������Ҫ������ײ�жϣ���ʱ�临�Ӷ�ΪO��N^2��)
extern std::set<class BoxCollider*>GameColliders;


//��ϷUI���
extern std::set<class UserInterface*>GameUIs;

//��ϷUIɾ������
extern std::vector<class UserInterface*>GameUIs_;


//��ҿ���������������������������ȫ��ֻ��һ����
extern class Controller* MainController;

//��Ϸ����������һ�㲻�ܶ������ڣ���Ϸ������Ƚ����⣬��Ϊ����������һ��Ϊȫ�֣���ֻ��һ����
extern class Camera* MainCamera;

//�����л�
extern bool changeLevel;

//��Ϸ��ʱ��lastTime��ַ
extern std::set<DWORD*>GameLastTimes;
//��Ϸ��ͣʱ���¼
extern DWORD pauseTime;
//��Ϸ��ͣ����ͼƬ
extern class IMAGE pauseImage;
//��Ϸ��ͣ
extern bool pause;



//������ģʽ
extern bool logPattern;

//��ײ����ʾ
extern bool collisionPattern;

//��Դ�أ�ȫ�ֽ���һ����
extern class Resources ResourcePool;