#include "Tools.h"
#include "tanks.h"
#include "TankPart.h"


int check_distance = 40;

default_random_engine e(time(NULL));
uniform_int_distribution<int> rengine(50, 550);

void ClearEnemy(list<Tank> &enemys) {
	for (auto& enemy : enemys) {
		enemy.Clear();
	}
}

void MoveEnemy(list<Tank>& enemys) {
	for (auto& enemy : enemys) {
		enemy.Move();
	}
}
void TurnEnemy(list<Tank>& enemys,int direction) {
	for (auto& enemy : enemys) {
		enemy.SetDirection(direction);
	}
}
void DrawEnemy(list<Tank> &enemys) {

	for (auto& enemy : enemys) {
		enemy.Draw();
	}
}

void EnemyShot(list<Tank> &enemys) {
	for (auto& enemy : enemys) {
		// enemy.Shot();
		// enemy.DrawBullets();
	}

}

void RemoveDieEnemys(list<Tank>& enemys) {
	for (auto p = enemys.begin(); p != enemys.end(); ) {
		if (p->GetDie() == true) {
			p->Clear();
			p = enemys.erase(p);
			
		}
		else {
			p++;
		}
		
	}
}



bool CheckCollision(XYPos p1,XYPos p2) {
	int distance = pow(abs(p1.x - p2.x), 2) + pow(abs(p1.y - p2.y), 2);
	distance = sqrt(distance);

	if (distance <= check_distance) 
		return true;
	return false;
}

void CreateEnemys(list<Tank>& enemys,int enemys_amount) {
	for (int i = 0; i < enemys_amount; ++i) {
		Tank enemys_tank(XYPos(rengine(e), rengine(e)), 1);
		e.seed(e());
		enemys_tank.SetDirection(e() % 4);
		enemys.push_back(enemys_tank);
	}
}

int main() {

	initgraph(800, 600);

	ExMessage m;		// 定义消息变量
	Tank tk(XYPos(300,500));
	tk.Draw();
	list<Tank>enemys;
	int enemys_amount = 5;
	
	CreateEnemys(enemys, enemys_amount);
	
	BeginBatchDraw();
		
	while (true) {
		MoveEnemy(enemys);
		DrawEnemy(enemys);
		
		if (enemys.size() <= 1) {
			CreateEnemys(enemys,4);
		}

		for (auto &b : tk.GetBullets()) {
			for (auto &en : enemys) {
				if (CheckCollision(en.GetXYPos(), b.GetPos()) == true) {
					b.Die();
					en.Die();
				}

			}
		}
		RemoveDieEnemys(enemys);

		EnemyShot(enemys);

		tk.DrawBullets();

		int tank_direction = UP;
		tk.Draw();
		peekmessage(&m, EX_MOUSE | EX_KEY);
		FlushBatchDraw();
		Sleep(5);
		ClearEnemy(enemys);
		tk.Clear();
		
		switch (m.message) {


		case WM_LBUTTONDOWN:
 			tk.Shot();

			break;


		case WM_KEYDOWN:

			switch (m.vkcode) {

			case VK_w:
			case VK_W:
				tank_direction = UP;
				tk.SetDirection(tank_direction);
				tk.Move();
				//tk.Draw();
				//FlushBatchDraw();
				//tk.Clear();
				
				break;


			case VK_d:
			case VK_D:
				tank_direction = RIGHT;
				tk.SetDirection(tank_direction);
				tk.Move();
				//tk.Draw();
				//FlushBatchDraw();
		
				//tk.Clear();
				
				break;
			case VK_s:
			case VK_S:
				tank_direction = DOWN;
				tk.SetDirection(tank_direction);
				tk.Move();
				//tk.Draw();
				//FlushBatchDraw();
		
				//tk.Clear();
			
				break;
			case VK_a:
			case VK_A:
				tank_direction = LEFT;
				tk.SetDirection(tank_direction);
				tk.Move();
				//tk.Draw();
				//FlushBatchDraw();
			
				//tk.Clear();
		
				break;
			case VK_SPACE:
				//tk.Draw();
				//FlushBatchDraw();
				//tk.Clear();
				tk.Move();
				break;
				break;
			case VK_ESCAPE:
				return 0;
				break;
			default:
				break;
			}

		default:
			break;

		}


	}
	EndBatchDraw();
	closegraph();
	return 0;
}

//#include <iostream>
//using namespace std;
//
////矩阵位置坐标
//typedef struct Rect {
//	Rect(int x, int y, int width, int height)
//		: x(x), y(y), width(width), height(height)
//	{}
//	int x;		//矩阵左上角x坐标
//	int y;		//矩阵右上角y坐标
//	int width;	//矩形宽度
//	int height;	//矩形高度
//} Rect;
///**
// * @brief 判断两个轴对齐的矩阵是否重叠
// * @param rc1 第一个矩阵的位置
// * @param rc2 第二个矩阵的位置
// * @return 两个矩阵是否重叠（边沿重叠，也认为是重叠）
// */
//bool isOverlap(const Rect& rc1, const Rect& rc2) {
//	if (rc1.x + rc1.width > rc2.x &&
//		rc2.x + rc2.width > rc1.x &&
//		rc1.y + rc1.height > rc2.y &&
//		rc2.y + rc2.height > rc1.y)
//		return true;
//	else
//		return false;
//}
//
//int main() {
//	Rect rc1(0, 0, 10, 10), rc2(11, 11, 2, 2);
//	if (isOverlap(rc1, rc2))
//		cout << "Rectangles Overlap";
//	else
//		cout << "Rectangles Don't Overlap";
//	return 0;
//}