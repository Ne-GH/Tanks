#ifndef __TANKS_H__
#define __TANKS_H__

#include "Tools.h"
#include "TankPart.h"


class Tank {
	#define WHELL_NUM 2

	int _direction = UP;
	int _pace = 1;
	bool _die = false;
	XYPos _pos;


	Body _body;
	Cover _cover;
	Barrel _barrel;
	Whell _whell[WHELL_NUM];
	list<Bullet> _bullets;


	COLORREF _line_color = BLACK;
	COLORREF _fill_color = LIGHTCYAN;

	#undef WHELL_NUM
public:
	Tank() {
		Tank(XYPos(0,0),5);
	}
	Tank(XYPos pos, int speed = 10) {
		_pos = pos;
		_pace = speed;



		_body = Body(30, 30);
		_body.SetPos(pos);
		_cover = Cover(_body.GetWidth() * 0.4);
		_cover.SetPos(pos);
		_barrel = Barrel(10, 20);
		_barrel.SetPos(XYPos(pos.x, pos.y - _cover.GetRadius() - _barrel.GetHigh() / 2));
		_whell[LEFTWHELL] = Whell(10, 40);
		_whell[LEFTWHELL].SetPos(
			XYPos(
				pos.x + _body.GetWidth() / 2 + _whell[LEFTWHELL].GetWidth() / 2,
				pos.y
			));
		_whell[RIGHTWHELL] = Whell(10, 40);
		_whell[RIGHTWHELL].SetPos(
			XYPos(
				pos.x - _body.GetWidth() / 2 - _whell[LEFTWHELL].GetWidth() / 2,
				pos.y
			));


		_body.SetFillColor(YELLOW);
		_cover.SetFillColor(CYAN);
		_barrel.SetFillColor(GREEN);
		_whell[LEFTWHELL].SetFillColor(RED);
		_whell[RIGHTWHELL].SetFillColor(RED);
		
		_body.SetLineColor(BLACK);
		_cover.SetLineColor(BLACK);
		_barrel.SetLineColor(BLACK);
		_whell[RIGHTWHELL].SetLineColor(BLACK);
		_whell[LEFTWHELL].SetLineColor(BLACK);

	}

	void SetTankPartPos() {

		_body.SetPos(_pos);
		_cover.SetPos(_pos);

		_barrel.SetPos(XYPos(_pos.x, _pos.y - _cover.GetRadius() - _barrel.GetHigh() / 2));
		_whell[LEFTWHELL].SetPos(
			XYPos(
				_pos.x + _body.GetWidth() / 2 + _whell[LEFTWHELL].GetWidth() / 2,
				_pos.y
			));
		_whell[RIGHTWHELL].SetPos(
			XYPos(
				_pos.x - _body.GetWidth() / 2 - _whell[LEFTWHELL].GetWidth() / 2,
				_pos.y
			));

		Rotation((_direction+4-UP)%4 * 90);
		
	}


	XYPos GetXYPos() {
		return _pos;
	}
	void SetXYPos(XYPos pos) {
		_pos = pos;


		_body.SetPos(pos);
		_cover.SetPos(pos);

		_barrel.SetPos(XYPos(pos.x, pos.y - _cover.GetRadius() - _barrel.GetHigh() / 2));
		_whell[LEFTWHELL].SetPos(
			XYPos(
				pos.x + _body.GetWidth() / 2 + _whell[LEFTWHELL].GetWidth() / 2,
				pos.y
			));
		_whell[RIGHTWHELL].SetPos(
			XYPos(
				pos.x - _body.GetWidth() / 2 - _whell[LEFTWHELL].GetWidth() / 2,
				pos.y
			));
	}
	int GetSpeed() {
		return _pace;
	}
	void SetSpeed(int speed) {
		_pace = speed;
	}
	COLORREF GetLineColor() {
		return _line_color;
	}
	COLORREF GetFillColor() {
		return _fill_color;
	}
	void SetFillColor(COLORREF fill_color) {
		_fill_color = fill_color;
	}
	void SetLineColor(COLORREF line_color) {
		_line_color = line_color;
	}
	int GetDirection() {
		return _direction;
	}

	void SetDirection(int direction) {

		_body.SetDirection(direction);
		_cover.SetDirection(direction);
		_barrel.SetDirection(direction);
		_whell[LEFTWHELL].SetDirection(direction);
		_whell[RIGHTWHELL].SetDirection(direction);

		int alpha = (direction + 4 - _direction) % 4 * 90;
		Rotation(alpha);

		_direction = direction;
		
	}
	void Die() {
		SetDie();
	}
	void SetDie() {
		_die = true;
	}
	bool GetDie() {
		return _die;
	}

	void Rotation(int alpha) {

		_body.Rotation(_pos, alpha);
		_cover.Rotation(_pos, alpha);
		_barrel.Rotation(_pos, alpha);
		_whell[LEFTWHELL].Rotation(_pos, alpha);
		_whell[RIGHTWHELL].Rotation(_pos, alpha);
		return;
	}

	void Clear() {


		_body.Clear();
		_cover.Clear();
		_whell[LEFTWHELL].Clear();
		_whell[RIGHTWHELL].Clear();
		_barrel.Clear();


	}

	void Draw() {

		if (_die == 1)
			return;

		_body.Draw();
		_cover.Draw();
		_whell[LEFTWHELL].Draw();
		_whell[RIGHTWHELL].Draw();
		_barrel.Draw();


	}


	void Move() {
		switch (_direction) {
		case UP:
			_pos.y -= _pace;
			break;
		case LEFT:
			_pos.x -= _pace;
			break;
		case DOWN:
			_pos.y += _pace;
			break;
		case RIGHT:
			_pos.x += _pace;
			break;
		}
		if (_pos.y <= 0) {
			_pos.y = 0;
		}
		if (_pos.x <= 0) {
			_pos.x = 0;
		}
		if (_pos.x >= getwidth()) {
			_pos.x = getwidth();
		}
		if (_pos.y >= getheight()) {
			_pos.y = getheight();
		}

		SetTankPartPos();

	}

	void Shot() {
		XYPos muzzle_pos = _barrel.GetMuzzlePos();
		Bullet bt(muzzle_pos, _direction);
		_bullets.push_back(bt);
	}
	void DrawBullets() {
		
		for (auto &b : _bullets) {
			XYPos pos = b.GetPos();

			if (pos.x <= 0 || pos.y <= 0 || pos.x >= getwidth() || pos.y >= getheight()) {
				b.Die();
				b.Clear();
				// return;
			}

			else {
				b.Clear();
				b.Flight();
				b.Draw();
				
			}
		}

		for (auto p = _bullets.begin(); p != _bullets.end(); ) {
			if (p->GetDie() == 1) {
				p->Clear();
				p = _bullets.erase(p);
			}
			else
				p++;
		}


	}


	list<Bullet>& GetBullets() {
		return _bullets;
	}

};




#endif // !__TANKS_H__