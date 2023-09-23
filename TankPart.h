#ifndef __TANK_PART_H__
#define __TANK_PART_H__

#include "Tools.h"


class TankPart {

protected:
	int _width;
	int _high;
	int _direction = UP;
	XYPos _pos;
	COLORREF _line_color;
	COLORREF _fill_color;

public:
	TankPart(int width = 0, int high = 0, int direction = UP, XYPos  pos = XYPos(0, 0)) {
		_width = width;
		_high = high;
		_direction = direction;
		_pos = pos;
	}

	int GetWidth() {
		return _width;
	}
	int GetHigh() {
		return _high;
	}

	void SetWidth(int width) {
		width = _width;
	}
	void SetHigh(int high) {
		_high = high;
	}


	int GetDirection() {
		return _direction;
	}
	void SetDirection(int direction) {
		_direction = direction;
	}

	COLORREF GetFillColor() {
		return _fill_color;
	}
	COLORREF GetLineColor() {
		return _line_color;
	}

	void SetFillColor(COLORREF fill_color) {
		_fill_color = fill_color;
	}
	void SetLineColor(COLORREF line_color) {
		_line_color = line_color;
	}


	XYPos GetPos() {
		return _pos;
	}
	void SetPos(XYPos pos) {
		_pos = pos;
	}


	void Rotation(XYPos center_pos, double angle) {
		double radians = AnglesToRadians(angle);
		auto p = _pos;
		_pos.x -= center_pos.x;
		_pos.y -= center_pos.y;

		p.x = _pos.x * cos(radians) - _pos.y * sin(radians);
		p.y = _pos.x * sin(radians) + _pos.y * cos(radians);

		_pos = p;
		_pos.x += center_pos.x;
		_pos.y += center_pos.y;
		return;
	}


	virtual void Draw() = 0;
	virtual void Clear() = 0;


};


class Barrel : public TankPart {

	XYPos _muzzle_pos;


public:
	Barrel() {  }
	Barrel(int width, int high) {
		_width = width;
		_high = high;
	}
	Barrel(int width, int high, XYPos pos) {
		_width = width;
		_high = high;
		_pos = pos;
	}
	XYPos GetMuzzlePos() {
		switch (_direction) {
		case UP:
			return XYPos(_pos.x, _pos.y - _width / 2);
			break;
		case RIGHT:
			return XYPos(_pos.x + _high / 2, _pos.y);
			break;
		case DOWN:
			return XYPos(_pos.x, _pos.y + _width / 2);
			break;
		case LEFT:
			return XYPos(_pos.x - _high / 2, _pos.y);
			break;
		default:
			break;
		}
	}
	void Draw() {
		setlinecolor(_line_color);
		setfillcolor(_fill_color);

		switch (GetDirection()) {
		case UP:
		case DOWN:

			fillrectangle(_pos.x - _width/2, _pos.y - _high/2, _pos.x + _width/2, _pos.y + _high/2);
			break;

		case LEFT:
		case RIGHT:
			fillrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}
	}

	void Clear() {
		switch (_direction) {
		case UP:
		case DOWN:
			clearrectangle(_pos.x - _width / 2, _pos.y - _high / 2, _pos.x + _width / 2, _pos.y + _high / 2);
			break;

		case LEFT:
		case RIGHT:
			clearrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}
	}


};

class Whell : public TankPart {

public:
	Whell() {  }
	Whell(int width, int high) {
		_width = width;
		_high = high;
	}
	Whell(int width, int high, XYPos pos) {
		_width = width;
		_high = high;
		_pos = pos;
	}
	void Draw() {

		setlinecolor(_line_color);
		setfillcolor(_fill_color);

		switch (_direction) {
		case UP:
		case DOWN:
			fillrectangle(_pos.x - _width / 2, _pos.y - _high / 2, _pos.x + _width / 2, _pos.y + _high / 2);
			break;

		case LEFT:
		case RIGHT:
			fillrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}

	}
	void Clear() {
		switch (_direction) {
		case UP:
		case DOWN:
			clearrectangle(_pos.x - _width / 2, _pos.y - _high / 2, _pos.x + _width / 2, _pos.y + _high / 2);
			break;

		case LEFT:
		case RIGHT:
			clearrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}
	}

};

class Body : public TankPart {


public:
	Body() {  }
	Body(int width, int high) {
		_width = width;
		_high = high;
	}
	Body(int width, int high, XYPos pos) {
		_width = width;
		_high = high;
		_pos = pos;
	}
	void Draw() {
		setlinecolor(_line_color);
		setfillcolor(_fill_color);


		switch (_direction) {
		case UP:
		case DOWN:
			fillrectangle(_pos.x - _width / 2, _pos.y - _high / 2, _pos.x + _width / 2, _pos.y + _high / 2);
			break;

		case LEFT:
		case RIGHT:
			fillrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}

	}
	void Clear() {
		switch (_direction) {
		case UP:
		case DOWN:
			clearrectangle(_pos.x - _width / 2, _pos.y - _high / 2, _pos.x + _width / 2, _pos.y + _high / 2);
			break;

		case LEFT:
		case RIGHT:
			clearrectangle(_pos.x - _high / 2, _pos.y - _width / 2, _pos.x + _high / 2, _pos.y + _width / 2);
			break;
		default:
			exit(1);
			break;
		}
	}
};

class Cover :public TankPart {
	int _radius;
	int _direction;


public:

	Cover() {  }
	Cover(int radius) {
		_radius = radius;
	}
	Cover(int radius, XYPos pos) {
		_pos = pos;
		_radius = radius;
	}

	int GetRadius() {
		return _radius;
	}
	void SetRadius(int radius) {
		_radius = radius;
	}


	void Draw() {

		setlinecolor(_line_color);
		setfillcolor(_fill_color);

		fillcircle(_pos.x, _pos.y, _radius);
	}
	void Clear() {
		clearcircle(_pos.x, _pos.y, _radius);
	}

};


class Bullet : public TankPart{

	int _die = 0;
	int _pace = 8;


public:
	Bullet(XYPos pos, int direction = UP) {

		_pos = pos;
		_direction = direction;
		_width = 5;
		_high = 10;
		SetFillColor(WHITE);

	}
	void Flight() {
		if (_direction == UP)
			_pos.y -= _pace;
		else if (_direction == DOWN)
			_pos.y += _pace;
		else if (_direction == LEFT)
			_pos.x -= _pace;
		else
			_pos.x += _pace;
	}
	void Draw() {
		
		setfillcolor(_fill_color);
		if (_direction == UP || _direction == DOWN) {
			fillellipse(
				_pos.x - _width / 2,
				_pos.y - _high / 2,
				_pos.x + _width / 2,
				_pos.y + _high / 2
			);
		}
		else {
			fillellipse(
				_pos.x - _high / 2,
				_pos.y - _width / 2,
				_pos.x + _high / 2,
				_pos.y + _width / 2
			);
		}

	}
	void Clear() {
		if (_direction == UP || _direction == DOWN) {
			clearellipse(
				_pos.x - _width / 2,
				_pos.y - _high / 2,
				_pos.x + _width / 2,
				_pos.y + _high / 2
			);
		}
		else {
			clearellipse(
				_pos.x - _high / 2,
				_pos.y - _width / 2,
				_pos.x + _high / 2,
				_pos.y + _width / 2
			);
		}
	}


	XYPos GetPos() {
		return _pos;
	}
	void SetPos(XYPos pos) {
		_pos = pos;
	}

	void Die() {
		_die = 1;
	}
	int GetDie() {
		return _die;
	}


};

#endif // !__TANK_PART_H__
